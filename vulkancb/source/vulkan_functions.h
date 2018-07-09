#ifndef VULKAN_FUNCTIONS_H
#define VULKAN_FUNCTIONS_H

#define VK_NO_PROTOTYPE // disable the decls for statically-linked vulkan lib.
#include "../external/vulkan.h"

namespace vulkan {

#define EXPORTED_VULKAN_FUNCTION( name ) extern PFN_##name name;

#define GLOBAL_LEVEL_VULKAN_FUNCTION( name ) extern PFN_##name name;

#define INSTANCE_LEVEL_VULKAN_FUNCTION( function ) extern PFN_##name name;

#define INSTANCE_LEVEL_VULKAN_FUNCTION_FROM_EXTENSION( function ) extern PFN_##name name;

#define DEVICE_LEVEL_VULKAN_FUNCTION( function ) extern PFN_##name name;)

#define DEVICE_LEVEL_VULKAN_FUNCTION_FROM_EXTENSION( function ) extern PFN_##name name;

#include "list_of_vulkan_functions.inl"
  
}

#endif // VULKAN_FUNCTIONS_H
