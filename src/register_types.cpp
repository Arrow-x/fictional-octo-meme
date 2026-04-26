#include "register_types.h"
// #include "example_node.h"
// #include "example_ref.h"
#include "example_resource.h"
#include "summator.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

auto initialize_gdextension_types(ModuleInitializationLevel p_level) { //NOLINT
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	GDREGISTER_RUNTIME_CLASS(gutils::ExampleResource)
	GDREGISTER_RUNTIME_CLASS(gutils::Summator)
	// GDREGISTER_RUNTIME_CLASS(gutils::BaseEntity)
	// GDREGISTER_RUNTIME_CLASS(gutils::Damage)
	// GDREGISTER_RUNTIME_CLASS(gutils::StatusEffect)
}

auto uninitialize_gdextension_types(ModuleInitializationLevel p_level) { //NOLINT
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
// Initialization
auto GDE_EXPORT example_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) -> GDExtensionBool {
	GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
	init_obj.register_initializer(initialize_gdextension_types);
	init_obj.register_terminator(uninitialize_gdextension_types);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
