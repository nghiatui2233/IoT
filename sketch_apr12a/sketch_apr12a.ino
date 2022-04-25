#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>
BlynkTimer timer;

char auth[] = "1B7eYHdzuDD9dzTLMScsQ1gFRO4Jgt_E";
const char* ssid = "FPT-DangKhoa";
const char* password =  "0939998576";
int value,real_value;

BLYNK_WRITE(A0){
  int value = param.asInt();
  digitalWrite(34, value);
}
BLYNK_WRITE(V1)
{
  int pinValue = param.asInt();
  digitalWrite(4, pinValue);
}

void sendSensor()
{
  for(int i=0;i<=9;i++){
    real_value+=analogRead(34);
  }
  value=real_value/40;
  int percent = map(value, 350, 1023, 0, 100);                                             
  percent=100-percent; 
  int t = percent; 
  Blynk.virtualWrite(V0, t);
}


void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  // Code sensor
  pinMode(5,INPUT_PULLUP); 
  pinMode(4,OUTPUT); 
  Blynk.begin(auth, ssid, password);                      
  timer.setInterval(1000L, sendSensor);
  
}
 
void loop() {
  Blynk.run();
   timer.run();
  Serial.print("Value analog: ");
  Serial.println(value);
  delay(700);
  real_value=0;
  }
