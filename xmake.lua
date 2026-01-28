set_project("libds4")
set_version("1.0.0")
set_languages("c11", "c++17")
add_rules("mode.debug", "mode.release")
add_requires("hidapi", {configs = {shared = false}})
option("build_shared")
    set_default(false)
    set_showmenu(true)
    set_description("Built libds4 as a shared library")
option_end()

option("build_tests")
    set_default(false)
    set_showmenu(true)
    set_description("Build test executables")
option_end()

target("libds4")
    add_defines("USING_XMAKE")
     if has_config("build_shared") then
        set_kind("shared")
        add_defines("DS4_BUILD_SHARED")

    else
        set_kind("static")
        add_defines("DS4_STATIC", {public = true})
    end
    add_files("src/ds4/*.c")
    add_includedirs("include", {public = true})
    add_packages("hidapi", {public = true})
    add_headerfiles("include/(ds4/*.h)")

target("ds4pp")
    add_defines("USING_XMAKE")
    set_kind("static")
    add_files("src/ds4pp/Device.cpp")
    add_includedirs("include", {public = true})
    add_deps("libds4", {public = true}) 
    add_headerfiles("include/(ds4pp/*.hpp)")

if has_config("build_tests") then

    target("cpp_test")
        set_default(false)
        set_kind("binary")
        add_files("tests/cpp_test.cpp")
        add_deps("ds4pp")
    
    target("commands")
        set_default(false)
        set_kind("binary")
        add_files("tests/commands.c")
        add_deps("libds4")

    target("debug_menu")
        set_default(false)
        set_kind("binary")
        add_files("tests/debug_menu.c")
        add_deps("libds4")
    
    target("touchpad_test")
        set_default(false)
        set_kind("binary")
        add_files("tests/touchpad_test.cpp")
        add_deps("ds4pp")
        
end