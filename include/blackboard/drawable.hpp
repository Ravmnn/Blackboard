#pragma once




namespace bb
{




class Drawable
{
public:
    virtual ~Drawable() = default;


    virtual void draw() = 0;
};




}