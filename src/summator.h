#pragma once

#include "example_ref.h"
#include "example_resource.h"
#include "macros.h"

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/variant/vector2.hpp>

namespace gutils {

class Summator : public godot::Node { //NOLINT
	GDCLASS(Summator, godot::Node) //NOLINT

	EXPORT_VAR(int, max_speed);
	EXPORT_VAR(int, count);
	EXPORT_VAR(int, mode)
	EXPORT_VAR(float, my_angle);
	EXPORT_VAR(float, speeds)
	EXPORT_VAR(godot::String, char_name);
	EXPORT_VAR(godot::Ref<gutils::ExampleResource>, test_resource)
	EXPORT_VAR(godot::NodePath, example_node_path)
	EXPORT_NODE(godot::MeshInstance3D, mesh_instance);

private:
	godot::Ref<ExampleRef> n;
	godot::Vector2 current_mouse_pos;

public:
	Summator();
	auto _notification(int what) -> void;
	auto _unhandled_input(const godot::Ref<godot::InputEvent> &p_event) -> void override;

	[[nodiscard]] auto get_total() const -> int;
	auto add(int p_value) -> void;

protected:
	static void _bind_methods();
};
} //namespace gutils
