-- WORKSPACE: Radio 180
workspace "Radio 180"

    architecture "x64"
    
    configurations 
    { 
        "Debug", 
        "Release", 
        "Distro" 
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- PROJECT: Ra180
project "Ra180"
    location "Ra180"
    kind "SharedLib"
    language "C++"
    
    targetdir ( "bin/" .. outputdir .. "/%{prj.name}" )
    objdir ( "bin-int/" .. outputdir .. "/%{prj.name}" )
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/vendor/spdlog/include"
    }
    
    filter "system:windows"
        cppdialect "C++20"
        staticruntime "On"
        systemversion "latest"
        
        defines 
        { 
            "RA180_PLATFORM_WINDOWS", 
            "RA180_BUILD_DLL" 
        }

        postbuildcommands 
        { 
            ( "{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox" ) 
        }

    filter "configurations:Debug"
        defines "RA180_DEBUG"
        symbols "On"
        
    filter "configurations:Release"
        defines "RA180_RELEASE"
        optimize "On"
        
    filter "configurations:Distro"
        defines "RA180_DISTRO"
        optimize "On"
        
-- PROJECT: Sandbox
project "Sandbox"
    location "Sandbox"
    kind "ConsoleApp"
    language "C++"
    
    targetdir ( "bin/" .. outputdir .. "/%{prj.name}" )
    objdir ( "bin-int/" .. outputdir .. "/%{prj.name}" )
    
    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "Ra180/src",
        "Ra180/vendor/spdlog/include"
    }
    
    links
    {
        "Ra180"
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