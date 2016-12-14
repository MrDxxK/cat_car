void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
}
int sensorValueL,sensorValueR;//第一级传感器 L:A0,R:A2
int sensorValueLL,sensorValueRR;//第二级传感器  LL:A6,RR:A7
void loop() {
  // put your main code here, to run repeatedly:
      
      sensorValueL=analogRead(A0);
      sensorValueR=analogRead(A2);
      sensorValueLL=analogRead(A6);
      sensorValueRR=analogRead(A7);
      Serial.print(sensorValueLL);
      Serial.print(" ");
      Serial.print(sensorValueL);
      Serial.print(" ");
      Serial.print(sensorValueR);
      Serial.print(" ");
      Serial.println(sensorValueRR);
      delay(1);//为了稳定
}
