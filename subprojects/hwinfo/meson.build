project('hwinfo', 'cpp')


cc = meson.get_compiler('cpp')

lib_dir = meson.current_source_dir() / 'lib'

lib_names = [
    'hwinfo_battery', 'hwinfo_computer', 'hwinfo_cpu', 'hwinfo_disk',
    'hwinfo_gpu', 'hwinfo_mainboard', 'hwinfo_network', 'hwinfo_os', 'hwinfo_ram'
]

libs = []


foreach name : lib_names
    libs += cc.find_library(name, dirs: lib_dir, static: true)
endforeach


hwinfo_dep = declare_dependency(
    dependencies: libs,
    include_directories: include_directories('include')
)