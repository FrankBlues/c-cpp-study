#ifndef FOLDER_H
#define FOLDER_H

#include <iostream>
#include "Message.h"

class Folder
{
    friend void swap(Folder &, Folder &);
    friend class Message;
public:
    Folder() = default;
    Folder(const Folder &);
    Folder& operator=(const Folder &);
    ~Folder();

    void print_debug();
    void addMsg(Message *m) { msgs.insert(m); }
    void remMsg(Message *m) { msgs.erase(m); }

private:
    std::set<Message*> msgs;

    void add_to_Message(const Folder&);
    void remove_from_Message();


};


#endif