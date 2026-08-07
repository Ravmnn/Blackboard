project('imgui', 'cpp')


imgui_includes = declare_dependency(
    include_directories: include_directories('include')
)


raylib_dep = dependency('raylib',
    required: false,
    fallback: ['raylib', 'raylib_dep']
)


subdir('src')


imgui_dep = declare_dependency(
    link_with: imgui_lib,
    include_directories: include_directories('include')
)