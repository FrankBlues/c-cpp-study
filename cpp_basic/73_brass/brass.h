//bank account classes

#ifndef BRASS_H_
#define BRASS_H_
class Brass
{
  private:
    enum
    {
        MAX = 35
    };
    char fullName[MAX];
    long acctNum;
    double balance;

  public:
    Brass(const char *s = "Nullbody", long an = -1,
          double bal = 0.0);
    void Deposit(double amt);
    //虚方法，如果没有virtual 程序将根据引用类型或指针类型选择方法；
    //使用了virtual 程序将根据引用或指针指向的对象的类型来选择方法
    virtual void Withdraw(double amt);
    double Balance() const;
    virtual void ViewAcct() const;
    //虚拟析构函数
    virtual ~Brass() {}
};

//Brass Plus Account Class
class BrassPlus : public Brass
{
  private:
    double maxLoan;
    double rate;
    double owesBank;

  public:
    BrassPlus(onst char *s = "Nullbody", long an = -1,
              double bal = 0.0, double ml = 500, double r = 0.1);
    BrassPlus(const Brass &ba, double ml = 500, double r = 0.1);
    //在基类中被声明虚拟后，在派生类自动生成虚方法
    //可以不指定virtual
    virtual void ViewAcct() const;
    virtual void Withdraw(double amt);
    void ResetMax(double m) { maxLoan = m; }
    void ResetRate(double r) { rate = r; }
    void ResetOwes() { owesBank = 0; }
}
#endif