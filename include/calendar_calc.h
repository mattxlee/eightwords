#ifndef __L4W_CALENDAR_CALC_DATA__
#define __L4W_CALENDAR_CALC_DATA__

#include "calendar_type.h"

class CalendarCalc {
public:
  CalendarDay queryChineseDay(int year, int month, int day);
};

namespace utils {

time_t make_time_t(int year, int month, int day);

int seconds_of_a_day();

std::tuple<int, int, int> make_date(time_t t);

} // namespace utils

#endif