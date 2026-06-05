#pragma once

#define REG(CLASS, TYPE, NAME)                                                    \
	ClassDB::bind_method(D_METHOD("get_" #NAME), &CLASS::get_##NAME);             \
	ClassDB::bind_method(D_METHOD("set_" #NAME, "p_" #NAME), &CLASS::set_##NAME); \
	ADD_PROPERTY(PropertyInfo(TYPE, #NAME), "set_" #NAME, "get_" #NAME);

#define REG_HINT(CLASS, TYPE, NAME, HINT, ...)                                    \
	ClassDB::bind_method(D_METHOD("get_" #NAME), &CLASS::get_##NAME);             \
	ClassDB::bind_method(D_METHOD("set_" #NAME, "p_" #NAME), &CLASS::set_##NAME); \
	ADD_PROPERTY(PropertyInfo(TYPE, #NAME, HINT __VA_OPT__(, ) __VA_ARGS__), "set_" #NAME, "get_" #NAME);

#define REG_NODE(CLASS, NAME, HINT_STRING)                                        \
	ClassDB::bind_method(D_METHOD("get_" #NAME), &CLASS::get_##NAME);             \
	ClassDB::bind_method(D_METHOD("set_" #NAME, "p_" #NAME), &CLASS::set_##NAME); \
	ADD_PROPERTY(PropertyInfo(godot::Variant::OBJECT, #NAME, godot::PROPERTY_HINT_NODE_TYPE, HINT_STRING), "set_" #NAME, "get_" #NAME);

#define REG_RESOURCE(CLASS, NAME, HINT_STRING)                                    \
	ClassDB::bind_method(D_METHOD("get_" #NAME), &CLASS::get_##NAME);             \
	ClassDB::bind_method(D_METHOD("set_" #NAME, "p_" #NAME), &CLASS::set_##NAME); \
	ADD_PROPERTY(PropertyInfo(godot::Variant::OBJECT, #NAME, godot::PROPERTY_HINT_RESOURCE_TYPE, HINT_STRING), "set_" #NAME, "get_" #NAME);

#define REG_SIGNAL(CLASS, NAME) \
	godot::ClassDB::add_signal(CLASS::get_class_static(), godot::MethodInfo(NAME))

#define EXPORT_VAR(TYPE, NAME, ...)                              \
	TYPE NAME __VA_OPT__(=) __VA_ARGS__;                         \
                                                                 \
	auto set_##NAME(const TYPE &value) -> void { NAME = value; } \
	auto get_##NAME() const -> TYPE { return NAME; }

#define EXPORT_NODE(TYPE, NAME)                            \
	TYPE *NAME = nullptr;                                  \
                                                           \
	auto set_##NAME(TYPE *value) -> void { NAME = value; } \
	auto get_##NAME() const -> TYPE * { return NAME; }
