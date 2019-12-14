//class definition for the stack ADT
#ifndef STACK_H_
#define STACK_H_

typedef unsigned long Item;

class Stack
{
  private:
    enum  //constant specific to class
    {
        MAX = 10
    };               
    Item items[MAX]; //holds stack items
    int top;         //index for top stack item
  public:
    Stack();
    bool isempty() const;
    bool isfull() const;
    bool push(const Item &item); //add item to stack
    bool pop(Item &item);        //pop top into item
};

#endif