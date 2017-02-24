#include "RTC_A.h"

static RTC_MODE _Mode;
static volatile voidFuncPtr intUserFunc[5];

void RTC_init(uint8_t PrescRT0, uint8_t PrescRT0int, uint8_t SourceRT1, uint8_t PrescRT1, uint8_t PrescRT1int) {

  SelectSource(RTCSRC_XT1);
  _Mode = RTCMODE_COUNTER;
  RTCCTL01 = RTCHOLD; // disable interrupts, enable coutner mode, clear flags, hold is set, clock source = ACLK

  RTCPS0CTL = PrescRT0 + RT0PSHOLD + PrescRT0int;
  RTCPS1CTL = SourceRT1 + PrescRT1 + RT1PSHOLD + PrescRT1int;
}

void RTC_stopCounter0(void) {

  RTCPS0CTL &= ~RT0PSHOLD;

}

void RTC_startCounter0(void) {

  RTCPS0CTL |= RT0PSHOLD;

}

void RTC_resetCounter0(void) {

}

void RTC_enableCounter0Interrupt(void (*userFunc)(void)) {

  intUserFunc[RTC_INT_RTCPS0] = userFunc;
  RTC_disableCounter1Interrupt();
  RTCPS0CTL |= RT0PSIE;

}

void RTC_disableCounter0Interrupt(void) {

  RTCPS0CTL &= ~RT0PSIE;
  RTCPS0CTL &= ~RT0PSIFG;

}

void RTC_stopCounter1(void) {

  RTCPS1CTL &= ~RT1PSHOLD;

}

void RTC_startCounter1(void) {

  RTCPS1CTL |= RT1PSHOLD;

}

void RTC_resetCounter1(void) {

}

void RTC_enableCounter1Interrupt(void (*userFunc)(void)) {

  intUserFunc[RTC_INT_RTCPS1] = userFunc;
  RTC_disableCounter1Interrupt();
  RTCPS1CTL |= RT1PSIE;

}

void RTC_disableCounter1Interrupt(void) {

  RTCPS1CTL &= ~RT1PSIE;
  RTCPS1CTL &= ~RT1PSIFG;

}

void RTC_init(uint8_t Second, uint8_t Minute, uint8_t Hour, uint8_t Day, RTC_DOW DOW, uint8_t Month, uint16_t Year) {

  _Mode = RTCMODE_CALENDAR; // set calendar mode

  SelectSource(RTCSRC_XT1); // select clock source

  RTCCTL01 = RTCMODE; // disable interrupts, enable calendar mode, clear flags, clear hold, clock source = ACLK

  RTC_setTime(Second, Minute, Hour, Day, DOW, Month, Year); // setTime

}

void RTC_setTime(uint8_t Second, uint8_t Minute, uint8_t Hour, uint8_t Day, RTC_DOW DOW, uint8_t Month, uint16_t Year) {

  RTCSEC = constrain(Second, 0, 59);
  RTCMIN = constrain(Minute, 0, 59);
  RTCHOUR = constrain(Hour, 0, 23);
  RTCDAY = constrain(Day, 1, 31);
  RTCDOW = constrain(DOW, 0, 6);
  RTCMON = constrain(Month, 1, 12);
  RTCYEAR = constrain(Year, 0, 4095);

}

void SelectSource(RTCSRC Source) {

  switch (Source) {

    case RTCSRC_VLO:
      break;

    case RTCSRC_XT1:
      P5SEL |= 0x03;
      UCSCTL6 &= ~XT1OFF;
      UCSCTL6 |= XCAP_3;
      break;

  }

}

uint8_t RTC_getSecond(void) {

  if (_Mode == RTCMODE_CALENDAR) {
    while ((RTCCTL01 & RTCRDY) == 0); // wait for a safe reading
    return RTCSEC;
  } else return 0;

}

uint8_t RTC_getMinute(void) {

  if (_Mode == RTCMODE_CALENDAR) {
    while ((RTCCTL01 & RTCRDY) == 0); // wait for a safe reading
    return RTCMIN;
  } else return 0;

}

uint8_t RTC_getHour(void) {

  if (_Mode == RTCMODE_CALENDAR) {
    while ((RTCCTL01 & RTCRDY) == 0); // wait for a safe reading
    return RTCHOUR;
  } else return 0;
}

uint8_t RTC_getDay(void) {

  if (_Mode == RTCMODE_CALENDAR) {
    while ((RTCCTL01 & RTCRDY) == 0); // wait for a safe reading
    return RTCDAY;
  } else return 0;

}

uint8_t RTC_getDayOfWeek(void) {

  if (_Mode == RTCMODE_CALENDAR) {
    while ((RTCCTL01 & RTCRDY) == 0); // wait for a safe reading
    return RTCDOW;
  } else return 0;

}

