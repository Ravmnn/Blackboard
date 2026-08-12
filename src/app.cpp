#include <blackboard/app.hpp>

#include <filesystem>

#include <platform_folders.h>

#include <rlgl.h>

#include <rl_imgui.h>
#include <implot.h>

#include <blackboard/app_paths.hpp>
#include <blackboard/debug/profiler.hpp>
#include <blackboard/debug/imgui_style_set.hpp>
#include <blackboard/debug/logger.hpp>
#include <blackboard/debug/profiler_imgui.hpp>
#include <blackboard/editor/editor.hpp>




// TODO: organize these usings
using bb::App,
    bb::debug::ImGuiStyleSet,
    bb::debug::Profiler,
    bb::debug::ProfilerImGui,
    bb::debug::Logger,
    bb::rendering::WindowRenderer,
    bb::ui::Context,
    bb::editor::Editor,

    std::filesystem::path;




void App::initialize() noexcept
{
    SetTraceLogLevel(LOG_WARNING);

    initialize_logger();
    initialize_window();
    initialize_app();
    initialize_imgui();
}


void App::initialize_logger() noexcept
{
    Logger::log_to_stdout = true;
    Logger::log_to_file = true;
    Logger::log_file_directory = AppPaths::logs();

    Logger::create_log_file();

    Logger::info("Application started");
}


void App::initialize_window() noexcept
{
    const int monitor = GetCurrentMonitor();

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(GetMonitorWidth(monitor), GetMonitorHeight(monitor), "Blackboard");
    PollInputEvents();
    SetTargetFPS(0);

    Logger::info("Window created", true);
}


void App::initialize_app() noexcept
{
    window_renderer = new WindowRenderer;
    window_renderer->use_buffer_texture = false;

    ui_context = new Context;
    editor = new Editor(*ui_context);

    Logger::info("Editor created", true);
}


void App::initialize_imgui() noexcept
{
    rlImGuiSetup(true);
    ImPlot::CreateContext();

    ImGuiStyleSet::setup_style();

    Logger::info("ImGui context created", true);
}




void App::deinitialize() noexcept
{
    Logger::info("Application shutting down");

    deinitialize_app();
    deinitialize_imgui();
    deinitialize_window();
    deinitialize_logger();
}


void App::deinitialize_app() noexcept
{
    delete window_renderer;
    delete ui_context;

    window_renderer = nullptr;
    ui_context = nullptr;

    Logger::info("Editor destroyed", true);
}


void App::deinitialize_imgui() noexcept
{
    rlImGuiShutdown();
    ImPlot::DestroyContext();

    Logger::info("ImGui context destroyed", true);
}


void App::deinitialize_window() noexcept
{
    CloseWindow();
    Logger::info("Window destroyed", true);
}


void App::deinitialize_logger() noexcept
{
    Logger::info("Bye bye!");

    Logger::close_log_file();
}








void App::update() noexcept
{
    Profiler::begin_root();
    Profiler::begin("app::update");


    update_keybindings();

    rlDisableBackfaceCulling(); // IMGUI enables this every frame, so it also has to be disabled every frame

    ui_context->disable_mouse_input = ImGui::GetIO().WantCaptureMouse;
    ui_context->update();


    Profiler::end();
}


void App::update_keybindings() noexcept
{
    if (IsKeyPressed(KEY_F1)) ProfilerImGui::is_open = !ProfilerImGui::is_open;

    // TODO: move debug drawing from StrokeRendererRL to a separated class
    // if (IsKeyPressed(KEY_TWO)) editor->stroke_manager.renderer_rl.should_debug_draw_points = !editor->stroke_manager.renderer_rl.should_debug_draw_points;
    // if (IsKeyPressed(KEY_THREE)) editor->stroke_manager.renderer_rl.should_debug_draw_samples = !editor->stroke_manager.renderer_rl.should_debug_draw_samples;
    // if (IsKeyPressed(KEY_FOUR)) editor->stroke_manager.renderer_rl.should_debug_draw_edges = !editor->stroke_manager.renderer_rl.should_debug_draw_edges;
    if (IsKeyPressed(KEY_FIVE)) editor->wire_mode = !editor->wire_mode;
}




void App::draw() noexcept
{
    window_renderer->begin_render();

    Profiler::begin("app::draw");
    ui_context->draw();
    Profiler::end();

    draw_imgui();

    Profiler::begin("gl::sync");
    window_renderer->end_render();
    Profiler::end();


    Profiler::reset();
    Profiler::end_root();
}


void App::draw_imgui() noexcept
{
    rlImGuiBegin();
    ProfilerImGui::draw(*Profiler::root());
    rlImGuiEnd();
}