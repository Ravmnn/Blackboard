subdir('tools')




sources = files(
    'canvas.cpp', 'stroke_renderer.cpp', 'stroke_mesh_generator.cpp', 'canvas_camera.cpp', 'trail.cpp'
)

editor_lib = static_library('editor', sources,
    dependencies: global_deps,
    link_with: tools_lib
)