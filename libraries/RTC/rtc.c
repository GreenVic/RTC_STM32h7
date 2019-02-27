/* Includes ------------------------------------------------------------------*/
#include "rtc.h"
#include "stm32h7xx_hal.h"

/* Private define ------------------------------------------------------------*/
#define YEAR_MILE_STONE  1900
#define MONTH_FEBRUARY  1
#define MONTH_MARCH  2
/* Private variables ---------------------------------------------------------*/
static RTC_HandleTypeDef hrtc;

/* Functions implementation---------------------------------------------------*/
void MX_RTC_Init(void)
{
  /**Initialize RTC Only 
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  HAL_RTC_Init(&hrtc);
}

void SetTime(time_t timeStamp)
{
  struct tm *calendar;
  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};
	
  /* Convert from time stamp to calendar */
  calendar = localtime(&timeStamp);
  
  /* Prepare for setting time */
  sTime.Hours = calendar->tm_hour;
  sTime.Minutes = calendar->tm_min;
  sTime.Seconds = calendar->tm_sec;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  /* Set time */
  HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	
  /* Prepare for setting date */
  sDate.WeekDay = calendar->tm_wday;
  sDate.Month = calendar->tm_mon;
  sDate.Date = calendar->tm_mday;
  sDate.Year = calendar->tm_year;
  
  /* Set date */
  HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
}

struct tm GetTime(void)
{
  struct tm ret = {0};
  RTC_DateTypeDef dateStruct;
  RTC_TimeTypeDef timeStruct;
	
  /* Get time from RTC block */
  HAL_RTC_GetTime(&hrtc, &timeStruct, RTC_FORMAT_BIN);
  HAL_RTC_GetDate(&hrtc, &dateStruct, RTC_FORMAT_BIN);
	
  /* Set values to return */
  ret.tm_wday = dateStruct.WeekDay;
  ret.tm_year = dateStruct.Year;
  ret.tm_hour = timeStruct.Hours;
  ret.tm_min  = timeStruct.Minutes;
  ret.tm_sec  = timeStruct.Seconds;
  
  /* Check if 00:00:00 Feb-29th of leap year */
  if((timeStruct.Seconds == 0) && (timeStruct.Minutes == 0) && (dateStruct.Date == 29)
    && (timeStruct.Hours == 0) && (dateStruct.Month == MONTH_FEBRUARY))
  {
    uint16_t year = dateStruct.Year + YEAR_MILE_STONE; /* Year in real life form */
    /* Check if leap year */
    if(((year % 4)) || ((!(year % 100)) && (year % 400)))
    {
      ret.tm_mon  = MONTH_MARCH;
      ret.tm_mday = 1;
      /* Convert to time stamp */
      time_t timeStamp = mktime(&ret);
      /* Set date as March-1st */
      SetTime(timeStamp);
      return ret;
    }
  }
	
  /* Not case of 29-Feb 00:00:00 in leap year, return normally */
  ret.tm_mon  = dateStruct.Month;
  ret.tm_mday = dateStruct.Date;
  return ret;
}

void HAL_RTC_MspInit(RTC_HandleTypeDef* rtcHandle)
{
  if(rtcHandle->Instance==RTC)
  {
    /* RTC clock enable */
    __HAL_RCC_RTC_ENABLE();
  }
}

void HAL_RTC_MspDeInit(RTC_HandleTypeDef* rtcHandle)
{
  if(rtcHandle->Instance==RTC)
  {
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();
  }
} 

/***************************** END OF FILE**********************************/
