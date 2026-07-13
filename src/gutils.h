#pragma once

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/physics_direct_space_state3d.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters3d.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/world3d.hpp>

namespace gutils {

inline auto get_scene_root() -> godot::Node * {
	auto *scene_tree = godot::Object::cast_to<godot::SceneTree>(
			godot::Engine::get_singleton()->get_main_loop());

	if (scene_tree == nullptr) {
		return nullptr;
	}
	return scene_tree->get_current_scene();
}

inline auto ray_cast(const godot::Ref<godot::PhysicsRayQueryParameters3D> &query) -> godot::Dictionary {
	auto *r = get_scene_root();
	godot::Dictionary d;
	if (r != nullptr) {
		d = r->get_viewport()->get_world_3d()->get_direct_space_state()->intersect_ray(query);
	}
	return d;
}

#define REG(CLASS, TYPE, NAME, ...)                                                             \
	godot::ClassDB::bind_method(godot::D_METHOD("get_" #NAME), &CLASS::get_##NAME);             \
	godot::ClassDB::bind_method(godot::D_METHOD("set_" #NAME, "p_" #NAME), &CLASS::set_##NAME); \
	ADD_PROPERTY(godot::PropertyInfo(TYPE, #NAME __VA_OPT__(, ) __VA_ARGS__), "set_" #NAME, "get_" #NAME);

#define REG_NODE(CLASS, NAME, HINT_STRING) \
	REG(CLASS, godot::Variant::OBJECT, NAME, godot::PROPERTY_HINT_NODE_TYPE, HINT_STRING);

#define REG_RESOURCE(CLASS, NAME, HINT_STRING) \
	REG(CLASS, godot::Variant::OBJECT, NAME, godot::PROPERTY_HINT_RESOURCE_TYPE, HINT_STRING);

#define REG_SIGNAL(CLASS, NAME) \
	godot::ClassDB::add_signal(CLASS::get_class_static(), godot::MethodInfo(NAME))

#define REG_METHOD(CLASS, NAME, ...) \
	godot::ClassDB::bind_method(godot::D_METHOD(#NAME __VA_OPT__(, ) #__VA_ARGS__), &CLASS::NAME)

#define EXPORT(TYPE, NAME, ...)                           \
	TYPE NAME __VA_OPT__(=) __VA_ARGS__;                  \
                                                          \
	auto set_##NAME(TYPE value) -> void { NAME = value; } \
	auto get_##NAME() -> TYPE { return NAME; }

} //namespace gutils
