/* Real Time Clock for MSP430F5529 LaunchPad
 *  
 *  Demonstrates how to:
 *  - set time
 *  - call a user defined function for updates at a fixed interval
 *  - call a daily alarm function
 *  - print out year, month, day, hour, min, and second
 *  - toggles the red LED on and off every second
 *  
 *  Example by Fmilburn 2/2017
*/

#include "RTC_A.h"

volatile boolean       updateFlag =      false;
volatile boolean       alarmFlag =       false;
const unsigned long    updateInterval =  10;     // seconds between updates
volatile unsigned long updateTime =      0;      // seconds since last update
volatile int           ledStatus =       HIGH;

void setup()
{
  // Second, Minute, Hour, Day, Day of Week, Month, Year);
  RTC_init(0, 59, 12, 24, FRIDAY, 2, 2017);

  // call the function Update() every second
  RTC_enableRTCInterrupt(Update); 

  // call function Alarm() every day at 13:00
  RTC_setAlarm(00, 13, NO_ALARM, NO_ALARM, Alarm); 
  
  Serial.begin(115200);
  Serial.println("Starting RTC");

  pinMode(RED_LED, OUTPUT);
  digitalWrite(RED_LED, ledStatus);  
}


void loop(){

  if (alarmFlag == true){
    // reset the alarm flag and sound the alarm
    alarmFlag = false;
    printAlarm();
  }
  
  if (updateFlag == true){
    // reset the update flag and print the date and time
    updateFlag = false;
    printDateAndTime();
  }
}

void printAlarm(){
  
  Serial.println("Alarm Alarm Alarm...");
  
}

void printDateAndTime(){

  Serial.print(RTC_getYear());
  Serial.print("/");
  Serial.print(RTC_getMonth());
  Serial.print("/");
  Serial.print(RTC_getDay());
  Serial.print("  ");
  Serial.print(RTC_getHour());
  Serial.print(":");
  Serial.print(RTC_getMinute());
  Serial.print(":");
  Serial.println(RTC_getSecond());

}

void Alarm(void) {
  // ISR flags when alarm time occurs
  
  alarmFlag = true;  
  
}

void Update(void){
  // ISR flags when update interval expires and toggles LED

  if (ledStatus == HIGH){
    ledStatus = LOW;
    digitalWrite(RED_LED, ledStatus);
  }
  else{
    ledStatus = HIGH;
    digitalWrite(RED_LED, ledStatus);
  }
  
  updateTime++;
  if (updateTime == updateInterval){
    updateTime = 0;
    updateFlag = true;
  }
}
