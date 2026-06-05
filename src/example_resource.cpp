#include "example_resource.h"

using namespace godot;
using namespace gutils;

ExampleResource::ExampleResource() {
}

void ExampleResource::_bind_methods() {
	REG(ExampleResource, Variant::INT, test_int)
	REG(ExampleResource, Variant::STRING, test_string)
}
