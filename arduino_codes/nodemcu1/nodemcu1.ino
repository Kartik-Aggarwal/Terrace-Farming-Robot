#include <ESP8266WiFi.h>

WiFiClient client;
WiFiServer server(80);


const char* ssid = "Mini";
const char* password = "garvit32";

/* data received from application */
String  data = "";


int leftMotorForward = 2;     /* GPIO2(D4) -> IN3   */
int rightMotorForward = 15;   /* GPIO15(D8) -> IN1  */
int leftMotorBackward = 0;    /* GPIO0(D3) -> IN4   */
int rightMotorBackward = 13;  /* GPIO13(D7) -> IN2  */
int rightMotorENB = 14; /* GPIO14(D5) -> Motor-A Enable */
int leftMotorENB = 12;  /* GPIO12(D6) -> Motor-B Enable */

void setup()
{
  pinMode(leftMotorForward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);
  pinMode(rightMotorBackward, OUTPUT);

  pinMode(leftMotorENB, OUTPUT);
  pinMode(rightMotorENB, OUTPUT);

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

  if (data == "forward") MotorForward();
  else if (data == "backward") MotorBackward();
  else if (data == "left") TurnLeft();
  else if (data == "right") TurnRight();
  else if (data == "stop") MotorStop();
  else if (data == "topright") goAheadRight();
  else if (data == "topleft") goAheadLeft();
  else if (data == "bottomright") goBackRight();
  else if (data == "bottomleft") goBackLeft();
}

/********************************************* FORWARD *****************************************************/
void MotorForward(void)
{
  digitalWrite(leftMotorENB, HIGH);
  digitalWrite(rightMotorENB, HIGH);
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}

/********************************************* BACKWARD *****************************************************/
void MotorBackward(void)
{
  digitalWrite(leftMotorENB, HIGH);
  digitalWrite(rightMotorENB, HIGH);
  digitalWrite(leftMotorBackward, HIGH);
  digitalWrite(rightMotorBackward, HIGH);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(rightMotorForward, LOW);
}

/********************************************* TURN LEFT *****************************************************/
void TurnLeft(void)
{
  digitalWrite(leftMotorENB, HIGH);
  digitalWrite(rightMotorENB, HIGH);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(rightMotorBackward, LOW);
  digitalWrite(leftMotorBackward, HIGH);
}

/********************************************* TURN RIGHT *****************************************************/
void TurnRight(void)
{
  digitalWrite(leftMotorENB, HIGH);
  digitalWrite(rightMotorENB, HIGH);
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
}

/********************************************* STOP *****************************************************/
void MotorStop(void)
{
  digitalWrite(leftMotorENB, LOW);
  digitalWrite(rightMotorENB, LOW);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}

/********************************************* AHEADRIGHT *****************************************************/
void goAheadRight(void)
{
  digitalWrite(leftMotorENB, HIGH);
  digitalWrite(rightMotorENB, HIGH);
  digitalWrite(leftMotorForward, HIGH);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}/********************************************* AHEADLEFT *****************************************************/
void goAheadLeft(void)
{
  digitalWrite(leftMotorENB, HIGH);
  digitalWrite(rightMotorENB, HIGH);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(rightMotorForward, HIGH);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorBackward, LOW);
}
/********************************************* BACKRIGHT *****************************************************/
void goBackRight(void)
{
  digitalWrite(leftMotorENB, HIGH);
  digitalWrite(rightMotorENB, HIGH);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(leftMotorBackward, HIGH);
  digitalWrite(rightMotorBackward, LOW);
}
/********************************************* BACKLEFT *****************************************************/
void goBackLeft(void)
{
  digitalWrite(leftMotorENB, HIGH);
  digitalWrite(rightMotorENB, HIGH);
  digitalWrite(leftMotorForward, LOW);
  digitalWrite(rightMotorForward, LOW);
  digitalWrite(leftMotorBackward, LOW);
  digitalWrite(rightMotorBackward, HIGH);
}


/********************************** RECEIVE DATA FROM the APP ******************************************/
String checkClient (void)
{
  while (!client.available()) delay(1);
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length() - 9, 9);
  return request;
}
