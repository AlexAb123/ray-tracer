## Building

**Windows (Visual Studio 2022)**

1. Download the **[Vulkan SDK](https://vulkan.lunarg.com)**.
2. Clone **[vcpkg](https://github.com/microsoft/vcpkg)** and run the **bootsrap-vcpkg** script.
3. Create a file called `CMakeUserPresets.json` at the root of the project and paste in the following JSON block, adjusting `VCPKG_ROOT` depending on where vcpkg is located on your computer. 
```json
{
  "version": 3,
  "configurePresets": [
    {
      "name": "x64-release",
      "displayName": "x64 Release",
      "inherits": "x64-release-base",
      "environment": {
        "VCPKG_ROOT": "C:/path/to/vcpkg"
      }
    }
  ]
}
```
Alternatively, if you included **vcpkg** with your Visual Studio installation, you can skip step 2 and don't need to set `VCPKG_ROOT` manually, meaning you can remove the `environment` section from the above JSON snippet.