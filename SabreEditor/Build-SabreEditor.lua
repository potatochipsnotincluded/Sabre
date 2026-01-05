project "SabreEditor"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++23"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp" }
	defines
	{
		'SOLUTION_DIR="' .. _WORKING_DIR .. '"'
	}
   includedirs
   {
      "Source",

	  -- Include Core
	  "../Sabre/Source",
	  "../Vendor/GLFW/include",
	  "../Vendor/Glad/include",
	  "../Vendor/Assimp/include"
	}

   links
   {
      "Sabre"
   } 

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")
	
   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

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