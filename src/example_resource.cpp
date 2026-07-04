#include "example_resource.h"

using namespace godot;
using namespace gutils;

ExampleResource::ExampleResource() {
}
auto ExampleResource::_notification(int what) -> void {
	switch (what) {
		case NOTIFICATION_PREDELETE: {
			print_line("deleted?");

			break;
		}
	}
}

void ExampleResource::_bind_methods() {
	// REG(ExampleResource, Variant::INT, test_int)
	// REG(ExampleResource, Variant::STRING, test_string)
	// REG(ExampleResource, Variant::INT, id)
}
