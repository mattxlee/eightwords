#include <iostream>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "calendar.h"
#include "eightwords.h"

class Arguments
{
  public:
    Arguments(int argc, const char *argv[])
    {
        m_options.add_options()                                                 // all options
                ("help,h", "显示帮助")                                          // --help, -h
                ("year,y", po::value(&year)->default_value(1990), "年")         // --year, -y
                ("month,m", po::value(&month)->default_value(10), "月")         // --month, -m
                ("day,d", po::value(&day)->default_value(10), "日")             // --day, d
                ("hour,H", po::value(&hour)->default_value(7), "小时")          // --hour, -h
                ("sqlite3,s", po::value(&sqlite3File), "Sqlite3数据库文件名称") // --sqlite3, -s
                ;

        po::variables_map vars;
        po::store(po::parse_command_line(argc, argv, m_options), vars);
        po::notify(vars);

        if (vars.count("help") > 0)
        {
            help = true;
        }
    }

    void showHelp()
    {
        std::cout << m_options << std::endl;
    }

  public:
    bool help = false;
    int year;
    int month;
    int day;
    int hour;
    std::string sqlite3File;

  private:
    po::options_description m_options;
};

int main(int argc, const char *argv[])
{
    try
    {
        // 解析参数
        Arguments args(argc, argv);
        if (args.help)
        {
            args.showHelp();
            return 0;
        }

        // 校验参数
        if (args.year < 1920 || args.year > 2019)
        {
            throw std::runtime_error("无效的年(1920-2019)");
        }

        if (args.month < 1 || args.month > 12)
        {
            throw std::runtime_error("无效的月(1-12)");
        }

        if (args.day < 1 || args.day > 31)
        {
            throw std::runtime_error("无效的日(1-31)");
        }

        if (args.hour < 1 || args.hour > 24)
        {
            throw std::runtime_error("无效的小时(1-24)");
        }

        if (args.sqlite3File.empty())
        {
            throw std::runtime_error("请指定Sqlite3本地数据库文件");
        }

        // 转换中文日期
        Calendar calendar(args.sqlite3File);
        CalendarDay chinaDay = calendar.queryChinaDay(args.year, args.month, args.day);

        // 查询时辰
        Table8x2 table;
        CNStringList result = table.analyze(chinaDay.chinaYear, chinaDay.chinaMonth, chinaDay.chinaDay, args.hour);

        // 输出八字
        for (const CNString &str : result)
        {
            for (const CNChar &ch : str)
            {
                std::cout << ch;
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    catch (std::exception &except)
    {
        std::cerr << "错误: " << except.what() << std::endl;
    }
    return 0;
}
