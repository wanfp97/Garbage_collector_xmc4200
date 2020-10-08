#include <ESP8266WiFi.h>

String  i;
WiFiServer server(80);

  int DIRECTION = 16;
  int CLAMP  = 5;
  int ROTATE  = 4;

  int DIRECTION_BUS_IO_0  = 14;
  int DIRECTION_BUS_IO_1  = 12;
  int CLAMP_BUS_IO_0  = 13;
  int CLAMP_BUS_IO_1 = 15;  


void setup()
{
  i = "";

  Serial.begin(9600);

  pinMode(DIRECTION, OUTPUT); 
  pinMode(CLAMP, OUTPUT);  
  pinMode(ROTATE, OUTPUT);   
  
  pinMode(DIRECTION_BUS_IO_0, OUTPUT); 
  pinMode(DIRECTION_BUS_IO_1, OUTPUT);
  pinMode(CLAMP_BUS_IO_0, OUTPUT);
  pinMode(CLAMP_BUS_IO_1, OUTPUT);

  //init
  digitalWrite(DIRECTION,LOW);
  digitalWrite(CLAMP,LOW);
  digitalWrite(ROTATE,LOW);
  digitalWrite(DIRECTION_BUS_IO_0,LOW);
  digitalWrite(DIRECTION_BUS_IO_1,LOW);
  digitalWrite(CLAMP_BUS_IO_0,LOW);
  digitalWrite(CLAMP_BUS_IO_1,LOW);
  
    WiFi.disconnect();
  delay(2000);
  Serial.println("Connecting to WIFI");
   WiFi.begin("POCOPHONE","wanfp979");
  while ((!(WiFi.status() == WL_CONNECTED))){
    delay(300);
    Serial.print("..");

  }Serial.println("I am Connected");
  Serial.println("My Local IP is : ");
  Serial.print((WiFi.localIP()));
  server.begin();

}


void loop()
{

    WiFiClient client = server.available();
    if (!client) { return; }
    while(!client.available()){  delay(1); }
    i = (client.readStringUntil('\r'));
    i.remove(0, 5);
    i.remove(i.length()-9,9);
    
    if (i == "forward") {
      digitalWrite(DIRECTION_BUS_IO_0,LOW);
      digitalWrite(DIRECTION_BUS_IO_1,LOW);

      delay(50);
      
      digitalWrite(DIRECTION,HIGH);

      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("forward");
      client.println("</html>");
      client.stop();
      

    }
    if (i == "reverse") {
      digitalWrite(DIRECTION_BUS_IO_0,HIGH);
      digitalWrite(DIRECTION_BUS_IO_1,LOW);
      
      delay(50);
      
      digitalWrite(DIRECTION,HIGH);
      
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("reverse");
      client.println("</html>");
      client.stop();
      

    }
    if (i == "left") {
      digitalWrite(DIRECTION_BUS_IO_0,LOW);
      digitalWrite(DIRECTION_BUS_IO_1,HIGH);
      
      delay(50);
      
      digitalWrite(DIRECTION,HIGH);
      
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("left");
      client.println("</html>");
      client.stop();
      

    }
    if (i == "right") {
      digitalWrite(DIRECTION_BUS_IO_0,HIGH);
      digitalWrite(DIRECTION_BUS_IO_1,HIGH);
      
      delay(50);
      
      digitalWrite(DIRECTION,HIGH);
      
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("right");
      client.println("</html>");
      client.stop();
      

    }
    if (i == "stop") {
      digitalWrite(DIRECTION,LOW);
      
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("right");
      client.println("</html>");
      client.stop();
      

    }

    if (i == "up") {
      digitalWrite(CLAMP_BUS_IO_0,LOW);
      digitalWrite(CLAMP_BUS_IO_1,LOW);

      delay(100);
      
      digitalWrite(CLAMP,HIGH);

      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("up");
      client.println("</html>");
      client.stop();
      

    }
    if (i == "down") {
      digitalWrite(CLAMP_BUS_IO_0,HIGH);
      digitalWrite(CLAMP_BUS_IO_1,LOW);

      delay(100);
      
      digitalWrite(CLAMP,HIGH);
      
      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("down");
      client.println("</html>");
      client.stop();
      

    }
    if (i == "open") {
      digitalWrite(CLAMP_BUS_IO_0,LOW);
      digitalWrite(CLAMP_BUS_IO_1,HIGH);

      delay(100);
      
      digitalWrite(CLAMP,HIGH);

      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("open");
      client.println("</html>");
      client.stop();
      

    }
    if (i == "close") {
      digitalWrite(CLAMP_BUS_IO_0,HIGH);
      digitalWrite(CLAMP_BUS_IO_1,HIGH);

      delay(100);
      
      digitalWrite(CLAMP,HIGH);

      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("close");
      client.println("</html>");
      client.stop();
      

    }
    if (i == "hold") {
      digitalWrite(CLAMP,LOW);

      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("close");
      client.println("</html>");
      client.stop();
      

    }

    if (i == "metal") {
      digitalWrite(ROTATE,HIGH);

      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("close");
      client.println("</html>");
      client.stop();

    }

    if (i == "non_metal") {
      digitalWrite(ROTATE,LOW);

      client.println("HTTP/1.1 200 OK");
      client.println("Content-Type: text/html");
      client.println("");
      client.println("<!DOCTYPE HTML>");
      client.println("<html>");
      client.println("close");
      client.println("</html>");
      client.stop();

    }
}
