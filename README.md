# 八字排盘源代码

## 用途
将英文年、月、日、时进行八字排盘。例入：输入1990-10-10 7时（程序默认参数）将输出：“庚午 丙戌 戊申 丙辰”

## 编译

### 库需求

#### Boost
解析命令行参数使用

#### iconv
字符集转换使用

#### sqlite3
从sqlite3数据库中查询农历日期

### 编译指令

```
mkdir build
cd build && cmake ..
make
```

## 使用说明
编译出来的工具为命令行工具，使用-h或--help将显示以下命令行信息
```
  -h [ --help ]             显示帮助
  -y [ --year ] arg (=1990) 年
  -m [ --month ] arg (=10)  月
  -d [ --day ] arg (=10)    日
  -H [ --hour ] arg (=7)    小时
  -s [ --sqlite3 ] arg      Sqlite3数据库文件名称
```
需要通过--sqlite3,-s参数将日历数据库文件路径传给程序，日历数据库文件名称为calendar.db，保存在工程目录的data目录下

例如，执行如下命令将会把1980年2月10日3点出生的八字排盘
```
build/eightwords -s ./data/calendar.db -y 1980 -m 2 -d 10 -H 3
```

命令结果为
```
庚申 戊寅 癸丑 甲寅
```
