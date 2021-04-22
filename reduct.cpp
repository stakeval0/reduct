#include<stdlib.h>
#include<string.h>
#include<sys/ioctl.h>
#include<unistd.h>
#include<iostream>
#include<vector>
#include"ratio.h"
using namespace std;
const ratio R_ZERO=0;
void swap(int n,int m,vector<vector<ratio>> &a,int i){
  if(i<n-1){
    vector<ratio> b=a[i];
    for(int j=i;j<n-1;j++){
      a[j]=a[j+1];
    }
    a[n-1]=b;
  }
}
void sort(int n,int m,vector<vector<ratio>> &a,int i0,int j0){
  int i,j,end=i0,counter;
  for(j=j0;end<n-1&&j<m;j++){
    counter=0;
    for(i=n-1;i>=end;i--){
      if(a[i][j]==R_ZERO){
        swap(n,m,a,i);
      }else{
        counter++;
      }
    }
    end+=counter;
  }
}
void dec(vector<ratio> &a,vector<ratio> &b,int init){
  for(int i=init;i<a.size();i++){
    a[i]-=b[i];
  }
}
void times(vector<ratio> &a,int init,ratio k){
  for(int i=init;i<a.size();i++){
    a[i]*=k;
  }
}
void divide(vector<ratio> &a,int init,ratio k){
  for(int i=init;i<a.size();i++){
    a[i]/=k;
  }
}
void reduct(int n,int m,vector<vector<ratio>> &a){
  int i,j,init;ratio a0,a1;
  sort(n,m,a,0,0);
  for(init=0,j=0;init<n&&j<m;j++){
    if(a[init][j]!=R_ZERO){
      a0=a[init][j];divide(a[init],j,a0);
      for(i=init+1;i<n;i++){
        if(a[i][j]!=R_ZERO){
          a1=a[i][j];
          divide(a[i],j,a1);
          dec(a[i],a[init],j);
        }
      }
      sort(n,m,a,init,j);
      for(i=init-1;i>=0;i--){
        if(a[i][j]!=R_ZERO){
          a1=a[i][j];
          times(a[init],j,a1);
          dec(a[i],a[init],j);divide(a[init],j,a1);
        }
      }
      init++;
    }
  }
}
char analysis(int m,vector<ratio> &a,const char *s,int *j){
  int i,k=0;char result='\0';bool space=true,nSlash=true,noNum=true;
  for(i=0;s[i]!='\0'&&*j<m;i++){
    if(s[i]==' '){
      space=true;
    }else if(s[i]=='/'){
      nSlash=false;
    }else if(s[i]>='0'&&s[i]<='9'||s[i]=='-'){
      if(space){
        if(nSlash){
          a[(*j)++]=ator(s+i);
          noNum=false;
        }
        space=false;
      }
      nSlash=true;
    }else if(s[i]!='.'){
      result=s[i];break;
    }
  }
  if(!noNum){
    (*j)--;
  }
  return result;
}
int termnlWid(void){
  struct winsize ws;
  if(ioctl(STDOUT_FILENO,TIOCGWINSZ,&ws)!=-1){
    return ws.ws_col;
  }
}
int cMax(int n,int m,vector<vector<ratio>> &a,int j){
  int i,maxLen=a[0][j].to_s().length(),length;
  if(j<m){
    for(i=1;i<n;i++){
      length=a[i][j].to_s().length();
      if(maxLen<length){
        maxLen=length;
      }
    }
    return maxLen;
  }
}
void output(int n,int m,vector<vector<ratio>> &a){
  int i,j,aLen[m]={};
  for(j=0;j<m;j++){
    aLen[j]=cMax(n,m,a,j);
  }
  printf("\n");
  for(i=0;i<n;i++){
    for(j=0;j<m;j++){
      printf("%*s ",aLen[j],a[i][j].to_s().c_str());
    }
    printf("\n");
  }
}
int main(int argc,char *argv[]){
  if(argc!=3){
    printf("usage: %s [the number of row] [the number of column]\n",argv[0]);
    return 0;
  }
  //input関数を小分けに作った方が良かったかもしれない。
  int n=atoi(argv[1]),m=atoi(argv[2]),i,j,k,lenSum,promptLen;
  vector<vector<ratio>> a(n,vector<ratio>(m));char cmd=0;string s;
  for(i=0;i<n;i++){
    lenSum=0;
    for(j=0;j<m;j++){
      promptLen=printf("a_{%d,%d}> ",i+1,j+1);getline(cin,s);
      cmd=analysis(m,a[i],s.c_str(),&j);
      lenSum+=s.length()+promptLen+1;
      lenSum%=termnlWid();
      for(k=0;k<lenSum;k++){
        printf(" ");
      }
      printf("\033[1A");
      if(cmd!='\0'){
        if(cmd!='u'&&cmd!='r'||i==0&&j==0){
          printf("\nyour input is inappropriate!\n");
          printf("inputted letter must be only number, u for undo or r for reRow.\n");
          printf("also, you can't use \"u\" and \"r\" for a_{1,1}.\n");
          printf("please input again.\n");
          j--;
        }else if(cmd=='r'){
          i-=1+(m-j)/m;j=0;break;
        }else{
          printf("\n");
          i-=(m-j)/m;j=(m-1+j)%m-1;
        }
        lenSum=0;
        for(k=0;k<j+1;k++){
          lenSum+=printf("a_{%d,%d}> %s ",i+1,k+1,a[i][k].to_s().c_str());
        }
      }
    }
    printf("\n");
  }
  reduct(n,m,a);
  output(n,m,a);
  return 0;
}