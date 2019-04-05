//Time class before operator overloading
#ifndef MYTIME0_H_
#define MYTIME0_H_
#include <iostream>
class Time
{
private:
  int hours;
  int minutes;

public:
  Time();
  Time(int h, int m = 0);
  void AddMin(int m);
  void AddHr(int h);
  void Reset(int h = 0, int m = 0);
  //Time sum(const Time &t) const;
  Time operator+(const Time &t) const; //op overload
  Time operator-(const Time &t) const; //op overload
  Time operator*(double n) const;      //op overload only Time*n
  friend Time operator*(double m, const Time &t) //inline definition
  {
    return t * m;
  }
  friend std::ostream &operator<<(std::ostream &os, const Time &t);
};

#endif