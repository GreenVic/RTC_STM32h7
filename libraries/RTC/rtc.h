/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __rtc_H
#define __rtc_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "time.h"

/* Export variables ----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
/**
  * @brief  Init Real Time Clock
  * @param  None
  * @retval None
  */
void MX_RTC_Init(void);

/**
  * @brief  Get RTC in calendar struct
  * @param  None
  * @retval calendar struct, refer "time.h"
  */
struct tm GetTime(void);

/**
  * @brief  Set time to RTC block
  * @param  Current time in epoch time stamp
  * @retval None
  */
void SetTime(time_t timeStamp);

#ifdef __cplusplus
}
#endif
#endif /*__ rtc_H */

/**
  * @}
  */

/**
  * @}
  */

/*****************************END OF FILE**********************************/
