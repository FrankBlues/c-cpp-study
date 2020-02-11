#include "Screen.h"

inline  // 在类定义外部设置为内联 
Screen &Screen::move(pos r, pos c)
{
    pos row = r * width;
    cursor = row + c;
    return *this;       // 以左值的形式返回对象
}

char Screen::get(pos r, pos c) const // 在类内部显式内联
{
    pos row = r * width;
    return contents[row + c];
}

