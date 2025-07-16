﻿/*
 * button.h
 *
 * Created: 2025-03-05 오후 2:30:04
 *  Author: microsoft
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_
#define  F_CPU 16000000UL  // 16MHZ
#include <avr/io.h>  // PORTA PORTB등의 I/O 관련 register등이 있다. 
#include <util/delay.h>  // _delay_ms _delay_us

#define LED_DDR DDRG   // 이렇게 하는 이유: LED PORT가 변경 되면
                       // #define만 바꿔주면 compiler가 변경 
#define LED_PORT PORTG
 
#define BUTTON_DDR DDRE 
#define BUTTON_PIN PINE    // PIND는 PORTD를 읽는 register 5v:1  0v:0 

#define BUTTON0PIN  7    // PORTD.3
#define BUTTON1PIN  2    // PORTD.3

#define BUTTON0		0   // PORTD.3의 가상의 index(S/W 번호)
#define BUTTON1		1

#define BUTTON_NUMER 2   // button갯수 
#define BUTTON_PRESS  1   // 버튼을 누르면 high(active-high)
#define BUTTON_RELEASE 0  // 버튼을 떼면 low
#endif /* BUTTON_H_ */