# Run

## Test

```bash
make
./Triangle
```

### Temporarily remove the call to DestroyDebugUtilsMessengerEXT

Error:

```bash
validation layer: Validation Error: [ VUID-vkDestroyInstance-instance-00629 ] Object 0: handle = 0x562632d70590, type = VK_OBJECT_TYPE_INSTANCE; Object 1: handle = 0xfd5b260000000001, type = VK_OBJECT_TYPE_DEBUG_UTILS_MESSENGER_EXT; | MessageID = 0x8b3d8e18 | vkDestroyInstance():  OBJ ERROR : For VkInstance 0x562632d70590[], VkDebugUtilsMessengerEXT 0xfd5b260000000001[] has not been destroyed. The Vulkan spec states: All child objects created using instance must have been destroyed prior to destroying instance (https://vulkan.lunarg.com/doc/view/1.3.268.0/linux/1.3-extensions/vkspec.html#VUID-vkDestroyInstance-instance-00629)
validation layer: Validation Error: [ VUID-vkDestroyInstance-instance-00629 ] Object 0: handle = 0x562632d70590, type = VK_OBJECT_TYPE_INSTANCE; Object 1: handle = 0xfd5b260000000001, type = VK_OBJECT_TYPE_DEBUG_UTILS_MESSENGER_EXT; | MessageID = 0x8b3d8e18 | vkDestroyInstance():  OBJ ERROR : For VkInstance 0x562632d70590[], VkDebugUtilsMessengerEXT 0xfd5b260000000001[] has not been destroyed. The Vulkan spec states: All child objects created using instance must have been destroyed prior to destroying instance (https://vulkan.lunarg.com/doc/view/1.3.268.0/linux/1.3-extensions/vkspec.html#VUID-vkDestroyInstance-instance-00629)
validation layer: Unloading layer library libVkLayer_MESA_device_select.so
validation layer: Unloading layer library libVkLayer_khronos_validation.so
```

