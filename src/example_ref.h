#pragma once

#include "macros.h"
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/signal.hpp>
#include <godot_cpp/variant/string_name.hpp>
namespace gutils {

namespace signals {
constexpr inline auto example_signal{ "example_signal" };
}

class ExampleRef : public godot::RefCounted {
	GDCLASS(ExampleRef, godot::RefCounted)

	EXPORT_VAR(int, something)

public:
	ExampleRef();

protected:
	static void _bind_methods();
};

} //namespace gutils
