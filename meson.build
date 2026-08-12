project('Blackboard', 'cpp',
    default_options: ['warning_level=3', 'cpp_std=c++23']
)

add_project_arguments(
    '-Wno-missing-field-initializers',
    language: 'cpp'
)


cc = meson.get_compiler('cpp')




math_lib = cc.find_library('m', required: true)


project_dep = declare_dependency(
    include_directories: include_directories('include')
)

raylib_dep = dependency('raylib',
    required: false,
    fallback: ['raylib', 'raylib_dep']
)

imgui_dep = dependency('imgui',
    required: false,
    fallback: ['imgui', 'imgui_dep']
)

platform_folders_dep = dependency('platform_folders',
    required: false,
    fallback: ['platform_folders', 'platform_folders_dep']
)


global_deps = [math_lib, project_dep, raylib_dep, imgui_dep, platform_folders_dep]




subdir('src')