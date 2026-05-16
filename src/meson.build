subdir('ui')
subdir('editor')
subdir('rendering')


sources = files('main.cpp', 'texture_sample.cpp', 'timer.cpp', 'mouse_button_event.cpp')

executable('bboard', sources,
    dependencies: global_deps,
    link_with: [ui_lib, editor_lib, rendering_lib]
)