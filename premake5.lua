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

local gameEnginePath = "vendor/Clementine"

project "Ra180"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    staticruntime "on"
    
    targetdir ( "bin/" .. outputdir .. "/%{prj.name}" )
    objdir ( "bin-int/" .. outputdir .. "/%{prj.name}" )
    
    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "%{gameEnginePath}/Clementine/src",
        "%{gameEnginePath}/Clementine/vendor/spdlog/include",
        "%{gameEnginePath}/Clementine/vendor"
    }
    
    links
    {
        "Clementine"
    }
    
    filter "system:windows"
        systemversion "latest"
        defines "CLMT_PLATFORM_WINDOWS"

    filter "configurations:Debug"
        defines "CLMT_DEBUG"
        runtime "Debug"
        symbols "on"
        
    filter "configurations:Release"
        defines "CLMT_RELEASE"
        runtime "Release"
        optimize "on"
        
    filter "configurations:Distro"
        defines "CLMT_DISTRO"
        runtime "Release"
        optimize "on"

-- Clean Function --
newaction {
    trigger     = "clean",
    description = "Clean the project build files",
    execute     = function ()
       print("Clean the build... ")
       os.rmdir("%{wks.location}/bin/*")
       os.rmdir("%{wks.location}/bin-int/*")
       os.remove("%{wks.location}/%{prj.name}.sln")
       print("Done.")
    end
 }