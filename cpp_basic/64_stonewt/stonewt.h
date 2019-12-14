//definition for Stonewt
#ifndef STONEWT_H_
#define STONEWT_H_
class Stonewt
{
  private:
    enum
    {
        Lbs_per_stn = 14
    }; //pounds per stone
    int stone;
    double pds_left;
    double pounds;

  public:
    Stonewt(double lbs);
    Stonewt(int stn, double lbs);
    Stonewt();
    ~Stonewt();
    void show_lbs() const; //pounds
    void show_stn() const; //stone
};

#endif