#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <set>

#include "Folder.h"

// class Folder;

class Message
{
    friend class Folder;
    friend void swap(Message &, Message &);
private:
    std::string contents; // actual message text
    std::set<Folder*> folders; // Folders that have this Message
    // utility functions used by copy constructor, assignment, and destructor
    // add this Message to the Folders that point to the parameter
    void add_to_Folders(const Message&);
    // remove this Message from every Folder in folders
    void remove_from_Folders();
    void addFldr(Folder *f) { folders.insert(f); }
    void remFldr(Folder *f) { folders.erase(f); }
public:
    // folders is implicitly initialized to the empty set
    explicit Message(const std::string &str = ""): contents(str) {}
    // copy control to manage pointers to this Message
    Message(const Message&); // copy constructor
    Message& operator=(const Message&); // copy assignment
    ~Message();
    Message(Message &&); // move constructor
    Message& operator=(Message &&);  // move-assignment operator


    void move_Folders(Message *m);  // move the Folder pointers from m to this Message

    // add/remove this Message from the specified Folder's set of messages
    void save(Folder&);
    void remove(Folder&);
};




#endif