#ifndef SCREEN_H
#define SCREEN_H
#include <iostream>
#include <string>

class Screen
{
    // 把Window_mgr类指定为友元，Window类可访问Screen的私有部分
    // 把整个类声明成友元
    // friend class Window_mgr;
    // 或者把其中一个方法声明成友元
    friend void Window_mgr::clear(Window_mgr::ScreenIndex);
public:
    typedef std::string::size_type pos;
    // using pos = std::string::size_type;
    Screen() = default; // 因为有另一个构造函数,所以需要
    // cursor被其类内初始化为0
    Screen(pos ht, pos wd, char c): height(ht), width(wd),
    contents(ht*wd, c){}
    // 设置光标所在位置
    Screen &set(char);  // 如果返回不是引用 则是*this对象的副本
    Screen &set(pos, pos, char);

    char get() const {return contents[cursor];} //读取光标处字符 隐式内联
    inline char get(pos r, pos c) const; // 显式内联
    Screen &move(pos r, pos c); //能在之后被设为内联

    // 根据对象是否是const重载了display函数
    Screen &display(std::ostream &os){do_display(os); return *this;}
    const Screen &display(std::ostream &os) const {do_display(os); return *this;}
		
	void some_member() const;
private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;

    void do_display(std::ostream &os) const {os << contents;}
	mutable size_t access_ctr = 0; // may change even in a const object
};


// 内联在同一个文件下
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

inline Screen &Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}

inline Screen &Screen::set(pos r, pos col, char ch)
{
    contents[r*width + col] = ch;  // 设置给定位置的新值
    return *this;
}

void Screen::some_member() const
{
	++access_ctr;  // 可以被改变
    std::cout << access_ctr << std::endl;
}

#endif