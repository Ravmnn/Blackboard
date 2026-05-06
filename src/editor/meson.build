subdir('tools')




sources = files(
    'canvas.cpp', 'stroke_renderer.cpp', 'canvas_camera.cpp', 'trail.cpp'
)

editor_lib = static_library('editor', sources,
    dependencies: global_deps,
    link_with: tools_lib
)