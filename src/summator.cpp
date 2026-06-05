#include "summator.h"
#include "gutils.h"
#include "macros.h"

#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/physics_direct_space_state3d.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters3d.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/world3d.hpp>
#include <godot_cpp/variant/variant.hpp>

using namespace godot;
using namespace gutils;

Summator::Summator() {}

auto Summator::_notification(int what) -> void {
	switch (what) {
		case NOTIFICATION_READY: {
			set_process(true);
			set_physics_process(true);
			print_line(gutils::get_scene_root());
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

auto Summator::_unhandled_input(const Ref<InputEvent> &p_event) -> void {
	Ref<InputEventMouse> mouse_event = p_event;
	if (mouse_event.is_valid()) {
		print_line("god forbid a white boy get a little motion ", get_class());
		get_viewport()->set_input_as_handled();
	}
	Ref<InputEventMouseButton> mouse_event_button = p_event;
	if (mouse_event_button.is_valid()) {
		if (mouse_event_button->is_pressed() && mouse_event_button->get_button_index() == MOUSE_BUTTON_LEFT) {
			// if (EngineDebugger::get_singleton()->is_active()) {
			// 	EngineDebugger::get_singleton()->debug();
			// }
			print_line("Left mouse button clicked at: ", mouse_event_button->get_position());
		}
		if (mouse_event_button->get_button_index() == MOUSE_BUTTON_LEFT && mouse_event_button->is_double_click()) {
			print_line("double click me daddy ", mouse_event_button->get_position());
		}
	}
}

auto Summator::add(int p_value) -> void {
	count += p_value;
	// 2. Define your ray boundaries (in global coordinates)
	Vector3 ray_from = get_global_position();
	auto ray_to = ray_from + Vector3(0, -10, 0); // Ray casting 10 units down
	auto query = PhysicsRayQueryParameters3D::create(ray_from, ray_to);
	auto o = get_viewport()->get_world_3d()->get_direct_space_state()->intersect_ray(query);
}

auto Summator::get_total() const -> int {
	return count;
}

auto Summator::_bind_methods() -> void {
	REG(Summator, Variant::INT, max_speed);
	REG(Summator, Variant::INT, count);
	REG(Summator, Variant::FLOAT, my_angle);
	REG(Summator, Variant::STRING, char_name);

	REG_HINT(Summator, Variant::FLOAT, speeds, PROPERTY_HINT_RANGE, "0, 100, 0.5, or_greater");
	REG_HINT(Summator, Variant::INT, mode, PROPERTY_HINT_ENUM, "Idle, Walk, Run, Jump");
	REG_HINT(Summator, Variant::NODE_PATH, example_node_path, godot::PROPERTY_HINT_NODE_PATH_VALID_TYPES, "AnimatedSprite2D");
	REG_HINT(Summator, Variant::VECTOR2, current_mouse_pos, PROPERTY_HINT_NONE, "", PROPERTY_USAGE_STORAGE);

	REG_NODE(Summator, mesh_instance, "MeshInstance3D");
	REG_RESOURCE(Summator, test_resource, "ExampleResource");

	ClassDB::bind_method(D_METHOD("add", "value"), &Summator::add);
	ClassDB::bind_method(D_METHOD("get_total"), &Summator::get_total);
}
