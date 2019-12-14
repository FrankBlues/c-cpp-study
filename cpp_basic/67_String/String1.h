//string class definition . bad example
#include <iostream>
#ifndef STRING1_H_
#define STRING1_H_
class String1
{
private:
  char *str;
  int len;
  static int num_strings;       //number of objects
  static const int CINLIM = 80; //cin input limit or enum {CINLIM = 80}
public:
  String1(const char *s);
  String1();
  String1(const String1 &); //copy constructor
  ~String1();

  int length();
  //overload operator methods
  String1 &operator=(const String1 &);
  String1 &operator=(const char *);
  char &operator[](int i);
  const char &operator[](int i) const;

  //overload operator friends
  friend bool operator<(const String1 &st1, const String1 &st2);
  friend bool operator>(const String1 &st1, const String1 &st2);
  friend bool operator==(const String1 &st1, const String1 &st2);

  friend std::ostream &operator<<(std::ostream &os, const String1 &st);
  friend std::istream &operator>>(std::istream &is, String1 &st);

  //static function
  static int HowMany();
};

#endif