#include "calendar_cal2.h"

#include <cstring>

#include <array>
#include <string>

#include <stdexcept>

#include "eightwords_type.h"

static std::array<std::string, 10> TIAN_GAN
    = { "甲", "乙", "丙", "丁", "戊", "己", "庚", "辛", "壬", "癸" };
static std::array<std::string, 12> DI_ZHI = { "子", "丑", "寅", "卯", "辰",
  "巳", "午", "未", "申", "酉", "戌", "亥" };

namespace utils {

time_t make_time_t(int year, int month, int day) {
  tm t;
  memset(&t, 0, sizeof(t));
  t.tm_year = year - 1900;
  t.tm_mon = month - 1;
  t.tm_mday = day;
  return mktime(&t);
}

int seconds_of_a_day() {
  return 60 * 60 * 24;
}

int diff_days(time_t lhs, time_t rhs) {
  long secs = std::abs(rhs - lhs);
  return secs / seconds_of_a_day();
}

std::tuple<int, int, int> make_date(time_t t) {
  tm* date = gmtime(&t);
  return std::make_tuple(date->tm_year + 1900, date->tm_mon + 1, date->tm_mday);
}

} // namespace utils

namespace lunar {

int LunarData[100] = { 2635, 333387, 1701, 1748, 267701, 694, 2391, 133423,
  1175, 396438, 3402, 3749, 331177, 1453, 694, 201326, 2350, 465197, 3221, 3402,
  400202, 2901, 1386, 267611, 605, 2349, 137515, 2709, 464533, 1738, 2901,
  330421, 1242, 2651, 199255, 1323, 529706, 3733, 1706, 398762, 2741, 1206,
  267438, 2647, 1318, 204070, 3477, 461653, 1386, 2413, 330077, 1197, 2637,
  268877, 3365, 531109, 2900, 2922, 398042, 2395, 1179, 267415, 2635, 661067,
  1701, 1748, 398772, 2742, 2391, 330031, 1175, 1611, 200010, 3749, 527717,
  1452, 2742, 332397, 2350, 3222, 268949, 3402, 3493, 133973, 1386, 464219, 605,
  2349, 334123, 2709, 2890, 267946, 2773, 592565, 1210, 2651, 395863, 1323,
  2707, 265877 };

int MonthAdd[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

std::string months[12] = { "正月", "二月", "三月", "四月", "五月", "六月",
  "七月", "八月", "九月", "十月", "冬月", "腊月" };

std::string days[30] = { "初一", "初二", "初三", "初四", "初五", "初六", "初七",
  "初八", "初九", "初十", "十一", "十二", "十三", "十四", "十五", "十六",
  "十七", "十八", "十九", "二十", "廿一", "廿二", "廿三", "廿四", "廿五",
  "廿六", "廿七", "廿八", "廿九", "三十" };

struct Date {
  int month;
  int day;
  std::string lunarCalendar;
};

Date GetLunarCalendarMonth(int year, int month, int day) {
  try {
    int nTheDate;
    int nIsEnd = 0, k = 0, m = 0, n = 0, nBit = 0, i = 0;
    std::string calendar = "";
    // 计算到初始时间1921年2月8日的天数：1921-2-8(正月初一)
    nTheDate = (year - 1921) * 365 + (year - 1921) / 4 + day
        + MonthAdd[month - 1] - 38;
    // 判断是否为闰年并且月份大于2月
    if ((year % 4 == 0) && (month > 2))
      nTheDate += 1;
    // 计算天干，地支，月，日
    while (nIsEnd != 1) {
      if (LunarData[m] < 4095)
        k = 11;
      else
        k = 12;
      n = k;
      while (n >= 0) {
        // 获取LunarData[m]的第n个二进制位的值
        nBit = LunarData[m];
        for (i = 0; i < n; i++)
          nBit = nBit / 2;
        nBit = nBit % 2;
        if (nTheDate <= (29 + nBit)) {
          nIsEnd = 1;
          break;
        }
        nTheDate = nTheDate - 29 - nBit;
        n -= 1;
      }
      if (nIsEnd == 1)
        break;
      m = m + 1;
    }
    year = 1921 + m;
    month = k - n + 1;
    day = nTheDate;

    // #region 格式化日期显示为三月廿四
    if (k == 12) {
      if (month == LunarData[m] / 65536 + 1)
        month = 1 - month;
      else if (month > LunarData[m] / 65536 + 1)
        month = month - 1;
    }
    // 农历月
    if (month < 1) {
      calendar += "闰" + months[abs(month) - 1];
      month = abs(month);
    } else {
      calendar += months[month - 1];
    }
    Date dt;
    dt.month = month;
    dt.day = day;
    dt.lunarCalendar = calendar + days[day - 1];
    return dt;
  } catch (std::exception const&) {
    return Date();
  }
}

} // namespace lunar

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

std::tuple<CNChar, CNChar> calcCnMonth(
    int tian_gan_index_of_year, int year, int month, int day) {
  lunar::Date lunar_date = lunar::GetLunarCalendarMonth(year, month, day);
  int tian_gan_index
      = ((tian_gan_index_of_year * 2 + lunar_date.month) - 1) % TIAN_GAN.size();
  int di_zhi_index = (lunar_date.month - 1 + 2) % DI_ZHI.size();
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
  int days = utils::diff_days(
      utils::make_time_t(year, 1, 1), utils::make_time_t(year, month, day));
  base = (days + base) % 60;
  int tian_gan_index = base % TIAN_GAN.size();
  int di_zhi_index = base % DI_ZHI.size();
  return std::make_tuple(TIAN_GAN[tian_gan_index], DI_ZHI[di_zhi_index]);
}

} // namespace

CalendarDay CalendarCal2::queryChineseDay(int year, int month, int day) {
  CalendarDay res;
  int tian_gan_index_of_year;
  CNChar gan, zhi;
  std::tie(gan, zhi) = calcCnYear(year, &tian_gan_index_of_year);
  res.chinaYear = gan + zhi;
  std::tie(gan, zhi) = calcCnMonth(tian_gan_index_of_year, year, month, day);
  res.chinaMonth = gan + zhi;
  std::tie(gan, zhi) = calcCnDay(year, month, day);
  res.chinaDay = gan + zhi;
  return res;
}
