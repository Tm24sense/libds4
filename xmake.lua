set_project("libds4")
set_version("1.0.0")
set_languages("c11", "c++17")
add_rules("mode.debug", "mode.release")


add_requires("hidapi")
target("ds4")
    set_kind("static")
    add_files("src/ds4/*.c")
    add_includedirs("include", {public = true})
    add_packages("hidapi")
    add_headerfiles("include/(ds4/*.h)")

target("ds4pp")
    set_kind("static")
    add_files("src/ds4pp/Device.cpp")
    add_includedirs("include", {public = true})
    add_deps("ds4") 
    add_headerfiles("include/(ds4pp/*.hpp)")


option("build_tests")
    set_default(false)
    set_showmenu(true)
    set_description("Build test executables")

if has_config("build_tests") then
    target("cpp_test")
        set_kind("binary")
        add_files("tests/cpp_test.cpp")
        add_deps("ds4pp")

    target("commands")
        set_kind("binary")
        add_files("tests/commands.c")
        add_deps("ds4")

    target("debug_menu")
        set_kind("binary")
        add_files("tests/debug_menu.c")
        add_deps("ds4")
    target("touchpad_test")
        set_kind("binary")
        add_files("tests/touchpad_test.cpp")
        add_deps("ds4pp")
end