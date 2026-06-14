#pragma once
#include "macros.h"
#include <godot_cpp/classes/resource.hpp>

namespace gutils {

class ExampleResource : public godot::Resource { //NOLINT
	GDCLASS(ExampleResource, godot::Resource) //NOLINT
public:
	EXPORT(int, test_int)
	EXPORT(godot::String, test_string)
public:
	ExampleResource();

protected:
	static void _bind_methods();
};
} //namespace gutils
