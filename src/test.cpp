#include <gtest/gtest.h>

#include "calendar.h"
#include "calendar_cal2.h"

static int TEST_YEAR = 1989;
static int TEST_MONTH = 2;
static int TEST_DAY = 8;

TEST(EightWords, ChineseCalendarCalc) {
    Calendar calendar("../data/calendar.db");
    CalendarCal2 calendar_calc;

    CalendarDay d1 = calendar.queryChineseDay(TEST_YEAR, TEST_MONTH, TEST_DAY);
    CalendarDay d2 = calendar_calc.queryChineseDay(TEST_YEAR, TEST_MONTH, TEST_DAY);

    std::cout << "date: " << TEST_YEAR << "-" << TEST_MONTH << "-" << TEST_DAY << std::endl;
    std::cout << "  db: " << d1.toString() << std::endl;
    std::cout << "calc: " << d2.toString() << std::endl;

    EXPECT_EQ(d1, d2);
}

// TEST(EightWords, ChineseCalendarCalcAll) {
//     Calendar calendar("../data/calendar.db");
//     CalendarCal2 calendar_calc;

//     time_t the_day = utils::make_time_t(1980, 1, 1);
//     time_t end_of_the_day = utils::make_time_t(2099, 12, 31);
//     while (the_day < end_of_the_day) {
//         int year, month, day;
//         std::tie(year, month, day) = utils::make_date(the_day);
//         try {
//             CalendarDay d1 = calendar.queryChineseDay(year, month, day);
//             CalendarDay d2 = calendar_calc.queryChineseDay(year, month, day);
//             EXPECT_EQ(d1, d2);
//             if (d1 != d2) {
//                 std::cerr << " (" << year << "-" << month << "-" << day << ")" << d1.toString()
//                           << " != " << d2.toString() << std::endl;
//                 break;
//             }
//         } catch (std::exception const& e) {
//             // The record doesn't exist from the database
//         }
//         // Next
//         the_day += utils::seconds_of_a_day();
//     }
// }
