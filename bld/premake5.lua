-- WORKSPACE: Radio180 --
workspace "Radio180"

    architecture "x64"
    
    configurations 
    { 
        "Debug", 
        "Release", 
        "Distro" 
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- PROJECT: Ra180 --
project "Ra180"
    kind "ConsoleApp"
    language "C++"
    
    targetdir ( "./bin/"     .. outputdir )
    objdir    ( "./bin-int/" .. outputdir )
    
    files
    {
        "../src/*.h",
        "../src/*.cpp",
        "../src/**.h"
        "../src/**.cpp",
    }

    includedirs
    {
        "../src",
        "../src/**",
        "../vendors/spdlog/include"
    }
    
    filter "system:windows"
        cppdialect "C++20"
        staticruntime "on"
        systemversion "latest"
        defines "RA180_PLATFORM_WINDOWS"

    filter "configurations:Debug"
        defines "RA180_DEBUG"
        symbols "On"
        
    filter "configurations:Release"
        defines "RA180_RELEASE"
        optimize "On"
        
    filter "configurations:Distro"
        defines "RA180_DISTRO"
        optimize "On"

-- Clean Function --
newaction {
    trigger     = "clean",
    description = "Clean the project build files",
    execute     = function ()
       print("Clean the build... ")
       os.rmdir("./bin")
       os.rmdir("./bin-int")
       os.remove("../*.sln")
       os.remove("../*.vcx*")
       print("Done.")
    end
 }