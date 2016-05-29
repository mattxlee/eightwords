#ifndef __EIGHT_WORDS_H__
#define __EIGHT_WORDS_H__

#include "eightwords_type.h"

// 八字排盘
class Table8x2
{
  public:
    Table8x2();
    CNStringList analyze(const std::string &cn_year, const std::string &cn_month, const std::string &cn_day, int hour);

  private:
    CNTimeDayTable _dayTable;
    HourToCNHour _hourToCnHour;
    CNStringList _8x2;
};

#endif
