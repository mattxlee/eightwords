#ifndef __L4W_CALENDAR_DATA__
#define __L4W_CALENDAR_DATA__

#include <sqlite3.h>

#include <string>

#include "calendar_type.h"

class Calendar {
public:
    explicit Calendar(const std::string& dbFile);
    ~Calendar();

    CalendarDay queryChinaDay(int year, int month, int day);

private:
    void CC(int ret);

private:
    sqlite3* m_sqlite3 = nullptr;
};

#endif
