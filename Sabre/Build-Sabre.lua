project "Sabre"
   kind "StaticLib"
   language "C++"
   cppdialect "C++23"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp", "../Vendor/Glad/src/*.c" }
	defines
	{
		'SOLUTION_DIR="' .. _WORKING_DIR .. '"'
	}
   includedirs
   {
      "Source",
	  "../Vendor/GLFW/include",
	  "../Vendor/Glad/include"
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")
   
   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }
		libdirs {"../Vendor/GLFW/Windows" }
		links {"glfw3"}
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