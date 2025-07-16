/*
 * uart.h
 *
 * Created: 2025-03-12 오후 12:02:47
 *  Author: microsoft
 */ 


#ifndef UART_H_
#define UART_H_


#define  F_CPU 16000000UL  // 16MHZ
#include <avr/io.h>
#include <util/delay.h>  // _delay_ms _delay_us
#include <avr/interrupt.h>
#include <stdio.h>		// printf
#include <string.h>

#include "def.h"

volatile uint8_t rx_buff[COMMAND_NUMBER][COMMAND_LENGTH];
// 2차원 array로 변경

// -> buffer가 command를 element로 하는 원형큐가 되는것!!
volatile int rear; // push (ISR에서)
volatile int front; // pop (main에서)


#endif /* UART_H_ */