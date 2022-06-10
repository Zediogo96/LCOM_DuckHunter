#ifndef _RTC_H_
#define _RTC_H_

#include <lcom/lcf.h>
#include <minix/sysutil.h>

#define RTC_HOUR 0x04
#define RTC_MIN 0x02
#define RTC_SEC 0x00

#define RTC_REG_A 0x0A
#define RTC_REG_B 0x0B
#define RTC_REG_C 0x0C
#define RTC_REG_D 0x0D

#define UIP_FLAG BIT(7)
#define DM_FLAG BIT(2)

#define RTC_REG_ADDRESS 0x70
#define RTC_REG_DATA 0x71

/**
 * @brief Auxiliar function to determine if the information read from the RTC is in BCD.
 *
 * @return true if it's in BCD
 * @return else false
 */
bool isBCD();

/**
 * @brief Auxiliar function to convert from BCD to Binary.
 *
 * @param bcd number to be converted
 * @return uint32_t number converted
 */
uint32_t BCD_2_Binary(uint32_t bcd);

/**
 * @brief Get the current time from the RTC, handling necessary conversions due to the data being presented in BCD mode and 12h format.
 * Handles special case when the MSB of the BCD number is 0x08.
 * @param hours 
 * @param minutes 
 */
void getCurrentTime(uint8_t *hours, uint8_t *minutes);

#endif
