#define my_Serial Serial //定义串口通讯为Serial

String msg = ""; //定义一个字符串

void setup()
{
  // 初始化蓝牙通信波特率
  my_Serial.begin(9600);
}
void loop()
{
  //每收到一次信号，向通信另一端反馈一次
  if (my_Serial.available() > 0)  //如果串口有数据输入
  {
    msg = my_Serial.readStringUntil('\n'); //获取换行符前所有的内容
    my_Serial.println("^_^ Hello,mCookie!");  //向蓝牙通信的另一端发送数据
  }
}
