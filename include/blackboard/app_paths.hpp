#pragma once

#include <filesystem>

#include <platform_folders.h>

#include <blackboard/app.hpp>




namespace bb
{




class AppPaths
{
public:
    static std::filesystem::path root() noexcept { return std::filesystem::path(sago::getDataHome()) / App::Name; }
    static std::filesystem::path logs() noexcept { return root() / "logs"; }
};




}