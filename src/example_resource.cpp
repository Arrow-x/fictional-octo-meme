#include "example_resource.h"

using namespace godot;
using namespace gutils;

ExampleResource::ExampleResource() : test_int(0), test_string("") {
}

void ExampleResource::_bind_methods() {
	REG(ExampleResource, Variant::INT, test_int)
	REG(ExampleResource, Variant::STRING, test_string)
}
