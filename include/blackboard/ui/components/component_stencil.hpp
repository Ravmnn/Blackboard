#pragma once

#include <blackboard/rendering/stencil.hpp>




namespace bb::ui
{




class Component;


class ComponentStencil
{
public:
    static unsigned char get_stencil_id_of_component(const Component& component) noexcept;
};




}