#ifndef _TIMER_H_
#define _TIMER_H_

#pragma once

/**
 * @brief Changes the operating frequency of a timer
 * @param timer which timer we want to change
 * @param freq value of the frequency to be update
 * @return 0 if sucessful, 1 otherwise
 */
int(timer_set_frequency)(uint8_t timer, uint32_t freq);

/**
 * @brief Subscribes timer 0 interrupts
 * @param bit_no used to update hook_id upon function execution
 * @return 0 if sucessful, 1 otherwise
 */
int(timer_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes timer 0 interrupts
 * @return 0 if sucessful, 1 otherwise
 */
int(timer_unsubscribe_int)();

/**
 * @brief Timer 0 interruption handler, increments no_interrupts variable by 1 for each interrupt
 */
void(timer_int_handler)();

/**
 * @brief Reads the timer configuration (status) via a read-back command
 * @param timer timer we want to read the configuration from
 * @param st status variable that will be passed the information read from timer
 * @return 0 if sucessful, 1 otherwise
 */
int(timer_get_conf)(uint8_t timer, uint8_t *st);

#endif // _TIMER_H_
