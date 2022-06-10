#pragma once

#include <stdint.h>

/**
 * @brief Returns the least significant byte of the 16 bits integer
 * @param val original 16 bit number we want to extract LSB from
 * @param lsb pointer of type uint8_t that the information will be passed into
 */
int(util_get_LSB)(uint16_t val, uint8_t *lsb);

/**
 * @brief Returns the most significant byte of the 16 bits integer
 * @param val original 16 bit number we want to extract MSB from
 * @param lsb pointer of type uint8_t that the information will be passed into
 */
int(util_get_MSB)(uint16_t val, uint8_t *msb);

/**
 * @brief Auxiliar function to extract a 32 bit number to a bit and
 * pass that information converted into a 8 bit number to a variable.
 * @param port Port that we want to extract information from
 * @param value pointer of type uint8_t that information will be passed into
 */
int(util_sys_inb)(int port, uint8_t *value);

/**
 * @brief Auxiliar function to check if a given scan_code is a BREAK or a MAKE code
 * @param scan_code
 * @return returns true if it's a make code, false if it's a break
 *
 */
bool(isMakeCode)(uint8_t scan_code);
