subdir('ui')
subdir('editor')
subdir('rendering')


sources = files(
    'main.cpp', 'texture_sample.cpp', 'timer.cpp', 'mouse_button_event.cpp', 'mouse_button_set.cpp',
    'mouse_position_provider.cpp'
)

executable('bboard', sources,
    dependencies: global_deps,
    link_with: [ui_lib, editor_lib, rendering_lib]
)