/**
 * 串口通信实验
 * 
 * 两块开发板串口通信实现聊天室
 * 
 * 分别使用RXD、TXD 作为监听自己信息端口;GPIO16、GPIO17作为监听对方信息端口
 * 
 * 实验准备物料
 *   ESP32开发板 2个
 *   杜邦线 三根 
 *   
 * 作者：灵儿、诗杰、唐老师、杰文
 * 
 *   This example code is in the public domain.
 *   基于以下代码参考编写本实验
 *   https://docs.arduino.cc/built-in-examples/communication/MultiSerialMega
 * 
 * 实验问题与总结
 *  问题1：
 *    ESP32 开发板的2号串口通信引脚寻找
 *  答案1：
 *    查看ESP32引脚图 发现可以通过所有GPIO口进行宏定义
 *  问题2：
 *    Serial串口读取消息 保存为字符串
 *  答案2：
 *    刚开始使用Serial.read()方法一个一个字节读，发现不能转为String,通过Ardunio官网发现readString()方法
 *  在编码过程中，碰到基础C语言的问题，需要加强基础语言
 *   
 */
//判断是否存在 RX2 宏定义 
#ifndef RX2
//如果不存在 就创建 RX2 宏 
#define RX2 16
//结束宏定义
#endif

//判断是否存在 TX2 宏定义 
#ifndef TX2
//如果不存在 就创建 TX2 宏 
#define TX2 17
//结束宏定义
#endif

//定义对方消息变量
String otherMsg;
//定义自己消息变量
String myMsg;

void setup() {
  //初始化串口端口和定义波特率
  Serial.begin(115200);
  Serial2.begin(115200,SERIAL_8N1,RX2,TX2);
}

void loop() {
  //获取监听自己串口数据
  if(Serial.available()) {
    //读取保存自己消息
    myMsg = Serial.readString();
    //打印消息到对方消息串口
    Serial2.print("杰文哥哥：");
    Serial2.print(myMsg);
    //打印消息到自己消息串口
    Serial.print("杰文哥哥：");
    Serial.print(myMsg);
  }

  //获取对方串口数据
  if(Serial2.available()) {
    //读取保存对方消息
    otherMsg = Serial2.readString();
    //打印消息
    Serial.print(otherMsg);
  }
  
}
