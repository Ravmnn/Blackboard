#pragma once




namespace bb::debug
{




class ProfilerItem;


class ProfilerIMGUI
{
public:
    inline static bool is_open = false;


    static void draw(const ProfilerItem& item) noexcept;


private:
    static void draw_item(const ProfilerItem& item) noexcept;
    static void draw_time(const ProfilerItem& item) noexcept;
};




}