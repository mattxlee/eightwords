# 八字排盘源代码

## 用途

将英文年、月、日、时进行八字排盘。例如：输入 `1990-10-10 7时` 将输出：“庚午 丙戌 戊申 丙辰”

## 编译及环境需求

### 库需求

* libiconv - 字符集转换，此库必须要有

*下方两个库只在要求编译测试目标的时候才需要*

* sqlite3 - 从sqlite3数据库中查询农历日期，测试目标才需要，因为测试用例会读取 calendar.db 来获取对照数据

* googletest - 如果你要编译测试目标的话，那么测试框架库肯定不能少

### 编译步骤

因为已经添加了 vcpkg 作为项目的子模块作为包管理器，并且在项目的根目录下的 vcpkg.json 文件中已经说明了依赖库，所以最简单的办法就是直接添加 CMAKE_TOOLCHAIN_FILE 指向子模块中的 vcpkg.cmake 来下载、安装和编译。

1. 先将项目克隆到本地，同时也初始化子模块

```bash
git clone https://github.com/mattxlee/eightwords && cd eightwords && git submodule update --init
```

2. 使用 vcpkg 来作为包管理器，让 cmake 脚本开始配置并准备当前平台的编译文件

  * 下方命令会在当前的项目根目录下建立名为 build 的目录，所有编译输出的文件都将存在这个目录下

  * 若不想编译测试目标，可以把 `-DBUILD_TEST=1` 删除

```bash
cmake . -B build -DCMAKE_TOOLCHAIN_FILE=`pwd/vcpkg/scripts/buildsystems/vcpkg.cmake -DBUILD_TEST=1
```

3. 执行下方的命令开始编译，注意调整 `-j7` 防止 CPU 过热 🙈

```bash
cmake --build build -j7
```

注：若要编译非优化且带调试信息的版本，请在配置时添加 `-DCMAKE_BUILD_TYPE=Debug`

## 使用说明

1. 所有的与库相关的符号说明都在命名空间 `l4w` 里

2. 八字排盘的转换对象请查看 [include/eightwords.h](include/eightwords.h)，其实只有一个方法：`Table8x2::analyze`

3. 本库并不提供农历转换工具，但是提供了一个数据库，这个数据库中有一段时间（将近十年）的阳历和农历的对照表，保存在 [data/calendar.db](data/calendar.db)，是 sqlite3 格式

4. 具体的细节请参考 [test/test.cpp](test/test.cpp)

## 注

注：这个排盘的算法是曾经的我的一个朋友教的，但是现在的我已经完全忘记了🫠。不过我想在代码输出正确的情况下你们应该不会介意这件事情🙂，毕竟这个世界不存在过不去的坎，也不存在忘不掉的事。现在的我，也就只能对代码做一些修补和优化，稍微的保证一下它的合理性和鲁棒性吧，完结撒花👏🎉🎉。

再注：其实本来想把中文日历转换加上的，但是后来想想这个功能和八字排盘其实没太大关系，所以删除掉了，但是留了一个古老的数据库来作为排盘程序的结果验证👏。
