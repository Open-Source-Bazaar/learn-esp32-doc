/*
  红绿灯实验

  红灯和绿灯交替点亮

  分别使用GPIO16、GPIO17作为红绿灯控制输出口，控制红绿LED作为红绿灯的替代演示。
  正式项目可将红绿LED替换为继电器即可。
  
  实验准备物料：
    面包板 1块
    杜邦线 红色2根 （一头针，一个孔；两个孔）
          黑色1根
    面包线 绿色2根 （两头针）
    LED   绿色1个
          红色1个
    电阻   1k 2个
    ESP32开发板 一个

  作者：灵儿、杰文、诗杰、古神、唐总、miya

  This example code is in the public domain.
  基于以下代码参考编写本实验
  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

// 配置红绿灯变量
int redlight=16;
int greenlight=17;
// 配置通行时间和等待时间变量
int passTime=5000;
int standTime=1000;


// 初始化设备
void setup() {
  Serial.begin(115200);
  // 初始化红绿灯控制输出口
  pinMode(redlight, OUTPUT);
  pinMode(greenlight, OUTPUT);
  // 初始化控制输出口为低电平
  digitalWrite(redlight, LOW);  
  digitalWrite(greenlight, LOW);  
  Serial.print("初始化");
}

// 执行循环任务
void loop() {
//  // 设置通行状态和时间
//  digitalWrite(redlight, HIGH);  
//  digitalWrite(greenlight, LOW);  
//  delay(passTime);        
//  
//  // 设置等待状态和时间
//  digitalWrite(greenlight, HIGH);  
//  digitalWrite(redlight, LOW);     
//  delay(standTime); 

    for(int i = 0; i < 100; i++){
      Serial.println(i);
      delay(100); 
     }
}
