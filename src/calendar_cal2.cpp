#include "calendar_cal2.h"

#include <cstring>

#include <array>
#include <string>

#include <stdexcept>

#include "eightwords_type.h"

static std::array<std::string, 10> TIAN_GAN = {"甲", "乙", "丙", "丁", "戊", "己", "庚", "辛", "壬", "癸"};
static std::array<std::string, 12> DI_ZHI = {"子", "丑", "寅", "卯", "辰", "巳", "午", "未", "申", "酉", "戌", "亥"};

namespace utils {

time_t make_time_t(int year, int month, int day) {
    tm t;
    memset(&t, 0, sizeof(t));
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    return mktime(&t);
}

int seconds_of_a_day() { return 60 * 60 * 24; }

int diff_days(time_t lhs, time_t rhs) {
    long secs = std::abs(rhs - lhs);
    return secs / seconds_of_a_day();
}

std::tuple<int, int, int> make_date(time_t t) {
    tm* date = gmtime(&t);
    return std::make_tuple(date->tm_year + 1900, date->tm_mon + 1, date->tm_mday);
}

}  // namespace utils

namespace {

void checkYear(int year) {
    if (year < 1900 || year > 2100) {
        throw std::runtime_error("无法计算年干，输入年要在1900--2100范围之内");
    }
}

std::tuple<CNChar, CNChar> calcCnYear(int year, int* out_tian_gan_index) {
    checkYear(year);
    // 天干
    int tian_gan_index = (year % 10) - 3 - 1;
    if (tian_gan_index < 0) {
        tian_gan_index += 10;
    }
    if (out_tian_gan_index) {
        *out_tian_gan_index = tian_gan_index + 1;
    }
    // 地支
    int di_zhi_index;
    if (year <= 1999) {
        di_zhi_index = (year % 100);
    } else {
        di_zhi_index = (year % 100) + 4;
    }
    di_zhi_index = (di_zhi_index % 60) % DI_ZHI.size();
    // 返回
    return std::make_tuple(TIAN_GAN[tian_gan_index], DI_ZHI[di_zhi_index]);
}

std::tuple<CNChar, CNChar> calcCnMonth(int tian_gan_index_of_year, int month) {
    int tian_gan_index = (tian_gan_index_of_year * 2 + month) % TIAN_GAN.size();
    int di_zhi_index = (month + 2 - 1) % DI_ZHI.size();
    return std::make_tuple(TIAN_GAN[tian_gan_index], DI_ZHI[di_zhi_index]);
}

std::tuple<CNChar, CNChar> calcCnDay(int year, int month, int day) {
    checkYear(year);
    int base;
    if (year <= 1999) {
        base = ((year % 100) + 3) * 5 + 55 + ((year % 100) - 1) / 4;
    } else {
        base = ((year % 100) + 7) * 5 + 15 + ((year % 100) + 19) / 4;
    }
    base %= 60;
    int days = utils::diff_days(utils::make_time_t(year, 1, 1), utils::make_time_t(year, month, day));
    base = (days + base) % 60;
    int tian_gan_index = base % TIAN_GAN.size();
    int di_zhi_index = base % DI_ZHI.size();
    return std::make_tuple(TIAN_GAN[tian_gan_index], DI_ZHI[di_zhi_index]);
}

}  // namespace

CalendarDay CalendarCal2::queryChineseDay(int year, int month, int day) {
    CalendarDay res;
    int tian_gan_index_of_year;
    CNChar gan, zhi;
    std::tie(gan, zhi) = calcCnYear(year, &tian_gan_index_of_year);
    res.chinaYear = gan + zhi;
    std::tie(gan, zhi) = calcCnMonth(tian_gan_index_of_year, month);
    res.chinaMonth = gan + zhi;
    std::tie(gan, zhi) = calcCnDay(year, month, day);
    res.chinaDay = gan + zhi;
    return res;
}
