#include <iostream>

#include <cxxopts.hpp>

#include "calendar.h"
#include "eightwords.h"

class Arguments {
public:
    Arguments(int argc, const char* argv[]) {
        cxxopts::Options opts("Eight-words", "八字排盘");
        opts.add_options()                                                 // All options
                ("h,help", "Show help")                                    // --help
                ("y,year", "Year", cxxopts::value<int>())                  // --year
                ("m,month", "Month", cxxopts::value<int>())                // --month
                ("d,day", "Day", cxxopts::value<int>())                    // --day
                ("H,hour", "Hour", cxxopts::value<int>())                  // --hour
                ("f,database", "Database", cxxopts::value<std::string>())  // --database
                ;

        cxxopts::ParseResult res = opts.parse(argc, argv);
        if (res.count("help") > 0) {
            help = true;
            std::cout << opts.help() << std::endl;
            return;
        }

        year = res["year"].as<int>();
        month = res["month"].as<int>();
        day = res["day"].as<int>();
        hour = res["hour"].as<int>();
        sqlite3File = res["database"].as<std::string>();
    }

public:
    bool help = false;
    int year;
    int month;
    int day;
    int hour;
    std::string sqlite3File;
};

int main(int argc, const char* argv[]) {
    try {
        // 解析参数
        Arguments args(argc, argv);
        if (args.help) {
            return 0;
        }

        // 校验参数
        if (args.year < 1920 || args.year > 2019) {
            throw std::runtime_error("无效的年(1920-2019)");
        }

        if (args.month < 1 || args.month > 12) {
            throw std::runtime_error("无效的月(1-12)");
        }

        if (args.day < 1 || args.day > 31) {
            throw std::runtime_error("无效的日(1-31)");
        }

        if (args.hour < 1 || args.hour > 24) {
            throw std::runtime_error("无效的小时(1-24)");
        }

        if (args.sqlite3File.empty()) {
            throw std::runtime_error("请指定Sqlite3本地数据库文件");
        }

        // 转换中文日期
        Calendar calendar(args.sqlite3File);
        CalendarDay chinaDay = calendar.queryChinaDay(args.year, args.month, args.day);

        // 查询时辰
        Table8x2 table;
        CNStringList result = table.analyze(chinaDay.chinaYear, chinaDay.chinaMonth, chinaDay.chinaDay, args.hour);

        // 输出八字
        for (const CNString& str : result) {
            for (const CNChar& ch : str) {
                std::cout << ch;
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    } catch (std::exception& except) {
        std::cerr << "错误: " << except.what() << std::endl;
    }
    return 0;
}
