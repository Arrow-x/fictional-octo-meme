#pragma once

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>

namespace gutils {

inline auto get_scene_root() -> godot::Node * {
	auto *scene_tree = godot::Object::cast_to<godot::SceneTree>(
			godot::Engine::get_singleton()->get_main_loop());

	if (scene_tree == nullptr) {
		return nullptr;
	}
	return scene_tree->get_current_scene();
}
} //namespace gutils
