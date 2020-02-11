#include <vector>
#include <string>
using std::string;
#include "Screen.h"

class Window_mgr
{
public:
    // 窗口中每个屏幕的编号
    using ScreenIndex = std::vector<Screen>::size_type;
    // 按照编号将指定的Screen重置为空白
    void clear(ScreenIndex);
    // 添加一个screen,返回编号
    // 返回类型需要指定作用域
    ScreenIndex addscreen(const Screen&);
private:
    // 默认 一个Window_mgr包含一个标准尺寸的空白Screen
    std::vector<Screen> screens{Screen(24, 80, ' ')};
};

void Window_mgr::clear(ScreenIndex i)
{
    // s是一个Screen的引用，指向我们想清空的那个屏幕
    Screen &s = screens[i];
    s.contents = string(s.height*s.width, ' ');
}

Window_mgr::ScreenIndex Window_mgr::addscreen(const Screen &s)
{
    screens.push_back(s);
    return screens.size() - 1;
}