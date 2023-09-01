#include "HX711.h"
#include  <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID           "TMPLxxxxxx"
#define BLYNK_DEVICE_NAME           "Device"
#define BLYNK_AUTH_TOKEN            "YourAuthToken"


// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
//Define a object of HX711 and servo 
#define VPIN_BUTTON_1 V1
#define MOTOR_CONTROL_PIN D0
#define calibration_factor -400000.00
HX711 scale(D4,D5);
Servo esc;
//int dutyCylce=0;
//int LoadValue=0;



char auth[] = BLYNK_AUTH_TOKEN;
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "YourNetworkName";
char pass[] = "YourPassword";


BlynkTimer timer;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void readsensorhx711(){
Loadvalue=abs(scale.get_units());
if (isnan(Loadvalue)==true){
Serial.print("SENSOR VALUE NOT READING")  
}
Serial.print(Loadvalue);
Blynk.virtualWrite(VPIN_BUTTON, Loadvalue);
  
}
void setup()
{
  // Debug console
  Serial.begin(9600);

  Serial.print(" Agmark Thrust Stand");
  delay(1000);
  //Calibration
  scale.set_scale(calibration_factor);
 scale.tare();

BLYNK_CONNECTED() {
  // Request the latest state from the server
  Blynk.syncVirtual(VPIN_BUTTON_1);
}

  //Blynk.begin(auth, wifi, ssid, pass);
  Blynk.begin(auth,ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
  //Blynk.begin(auth, wifi, ssid, pass, IPAddress(192,168,1,100), 8080);
  // Setup a function to be called every second
  timer.setInterval(1000L, readsensorhx711);
}

void loop()
{
  Blynk.run();
  timer.run();
  
}