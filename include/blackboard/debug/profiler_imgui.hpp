#pragma once




namespace bb::debug
{




class ProfilerItem;


class ProfilerIMGUI
{
public:
    inline static bool is_open = false;


    static void draw(ProfilerItem& item) noexcept;


private:
    static void draw_item(ProfilerItem& item) noexcept;
    static int get_tree_node_flags(const ProfilerItem& item) noexcept;

    static void draw_time(ProfilerItem& item) noexcept;
};




}