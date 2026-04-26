#pragma once

#define REG(CLASS, TYPE, NAME)                                                    \
	ClassDB::bind_method(D_METHOD("get_" #NAME), &CLASS::get_##NAME);             \
	ClassDB::bind_method(D_METHOD("set_" #NAME, "p_" #NAME), &CLASS::set_##NAME); \
	ADD_PROPERTY(PropertyInfo(TYPE, #NAME), "set_" #NAME, "get_" #NAME);

#define REG_HINT(CLASS, TYPE, NAME, HINT, HINT_STRING)                            \
	ClassDB::bind_method(D_METHOD("get_" #NAME), &CLASS::get_##NAME);             \
	ClassDB::bind_method(D_METHOD("set_" #NAME, "p_" #NAME), &CLASS::set_##NAME); \
	ADD_PROPERTY(PropertyInfo(TYPE, #NAME, HINT, HINT_STRING), "set_" #NAME, "get_" #NAME);

#define REG_NODE(CLASS, NAME, HINT_STRING)                                        \
	ClassDB::bind_method(D_METHOD("get_" #NAME), &CLASS::get_##NAME);             \
	ClassDB::bind_method(D_METHOD("set_" #NAME, "p_" #NAME), &CLASS::set_##NAME); \
	ADD_PROPERTY(PropertyInfo(godot::Variant::OBJECT, #NAME, godot::PROPERTY_HINT_NODE_TYPE, HINT_STRING), "set_" #NAME, "get_" #NAME);

#define REG_RESOURCE(CLASS, NAME, HINT_STRING)                                    \
	ClassDB::bind_method(D_METHOD("get_" #NAME), &CLASS::get_##NAME);             \
	ClassDB::bind_method(D_METHOD("set_" #NAME, "p_" #NAME), &CLASS::set_##NAME); \
	ADD_PROPERTY(PropertyInfo(godot::Variant::OBJECT, #NAME, godot::PROPERTY_HINT_RESOURCE_TYPE, HINT_STRING), "set_" #NAME, "get_" #NAME);

#define EXPORT_VAR(TYPE, NAME)                           \
private:                                                 \
	TYPE NAME;                                           \
                                                         \
public:                                                  \
	void set_##NAME(const TYPE &value) { NAME = value; } \
	auto get_##NAME() const -> TYPE { return NAME; }

#define EXPORT_NODE(TYPE, NAME)                    \
private:                                           \
	TYPE *NAME;                                    \
                                                   \
public:                                            \
	void set_##NAME(TYPE *value) { NAME = value; } \
	[[nodiscard]] auto get_##NAME() const -> TYPE * { return NAME; }

#define REG_SIGNAL(NAME) \
	godot::ClassDB::add_signal(get_class_static(), godot::MethodInfo(NAME))
