#include "web.h"

IPAddress local_IP(192, 168, 4, 1); // 本地IP
IPAddress gateway(192, 168, 4, 1);  // 网关
IPAddress subnet(255, 255, 255, 0); // 子网掩码

WebServer server(80);

// 初始化 LittleFS
bool initFS()
{
  if (!LittleFS.begin())
  {
    Serial.println("LittleFS 挂载失败！");
    return false;
  }
  Serial.println("LittleFS 挂载成功");
  return true;
}

// 网页请求处理
void handleWebRequest()
{
  String path = server.uri();
  if (path == "/")
    path = "/index.html";

  // 自动判断文件类型
  String contentType = "text/plain";
  if (path.endsWith(".html")) contentType = "text/html";
  else if (path.endsWith(".css")) contentType = "text/css";
  else if (path.endsWith(".js")) contentType = "application/javascript";
  else if (path.endsWith(".png")) contentType = "image/png";
  else if (path.endsWith(".jpg") || path.endsWith(".jpeg")) contentType = "image/jpeg";
  else if (path.endsWith(".ico")) contentType = "image/x-icon";
  
  // 读取并返回文件
  if (LittleFS.exists(path)) {
    File file = LittleFS.open(path, "r");
    server.streamFile(file, contentType);
    file.close();
  } else {
    server.send(404, "text/plain", "File Not Found - index.html!");
  }
}

void handleCmdButton() {
  // 定义按钮
  String key = server.arg("key");
  // 定义事件类型：按下还是松开
  String type = server.arg("type");
  if (key.isEmpty() || type.isEmpty()) {
    server.send(400, "text/plain", "400 Bad Request - Missing 'key' or 'type' parameter");
    return;
  }
  if (type == "up") {
    if (key == "triangle" || key == "cross") {
      
    } else if (key == "square" || key == "circle") {
      Serial.println('G');  
    } else {
      Serial.println('0'); 
    }     
  } else {
    if (key == "up") {
      Serial.println('1');  
    } else if (key == "down") {
      Serial.println('2');  
    } else if (key == "left") {
      Serial.println('3');  
    } else if (key == "right") {
      Serial.println('4');  
    } else if (key == "triangle") {
      Serial.println('E');  
    } else if (key == "cross") {
      Serial.println('F');  
    } else if (key == "square") {
      Serial.println('H');  
    } else if (key == "circle") {
      Serial.println('I');  
    } else if (key == "l1") {
      Serial.println('9');  
    } else if (key == "r1") {
      Serial.println('A');  
    } else if (key == "l2") {
      Serial.println('B');  
    } else if (key == "r2") {
      Serial.println('C');  
    }
  }

  server.send(200);
}

void handleCmdStick() {
  String stickId = server.arg("stickId");
  String direct = server.arg("direct");
  String stepValue = server.arg("stepValue");
  if (stickId.isEmpty() || direct.isEmpty() || stepValue.isEmpty()) {
    server.send(400, "text/plain", "400 Bad Request - Missing 'stickId', 'direct' or 'stepValue' parameter");
    return;
  }
  if (stickId != "left-analog") {
    server.send(200);
    return;
  }
  if (direct == "stop") {
    Serial.println('0'); 
  } else {
    if (direct == "up") {
      Serial.println('1'+stepValue); 
    } else if (direct == "down") {
      Serial.println('2'+stepValue); 
    } else if (direct == "left") {
      Serial.println('3'+stepValue); 
    } else if (direct == "right") {
      Serial.println('4'+stepValue); 
    } else if (direct == "uple") {
      Serial.println('5'+stepValue); 
    } else if (direct == "uprt") {
      Serial.println('6'+stepValue); 
    } else if (direct == "dnle") {
      Serial.println('7'+stepValue); 
    } else if (direct == "dnrt") {
      Serial.println('8'+stepValue); 
    }
  }
  // Serial.println(stickId + " - Direct: " + direct + ", Step Value: " + stepValue); 
  server.send(200);
}