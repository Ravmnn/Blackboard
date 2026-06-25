subdir('effects')
subdir('stroke')
subdir('tools')
subdir('ui')




sources = files(
    'canvas.cpp', 'editor.cpp', 'canvas_camera.cpp',
    'lazy_cursor.cpp', 'palette.cpp', 'canvas_renderer.cpp'
)

editor_lib = static_library('editor', sources,
    dependencies: global_deps,
    link_with: [editor_effects_lib, editor_stroke_lib, editor_tools_lib, editor_ui_lib]
)