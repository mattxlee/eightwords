#include "calendar_calc.h"

#include <cstring>
#include <chrono>

namespace lunar {

static uint32_t LUNAR_INFO[] = {
        0x04bd8, 0x04ae0, 0x0a570, 0x054d5, 0x0d260, 0x0d950, 0x16554, 0x056a0, 0x09ad0, 0x055d2, 0x04ae0, 0x0a5b6,
        0x0a4d0, 0x0d250, 0x1d255, 0x0b540, 0x0d6a0, 0x0ada2, 0x095b0, 0x14977, 0x04970, 0x0a4b0, 0x0b4b5, 0x06a50,
        0x06d40, 0x1ab54, 0x02b60, 0x09570, 0x052f2, 0x04970, 0x06566, 0x0d4a0, 0x0ea50, 0x06e95, 0x05ad0, 0x02b60,
        0x186e3, 0x092e0, 0x1c8d7, 0x0c950, 0x0d4a0, 0x1d8a6, 0x0b550, 0x056a0, 0x1a5b4, 0x025d0, 0x092d0, 0x0d2b2,
        0x0a950, 0x0b557, 0x06ca0, 0x0b550, 0x15355, 0x04da0, 0x0a5d0, 0x14573, 0x052d0, 0x0a9a8, 0x0e950, 0x06aa0,
        0x0aea6, 0x0ab50, 0x04b60, 0x0aae4, 0x0a570, 0x05260, 0x0f263, 0x0d950, 0x05b57, 0x056a0, 0x096d0, 0x04dd5,
        0x04ad0, 0x0a4d0, 0x0d4d4, 0x0d250, 0x0d558, 0x0b540, 0x0b5a0, 0x195a6, 0x095b0, 0x049b0, 0x0a974, 0x0a4b0,
        0x0b27a, 0x06a50, 0x06d40, 0x0af46, 0x0ab60, 0x09570, 0x04af5, 0x04970, 0x064b0, 0x074a3, 0x0ea50, 0x06b58,
        0x055c0, 0x0ab60, 0x096d5, 0x092e0, 0x0c960, 0x0d954, 0x0d4a0, 0x0da50, 0x07552, 0x056a0, 0x0abb7, 0x025d0,
        0x092d0, 0x0cab5, 0x0a950, 0x0b4a0, 0x0baa4, 0x0ad50, 0x055d9, 0x04ba0, 0x0a5b0, 0x15176, 0x052b0, 0x0a930,
        0x07954, 0x06aa0, 0x0ad50, 0x05b52, 0x04b60, 0x0a6e6, 0x0a4e0, 0x0d260, 0x0ea65, 0x0d530, 0x05aa0, 0x076a3,
        0x096d0, 0x04bd7, 0x04ad0, 0x0a4d0, 0x1d0b6, 0x0d250, 0x0d520, 0x0dd45, 0x0b5a0, 0x056d0, 0x055b2, 0x049b0,
        0x0a577, 0x0a4b0, 0x0aa50, 0x1b255, 0x06d20, 0x0ada0};

// 传回农历y年m月的总天数
static int monthDays(int y, int m) {
    if ((LUNAR_INFO[y - 1900] & (0x10000 >> m)) == 0) {
        return 29;
    } else {
        return 30;
    }
}

// 传回农历y年闰哪个月1-12 , 没闰传回0
static int leapMonth(int y) { return (int)(LUNAR_INFO[y - 1900] & 0xf); }

// 传回农历y年闰月的天数
static int leapDays(int y) {
    if (leapMonth(y) != 0) {
        if ((LUNAR_INFO[y - 1900] & 0x10000) != 0)
            return 30;
        else
            return 29;
    } else
        return 0;
}

// 传回农历y年的总天数
static int yearDays(int y) {
    int i, sum = 348;
    for (i = 0x8000; i > 0x8; i >>= 1) {
        if ((LUNAR_INFO[y - 1900] & i) != 0) sum += 1;
    }
    return sum + leapDays(y);
}

// 将日期转成time_t
time_t to_time_t(int year, int month, int day) {
    tm t;
    memset(&t, 0, sizeof(t));
    t.tm_year = year - 1900;
    t.tm_mon = month - 1;
    t.tm_mday = day;
    return mktime(&t);
}

static std::string GAN[] = {"甲", "乙", "丙", "丁", "戊", "己", "庚", "辛", "壬", "癸"};
static std::string ZHI[] = {"子", "丑", "寅", "卯", "辰", "巳", "午", "未", "申", "酉", "戌", "亥"};

class ChineseEra {
public:
    static std::string calcYear(int cnYearNum) {
        int num = cnYearNum - 1900 + 36;
        return GAN[num % 10] + ZHI[num % 12];
    }

