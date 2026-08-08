#include "blackboard/debug/profiler.hpp"
#include <blackboard/app.hpp>

#include <rlgl.h>

#include <imgui.h>
#include <rl_imgui.h>

#include <blackboard/debug/imgui_setup.hpp>
#include <blackboard/debug/profiler_imgui.hpp>
#include <blackboard/editor/editor.hpp>




using bb::App,
    bb::debug::IMGUISetup,
    bb::debug::Profiler,
    bb::debug::ProfilerIMGUI,
    bb::rendering::WindowRenderer,
    bb::ui::Context,
    bb::editor::Editor;




void App::initialize() noexcept
{
    SetTraceLogLevel(LOG_WARNING);

    initialize_window();
    initialize_app();
    initialize_imgui();
}


void App::initialize_window() noexcept
{
    const int monitor = GetCurrentMonitor();

    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_MAXIMIZED | FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT);
    InitWindow(GetMonitorWidth(monitor), GetMonitorHeight(monitor), "Blackboard");
    PollInputEvents();
}


void App::initialize_app() noexcept
{
    window_renderer = new WindowRenderer;
    window_renderer->use_buffer_texture = false;

    ui_context = new Context;

    new Editor(*ui_context);
}


void App::initialize_imgui() noexcept
{
    rlImGuiSetup(true);

    IMGUISetup::setup_style();
}


void App::deinitialize() noexcept
{
    deinitialize_app();
    deinitialize_imgui();

    CloseWindow();
}


void App::deinitialize_app() noexcept
{
    delete window_renderer;
    delete ui_context;

    window_renderer = nullptr;
    ui_context = nullptr;
}


void App::deinitialize_imgui() noexcept
{
    rlImGuiShutdown();
}




void App::update() noexcept
{
    rlDisableBackfaceCulling(); // IMGUI enables this every frame, so it also has to be disabled every frame

    ui_context->disable_mouse_input = ImGui::GetIO().WantCaptureMouse;
    ui_context->update();
}




void App::draw() noexcept
{
    window_renderer->begin_render();
    ui_context->draw();

    rlImGuiBegin();
    ProfilerIMGUI::draw(*Profiler::root());
    rlImGuiEnd();

    window_renderer->end_render();
}