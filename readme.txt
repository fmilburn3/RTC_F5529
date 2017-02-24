This code has been very lightly edited by Fmilburn.  A new example was developed.  Feb 2017

RTC_A Library for Energia

Author:  B@tto
Contact: batto@hotmail.fr

Current version
0.9b

History
0.9b 01/05/2014 : initial release. Calendar functions seems okay, coutner functions not tested.

Description
RTC_A library is designed to use RTC_A peripheral of some MSP430/CC430 families.

Consideration
This library is built to use ACLK driven by XT1 oscillator using a 32768 Hz quartz.
BCD organisation is not driven.

Functions

/* Calendar functions */


void RTC_init(uint8_t Second, uint8_t Minute, uint8_t Hour, uint8_t Day, RTC_DOW DOW, uint8_t Month, uint16_t Year)
Calendar initialisation with specific time. 


void RTC_setTime(uint8_t Second, uint8_t Minute, uint8_t Hour, uint8_t Day, RTC_DOW DOW, uint8_t Month, uint16_t Year)
Set calendar time


uint8_t RTC_getSecond(void) 
uint8_t RTC_getMinute(void) 
uint8_t RTC_getHour(void)
uint8_t RTC_getDayOfWeek(void)
uint8_t RTC_getDay(void)
uint8_t RTC_getMonth(void)
uint16_t RTC_getYear(void)
Return the correspondant time fraction


void RTC_setAlarm(int8_t Minute, int8_t Hour, int8_t Day, RTC_DOW DOW, void (*userFunc)(void))
Set interrupt alarm. If you don't want that a parameter is taking account in alarm time, set it to NO_ALARM or -1. 

RTC_DOW could be : MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY or SUNDAY.

Examples :

1) Alarm wanted each Monday at 18:00 ==> RTC_setAlarm(NO_ALARM, 18, NO_ALARM, MONDAY, Alarm());
2) Alarm wanted each Monday at 18:30 ==> RTC_setAlarm(30, 18, NO_ALARM, MONDAY, Alarm());
3) Alarm wanted each xx:30 ==> RTC_setAlarm(30, NO_ALARM, NO_ALARM, NO_ALARM, Alarm());

Once you have configure the alarm, interrupt is actived and the program pointed by userFunc will be call (like an attachInterrupt())


void RTC_disableAlarm(void)
Disable alarm interrupt.


void RTC_enableInterrupt(RTCFREQ Freq, void (*userFunc)(void))
Another interruption could be set called time event interruption. Occurrence could be each minute changed, each hour change, at midnight or at noon.
Freq could be : MINUTE_CHANGED, HOUR_CHANGED, AT_MIDNIGHT or AT_NOON.
Once you have configure the interrupt, it is actived and the program pointed by userFunc will be call (like an attachInterrupt())


void RTC_disableInterrupt(void); 
disable time event interrupt.


void RTC_enableRTCInterrupt(void (*userFunc)(void));
The third interrutption available is the ready interruption. When a new reading is available, this interruption is activated, so each second. This allow a safe reading.
It's typically  here where you drive your hour display for example.
Once you have configure the interrupt, it is actived and the program pointed by userFunc will be call (like an attachInterrupt())


void RTC_disableRTCInterrupt(void);
Once you have configure the interrupt, it is actived and the program pointed by userFunc will be call (like an attachInterrupt())


void RTC_setCalibration(int8_t Correction);
Counter can be calibrated to compensate crystal error and/or temperature variations. See datasheet for more information about calculating correction.



/* Counter functions */

void RTC_init(uint8_t PrescRT0, uint8_t PrescRT0int, uint8_t SourceRT1, uint8_t PrescRT1, uint8_t PrescRT1int)

Counter mode initialisation 

PrescRT0 may be :

