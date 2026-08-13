#pragma once




namespace bb::debug
{




class LoggerImGui
{
public:
    inline static bool is_open = false;


    static void draw() noexcept;
};




}