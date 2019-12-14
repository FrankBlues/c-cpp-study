//stock class declaration with constructors,destructors
#ifndef STOCK1_H_
#define STOCK1_H_

class Stock //class declaration
{
  private:
    char company[30];
    int shares;
    double share_val;
    double total_val;
    void set_tot() { total_val = shares * share_val; } //inline

  public:
    Stock(); //default constructor
    Stock(const char *co, int n = 0, double pr = 0.0);
    ~Stock(){}; //do nothing
    void buy(int num, double price);
    void sell(int num, double price);
    void update(double price);
    void show() const; //声明该方法不会改变对象
    const Stock &topval(const Stock &s) const;
};

#endif