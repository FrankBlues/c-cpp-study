//Stack member
#include "stack.h"

Stack::Stack() // create an empty stack
{
    top = 0;
}

bool Stack::isempty() const
{
    return top == 0;
}
bool Stack::isfull() const
{
    return top == MAX;
}

bool Stack::push(const Item &item) //add item to stack
{
    if (top < MAX)
    {
        items[top++] = item;
        return true;
    }
    else
        return false;
}

bool Stack::pop(Item &item) //pop top into item
{
    if (top > 0)
    {
        item = items[--top];
        return true;
    }
    else
        return false;
}