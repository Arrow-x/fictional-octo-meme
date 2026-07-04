#pragma once
#include <godot_cpp/classes/ref_counted.hpp>

namespace gutils {

class ExampleResource : public godot::RefCounted { //NOLINT
	GDCLASS(ExampleResource, godot::RefCounted) //NOLINT
public:
	// EXPORT(int, test_int)
	// EXPORT(u_int32_t, id)
	// EXPORT(godot::String, test_string)
public:
	ExampleResource();
	auto _notification(int what) -> void;

protected:
	static void _bind_methods();
};
} //namespace gutils
