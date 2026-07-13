#pragma once

#ifndef USING_PCH
#include "gutils.h"
#include <godot_cpp/classes/resource.hpp>
#endif // !USING_PCH

namespace scripts {

class ExampleResource : public godot::Resource {
	GDCLASS(ExampleResource, godot::Resource)
public:
	EXPORT(int, test_int)
	EXPORT(int, id)
	EXPORT(godot::String, test_string)
public:
	ExampleResource();

protected:
	static void _bind_methods();
};
} //namespace scripts
