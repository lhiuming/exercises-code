#include "common.h"
#include <iostream>

namespace vulkan {

  bool connect_with_vulkan_loader_library(VK_LOADER_LIB_TYPE& library) {
#if defined _WIN32
    library = LoadLibrary("vulkan-1.dll");
#elif defined __linux
    library = dlopen("libvulkan.so.1", RTLD_NOW);
#endif
    if (library == nullptr) {
      std::cout << "Fail to connect with a Vulkan runtime library" << std::endl;
      return false;
    }
    return true;
  }

  bool load_function_exported_from_vk_loader_lib(VK_LOADER_LIB_TYPE const& library) {
    // TODO 
    
  }


}
