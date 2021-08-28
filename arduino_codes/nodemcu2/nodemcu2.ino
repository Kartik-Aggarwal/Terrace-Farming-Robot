#include <ESP8266WiFi.h>
#include <Servo.h>

WiFiClient client;
WiFiServer server(80);


const char* ssid = "IITJ";
const char* password = "garvit32";

/* data received from application */
String  data =""; 


int leftMotorForward = 2;     /* GPIO2(D4) -> IN3   */
int rightMotorForward = 15;   /* GPIO15(D8) -> IN1  */
int leftMotorBackward = 0;    /* GPIO0(D3) -> IN4   */
int rightMotorBackward = 13;  /* GPIO13(D7) -> IN2  */
int rightMotorENB = 14; /* GPIO14(D5) -> Motor-A Enable */
int leftMotorENB = 12; /* GPIO12(D6) -> Motor-B Enable */
int water = 4; /* GPIO4(D2) -> Relay */
Servo myservo; /*GPIO5(D1) -> Servo */
int pos = 0;

void setup()
{
  pinMode(leftMotorForward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT); 
  pinMode(leftMotorBackward, OUTPUT);  
  pinMode(rightMotorBackward, OUTPUT);

  pinMode(leftMotorENB, OUTPUT); 
  pinMode(rightMotorENB, OUTPUT);

  myservo.attach(5);

  /* start server communication */
  server.begin();
}

void loop()
{
    /* If the server available, run the "checkClient" function */  
    client = server.available();
    if (!client) return; 
    data = checkClient ();

/************************ Run function according to incoming data from application *************************/

    if (data == "Forward_Up") ForwardUp();
    else if (data == "Forward_Down") ForwardDown();
    else if (data == "Rear_Up") RearUp();
    else if (data == "Rear_Down") RearDown();
    else if (data == "FD_RU") FDRU();
    else if (data == "FU_RD") FURD();
    else if (data == "Water_Enable") waterenable();
    else if (data == "Water_Disable") waterdisable();
    else if (data == "Seeder_Enable") seederenable();
    else if (data == "Seeder_Disable") seederdisable();
    else if (data == "stop") MotorStop();
} 

/********************************************* FORWARDUP *****************************************************/
void ForwardUp(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}

/********************************************* FORWARDDOWN*****************************************************/
void ForwardDown(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorBackward,HIGH);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,LOW);
}

/********************************************* REARUP*****************************************************/
void RearUp(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH); 
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorBackward,LOW);  
}

/*********************************************REARDOWN*****************************************************/
void RearDown(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
}

/********************************************* STOP *****************************************************/
void MotorStop(void)   
{
  digitalWrite(leftMotorENB,LOW);
  digitalWrite(rightMotorENB,LOW);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}

/********************************************* FRONT DOWN REAR UP *****************************************************/
void FDRU(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(leftMotorBackward,HIGH);
  digitalWrite(rightMotorBackward,LOW);
}

/********************************************* FRONT UP REAR DOWN *****************************************************/
void FURD(void)   
{
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorBackward,HIGH);
}
/********************************************* RELAY ON *****************************************************/
void waterenable(void)   
{
  digitalWrite(water,HIGH);
}
/********************************************* RELAY OFF *****************************************************/
void waterdisable(void)   
{
  digitalWrite(water,LOW);
}
/********************************************* SEEDER ON  *****************************************************/
void seederenable(void)   
{
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15); }
}

/********************************************* SEEDER OFF  *****************************************************/
void seederdisable(void)   
{
   for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
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
