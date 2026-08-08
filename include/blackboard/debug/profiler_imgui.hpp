#pragma once




namespace bb::debug
{




class ProfilerGroupItem;


class ProfilerIMGUI
{
public:
    static void draw(const ProfilerGroupItem& group) noexcept;
};




}