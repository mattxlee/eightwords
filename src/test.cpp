#include <gtest/gtest.h>

#include "calendar.h"
#include "calendar_calc.h"

static int TEST_YEAR = 1989;
static int TEST_MONTH = 2;
static int TEST_DAY = 8;

TEST(EightWords, ChineseCalendarCalc) {
    Calendar calendar("../data/calendar.db");
    CalendarCalc calendar_calc;

    CalendarDay d1 = calendar.queryChineseDay(TEST_YEAR, TEST_MONTH, TEST_DAY);
    CalendarDay d2 = calendar_calc.queryChineseDay(TEST_YEAR, TEST_MONTH, TEST_DAY);

    std::cout << d1.toString() << std::endl;
    std::cout << d2.toString() << std::endl;

    EXPECT_EQ(d1, d2);
}
