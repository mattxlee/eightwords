#include <gtest/gtest.h>

#include <sstream>

#include "calendar.h"
#include "eightwords.h"

static int TEST_YEAR = 1989;
static int TEST_MONTH = 2;
static int TEST_DAY = 8;

std::string CNStringToString(CNString const& cn_str) {
  std::stringstream ss;
  for (auto const& cn_char : cn_str) {
    ss << cn_char;
  }
  return ss.str();
}

TEST(EightWords, Calculation) {
  Calendar calendar("data/calendar.db");
  auto calendar_day = calendar.queryChineseDay(1980, 2, 10);

  Table8x2 table;
  auto cn_list = table.analyze(calendar_day.chinaYear, calendar_day.chinaMonth,
      calendar_day.chinaDay, 3);

  // 庚申 戊寅 癸丑 甲寅
  EXPECT_EQ(cn_list.size(), 4);
  EXPECT_EQ(CNStringToString(cn_list[0]), "庚申");
  EXPECT_EQ(CNStringToString(cn_list[1]), "戊寅");
  EXPECT_EQ(CNStringToString(cn_list[2]), "癸丑");
  EXPECT_EQ(CNStringToString(cn_list[3]), "甲寅");
}