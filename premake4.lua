--
-- Premake4 build script (http://industriousone.com/premake/download)
--

solution 'myuv'
    configurations {'Debug', 'Release'}            
    targetdir 'bin'
    platforms {"x64"}
    flags {'ExtraWarnings'}
    
    configuration 'Debug'
        defines { 'DEBUG' }
        flags { 'Symbols' }
        
    configuration 'Release'
        defines { 'NDEBUG' }
        flags { 'Symbols', 'Optimize' }           
        
    project 'myuv'
        location 'build'
        kind 'ConsoleApp'
        language 'C'
        uuid "8701594A-72B8-4a6a-AEF3-6B41BBC33E65"
        
        defines
        {
            "WIN32",
            "NOMINMAX",
            "WIN32_LEAN_AND_MEAN",
            "_WIN32_WINNT=0x0600",
            "_SCL_SECURE_NO_WARNINGS",
            "_CRT_SECURE_NO_WARNINGS",
        }
        
        files 
        {
            'src/*.h',
            'src/*.c',
        }
        includedirs
        {
            "src",
            "dep/libuv/include",
            "dep/lua/src",
        }
        links 
        {
            "libuv", 
            "liblua",
        }

    project 'libuv'
        location 'build'
        kind 'StaticLib'
        language 'C'
        uuid "CEBF9FA1-2A97-4980-83A1-3B4C39AC7AC8"
        
        defines
        {
            "WIN32",
            "NOMINMAX",
            "WIN32_LEAN_AND_MEAN",
            "_WIN32_WINNT=0x0600",
            "_SCL_SECURE_NO_WARNINGS",
            "_CRT_SECURE_NO_WARNINGS",
        }
        
        files 
        {
            'dep/libuv/include/tree.h',
            'dep/libuv/include/uv.h',
            'dep/libuv/include/uv-errno.h',
            'dep/libuv/include/uv-version.h',
            'dep/libuv/include/uv-win.h',
            'dep/libuv/src/fs-poll.c',
            'dep/libuv/src/heap-inl.h',
            'dep/libuv/src/inet.c',
            'dep/libuv/src/queue.h',
            'dep/libuv/src/uv-common.h',
            'dep/libuv/src/uv-common.c',
            'dep/libuv/src/version.c',
            'dep/libuv/src/win/*.c',
        }
        includedirs
        {
            "dep/libuv/include",
            "dep/libuv/src",
        }
        
    project 'liblua'
        location 'build'
        kind 'StaticLib'
        language 'C'
        uuid "7C0A496A-CCC3-4e4b-AEB1-4AD192BF7D47"
        
        defines
        {
            "WIN32",
            "NOMINMAX",
            "WIN32_LEAN_AND_MEAN",
            "_WIN32_WINNT=0x0600",
            "_SCL_SECURE_NO_WARNINGS",
            "_CRT_SECURE_NO_WARNINGS",
        }
        
        files 
        {
            'dep/lua/src/*.h',
            'dep/lua/src/*.c',
        }
        excludes
        {
            'dep/lua/src/lua.c',
            'dep/lua/src/luac.c',
        }
        includedirs
        {
            "dep/lua/src",
        }        
