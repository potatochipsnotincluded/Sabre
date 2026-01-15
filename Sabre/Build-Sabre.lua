project "Sabre"
   kind "StaticLib"
   language "C++"
   cppdialect "C++23"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp", "../Vendor/Glad/src/*.c" }
local root = os.getenv("SABRE_INSTALL_LOC")
root = root:gsub("\\", "\\\\")

defines
{
    'SOLUTION_DIR="' .. root .. '"'
}
   includedirs
   {
      "Source",
	  "../Vendor/GLFW/include",
	  "../Vendor/Glad/include",
	  "../Vendor/Assimp/include"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")
   
   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }
		libdirs {"../Vendor/GLFW/Windows", "../Vendor/Assimp/Windows" }
		links {"glfw3", "assimp-vc143-mt"}
		
	filter "system:macosx"
       defines { "MACOSX" }
		libdirs { "../Vendor/GLFW/MacUniversal" }
		links {
			"glfw",          -- your GLFW library
			"Cocoa.framework",
			"IOKit.framework",
			"CoreVideo.framework",
			"OpenGL.framework"
		}
   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"