    static std::string calcMonth(int year, int cnMonthNum) {
        std::string tg, dz;
        int num = (year - 4) % 5;
        int gan_index;
        if (num == 4) {
            gan_index = (cnMonthNum - 1) % 10;
        } else {
            gan_index = (cnMonthNum + (num * 2) + 1) % 10;
        }
        int dz_index = (cnMonthNum + 1) % 12;
        return GAN[gan_index] + ZHI[dz_index];
    }

    static std::string calcDay(int gzr) {
        std::string res;
        if (gzr % 10 == 0) {
            res = GAN[9] + ZHI[gzr % 12];
        }
        if (gzr % 12 == 0) {
            res = GAN[gzr % 10] + ZHI[11];
        }
        if ((gzr != 0 && (gzr % 10) != 0 && (gzr % 12) != 0)) {
            res = GAN[gzr % 10] + ZHI[gzr % 12];
        }
        if (gzr == 0) {
            res = GAN[gzr % 10] + ZHI[gzr % 12];
        }
        return res;
    }
};

}  // namespace lunar

CalendarDay CalendarCalc::queryChineseDay(int in_year, int in_month, int in_day) {
    int year{0}, month{0}, day{0};
    int yearCyl{0}, monCyl{0}, dayCyl{0};
    int leapMonth = 0;

    // 求出和1900年1月31日相差的天数
    time_t d1900_1_31 = lunar::to_time_t(1900, 1, 31);
    time_t in_date = lunar::to_time_t(in_year, in_month, in_day);
    long offset = (in_date - d1900_1_31) / (60 * 60 * 24);

    dayCyl = offset + 40;
    monCyl = 14;

    // 用offset减去每农历年的天数
    // 计算当天是农历第几天
    // i最终结果是农历的年份
    // offset是当年的第几天
    int iYear, daysOfYear = 0;
    for (iYear = 1900; iYear < 2050 && offset > 0; iYear++) {
        daysOfYear = lunar::yearDays(iYear);
        offset -= daysOfYear;
        monCyl += 12;
    }
    if (offset < 0) {
        offset += daysOfYear;
        iYear--;
        monCyl -= 12;
    }
    //农历年份
    year = iYear;

    yearCyl = iYear - 1864;
    leapMonth = lunar::leapMonth(iYear);  // 闰哪个月，1-12
    bool leap = false;

    // 用当年的天数offset，逐个减去每月（农历）的天数，求出当天是本月的第几天
    int iMonth, daysOfMonth = 0;
    for (iMonth = 1; iMonth < 13 && offset > 0; iMonth++) {
        //闰月
        if (leapMonth > 0 && iMonth == (leapMonth + 1) && !leap) {
            --iMonth;
            leap = true;
            daysOfMonth = lunar::leapDays(year);
        } else {
            daysOfMonth = lunar::monthDays(year, iMonth);
        }

        offset -= daysOfMonth;
        //解除闰月
        if (leap && iMonth == (leapMonth + 1)) leap = false;
        if (!leap) monCyl++;
    }
    // offset为0时，并且刚才计算的月份是闰月，要校正
    if (offset == 0 && leapMonth > 0 && iMonth == leapMonth + 1) {
        if (leap) {
            leap = false;
        } else {
            leap = true;
            --iMonth;
            --monCyl;
        }
    }
    // offset小于0时，也要校正
    if (offset < 0) {
        offset += daysOfMonth;
        --iMonth;
        --monCyl;
    }
    month = iMonth;
    day = offset + 1;

    CalendarDay res;
    res.chinaYear = lunar::ChineseEra::calcYear(year);
    res.chinaMonth = lunar::ChineseEra::calcMonth(in_year, month);
    res.chinaDay = lunar::ChineseEra::calcDay(offset);

    return res;
}
