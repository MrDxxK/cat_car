/*******已使用的接口********
 D:2,3,5,6,7,8,0,1,10,11
 A:0,1,2,3,6,7(在autodriver里使用)
 ***************************/
#include <Microduino_Motor.h>
#include <Adafruit_NeoPixel.h>
#include"music.h"


#define motor_pin0A 6  //PWM
#define motor_pin0B 8
#define motor_pin1A 5  //PWM
#define motor_pin1B 7
const int led_pin=2;


Motor MotorRight(motor_pin0A, motor_pin0B);
Motor MotorLeft(motor_pin1A, motor_pin1B);
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, led_pin, NEO_GRB + NEO_KHZ800);


void colorWipe(uint32_t c, uint8_t wait);


class car
{
 friend class autodriver;
 public:
    car():publicsped(255){};
    void change_sped(uint8_t sped)
      {
           publicsped=sped;
      }
     void towards()
     {
       MotorLeft.Driver(publicsped);
       MotorRight.Driver(publicsped);
     }
     void backwards()
     {
      MotorLeft.Driver(-publicsped);
      MotorRight.Driver(-publicsped);
     }
      void brake()
     {
      MotorLeft.Brake();
       MotorRight.Brake();
     }
     void Left()
     {
      MotorLeft.Driver(publicsped/2);
      MotorRight.Driver(publicsped);
     }
     void Left(int left,int right)
     {
      MotorLeft.Driver(left);      
      MotorRight.Driver(right);
     }
     void Right()
     {
      MotorLeft.Driver(publicsped);
      MotorRight.Driver(publicsped/2);
     }
     void Right(int left,int right)
     {
      MotorLeft.Driver(left);
      MotorRight.Driver(right);
     }     
     void car_stop()
     {
       MotorLeft.Free();
       MotorRight.Free();
     }
 private:
    uint8_t publicsped;//初始满速
                       //[-255,255]
};


class autodriver
{
  public:
  autodriver():sensorValueL(0),sensorValueR(0){};
  void autotrack(car &myCar)
  {
    
    if(check())
         myCar.towards();//nothing
    else 
    {
      if(sensorValueL>offlineL&&sensorValueLL<onlineLL)//一级转向
          myCar.Left(20,180);
      else if(sensorValueLL>offlineLL)//急转
          myCar.Left(-80,120);
      else if(sensorValueR>offlineR&&sensorValueRR<onlineRR)
            myCar.Right(180,20);
      else if(sensorValueRR>offlineRR)
          myCar.Right(120,-80);
      else 
          myCar.towards();
    }
  }
  private:
  //line.Finder
  //有两个传感器，一个在左侧，一个在右侧
  //左侧传感器为A0
  //右侧为A2
  unsigned long lasttimer=0,thistimer=0;
  int sensorValueL,sensorValueR;//第一级传感器 L:A0,R:A2
  int sensorValueLL,sensorValueRR;//第二级传感器  LL:A6,RR:A7
  const int onlineL=570,offlineL=680;//当时再测量！！！这个是传感器在白色下的阈值
  const int onlineR=650,offlineR=750;//同上，在黑色下的阈值
  const int onlineLL=550,offlineLL=720;
  const int onlineRR=445,offlineRR=470;
  
  inline void receive()
    {
      sensorValueL=analogRead(A0);
      sensorValueR=analogRead(A2);
      sensorValueLL=analogRead(A6);
      sensorValueRR=analogRead(A7);
      /*
      Serial.print(sensorValueLL);
      Serial.print(" ");
      Serial.print(sensorValueL);
      Serial.print(" ");
      Serial.print(sensorValueR);
      Serial.print(" ");
      Serial.println(sensorValueRR);*/
      delay(1);//为了稳定
    }
  inline bool check()//检查是否在线上,若在，则返回true，向左/右 偏则返回false，详细行走函数用sensorValueL/R控制
  {
   receive();
   if(sensorValueL<=onlineL&&sensorValueR<=onlineR)
        return true;
   else 
        return false;
  }
  /*
void motorsped(uint8_t &lsped,uint8_t &rsped)//返回的是左轮转速，rsped是右轮转速
                            //直接返回转速
  {
    if(check());//如果在线上，什么也不做
    else
    {
      while(sensorValueL>offline)//小车左侧感应器碰到黑线
        {
          
        }
    }
  }*/
};


class BToth
{
  public:
  BToth():msg(""){};
  void control(car &myCar)
  {
    receive();
    go(myCar);
  }
  private:
  void receive()
  {
    if (Serial.available() > 0)  //如果串口有数据输入
    {
    msg = Serial.readStringUntil('\n'); //获取换行符前所有的内容
    //Serial.println("^_^ Hello,mCookie!");  //向蓝牙通信的另一端发送数据
    }
  }
  void play_cat()
  {
     song_play();
  }
  void warning()
  {
   
    colorWipe(strip.Color(255, 0, 0), 1); // Red
    colorWipe(strip.Color(0, 0, 0), 5); // Red;
    colorWipe(strip.Color(0, 255, 0), 1); // Green
    colorWipe(strip.Color(0, 0, 0), 5); // Red
    colorWipe(strip.Color(0, 0, 255), 1); // Blue
    colorWipe(strip.Color(0, 0, 0), 1); // Red
   
  }
  void go(car &myCar)
  {
    if(msg=="w")//向前
      myCar.towards();
    else if(msg=="a")//left
       myCar.Left();
    else if(msg=="d")//right
      myCar.Right();
    else if(msg=="s")//back
      myCar.backwards();
    else if(msg=="b")
      myCar.brake();//brake
    else if(msg=="p")//逗猫
      {
        play_cat();
        play_cat();
        play_cat();
        msg="";
      }
    else if(msg=="auto")
    {
      autodriver robot;                        //以后调用autotrack之前先改变公共速度
      myCar.change_sped(100);//这样可以避免速度过快小车由于惯性冲出了可识别路径，也可以使小车在转弯时有足够的速度不至于转不过去。
      robot.autotrack(myCar);
    }
    else if(msg=="n")
      warning();
  }
  String msg;
  
};



void setup() {
  Serial.begin(9600);  //初始化
  //Serial.println("Microduino!");
  MotorLeft.Fix(1);
  MotorRight.Fix(1);
  pinMode(buzzer_pin, OUTPUT);
  strip.begin();
  strip.show();
}



BToth iphone;
car myCar;



void loop()
{
 iphone.control(myCar);
 /****调试代码*********
      autodriver robot;                        //以后调用autotrack之前先改变公共速度
      myCar.change_sped(100);//这样可以避免速度过快小车由于惯性冲出了可识别路径，也可以使小车在转弯时有足够的速度不至于转不过去。
      robot.autotrack(myCar);
***********************/
}



void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

