#include "summator.h"
#include "defer.h"
#include "gutils.h"
#include "macros.h"

#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/physics_direct_space_state3d.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters3d.hpp>
#include <godot_cpp/classes/physics_server3d_extension_ray_result.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/world3d.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <iostream>

using namespace godot;
using namespace gutils;

Summer::Summer() {}

auto Summer::_notification(int what) -> void {
	switch (what) {
		case NOTIFICATION_READY: {
			set_process(true);
			set_physics_process(true);

			break;
		}
		case NOTIFICATION_POSTINITIALIZE: {
			auto label = memnew(Label);
			label->set_text("kill me now");
			label->set_position(Vector2(10, 10));
			add_child(label);

			auto button = memnew(Button);
			button->set_text("who is your daddy?");
			button->set_position(Vector2(80, 10));
			add_child(button);
			button->connect("pressed", callable_mp(this, &Summer::add).bind(3));

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

auto Summer::_unhandled_input(const Ref<InputEvent> &p_event) -> void {
	// Ref<InputEventMouse> mouse_event = p_event;
	// if (mouse_event.is_valid()) {
	// 	print_line("god forbid a white boy get a little motion ", get_class());
	// 	get_viewport()->set_input_as_handled();
	// }
	// Ref<InputEventMouseButton> mouse_event_button = p_event;
	// if (mouse_event_button.is_valid()) {
	// 	// if (mouse_event_button->is_pressed() && mouse_event_button->get_button_index() == MOUSE_BUTTON_LEFT) {
	// 	// 	if (EngineDebugger::get_singleton()->is_active()) {
	// 	// 		EngineDebugger::get_singleton()->debug();
	// 	// 	}
	// 	// 	print_line("Left mouse button clicked at: ", mouse_event_button->get_position());
	// 	// 	add(9);
	// 	// }
	// 	if (mouse_event_button->get_button_index() == MOUSE_BUTTON_LEFT && mouse_event_button->is_double_click()) {
	// 		print_line("double click me", mouse_event_button->get_position());
	// 		// }
	// 	}
	// }
}

auto Summer::add(int p_value) -> void {
	std::cout << "who's your daddy?\n";
	count += p_value;
}

auto Summer::test() -> void {
	// 2. Define your ray boundaries (in global coordinates)
	Vector3 ray_from = get_global_position();
	auto ray_to = ray_from + Vector3(0, -10, 0); // Ray casting 10 units down
	auto query = PhysicsRayQueryParameters3D::create(ray_from, ray_to);
	Dictionary o = get_viewport()->get_world_3d()->get_direct_space_state()->intersect_ray(query);

	auto s = new LocalVector<int>;
	DEFER({ delete s; });

	s->push_back(1);
	s->push_back(3);
	for (const auto n : *s) {
		print_line(n);
	}

	auto _m = new HashMap<String, u_int32_t>;
	DEFER({ delete _m; });

	auto &m = *_m;

	m["something"] = 3;
	print_line(m["something"]);

	auto some = memnew(ExampleResource);
	print_line(sizeof(*some));
}

auto Summer::get_total() const -> int {
	print_line("hi daddy");
	return count;
}

auto Summer::_bind_methods() -> void {
	REG(Summer, Variant::INT, max_speed);
	REG(Summer, Variant::INT, count);
	REG(Summer, Variant::FLOAT, my_angle);
	REG(Summer, Variant::STRING, char_name);

	REG(Summer, Variant::FLOAT, speeds, PROPERTY_HINT_RANGE, "0, 100, 0.5, or_greater");
	REG(Summer, Variant::INT, mode, PROPERTY_HINT_ENUM, "Idle, Walk, Run, Jump");
	REG(Summer, Variant::NODE_PATH, example_node_path, PROPERTY_HINT_NODE_PATH_VALID_TYPES, "AnimatedSprite2D");
	REG(Summer, Variant::VECTOR2, current_mouse_pos, PROPERTY_HINT_NONE, "", PROPERTY_USAGE_STORAGE);

	REG_NODE(Summer, mesh_instance, "MeshInstance3D");
	REG_RESOURCE(Summer, test_resource, "ExampleResource");

	REG_METHOD(Summer, add, value);
	REG_METHOD(Summer, get_total);
}
