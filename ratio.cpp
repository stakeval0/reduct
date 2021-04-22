#include"ratio.h"
#include<stdio.h>
using namespace std;
const int INT_MIN=-2147483648;
const int INT_MAX=2147483647;
static int gcd(int x,int y){
  while(true){
    if(x > y){
      x%=y;
      if(x == 0){
        return y;
      }
    }else{
      y%=x;
      if(y == 0){
        return x;
      }
    }
  }
}
static void ftoiPair(double &x,double &y){//型変換もするので注意!
  while(x!=(int)x&&x>=INT_MIN&&x<=INT_MAX){
    x*=10;y*=10;
  }
  while(y!=(int)y&&y>=INT_MIN&&y<=INT_MAX){
    x*=10;y*=10;
  }
  if(x!=(int)x||y!=(int)y){
    fprintf(stderr,"ratio.h: Can't convert %f to int.\n",x!=(int)x?x:y);exit(1);
  }else{
    x=(int)x;y=(int)y;
  }
}
void ratio::init(void){
  if(deno==0){
    deno=1/deno;
  }
  if(nume==0){
    deno=1;return;
  }
  if(deno<0){
    nume*=-1;deno*=-1;
  }
  int g=gcd(abs(nume),abs(deno));
  nume/=g;deno/=g;
}
ratio::ratio(void):nume(1),deno(1){}
ratio::ratio(double n,double m){
  ftoiPair(n,m);
  nume=n;deno=m;
  init();
}
int ratio::getNume(void)const{
  return nume;
}
int ratio::getDeno(void)const{
  return deno;
}
string ratio::to_s(void){
  return deno==1?to_string(nume):to_string(nume)+"/"+to_string(deno);
}
ratio &ratio::operator=(const ratio &x){
  nume=x.nume;deno=x.deno;
  return *this;
}
ratio &ratio::operator+=(const ratio &x){
  *this=*this+x;
  return *this;
}
ratio &ratio::operator-=(const ratio &x){
  *this=*this-x;
  return *this;
}
ratio &ratio::operator*=(const ratio &x){
  *this=*this*x;
  return *this;
}
ratio &ratio::operator/=(const ratio &x){
  *this=*this/x;
  return *this;
}
ratio ator(const char *s){
  int i;double a,b;bool space=false;
  a=atof(s);
  for(i=0;s[i]==' ';i++){}
  if(s[i]!='\0'&&s[i+1]!='\0'){
    for(i;s[i]!='/'&&s[i+2]!='\0';i++){
      if(s[i]==' '){
        space=true;
      }else if(space&&(s[i]>='0'&&s[i]<='9'||s[i]=='-')){
        break;
      }
    }
  }
  s[i]=='/'?b=atof(s+i+1):b=1;
  ratio x(a,b);
  return x;
}
ratio operator+(const ratio &x1,const ratio &x2){
  ratio x((double)x1.getNume()*x2.getDeno()+(double)x2.getNume()*x1.getDeno(),(double)x1.getDeno()*x2.getDeno());
  return x;
}
ratio operator-(const ratio &x1,const ratio &x2){
  ratio x((double)x1.getNume()*x2.getDeno()-(double)x2.getNume()*x1.getDeno(),(double)x1.getDeno()*x2.getDeno());
  return x;
}
ratio operator*(const ratio &x1,const ratio &x2){
  ratio x((double)x1.getNume()*x2.getNume(),(double)x1.getDeno()*x2.getDeno());
  return x;
}
ratio operator/(const ratio &x1,const ratio &x2){
  ratio x((double)x1.getNume()*x2.getDeno(),(double)x1.getDeno()*x2.getNume());
  return x;
}
bool operator==(const ratio &x1,const ratio &x2){
  return x1.getNume()==x2.getNume()&&x1.getDeno()==x2.getDeno()?true:false;
}
bool operator!=(const ratio &x1,const ratio &x2){
  return !(x1==x2);
}