#include <WiFi.h>
#include "ThingSpeak.h" 

const char* ssid = "IoT";
const char* pass =  "1t3s0IoT23";

WiFiClient client;

unsigned long myChannelNumber = 2056567;
const char* myWriteAPIKey = "YBGEC8N0O5M3H7BE";

int number1 = random(0,50);
int number2 = random(0,50);
String myStatus = "";

void setup() {
 Serial.begin(115200);
 WiFi.begin(ssid, pass);
 Serial.println();
 Serial.print("Wait for WiFi...");
 while (WiFi.status() != WL_CONNECTED) {
   Serial.print(".");
   delay(500);
 }
 Serial.println("");
 Serial.println("WiFi Connected");
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());
 ThingSpeak.begin(client); // Initialize ThingSpeak
}

void loop() {
 // set the fields with the values
 ThingSpeak.setField(1, number1);
 ThingSpeak.setField(2, number2);
 // figure out the status message for multi fields
 if(number1 > number2){
   myStatus = String("field1 is greater than field2");
 }
 else if(number1 < number2){
   myStatus = String("field1 is less than field2");
 }
 else{
   myStatus = String("field1 equals field2");
 }
 // set the status
 ThingSpeak.setStatus(myStatus);
 // write to the ThingSpeak channel
 int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
 if(x == 200){
   Serial.println("ThingSpeak Channel update successful.");
 }
 else{
   Serial.println("Problem updating channel. HTTP error code " + String(x));
 }
 // change the values
 number1++;
 if(number1 > 99){
   number1 = 0;
 }
 number2 = random(0,100);
 delay(20000); // Wait 20 seconds to update the channel again
}
