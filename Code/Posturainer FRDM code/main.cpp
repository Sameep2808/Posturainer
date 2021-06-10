#include "mbed.h"
#include "FXOS8700Q.h"
FXOS8700Q_acc acc( PTE25, PTE24, FXOS8700CQ_SLAVE_ADDR1);
FXOS8700Q_mag mag( PTE25, PTE24, FXOS8700CQ_SLAVE_ADDR1);
Serial pc(USBTX, USBRX);
Serial bt(PTC17, PTC16);// TX, RX
MotionSensorDataUnits mag_data;
MotionSensorDataUnits acc_data;
DigitalIn sw2(SW3);
DigitalOut r(LED1);
DigitalOut g(LED2);
DigitalOut b(LED3);
DigitalOut m1(PTD0);//BR
DigitalOut m2(PTD2);//TR
DigitalOut m3(PTD3);//BL
DigitalOut m4(PTD1);//TL
DigitalOut bth(PTB18);
float ix,iy,iz,c=0,x,y,z;
char in='0';
int ch=0;
int main()
{
    bt.baud(115200);
    pc.baud(115200);
    
    r=0;b=0;g=0;bth=5;
    m1=1;m2=1;m3=1;m4=1;
 
    while(1)
    {
    if((c==0)&&(bt.readable())){
        in=bt.getc();
        pc.printf("%c",in);
        }
        
    if((sw2==0)||(in!='0'))
    {   r=1;b=0;g=1;
        acc.enable();
        acc.getAxis(acc_data);
        pc.printf("Callibration\n");
        wait(3);
        ix=acc_data.x;iy=acc_data.y;iz=acc_data.z;
        pc.printf("INITIAL: X=%1.4f Y=%1.4f Z=%1.4f  ", ix, iy, iz);
        pc.printf("Callibrated\n");
        c=1;ch=0;in='0';
    }
    if((c==1)&&(sw2==1))
    {
        
        acc.enable();
        acc.getAxis(acc_data);
        //pc.printf("ACC: X=%1.4f Y=%1.4f Z=%1.4f  ", acc_data.x, acc_data.y, acc_data.z);
        x=abs(ix-acc_data.x);y=abs(iy-acc_data.y);z=abs(iz-acc_data.z);
        if(((x>=0.3)&&(x<=0.7))||((y>=0.3)&&(y<=0.7))||((z>=0.3)&&(z<=0.7)))//BR TR BL TL
        {   
            r=0;g=1;b=1;
            m1=0;m2=0;m3=0;m4=0;
            if(x<=-0.4){
                if(y<=-0.4){
                    m1=0;m2=5;m3=0;m4=0;}
                else if(y>=0.4){
                    m1=5;m2=0;m3=0;m4=0;}
                else{
                    m1=5;m2=5;m3=0;m4=0;}}
            else if(x>=0.4){
                if(y<=-0.4){
                    m1=0;m2=0;m3=0;m4=5;}
                else if(y>=0.4){
                    m1=0;m2=0;m3=5;m4=0;}
                else{
                    m1=0;m2=0;m3=5;m4=5;}}
            
            if(y<=-0.4){
                if(x<=-0.4){
                    m1=0;m2=0;m3=5;m4=0;}
                else if(x>=0.4){
                    m1=5;m2=0;m3=0;m4=0;}
                else{
                    m1=5;m2=0;m3=5;m4=0;}}
            else if(y>=0.4){
                if(x<=-0.4){
                    m1=0;m2=0;m3=0;m4=5;}
                else if(x>=0.4){
                    m1=0;m2=0;m3=5;m4=0;}
                else{
                    m1=0;m2=0;m3=5;m4=5;}}
        }
        else
        {   
            r=1;g=0;b=1;
            m1=1;m2=1;m3=1;m4=1;  
        }    
    }
    }
}