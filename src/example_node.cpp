#include "example_node.h"
// #include "example_ref.h"
// #include "example_resource.h"

using namespace godot;
using namespace gutils;

void ExampleNode::_ready() {
	// 	print_line("hi this is SpecialNode _ready");
	// 	String s = "something";
	// 	Ref<ExampleResource> m = memnew(ExampleResource);
	// 	Ref<ExampleRef> f = memnew(ExampleRef);
	// 	print_line("size of a Resource is**: ", sizeof(**m));
	// 	print_line("size of a RefCounted is**: ", sizeof(**f));
}

void ExampleNode::_bind_methods() {
	// REG_RESOURCE(ExampleNode, my_example_rec, "ExampleResource")
}
