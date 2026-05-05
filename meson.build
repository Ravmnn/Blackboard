project('Blackboard', 'cpp',
    default_options: ['warning_level=3', 'cpp_std=c++20']
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


flustral_lib = cc.find_library('flustral', required: true,
    dirs: ['/home/ravmn/Documentos/programming/cpp/Flustral/build/src']
)

flustral_dep = declare_dependency(
    dependencies: [flustral_lib],
    include_directories: ['/home/ravmn/Documentos/programming/cpp/Flustral/include']
)


global_deps = [project_dep, math_lib, raylib_dep, flustral_dep]




subdir('src')