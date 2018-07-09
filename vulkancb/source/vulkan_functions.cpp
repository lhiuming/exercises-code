#include "vulkan_functions.h"

namespace vulkan {

#define EXPORTED_VULKAN_FUNCTION( name ) PFN_##name name;

#define GLOBAL_LEVEL_VULKAN_FUNCTION( name ) PFN_##name name;

#define INSTANCE_LEVEL_VULKAN_FUNCTION( function ) PFN_##name name;

#define INSTANCE_LEVEL_VULKAN_FUNCTION_FROM_EXTENSION( function ) PFN_##name name;

#define DEVICE_LEVEL_VULKAN_FUNCTION( function ) PFN_##name name;)

#define DEVICE_LEVEL_VULKAN_FUNCTION_FROM_EXTENSION( function ) PFN_##name name;

#include "list_of_vulkan_functions.inl"

}