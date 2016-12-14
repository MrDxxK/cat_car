/*
[url=http://www.openjumper.com/]www.openjumper.com[/url]
日期:2013.5.18
IDE 版本:1.0.1
功能：利用SR04超声波传感器进行测距，并用串口显示测出的距离值
*/
 
// 设定SR04连接的Arduino引脚
const int TrigPin = 2; 
const int EchoPin = 3; 
const int TrigPin2 = 7; 
const int EchoPin2= 6; 
float distance; 
void setup() 
{   // 初始化串口通信及连接SR04的引脚
        Serial.begin(115200); 
        pinMode(TrigPin, OUTPUT); 
        pinMode(TrigPin2, OUTPUT); 
    // 要检测引脚上输入的脉冲宽度，需要先设置为输入状态
         pinMode(EchoPin, INPUT); 
        pinMode(EchoPin2, INPUT); 
    Serial.println("Ultrasonic sensor:");
} 
void loop() 
{ 
    // 产生一个10us的高脉冲去触发TrigPin 
        digitalWrite(TrigPin, LOW); 
        delayMicroseconds(2); 
        digitalWrite(TrigPin, HIGH); 
        delayMicroseconds(10);
        digitalWrite(TrigPin, LOW); 
    // 检测脉冲宽度，并计算出距离
        distance = pulseIn(EchoPin, HIGH) / 58.00;
        Serial.print(distance); 
        Serial.print("cm "); 
        delay(10);
        //由于模拟口不够
        // 产生一个10us的高脉冲去触发TrigPin 
        digitalWrite(TrigPin2, LOW); 
        delayMicroseconds(2); 
        digitalWrite(TrigPin2, HIGH); 
        delayMicroseconds(10);
        digitalWrite(TrigPin2, LOW); 
    // 检测脉冲宽度，并计算出距离
        distance = pulseIn(EchoPin2, HIGH) / 58.00;
        Serial.print(distance); 
        Serial.print("cm"); 
        Serial.println(); 
        delay(10);
}
