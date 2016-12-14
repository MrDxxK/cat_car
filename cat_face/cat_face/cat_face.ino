/***********
蓝牙串口
***********/
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
String msg="";//接受
void decode(const String &str,int &x,int&y,int &lenx,int &leny);
void walk(int &x,int &y,int &lenx,int &leny);
void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0)
    msg=Serial.readStringUntil('\n');
  int x,y,lenx,leny;
  decode(msg,x,y,lenx,leny);//解码并映射到[0,255]
  walk();
}
void walk(int &x,int &y,int &lenx,int &leny)
{
  const int levL=60,levR=180,middle=127;
  const middle_cat=(x+y)/2;
  if(middle_cat<=levL)
     myCar.Left(70,255);
  else if(middle_cat>levL&&middle_cat<middle)
     myCar.Left();
  else if(middle_cat>=middle&&middle_cat<levR)
     myCar.Right();
  else if(middle_cat>=LevR);
     myCar.Right(255,70);
}

