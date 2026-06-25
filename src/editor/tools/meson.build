subdir('brush')
subdir('eraser')


sources = ['tool.cpp', 'bubble.cpp']


editor_tools_lib = static_library('tools', sources,
    dependencies: global_deps,
    link_with: [tool_brush_lib, tool_eraser_lib]
)