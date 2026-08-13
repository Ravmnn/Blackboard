subdir('debug')
subdir('editor')
subdir('rendering')
subdir('ui')


sources = files(
    'main.cpp', 'app.cpp', 'texture_sample.cpp', 'mouse_button_event.cpp', 'mouse_button_set.cpp',
    'mouse_position_provider.cpp'
)

executable('bboard', sources,
    dependencies: global_deps,
    link_with: [debug_lib, editor_lib, rendering_lib, ui_lib],
    cpp_args: ['-DNO_FONT_AWESOME']
)