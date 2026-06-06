subdir('tools')
subdir('ui')




sources = files(
    'canvas.cpp', 'editor.cpp', 'stroke_renderer.cpp', 'stroke_mesh_generator.cpp', 'canvas_camera.cpp', 'trail.cpp',
    'lazy_cursor.cpp', 'palette.cpp'
)

editor_lib = static_library('editor', sources,
    dependencies: global_deps,
    link_with: [tools_lib, editor_ui_lib]
)