#define RT0PSDIV_0          (0x0000)     /* RTC Prescale Timer 0 Clock Divide /2 */
#define RT0PSDIV_1          (0x0800)     /* RTC Prescale Timer 0 Clock Divide /4 */
#define RT0PSDIV_2          (0x1000)     /* RTC Prescale Timer 0 Clock Divide /8 */
#define RT0PSDIV_3          (0x1800)     /* RTC Prescale Timer 0 Clock Divide /16 */
#define RT0PSDIV_4          (0x2000)     /* RTC Prescale Timer 0 Clock Divide /32 */
#define RT0PSDIV_5          (0x2800)     /* RTC Prescale Timer 0 Clock Divide /64 */
#define RT0PSDIV_6          (0x3000)     /* RTC Prescale Timer 0 Clock Divide /128 */
#define RT0PSDIV_7          (0x3800)     /* RTC Prescale Timer 0 Clock Divide /256 */

PrescRT0int may be :

#define RT0IP_0             (0x0000)     /* RTC Prescale Timer 0 Interrupt Interval /2 */
#define RT0IP_1             (0x0004)     /* RTC Prescale Timer 0 Interrupt Interval /4 */
#define RT0IP_2             (0x0008)     /* RTC Prescale Timer 0 Interrupt Interval /8 */
#define RT0IP_3             (0x000C)     /* RTC Prescale Timer 0 Interrupt Interval /16 */
#define RT0IP_4             (0x0010)     /* RTC Prescale Timer 0 Interrupt Interval /32 */
#define RT0IP_5             (0x0014)     /* RTC Prescale Timer 0 Interrupt Interval /64 */
#define RT0IP_6             (0x0018)     /* RTC Prescale Timer 0 Interrupt Interval /128 */
#define RT0IP_7             (0x001C)     /* RTC Prescale Timer 0 Interrupt Interval /256 */

SourceRT1 may be :

RT1SSEL_0           (0x0000)     /* RTC Prescale Timer Source Select ACLK */
RT1SSEL_1           (0x4000)     /* RTC Prescale Timer Source Select SMCLK */
RT1SSEL_2           (0x8000)     /* RTC Prescale Timer Source Select RT0PS */
RT1SSEL_3           (0xC000)     /* RTC Prescale Timer Source Select RT0PS */

PrescRT1 may be :
 
RT1PSDIV_0          (0x0000)     /* RTC Prescale Timer 1 Clock Divide /2 */
RT1PSDIV_1          (0x0800)     /* RTC Prescale Timer 1 Clock Divide /4 */
RT1PSDIV_2          (0x1000)     /* RTC Prescale Timer 1 Clock Divide /8 */
RT1PSDIV_3          (0x1800)     /* RTC Prescale Timer 1 Clock Divide /16 */
RT1PSDIV_4          (0x2000)     /* RTC Prescale Timer 1 Clock Divide /32 */
RT1PSDIV_5          (0x2800)     /* RTC Prescale Timer 1 Clock Divide /64 */
RT1PSDIV_6          (0x3000)     /* RTC Prescale Timer 1 Clock Divide /128 */
RT1PSDIV_7          (0x3800)     /* RTC Prescale Timer 1 Clock Divide /256 */

PrescRT1int may be :

 RT1IP_0             (0x0000)     /* RTC Prescale Timer 1 Interrupt Interval /2 */
 RT1IP_1             (0x0004)     /* RTC Prescale Timer 1 Interrupt Interval /4 */
 RT1IP_2             (0x0008)     /* RTC Prescale Timer 1 Interrupt Interval /8 */
 RT1IP_3             (0x000C)     /* RTC Prescale Timer 1 Interrupt Interval /16 */
 RT1IP_4             (0x0010)     /* RTC Prescale Timer 1 Interrupt Interval /32 */
 RT1IP_5             (0x0014)     /* RTC Prescale Timer 1 Interrupt Interval /64 */
 RT1IP_6             (0x0018)     /* RTC Prescale Timer 1 Interrupt Interval /128 */
 RT1IP_7             (0x001C)     /* RTC Prescale Timer 1 Interrupt Interval /256 */
 
void RTC_stopCounter0(void)
void RTC_startCounter0(void)
void RTC_resetCounter0(void)
void RTC_enableCounter0Interrupt(void (*userFunc)(void))
void RTC_disableCounter0Interrupt(void)

void RTC_stopCounter1(void)
void RTC_startCounter1(void)
void RTC_resetCounter1(void)
void RTC_enableCounter1Interrupt(void (*userFunc)(void))
void RTC_disableCounter1Interrupt(void)
