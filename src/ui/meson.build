subdir('components')




sources = files('clickable.cpp', 'ui_context.cpp')

ui_lib = static_library('ui', sources,
    dependencies: global_deps,
    link_with: components_lib
)