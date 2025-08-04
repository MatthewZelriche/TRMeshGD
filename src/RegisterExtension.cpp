// Copied from godot-cpp/test/src and modified.

#include "gdextension_interface.h"

#include "godot_cpp/core/print_string.hpp"
#include "godot_cpp/core/defs.hpp"
#include "godot_cpp/godot.hpp"

#include "TRMesh/test.hpp"

namespace {
void initializeExtension(godot::ModuleInitializationLevel p_level) {
   if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) { return; }

   godot::print_line("Loading TRMeshGD (Build Time: ", __DATE__, " ", __TIME__, ")");
   godot::print_line("TEST: ", test());
}

void uninitializeExtension(godot::ModuleInitializationLevel p_level) {
   if (p_level != godot::MODULE_INITIALIZATION_LEVEL_SCENE) { return; }
}
} // namespace

extern "C" {
// Plugin entry point
GDExtensionBool GDE_EXPORT GDExtensionInit(
    GDExtensionInterfaceGetProcAddress p_get_proc_address,
    GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
   {
      const godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library,
                                                           r_initialization);

      init_obj.register_initializer(initializeExtension);
      init_obj.register_terminator(uninitializeExtension);
      init_obj.set_minimum_library_initialization_level(
          godot::MODULE_INITIALIZATION_LEVEL_SCENE);

      return init_obj.init();
   }
}
}
