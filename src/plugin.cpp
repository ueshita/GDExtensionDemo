#include <godot_cpp/godot.hpp>
#include <godot_cpp/core/class_db.hpp>
#include "sprite.h"
#include "sprite_server.h"

using namespace godot;

void initialize_myplugin_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	ClassDB::register_class<SpriteCpp>();
	ClassDB::register_class<SpriteServerCpp>();
}

void uninitialize_myplugin_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" 
GDExtensionBool GDE_EXPORT myplugin_library_init(
	GDExtensionInterfaceGetProcAddress p_get_proc_address,
	GDExtensionClassLibraryPtr p_library,
	GDExtensionInitialization *r_initialization)
{
	GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_myplugin_module);
	init_obj.register_terminator(uninitialize_myplugin_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
