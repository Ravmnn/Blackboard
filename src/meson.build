subdir('components')
subdir('editor')
subdir('rendering')


sources = files('main.cpp', 'texture_sample.cpp', 'timer.cpp')

executable('bboard', sources,
    dependencies: global_deps,
    link_with: [components_lib, editor_lib, rendering_lib]
)