/*
 * ultrasonic.h
 *
 * Created: 2025-03-12 오후 2:49:13
 *  Author: microsoft
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_
#define  F_CPU 16000000UL  // 16MHZ
#include <avr/io.h>
#include <util/delay.h>  // _delay_ms _delay_us
#include <avr/interrupt.h>

#define	TRIG_LEFT	0
#define	TRIG_FRONT	1
#define	TRIG_RIGHT	2
#define	TRIG_PORT PORTA
#define	TRIG_DDR  DDRA

#define	ECHO_LEFT	4
#define	ECHO_FRONT	5
#define	ECHO_RIGHT	6
#define	ECHO_PIN PINE // External INT 4
#define ECHO_DDR DDRE




#endif /* ULTRASONIC_H_ */