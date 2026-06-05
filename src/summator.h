#pragma once

#include "example_resource.h"
#include "macros.h"

#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>

namespace gutils {

class Summator : public godot::Node3D {
	GDCLASS(Summator, godot::Node3D)

public:
	Summator();

	EXPORT_VAR(int, max_speed, 0);
	EXPORT_VAR(int, count, 0);
	EXPORT_VAR(int, mode)
	EXPORT_VAR(float, my_angle);
	EXPORT_VAR(float, speeds)
	EXPORT_VAR(godot::String, char_name);
	EXPORT_VAR(godot::Ref<gutils::ExampleResource>, test_resource)
	EXPORT_VAR(godot::NodePath, example_node_path)
	EXPORT_NODE(godot::MeshInstance3D, mesh_instance);

	EXPORT_VAR(godot::Vector2, current_mouse_pos);

	auto _notification(int what) -> void;
	auto _unhandled_input(const godot::Ref<godot::InputEvent> &p_event) -> void override;

	/**
	 * @brief get the currrent count
	 *
	 * this function returns the count
	 *
	 * @return the count
	 */
	[[nodiscard]] auto get_total() const -> int;
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

protected:
	static void _bind_methods();
};
} //namespace gutils