uint8_t RTC_getMonth(void) {

  if (_Mode == RTCMODE_CALENDAR) {
    while ((RTCCTL01 & RTCRDY) == 0); // wait for a safe reading
    return RTCMON;
  } else return 0;

}

uint16_t RTC_getYear(void) {

  if (_Mode == RTCMODE_CALENDAR) {
    while ((RTCCTL01 & RTCRDY) == 0); // wait for a safe reading
    return RTCYEAR;
  } else return 0;

}

void RTC_setAlarm(int8_t Minute, int8_t Hour, int8_t Day, RTC_DOW DOW, void (*userFunc)(void)) {

  intUserFunc[RTC_INT_ALARM] = userFunc;

  RTC_disableAlarm(); // alarm interrupt have to be disabled to avoid errors

  if (Minute != -1) {
    constrain(Minute, 0, 59);
    RTCAMIN = Minute | 0x80;
  } else RTCAMIN = 0;

  if (Hour != -1) {
    constrain(Hour, 0, 23);
    RTCAHOUR = Hour | 0x80;
  } else RTCAHOUR = 0;

  if (DOW != -1) {
    constrain(DOW, 0, 6);
    RTCADOW = DOW | 0x80;
  } else RTCADOW = 0;

  if (Day != -1) {
    constrain(Day, 1, 31);
    RTCADAY = Day | 0x80;
  } else  RTCADAY = 0;

  RTCCTL0 |= RTCAIE;

}

void RTC_disableAlarm(void) {

  RTCCTL0 &= ~RTCAIE; // disable alarm interrupt
  RTCCTL0 &= ~RTCAIFG; // clear alarm interrupt flag

}

void RTC_enableInterrupt(RTCFREQ Freq, void (*userFunc)(void)) {

  intUserFunc[RTC_INT_TIME_EVENT] = userFunc;

  RTC_disableInterrupt(); //reet time event interrupt registers

  RTCCTL1 = (RTCCTL1 & 0xFC) | Freq; // configure interrupt frequency

  RTCCTL0 |= RTCTEVIE; // enable time event interrupt

}

void RTC_disableInterrupt(void) {

  RTCCTL0 &= ~RTCTEVIE; // disable time event interrupt
  RTCCTL0 &= ~RTCTEVIFG; // clear time event interrupt flag

}

void RTC_enableRTCInterrupt(void (*userFunc)(void)) {

  intUserFunc[RTC_INT_RTC] = userFunc;

  RTC_disableRTCInterrupt(); // reset interrupt registers

  RTCCTL0 |= RTCRDYIE; // enable interrupt

}

void RTC_disableRTCInterrupt(void) {

  RTCCTL0 &= ~RTCRDYIE; // disable interrupt
  RTCCTL0 &= ~RTCRDYIFG; // clear interrupt flag

}

void RTC_setCalibration(int8_t Correction) {

  if (Correction < 0) RTCCTL23 = Correction & 0x3F;
  else   RTCCTL23 = RTCCALS | (Correction & 0x3F);
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=RTC_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(RTC_VECTOR)))
#endif
void RTC_int(void)
{

  volatile uint16_t Value = RTCIV ; // when RTCIV is read, the highest interrupt flag is cleared so we have to store it

  while (Value != 0) {

    if ((Value == RTCIV_RT1PSIFG ) && intUserFunc[RTC_INT_RTCPS1]) {
      RTCCTL1 &= ~RT1PSIFG;
      intUserFunc[RTC_INT_RTCPS1]();
      LPM3_EXIT;
    }

    if ((Value == RTCIV_RT0PSIFG ) && intUserFunc[RTC_INT_RTCPS0]) {
      RTCCTL0 &= ~RT0PSIFG;
      intUserFunc[RTC_INT_RTCPS0]();
      LPM3_EXIT;
    }

    if ((Value == RTCIV_RTCRDYIFG) && intUserFunc[RTC_INT_RTC]) {
      RTCCTL0 &= ~RTCRDYIFG;
      intUserFunc[RTC_INT_RTC]();
      LPM3_EXIT;
    }

    if ((Value == RTCIV_RTCTEVIFG) && intUserFunc[RTC_INT_TIME_EVENT]) {
      RTCCTL0 &= ~RTCTEVIFG;
      intUserFunc[RTC_INT_TIME_EVENT]();
      LPM3_EXIT;
    }

    if ((Value == RTCIV_RTCAIFG) && intUserFunc[RTC_INT_ALARM]) {
      RTCCTL0 &= ~RTCAIFG;
      intUserFunc[RTC_INT_ALARM]();
      LPM3_EXIT;
    }

    Value = RTCIV;

  }

}
