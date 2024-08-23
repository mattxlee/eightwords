#ifndef __CALENDAR_TYPE_H__
#define __CALENDAR_TYPE_H__

#include <map>
#include <string>

namespace l4w {

struct CalendarKey {
  int year; // 英文年
  int month; // 英文月
  int day; // 英文日
};

inline bool operator<(CalendarKey const& lhs, CalendarKey const& rhs) {
  if (lhs.year < rhs.year)
    return true;
  if (lhs.year > rhs.year)
    return false;

  if (lhs.month < rhs.month)
    return true;
  if (lhs.month > rhs.month)
    return false;

  if (lhs.day < rhs.day)
    return true;
  if (lhs.day > rhs.day)
    return false;

  return true;
}

inline bool operator==(CalendarKey const& lhs, CalendarKey const& rhs) {
  return lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day;
}

inline bool operator!=(CalendarKey const& lhs, CalendarKey const& rhs) {
  return !(lhs == rhs);
}

struct CalendarDay {
  std::string chinaYear; // 中文年
  std::string chinaMonth; // 中文月
  std::string chinaDay; // 中文日

  std::string toString() const {
    return chinaYear + " " + chinaMonth + " " + chinaDay;
  }
};

// 英中日历对照
typedef std::map<CalendarKey, CalendarDay> CalendarDayList;

inline bool operator==(CalendarDay const& lhs, CalendarDay const& rhs) {
  return lhs.chinaYear == rhs.chinaYear && lhs.chinaMonth == rhs.chinaMonth
      && lhs.chinaDay == rhs.chinaDay;
}

inline bool operator!=(CalendarDay const& lhs, CalendarDay const& rhs) {
  return !(lhs == rhs);
}

} // namespace l4w

#endif