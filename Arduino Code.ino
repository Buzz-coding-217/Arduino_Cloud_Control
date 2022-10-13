// Importing different libraries
#include <Arduino.h>
#include <WiFiNINA.h>
#include <Firebase_Arduino_WiFiNINA.h>

//Importing Host's url and autentication key
#define URL "traffic-light-1dbeb-default-rtdb.firebaseio.com"
#define Secret "UO0BLCqGoLmOLpT8ivvGCaEwlTi0dEaJMxaHecjh"

//setting up wifi credentials
char ssid[] = "shravel";
char pass[] = "asdfghjkl";

//setting a firebase instance
FirebaseData Fire;
String path = "/light/light";

void setup()
{
  Serial.begin(9600);

  //setting up the Pin Modes
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);

  //connecting with Wifi
  Serial.print("Connecting to Wi-Fi");
  int status = WL_IDLE_STATUS;
  while (status != WL_CONNECTED)
  {
    status = WiFi.begin(ssid, pass);
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(URL, Secret, ssid, pass);
  Firebase.reconnectWiFi(true);
}

void loop()
{
  //continously getting information from database
  if (Firebase.getString(Fire, path))
  {
    function(Fire.stringData());
  }
}

void function(String color)
{
  //changing the led depended upon their value from database
  if(color == "Red")
  {
    digitalWrite(10, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
    Serial.println("RED");
  }
  else if (color == "Yellow")
   {
     digitalWrite(10, LOW);
     digitalWrite(9, HIGH);
     digitalWrite(8, LOW);
     Serial.println("YELLOW");
   }
   else if (color == "Green")
   {
     digitalWrite(10, LOW);
     digitalWrite(9, LOW);
     digitalWrite(8, HIGH);
     Serial.println("GREEN");
   }
}
