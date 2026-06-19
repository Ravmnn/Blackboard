subdir('brush')
subdir('eraser')


sources = ['tool.cpp', 'bubble.cpp']


tools_lib = static_library('tools', sources,
    dependencies: global_deps,
    link_with: [brush_lib, eraser_lib]
)