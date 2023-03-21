#include<iostream>
using namespace std;

int main(){


    int a[10],b[10],p1,p2,p3;

    cout<<"enter the four bits"<<endl;

    cin>>a[3];
    cin>>a[5];
    cin>>a[6];
    cin>>a[7];


    a[1]=a[3]^a[5]^a[7];
     a[2]=a[3]^a[6]^a[7];
      a[4]=a[5]^a[6]^a[7];

      for(int i=1;i<8;i++){

        cout<<"\t"<<a[i];
      }

cout<<endl;
  //reciver side

  cout<<"Enter the 7 bits"<<endl;

  for(int i=1;i<8;i++){

    cin>>b[i];
  }   

  p1=b[1]^b[3]^b[5]^b[7];
  p2=b[2]^b[3]^b[6]^b[7];
  p3=b[4]^b[5]^b[6]^b[7];

  //index at error is

  int p=p1*1+p2*2+p3*4;

  if(p==0){
    cout<<"there is no eror in the data"<<endl;
  }

  else{
    cout<<"there is error found at position: "<<p;
    if(b[p]==0){
        b[p]=1;
    }

    else {
       b[p]=0;
    }

     for(int i=0;i<7;i++){

        cout<<" \t"<<b[i];
     } 
  }

return 0;

}
