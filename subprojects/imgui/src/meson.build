sources = files(
    'imgui.cpp', 'imgui_draw.cpp', 'imgui_tables.cpp', 'imgui_widgets.cpp',
    'rl_imgui.cpp'
)

imgui_lib = static_library('imgui', sources,
    dependencies: [imgui_includes, raylib_dep],
    cpp_args: ['-DNO_FONT_AWESOME']
)