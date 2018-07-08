#ifndef COMMON_H
#define COMMON_H

#if defined _WIN32
#include "windows.h";
#endif

namespace vulkan {

#if defined _WIN32
  typedef HMODULE VK_LOADER_LIB_TYPE;
#elif define __linux
  typedef void* VK_LOADER_LIB_TYPE;
#endif

  bool connect_with_vulkan_loader_library(VK_LOADER_LIB_TYPE & library);

  bool load_function_exported_from_vk_loader_lib(VK_LOADER_LIB_TYPE const & library);

}

#endif // COMMON_H
