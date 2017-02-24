/* RTC_A library is designed to drive MSP30/CC430's RTC_A peripheral

  See readme.txt for more informations */


#ifndef _RTC_A_H_
#define _RTC_A_H_

#include <msp430.h>
#include "Energia.h"
#include "wiring_private.h"

#ifndef __MSP430_HAS_RTC__
#error "Your microcontroller have not a RTC peripheral"
#endif



typedef enum RTC_DOW
{
  NO_ALARM = -1,
  MONDAY,
  TUESDAY,
  WEDNESDAY,
  THURSDAY,
  FRIDAY,
  SATURDAY,
  SUNDAY
} RTC_DOW;

typedef enum RTCSRC
{
  RTCSRC_VLO = 0,
  RTCSRC_XT1
} RTCSRC;

typedef enum RTC_MODE
{
  RTCMODE_CALENDAR = 0,
  RTCMODE_COUNTER
} RTC_MODE;

typedef enum RTCFREQ
{
  MINUTE_CHANGED = 0,
  HOUR_CHANGED,
  AT_MIDNIGHT,
  AT_NOON
} RTCFREQ;

typedef enum RTCFREQC
{
  OVERFLOW_8BIT = 0,
  OVERFLOW_16BIT,
  OVERFLOW_24BIT,
  OVERFLOW_32BIT
} RTCFREQC;

typedef enum RTCINT
{
  RTC_INT_ALARM = 0,
  RTC_INT_TIME_EVENT,
  RTC_INT_RTC,
  RTC_INT_RTCPS0,
  RTC_INT_RTCPS1,
} RTCINT;


/* Counter functions */

void RTC_init(uint8_t PrescRT0, uint8_t PrescRT0int, uint8_t SourceRT1, uint8_t PrescRT1, uint8_t PrescRT1int);

void RTC_stopCounter0(void);
void RTC_startCounter0(void);
void RTC_resetCounter0(void);
void RTC_enableCounter0Interrupt(void (*userFunc)(void));
void RTC_disableCounter0Interrupt(void);

void RTC_stopCounter1(void);
void RTC_startCounter1(void);
void RTC_resetCounter1(void);
void RTC_enableCounter1Interrupt(void (*userFunc)(void));
void RTC_disableCounter1Interrupt(void);


/* Calendar functions */

void RTC_init(uint8_t Second, uint8_t Minute, uint8_t Hour, uint8_t Day, RTC_DOW DOW, uint8_t Month, uint16_t Year);

void RTC_setTime(uint8_t Second, uint8_t Minute, uint8_t Hour, uint8_t Day, RTC_DOW DOW, uint8_t Month, uint16_t Year);

uint8_t RTC_getSecond(void);
uint8_t RTC_getMinute(void);
uint8_t RTC_getHour(void);
uint8_t RTC_getDayOfWeek(void);
uint8_t RTC_getDay(void);
uint8_t RTC_getMonth(void);
uint16_t RTC_getYear(void);

void RTC_setAlarm(int8_t Minute, int8_t Hour, int8_t Day, RTC_DOW DOW, void (*userFunc)(void));
void RTC_disableAlarm(void);

void RTC_enableInterrupt(RTCFREQ Freq, void (*userFunc)(void));
void RTC_disableInterrupt(void);

void RTC_enableRTCInterrupt(void (*userFunc)(void));
void RTC_disableRTCInterrupt(void);

void RTC_setCalibration(int8_t Correction);

/* Common functions */

void SelectSource(RTCSRC Source);

#endif
