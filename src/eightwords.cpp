#include "eightwords.h"
#include "face_converter.h"

#include <algorithm>
#include <stdexcept>

namespace l4w {

CNString splitChineseString(std::string const& src) {
  CNString result;
  Convertor conv(face_utf8, face_gb2312);
  Convertor conv2(face_gb2312, face_utf8);
  std::string gb2312 = conv.convert(src);
  for (std::size_t i = 0; i < gb2312.size(); i += 2) {
    char chs[3] = { gb2312[i], gb2312[i + 1], '\0' };
    auto str = conv2.convert(chs);
    result.push_back(str);
  }
  return result;
}

Table8x2::Table8x2() {
  // 甲子 丙子 戊子 庚子 壬子
  _dayTable["子"] = { { { "甲", "己" }, "甲" }, { { "乙", "庚" }, "丙" },
    { { "丙", "辛" }, "戊" }, { { "丁", "壬" }, "庚" },
    { { "戊", "癸" }, "壬" } };
  // 乙丑 丁丑 己丑 辛丑 癸丑
  _dayTable["丑"] = { { { "甲", "己" }, "乙" }, { { "乙", "庚" }, "丁" },
    { { "丙", "辛" }, "己" }, { { "丁", "壬" }, "辛" },
    { { "戊", "癸" }, "癸" } };
  // 丙寅 戊寅 庚寅 壬寅 甲寅
  _dayTable["寅"] = { { { "甲", "己" }, "丙" }, { { "乙", "庚" }, "戊" },
    { { "丙", "辛" }, "庚" }, { { "丁", "壬" }, "壬" },
    { { "戊", "癸" }, "甲" } };
  // 丁卯 己卯 辛卯 癸卯 乙卯
  _dayTable["卯"] = { { { "甲", "己" }, "丁" }, { { "乙", "庚" }, "己" },
    { { "丙", "辛" }, "辛" }, { { "丁", "壬" }, "癸" },
    { { "戊", "癸" }, "乙" } };
  // 戊辰 庚辰 壬辰 甲辰 丙辰
  _dayTable["辰"] = { { { "甲", "己" }, "戊" }, { { "乙", "庚" }, "庚" },
    { { "丙", "辛" }, "壬" }, { { "丁", "壬" }, "甲" },
    { { "戊", "癸" }, "丙" } };
  // 己巳 辛巳 癸巳 乙巳 丁巳
  _dayTable["巳"] = { { { "甲", "己" }, "己" }, { { "乙", "庚" }, "辛" },
    { { "丙", "辛" }, "癸" }, { { "丁", "壬" }, "乙" },
    { { "戊", "癸" }, "丁" } };
  // 庚午 壬午 甲午 丙午 戊午
  _dayTable["午"] = { { { "甲", "己" }, "庚" }, { { "乙", "庚" }, "壬" },
    { { "丙", "辛" }, "甲" }, { { "丁", "壬" }, "丙" },
    { { "戊", "癸" }, "戊" } };
  // 辛未 癸未 乙未 丁未 己未
  _dayTable["未"] = { { { "甲", "己" }, "辛" }, { { "乙", "庚" }, "癸" },
    { { "丙", "辛" }, "乙" }, { { "丁", "壬" }, "丁" },
    { { "戊", "癸" }, "己" } };
  // 壬申 甲申 丙申 戊申 庚申
  _dayTable["申"] = { { { "甲", "己" }, "壬" }, { { "乙", "庚" }, "甲" },
    { { "丙", "辛" }, "丙" }, { { "丁", "壬" }, "戊" },
    { { "戊", "癸" }, "庚" } };
  // 癸酉 乙酉 丁酉 己酉 辛酉
  _dayTable["酉"] = { { { "甲", "己" }, "癸" }, { { "乙", "庚" }, "乙" },
    { { "丙", "辛" }, "丁" }, { { "丁", "壬" }, "己" },
    { { "戊", "癸" }, "辛" } };
  // 甲戌 丙戌 戊戌 庚戌 壬戌
  _dayTable["戌"] = { { { "甲", "己" }, "甲" }, { { "乙", "庚" }, "丙" },
    { { "丙", "辛" }, "戊" }, { { "丁", "壬" }, "庚" },
    { { "戊", "癸" }, "壬" } };
  // 乙亥 丁亥 己亥 辛亥 癸亥
  _dayTable["亥"] = { { { "甲", "己" }, "乙" }, { { "乙", "庚" }, "丁" },
    { { "丙", "辛" }, "己" }, { { "丁", "壬" }, "辛" },
    { { "戊", "癸" }, "癸" } };
  // 时间对应
  _hourToCnHour = { { 23, "子" }, { 1, "丑" }, { 3, "寅" }, { 5, "卯" },
    { 7, "辰" }, { 9, "巳" }, { 11, "午" }, { 13, "未" }, { 15, "申" },
    { 17, "酉" }, { 19, "戌" }, { 21, "亥" } };
}

CNStringList Table8x2::analyze(std::string const& cn_year,
    std::string const& cn_month, std::string const& cn_day, int hour) {
  _8x2.push_back(splitChineseString(cn_year));
  _8x2.push_back(splitChineseString(cn_month));
  _8x2.push_back(splitChineseString(cn_day));
  // 根据时间推算时辰
  for (HourToCNHour::const_iterator i = _hourToCnHour.begin();
       i != _hourToCnHour.end(); ++i) {
    if (hour >= i->first && hour < i->first + 2) {
      _8x2.push_back({ "", i->second });
    }
  }
  // 23:00的数据单独在这里加上
  if (_8x2.size() < 4)
    _8x2.push_back({ "", _hourToCnHour[23] });
  // 计算第7个字
  auto rec = _dayTable[_8x2[3][1]];
  bool found = false;
  for (auto i = rec.begin(); i != rec.end(); ++i) {
    auto it = std::find(i->index.begin(), i->index.end(), _8x2[2][0]);
    if (it != i->index.end()) {
      // 找到，填充完成
      found = true;
      _8x2[3][0] = i->value;
    }
  }
  if (!found) {
    throw std::runtime_error("无法计算出八字中的第七个字");
  }
  // 返回
  return _8x2;
}

} // namespace l4w