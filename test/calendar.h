#ifndef __L4W_CALENDAR_DATA__
#define __L4W_CALENDAR_DATA__

#include <sqlite3.h>

#include <string>

#include "calendar_type.h"

namespace l4w {

class Calendar {
public:
  explicit Calendar(std::string const& dbFile);
  ~Calendar();

  Calendar(Calendar const&) = delete;
  Calendar& operator=(Calendar const&) = delete;

  Calendar(Calendar&& rhs) noexcept;
  Calendar& operator=(Calendar&& rhs) noexcept;

  CalendarDay queryChineseDay(int year, int month, int day);

private:
  void CC(int ret);

private:
  sqlite3* m_sqlite3 = nullptr;
};

} // namespace l4w

#endif