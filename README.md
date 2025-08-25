## Building

### Windows (Visual Studio 2022)

1. Download the **[Vulkan SDK](https://vulkan.lunarg.com)**.

If you included **vcpkg** with your Visual Studio installation, you can skip steps 2 and 3.

2. Clone **[vcpkg](https://github.com/microsoft/vcpkg)** and run the **bootsrap-vcpkg** script.
3. Set the path to the **vcpkg** root directory as `VCPKG_ROOT` in your system's environment variables.

4. Build from either inside Visual Studio or by running the following command in `x64 Native Tools Command Prompt for VS 2022`

```
cmake --preset release && cmake --build --preset release
```