#pragma once

#include <tuple>
#include <vector>




namespace bb::debug
{




class ProfilerItem;


class ProfilerImGui
{
public:
    inline static bool is_open = false;


    static void draw(ProfilerItem& item) noexcept;


private:
    static void draw_chart(ProfilerItem& item) noexcept;
    static int get_chart_flags() noexcept;

    static std::tuple<std::vector<const char*>, std::vector<double>> get_items_chart_node(ProfilerItem& item) noexcept;
    static void get_items_chart_node(ProfilerItem& item, std::vector<const char*>& labels, std::vector<double>& values) noexcept;

    static void draw_items(ProfilerItem& item) noexcept;
    static void draw_item(ProfilerItem& item) noexcept;
    static int get_tree_node_flags(const ProfilerItem& item) noexcept;

    static void draw_time(ProfilerItem& item) noexcept;
};




}