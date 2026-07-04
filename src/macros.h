#pragma once

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
