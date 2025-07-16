/*
 * dht11.h
 *
 * Created: 2025-03-18 오전 10:53:28
 *  Author: microsoft
 */ 


#ifndef DHT11_H_
#define DHT11_H_
#define  F_CPU 16000000UL  // 16MHZ
#include <avr/io.h>  // PORTA PORTB등의 I/O 관련 registe
#include <util/delay.h>
#include <stdio.h>
#define  DHT_DDR DDRG
#define  DHT_PORT PORTG
#define  DHT_PIN PING
#define  DHT_PIN_NUM 0
#define HIGH 1
#define LOW  0

uint8_t us_count = 0;										//		  0   1   2
enum state_define{OK, TIMEOUT, VALUE_ERROR, TRANS_ERROR};	//enum ~{	,	,	};		#define ~에 대한 value를 자동적으로 메길 수 있다
enum state_define state = OK;



#endif /* DHT11_H_ */