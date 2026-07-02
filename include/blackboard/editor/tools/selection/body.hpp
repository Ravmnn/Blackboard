#pragma once

#include <blackboard/updateable.hpp>
#include <blackboard/drawable.hpp>




namespace bb::editor
{




class Selection;


class SelectionBody : public Updateable, public Drawable
{
private:


public:
    Selection& selection;


    explicit SelectionBody(Selection& selection) noexcept;


    void update() noexcept override;
    void draw() noexcept override;
};




}