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
    cpp_args: ['-DNO_FONT_AWESOME'],
    install: true,
    install_dir: get_option('bindir')
)


install_data(
    '../resources/Blackboard.desktop',
    install_dir: join_paths(get_option('datadir'), 'applications')
)


install_data(
    '../resources/icon.png',
    install_dir: join_paths(get_option('datadir'), 'icons', 'hicolor', '512x512', 'apps')
)


install_subdir(
    'resources',
    install_dir: join_paths(get_option('datadir'), 'Blackboard')
)