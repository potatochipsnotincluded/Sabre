# Sabre Engine
Sabre Engine is a game engine in C++ with C# scripting. It supports Mac and Windows.
The `Scripts/` directory contains build scripts for Windows and Linux, and the `Vendor/` directory contains Premake binaries (currently version `5.0-beta2`).

## Getting Started
Open the `Scripts/` directory and run the appropriate `Setup` script to generate projects files. Windows uses Visual Studio 2022 and higher (for my development I use Visual Studio 2026), and Mac uses xcode.

## WARNINGS!
During early development random crashes on startup and programme exit occured. The latter, an error on programme exit, is mostly harmless and usually goes away. The former, the programme crashing on run, is not frequently seen. If it occurs, though, clean and rebuild, and if the error persists then create an issue.

## License
- Premake is licensed under BSD 3-Clause (see included LICENSE.txt file for more details).
- GLFW is licensed under zlib.
- JSON is licensed under MIT.
- stb image is licensed under MIT.
- Glad is licensed under the BSD-3 Clause "New" or "Revised" License.