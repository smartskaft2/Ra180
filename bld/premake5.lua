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
    location ".."
    kind "ConsoleApp"
    language "C++"
    
    targetdir ( "%{wrk.location}/bin/"     .. outputdir )
    objdir    ( "%{wrk.location}/bin-int/" .. outputdir )
    
    files
    {
        "%{prj.location}/src/**.h",
        "%{prj.location}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.location}/vendors/spdlog/include"
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
       os.rmdir("%{wrk.location}/bin/*")
       os.rmdir("%{wrk.location}/bin-int/*")
       os.remove("%{wrk.location}/%{prj.name}.sln")
       print("Done.")
    end
 }