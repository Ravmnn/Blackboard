#pragma once

#include <blackboard/editor/ui/radial_layout.hpp>
#include <blackboard/ui/components/shape.hpp>
#include <blackboard/ui/components/button.hpp>
#include <blackboard/event.hpp>




namespace bb::editor
{




class ColorMenu : public RadialLayout
{
private:
    bool is_shown_ = false;


public:
    static constexpr float HiddenRadius = 50;
    static constexpr float ShownRadius = 170;
    static constexpr unsigned int HiddenOpacity = 0;
    static constexpr unsigned int ShownOpacity = 255;


    Event<Color> color_selected;


    ColorMenu() noexcept;


    void toggle(const Vector2& position) noexcept;
    void show(const Vector2& position) noexcept;
    void hide() noexcept;


protected:
    void update_self() noexcept override;


    Vector2 get_position_for_child(Component& child, size_t i) noexcept override;


    void on_color_selected(const Color& color) noexcept;


    void set_children_opacity(const uint8_t opacity) noexcept {
        for_each_children<ui::Shape>([opacity](ui::Shape* const child) { child->set_both_opacity(opacity); });
    }


    void set_children_ignore_interaction(const bool ignore) noexcept {
        for_each_children<ui::Button>([ignore](ui::Button* const child) { child->ignore_event_triggering = ignore; });
    }
};




}