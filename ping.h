/*
 * ping.h
 *
 *  Created on: Oct 12, 2017
 *      Author: rtoepfer
 */

#ifndef PING_H_
#define PING_H_


void ping_init();
int gpio_read();
void gpio_set_out();
void gpio_set_in();
void ping_gpioInit();
void gpio_ping_on();
void gpio_ping_off();
void gpio_ping_micros(int micros);

//timer stuff//
uint32_t read_ping_when_done();
uint32_t read_distance();
void timer_3_init();


#endif /* PING_H_ */
