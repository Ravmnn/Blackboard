#pragma once

#include <blackboard/editor/editor.hpp>
#include <blackboard/ui/context.hpp>
#include <blackboard/rendering/window_renderer.hpp>




namespace bb
{




class App
{
public:
    inline static rendering::WindowRenderer* window_renderer = nullptr;
    inline static ui::Context* ui_context = nullptr;
    inline static editor::Editor* editor = nullptr;


    static void initialize() noexcept;
    static void deinitialize() noexcept;

    static void update() noexcept;
    static void draw() noexcept;


    [[nodiscard]] static bool is_open()  noexcept { return !WindowShouldClose(); }


private:
    static void initialize_window() noexcept;
    static void initialize_app() noexcept;
    static void initialize_imgui() noexcept;

    static void deinitialize_app() noexcept;
    static void deinitialize_imgui() noexcept;


    static void update_keybindings() noexcept;

    static void draw_imgui() noexcept;
};




}