#ifndef RATIO_H
#define RATIO_H
#include<string>
using namespace std;
class ratio{
  protected:
    int nume,deno;
    void init(void);
  public:
    ratio(void);
    ratio(double n,double m=1);
    int getNume(void)const;
    int getDeno(void)const;
    string to_s(void);
    ratio &operator=(const ratio &x);
    ratio &operator+=(const ratio &x);
    ratio &operator-=(const ratio &x);
    ratio &operator*=(const ratio &x);
    ratio &operator/=(const ratio &x);
};
ratio ator(const char *s);
ratio operator+(const ratio&,const ratio&);
ratio operator-(const ratio&,const ratio&);
ratio operator*(const ratio&,const ratio&);
ratio operator/(const ratio&,const ratio&);
bool operator==(const ratio&,const ratio&);
bool operator!=(const ratio&,const ratio&);
#endif