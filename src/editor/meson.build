subdir('effects')
subdir('stroke')
subdir('tools')
subdir('ui')




sources = files(
    'canvas.cpp', 'editor.cpp', 'canvas_camera.cpp', 'editor_environment.cpp',
    'lazy_cursor.cpp', 'palette.cpp', 'editor_drawing_environment.cpp', 'editor_selection_environment.cpp',
    'mouse_late_mode_indicator.cpp', 'editor_background.cpp', 'stroke_mesh_manager.cpp'
)

editor_lib = static_library('editor', sources,
    dependencies: global_deps,
    link_with: [editor_effects_lib, editor_stroke_lib, editor_tools_lib, editor_ui_lib]
)