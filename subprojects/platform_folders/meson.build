project('platform_folders', 'cpp')


platform_folders_includes = declare_dependency(
    include_directories: include_directories('include')
)


subdir('src')


platform_folders_dep = declare_dependency(
    link_with: platform_folders_lib,
    include_directories: include_directories('include')
)