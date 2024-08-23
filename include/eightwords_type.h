#ifndef __EIGHT_WORDS_TYPE_H__
#define __EIGHT_WORDS_TYPE_H__

#include <map>
#include <string>
#include <vector>

/*
 年上起月表.

 月/年 甲己 乙庚 丙辛 丁壬 戊癸
 ------------------------------
 正月 丙寅 戊寅 庚寅 壬寅 甲寅
 二月 丁卯 己卯 辛卯 癸卯 乙卯
 三月 戊辰 庚辰 壬辰 甲辰 丙辰
 四月 己巳 辛巳 癸巳 乙巳 丁巳
 五月 庚午 壬午 甲午 丙午 戊午
 六月 辛未 癸未 乙未 丁未 己未
 七月 壬申 甲申 丙申 戊申 庚申
 八月 癸酉 乙酉 丁酉 己酉 辛酉
 九月 甲戌 丙戌 戊戌 庚戌 壬戌
 十月 乙亥 丁亥 己亥 辛亥 癸亥
 冬月 丙子 戊子 庚子 壬子 甲子
 腊月 丁丑 己丑 辛丑 癸丑 乙丑

 日上起时表：

 时/日 甲己 乙庚 丙辛 丁壬 戊癸
 ------------------------------
 子 甲子 丙子 戊子 庚子 壬子
 丑 乙丑 丁丑 己丑 辛丑 癸丑
 寅 丙寅 戊寅 庚寅 壬寅 甲寅
 卯 丁卯 己卯 辛卯 癸卯 乙卯
 辰 戊辰 庚辰 壬辰 甲辰 丙辰
 巳 己巳 辛巳 癸巳 乙巳 丁巳
 午 庚午 壬午 甲午 丙午 戊午
 未 辛未 癸未 乙未 丁未 己未
 申 壬申 甲申 丙申 戊申 庚申
 酉 癸酉 乙酉 丁酉 己酉 辛酉
 戌 甲戌 丙戌 戊戌 庚戌 壬戌
 亥 乙亥 丁亥 己亥 辛亥 癸亥

 */

// 一个中文文字
typedef std::string CNChar;

// 中文字符串
typedef std::vector<CNChar> CNString;

// 小时对应中国时辰
typedef std::map<int, CNChar> HourToCNHour;

// 中文字符串数组
typedef std::vector<CNString> CNStringList;

// 值
struct CNDayToHour {
  CNString index; // 日对应的索引中文：甲己 乙庚 丙辛 丁壬 戊癸
  CNChar value; // 甲子 丙子 戊子 庚子 壬子 中的甲、丙、戊等
};

// 对照表
typedef std::map<CNChar, std::vector<CNDayToHour>> CNTimeDayTable;

#endif