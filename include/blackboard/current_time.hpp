#pragma once

#include <chrono>




namespace bb
{




class CurrentTime
{
public:
    static auto zone() noexcept { return std::chrono::zoned_time(std::chrono::current_zone(), std::chrono::system_clock::now()); }
    static auto local_time() noexcept { return zone().get_local_time(); }

    static auto total_days() noexcept { return std::chrono::floor<std::chrono::days>(local_time()); }

    static auto year_month_day() noexcept { return std::chrono::year_month_day(total_days()); }
    static auto hour_minute_second() noexcept { return std::chrono::hh_mm_ss(std::chrono::duration_cast<std::chrono::seconds>(local_time() - total_days())); }
    static auto hour_minute_second_with_ms() noexcept { return std::chrono::hh_mm_ss(std::chrono::duration_cast<std::chrono::milliseconds>(local_time() - total_days())); }

    static auto year() noexcept { return year_month_day().year(); }
    static auto month() noexcept { return year_month_day().month(); }
    static auto day() noexcept { return year_month_day().day(); }
    static auto hour() noexcept { return hour_minute_second().hours(); }
    static auto minutes() noexcept { return hour_minute_second().minutes(); }
    static auto seconds() noexcept { return hour_minute_second().seconds(); }
};




}