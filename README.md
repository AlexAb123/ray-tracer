### Building

**Windows (Visual Studio 2022)**

1. Download the **[Vulkan SDK](https://vulkan.lunarg.com)**.
2. Clone **[vcpkg](https://github.com/microsoft/vcpkg)** and run the **bootsrap-vcpkg** script.
3. Create a file called **CMakeUserPresets.json** at the root of the project and paste in the following JSON block, adjusting **VCPKG_ROOT** depending on where vcpkg is located on your PC.
```json
{
  "version": 3,
  "configurePresets": [
    {
      "name": "x64-release",
      "displayName": "x64 Release",
      "inherits": "x64-release-base",
      "environment": {
        "VCPKG_ROOT": "C:\\vcpkg"
      }
    }
  ]
}
```
Alternatively you can include vcpkg in your Visual Studio installation and skip steps 2 and 3.