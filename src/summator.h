#pragma once
#ifndef USING_PCH
#include "gutils.h"
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/canvas_item.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_action.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters3d.hpp>
#endif // !USING_PCH

namespace scripts {

class Summer : public godot::Node3D {
	GDCLASS(Summer, godot::Node3D)

public:
	Summer();

	EXPORT(int, max_speed, 0);
	EXPORT(int, count, 10);
	EXPORT(int, mode)
	EXPORT(float, my_angle, 0.0f);
	EXPORT(float, speeds)
	EXPORT(godot::String, char_name);
	// EXPORT(godot::Ref<scripts::ExampleResource>, test_resource)
	EXPORT(godot::NodePath, example_node_path)
	EXPORT(godot::Vector2, current_mouse_pos);
	EXPORT(godot::MeshInstance3D *, mesh_instance, nullptr);

	auto _notification(int what) -> void;
	auto _input(const godot::Ref<godot::InputEvent> &p_event) -> void override;

	/**
	 * @brief get the currrent count
	 *
	 * this function returns the count
	 *
	 * @return the count
	 */
	[[nodiscard]]
	auto get_total() const -> int;
	/**
	 * @brief Adds two numbers together.
	 *
	 * This function takes two integer inputs and returns their sum.
	 * It is a basic example of Doxygen documentation.
	 *
	 * @param p_value The first integer.
	 * @return void
	 */
	auto add(int p_value) -> void;
	auto test() -> void;

protected:
	static auto _bind_methods() -> void;
};
} //namespace scripts
