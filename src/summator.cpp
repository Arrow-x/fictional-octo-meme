#include "summator.h"
#include "gutils.h"
#include "macros.h"

#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/physics_direct_space_state3d.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters3d.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/world3d.hpp>
#include <godot_cpp/variant/variant.hpp>

using namespace godot;
using namespace gutils;

#define self Summator
#define print print_line
#define func auto self::

self::self() {}

func _notification(int what) -> void {
	switch (what) {
		case NOTIFICATION_READY: {
			set_process(true);
			set_physics_process(true);
			print(gutils::get_scene_root());
			break;
		}
		case NOTIFICATION_PHYSICS_PROCESS: {
			break;
		}
		case NOTIFICATION_PROCESS: {
			// double dt = get_process_delta_time();
			// print_line("process dt: ", dt);
			break;
		}

		default:
			break;
	}
}

func _unhandled_input(const Ref<InputEvent> &p_event) -> void {
	Ref<InputEventMouse> mouse_event = p_event;
	if (mouse_event.is_valid()) {
		print("god forbid a white boy get a little motion ", get_class());
		get_viewport()->set_input_as_handled();
	}
	Ref<InputEventMouseButton> mouse_event_button = p_event;
	if (mouse_event_button.is_valid()) {
		if (mouse_event_button->is_pressed() && mouse_event_button->get_button_index() == MOUSE_BUTTON_LEFT) {
			// if (EngineDebugger::get_singleton()->is_active()) {
			// 	EngineDebugger::get_singleton()->debug();
			// }
			print("Left mouse button clicked at: ", mouse_event_button->get_position());
		}
		if (mouse_event_button->get_button_index() == MOUSE_BUTTON_LEFT && mouse_event_button->is_double_click()) {
			print("double click me daddy ", mouse_event_button->get_position());
		}
	}
}

func add(int p_value) -> void {
	count += p_value;
	// 2. Define your ray boundaries (in global coordinates)
	Vector3 ray_from = get_global_position();
	auto ray_to = ray_from + Vector3(0, -10, 0); // Ray casting 10 units down
	auto query = PhysicsRayQueryParameters3D::create(ray_from, ray_to);
	auto o = get_viewport()->get_world_3d()->get_direct_space_state()->intersect_ray(query);
}

func get_total() const -> int {
	return count;
}

func _bind_methods() -> void {
	REG(self, Variant::INT, max_speed);
	REG(self, Variant::INT, count);
	REG(self, Variant::FLOAT, my_angle);
	REG(self, Variant::STRING, char_name);

	REG(self, Variant::FLOAT, speeds, PROPERTY_HINT_RANGE, "0, 100, 0.5, or_greater");
	REG(self, Variant::INT, mode, PROPERTY_HINT_ENUM, "Idle, Walk, Run, Jump");
	REG(self, Variant::NODE_PATH, example_node_path, PROPERTY_HINT_NODE_PATH_VALID_TYPES, "AnimatedSprite2D");
	REG(self, Variant::VECTOR2, current_mouse_pos, PROPERTY_HINT_NONE, "", PROPERTY_USAGE_STORAGE);

	REG_NODE(self, mesh_instance, "MeshInstance3D");
	REG_RESOURCE(self, test_resource, "ExampleResource");

	REG_METHOD(self, add, value);
	REG_METHOD(self, get_total);
}
