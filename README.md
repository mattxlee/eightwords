# 八字排盘源代码

[![Total alerts](https://img.shields.io/lgtm/alerts/g/mattxlee/eightwords.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/mattxlee/eightwords/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/mattxlee/eightwords.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/mattxlee/eightwords/context:cpp)

## 用途
将英文年、月、日、时进行八字排盘。例入：输入1990-10-10 7时（程序默认参数）将输出：“庚午 丙戌 戊申 丙辰”

## 编译及环境需求

### 库需求

* cxxopts - 解析命令行参数使用
* libiconv - 字符集转换使用
* sqlite3 - 从sqlite3数据库中查询农历日期

### 编译步骤

*使用CMake在Linux下或类Unix的环境下进行编译，因为编译过程中需要使用到autotools。在Windows下请使用WSL1/2*

依赖的三个包将由编译脚本自行从网上下载到本地并编译集成到项目中，你所需要做的只是在工程根目录下创建`build`目录，然后在该目录中使用编译指令`cmake .. && cmake --build .`即可。

注：若要编译非优化且带调试信息的版本，请使用`cmake .. -DCMAKE_BUILD_TYPE=Debug`来进行配置。

## 使用说明
编译出来的工具为命令行工具，使用-h或--help将显示以下命令行信息
```
  -h [ --help ]             显示帮助
  -y [ --year ] arg (=1990) 年
  -m [ --month ] arg (=10)  月
  -d [ --day ] arg (=10)    日
  -H [ --hour ] arg (=7)    小时
  -s [ --database ] arg     Sqlite3数据库文件名称
```
需要通过--database参数将日历数据库文件路径传给程序，日历数据库文件名称为calendar.db，保存在工程目录的data目录下

例如，执行如下命令将会把1980年2月10日3点出生的八字排盘
```
build/bin/eightwords_cli --database ./data/calendar.db -y 1980 -m 2 -d 10 -H 3
```

命令结果为
```
庚申 戊寅 癸丑 甲寅
```
