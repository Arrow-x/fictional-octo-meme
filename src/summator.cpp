#include "summator.h"

using namespace godot;
using namespace scripts;

Summer::Summer() {}

namespace {
auto hi() -> void {
	print_line("hi from hi");
}
} //namespace
auto Summer::_notification(int what) -> void {
	switch (what) {
		case NOTIFICATION_READY: {
			set_process(true);
			set_physics_process(true);

			auto hbox = memnew(HBoxContainer);
			hbox->set_position(Vector2(10, 10));
			add_child(hbox);

			auto label = memnew(Label);
			label->set_text("kill me now and don't talk to me ever again: ");
			hbox->add_child(label);

			auto button2 = memnew(Button);
			button2->set_text("test me daddy");
			hbox->add_child(button2);
			button2->connect("pressed", callable_mp(this, &Summer::test));
			auto c = callable_mp_static(&hi);

			popup_menu = memnew(MenuButton);
			popup_menu->set_text("who do you like?");
			popup_menu->set_flat(false);
			popup_menu->get_popup()->add_item("your mom");
			popup_menu->get_popup()->add_item("your sis");
			popup_menu->get_popup()->add_item("your cousin");
			hbox->add_child(popup_menu);
			popup_menu->get_popup()->connect("index_pressed", callable_mp(this, &Summer::show_menu));
			c.call();

			break;
		}

		case NOTIFICATION_PHYSICS_PROCESS: {
			break;
		}
			// double dt = get_process_delta_time();
		case NOTIFICATION_PROCESS: {
			// print_line("process dt: ", dt);
			break;
		}
		default:
			break;
	}
}

auto Summer::show_menu(int id) -> void {
	print_line("you clicked on: ", popup_menu->get_popup()->get_item_text(id));
}

auto Summer::_input(const Ref<InputEvent> &p_event) -> void {
	// Ref<InputEventMouse> mouse_event = p_event;
	// if (mouse_event.is_valid()) {
	// 	print_line("god forbid a white boy get a little motion ", get_class());
	// 	get_viewport()->set_input_as_handled();
	// }
	// Ref<InputEventMouseButton> mouse_event_button = p_event;
	// if (mouse_event_button.is_valid()) {
	// if (mouse_event_button->is_pressed() && mouse_event_button->get_button_index() == MOUSE_BUTTON_LEFT) {
	// 	if (EngineDebugger::get_singleton()->is_active()) {
	// 		EngineDebugger::get_singleton()->debug();
	// 	}
	// 	print_line("Left mouse button clicked at: ", mouse_event_button->get_position());
	// 	add(9);
	// }
	// if (mouse_event_button->get_button_index() == MOUSE_BUTTON_LEFT && mouse_event_button->is_double_click()) {
	// 	print_line("double click me", mouse_event_button->get_position());
	// 	// }
	// }
	// }
	if (p_event->is_action_pressed("interact")) {
		print_line("E");
	}
}

auto Summer::add(int p_value) -> void {
	count += p_value;
}

auto Summer::test() -> void {
	// 2. Define your ray boundaries (in global coordinates)
	Vector3 ray_from = get_global_position();
	auto ray_to = ray_from + Vector3(0, -10, 0); // Ray casting 10 units down
	auto query = PhysicsRayQueryParameters3D::create(ray_from, ray_to);
	Dictionary o = gutils::ray_cast(query);
	print_line("the ray cast resault: ", o);
}

auto Summer::get_total() const -> int {
	print_line("hi daddy");
	return count;
}

auto Summer::soome_func() -> void {
	print_line("hi");
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
	// REG_RESOURCE(Summer, test_resource, "ExampleResource");

	REG_METHOD(Summer, add, value);
	REG_METHOD(Summer, get_total);
}
