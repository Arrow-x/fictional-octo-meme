Since you are running pure C++ games and bypass GDScript constraints entirely, you can exploit Godot’s optimized internal container ecosystem. These structures exist under the godot:: namespace via <godot_cpp/core/templates/...> and use Godot's internal tracking memory allocators (memalloc, memrealloc). [1, 2, 3]
------------------------------
## 1. godot::LocalVector<T>
While Vector<T> uses Copy-on-Write (COW) which features an atomic reference-counting abstraction, LocalVector<T> does not use COW. It acts exactly like a std::vector, storing its contiguous pointer capacity directly on the stack. [4, 5, 6]

* When to use: Performance-critical loops (e.g., pathfinding node processing, physics iterations, real-time vertex buffers).
* API highlight: Features push_back(), resize(), clear(), and automatic scaling. [4, 6]

```cpp
#include <godot_cpp/core/templates/local_vector.hpp>
godot::LocalVector<MyCustomStruct> local_particles;
local_particles.push_back(MyCustomStruct(1, 2, 3));

```

## 2. godot::HashMap<K, V>
Godot's high-performance internal associative hash map. Unlike standard std::unordered_map which uses separate chaining (buckets pointing to linked lists), Godot's HashMap uses open addressing with quadratic probing. This keeps data tightly localized in memory, reducing CPU cache misses significantly. [7]

* When to use: High-speed entity entity registries or ID-to-Pointer lookups.
* Header: <godot_cpp/core/templates/hash_map.hpp>

```cpp
#include <godot_cpp/core/templates/hash_map.hpp>
godot::HashMap<uint64_t, MyEntity*> registry;
registry.insert(14203, new MyEntity());
if (registry.has(14203)) {
    MyEntity* ent = registry[14203];
}

```

## 3. godot::List<T>
A doubly-linked list representation. It allocates separate nodes for each element and maintains forward/backward references.

* When to use: When you need frequent insertions and deletions at random locations or at the front/back boundaries in O(1) time, and don't care about continuous memory caching.
* Header: <godot_cpp/core/templates/list.hpp>

```cpp
#include <godot_cpp/core/templates/list.hpp>
godot::List<godot::String> command_queue;
command_queue.push_back("move_forward");
command_queue.push_front("override_stop"); // O(1) front insertion
// Iteration uses specialized Element pointersfor (godot::List<godot::String>::Element *E = command_queue.front(); E; E = E->next()) {
    godot::String command = E->get();
}
```

## 4. godot::VMap<K, V>
The "Vector Map". This is an associative map implementation constructed entirely on top of a sorted Vector array. Lookups are done using a binary search ($O(\log N)$ complexity).

* When to use: Read-heavy configuration structures with very small item sizes (e.g., under 100 items). Since it's a flat array under the hood, memory fragmentation is zero, outperforming HashMap for minimal lookups.
* Header: <godot_cpp/core/templates/vmap.hpp>

```cpp
#include <godot_cpp/core/templates/vmap.hpp>
godot::VMap<godot::StringName, float> weapon_multipliers;
weapon_multipliers.insert("sword", 1.5f);

```

## 5. godot::RBMap<K, V> and godot::RBSet<T>
Godot's internal Red-Black Tree balanced search configurations. They guarantee $O(\log N)$ complexity rules for searches, insertions, and deletions. [8]

* When to use: When your data arrays need to strictly maintain sorted ordering at all times natively.
* Header: <godot_cpp/core/templates/rb_map.hpp> / <godot_cpp/core/templates/rb_set.hpp>

```cpp
#include <godot_cpp/core/templates/rb_map.hpp>
godot::RBMap<int, godot::String> render_layers_by_priority;
render_layers_by_priority.insert(10, "Background");
render_layers_by_priority.insert(0, "Foreground"); // Sorted automatically
```

------------------------------
## Low-Level Array Optimization Trick: ptrw()
If you still find yourself using core godot::Vector<T> templates due to code shared with Godot subsystems, always remember to avoid mutating elements directly through the indexing brackets [] inside high-speed loops.
Because Vector<T> is copy-on-write, using mutable indexers invokes a tracking branch check every single loop pass. Instead, extract a direct raw pointer to the underlying block memory using .ptrw(): [4, 5]

```cpp
godot::Vector<godot::Vector3> heavy_positions;
heavy_positions.resize(50000);
// Get the raw data Write Pointergodot::Vector3* raw_write_ptr = heavy_positions.ptrw();
for (int i = 0; i < 50000; ++i) {
    raw_write_ptr[i].x += 10.0f; // Blazing fast raw C pointer manipulation
}
```
