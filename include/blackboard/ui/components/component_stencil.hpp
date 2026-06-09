#pragma once

#include <blackboard/rendering/stencil.hpp>




namespace bb::ui
{




class Component;


class ComponentStencil
{
public:
    static void enable() noexcept { rendering::Stencil::enable(); }
    static void disable() noexcept { rendering::Stencil::disable(); }


    static void mask_and_increment(const Component& component) noexcept { mask_and_increment(get_stencil_value_for_component(component)); }
    static void mask_and_decrement(const Component& component) noexcept { mask_and_decrement(get_stencil_value_for_component(component)); }

    static void mask_and_increment(const unsigned char stencil_value) noexcept { rendering::Stencil::begin_write(GL_EQUAL, stencil_value, GL_INCR); }
    static void mask_and_decrement(const unsigned char stencil_value) noexcept { rendering::Stencil::begin_write(GL_EQUAL, stencil_value, GL_DECR); }


    static unsigned char get_stencil_value_for_component(const Component& component) noexcept;
};




}