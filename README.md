# MqttDemo
此为mqtt的使用demo，包括传感器网管代码，服务器接收代码，java客户端
<br><br>
Gateway是QT编写的传感器网关代码，运行环境QT4.8+TQ210，因未集成MQTT，所以采用TCP与mosquitto服务器连接，使用server.cpp接收消息并进行消息发布
<br>
MqttClient是java的maven工程，导入mqtt for java进行编写的PC客户端
<br>
除代码外需要有一台安装mosquitto的服务器即可
