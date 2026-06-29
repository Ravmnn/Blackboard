project('Blackboard', 'cpp',
    default_options: ['warning_level=3', 'cpp_std=c++23']
)

add_project_arguments(
    '-Wno-missing-field-initializers',
    language: 'cpp'
)


cc = meson.get_compiler('cpp')




inc = include_directories('include')

project_dep = declare_dependency(
    include_directories: inc
)


math_lib = cc.find_library('m', required: true)


raylib_dep = dependency('raylib',
    required: false,
    fallback: ['raylib', 'raylib_dep']
)


global_deps = [project_dep, math_lib, raylib_dep]




subdir('src')