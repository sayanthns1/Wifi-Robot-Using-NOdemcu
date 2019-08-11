
#include <ESP8266WiFi.h>
WiFiClient client;
WiFiServer server(80);

/* WIFI settings */
const char* ssid = "NS";
const char* password = "123456789";

/* data received from application */
String  data =""; 

/* define L298N or L293D motor control pins */
int LM1 = 2;     /* GPIO2(D4) -> IN3   */
int LM2 = 15;   /* GPIO15(D8) -> IN1  */
int RM1 = 0;    /* GPIO0(D3) -> IN4   */
int RM2 = 13;  /* GPIO13(D7) -> IN2  */

void setup()
{
  /* initialize motor control pins as output */
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT); 
  pinMode(RM1, OUTPUT);  
  pinMode(RM2, OUTPUT);

  /* start server communication */
  server.begin();
  Serial.begin(9600);
}

void loop()
{
    /* If the server available, run the "checkClient" function */  
    client = server.available();
    if (!client) return; 
    data = checkClient ();

/************************ Run function according to incoming data from application *************************/

    /* If the incoming data is "forward", run the "MotorForward" function */
    if (data == "forward") MotorForward();
    /* If the incoming data is "backward", run the "MotorBackward" function */
    else if (data == "backward") MotorBackward();
    /* If the incoming data is "left", run the "TurnLeft" function */
    else if (data == "left") TurnLeft();
    /* If the incoming data is "right", run the "TurnRight" function */
    else if (data == "right") TurnRight();
    /* If the incoming data is "stop", run the "MotorStop" function */
    else if (data == "stop") MotorStop();
} 

/********************************************* FORWARD *****************************************************/
void MotorForward(void)   
{
  digitalWrite(LM1,HIGH);
  digitalWrite(LM2,HIGH);
  digitalWrite(RM1,LOW);
  digitalWrite(RM2,LOW);
  Serial.print("f");
}

/********************************************* BACKWARD *****************************************************/
void MotorBackward(void)   
{
  digitalWrite(RM1,HIGH);
  digitalWrite(RM2,HIGH);
  digitalWrite(LM1,LOW);
  digitalWrite(LM2,LOW);
   Serial.print("b");
}

/********************************************* TURN LEFT *****************************************************/
void TurnLeft(void)   
{
  digitalWrite(LM1,LOW);
  digitalWrite(LM2,HIGH);
  digitalWrite(RM2,LOW);
  digitalWrite(RM1,HIGH);  
   Serial.print("l");
}

/********************************************* TURN RIGHT *****************************************************/
void TurnRight(void)   
{
  digitalWrite(LM1,HIGH);
  digitalWrite(LM2,LOW);
  digitalWrite(RM2,HIGH);
  digitalWrite(RM1,LOW);
   Serial.print("r");
}

/********************************************* STOP *****************************************************/
void MotorStop(void)   
{
  digitalWrite(LM1,LOW);
  digitalWrite(RM1,LOW);
  digitalWrite(LM2,LOW);
  digitalWrite(RM2,LOW);
   Serial.print("s");
}

/********************************** RECEIVE DATA FROM the APP ******************************************/
String checkClient (void)
{
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length()-9,9);
  return request;
}
