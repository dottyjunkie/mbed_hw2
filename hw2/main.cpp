#include "mbed.h"


BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);

char table[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

Serial pc( USBTX, USBRX );

AnalogOut Aout(DAC0_OUT);

AnalogIn Ain(A0);


int sample = 1000;

int i;


float ADCdata[1000];

int main(){
//
    for (i = 0; i < sample; i++){

    Aout = Ain;

    ADCdata[i] = Ain;

    wait(1./sample);

  }
wait(3.0);

int t1=0;
bool p1=false;
bool p2=false;
int i=500;
int freq=0;
int t2=0;
int ans[3];
while(freq==0){
    if(ADCdata[i-1]<ADCdata[i] && ADCdata[i+1]<ADCdata[i]){
        if(p1==false){
            t1=i;
            p1=true;
        }
        else if(p1==true){
            t2=i;
            p2=true;
        }
    }
    

    if(p2==1){
        freq=1/((t2-t1+1)*0.001);
    }
    i++;

}
if(freq>0){
    ans[0]=freq/100;
    ans[1]=(freq-ans[0]*100)/10;
    ans[2]=(freq-ans[0]*100-ans[1]*10);
  while(1){

    for (int i = 0; i<3; i++){

      display = table[ans[i]];

      wait(1);

    }

  }
  //
}
}