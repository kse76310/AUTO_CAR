/*
 * 01.LED_CONTROL.c
 *
 * Created: 2025-03-04 오후 4:25:34
 * Author : microsoft
 */ 

#include <avr/interrupt.h>
#include <stdio.h>		// printf
#include "button.h"
#include "extern.h"
#include "def.h"



void init_timer0(void);
void manul_mode(void);
void distance_check(void);
void auto_mode(void);

volatile int msec_count = 0;
volatile int ultrasonic_check_timer = 0;
volatile int button1_state= 0;

FILE OUTPUT = FDEV_SETUP_STREAM(UART0_transmit, NULL, _FDEV_SETUP_WRITE);

int func_index=MANUAL_MODE;

void(*pfunc[])() =
{
	manul_mode,			// 수동 mode
	distance_check,		// 초음파 거리 측정
	auto_mode_check,	// button check
	auto_mode			//자율주행 
	
};

// interrupt service routine은 반드시 main함수 이전에 정의한다.
ISR(TIMER0_OVF_vect)
{
	TCNT0 = 6; // 6 ~ 256으로 돌리기 위해
	msec_count++;
	ultrasonic_check_timer++;
}



int main(void)
{
	
	init_uart0();
	init_uart1();
	init_L298N();
	init_button();
	init_timer0();
	init_timer1();
	init_ultrasonic();
	init_speaker();
	
	stdout = &OUTPUT;
	sei();
	
	
	while(1)
	{		
		Beep(5);
		
		// 		Siren(5);
		// 		_delay_ms(3000);
		//auto_mode_check();
		//pfunc[func_index]();
	}
	
	
	return 0;
}



// AVR의 8bit counter timer0를 초기화한다.
// 임베디드/FPGA에서 가장 중요한건 초기화 -> init함수는 특히 신경쓰기!!
void init_timer0(void)
{
	// 분주 (divider / prescale)
	// 16MHz / 64 down!!
	// 16000000Hz / 64 = 250,000 Hz 로 만든다!
	// T(주기) = 1clock에 걸리는 시간 = 1 / 250000 = 0.000004sec = 0.004ms (4us)
	// 8bit timer overflow 발생 시 소요시간 = 0.004ms * 256 = 1.024ms = 0.001024sec
	//	-> interrupt를 정확하게 1ms마다 오게 하고싶으면, 
	//    사용자 지정으로 256이 아니라 250클록마다 인터럽트가 생기도록
	
	// TCMT0 초기값 설정
	TCNT0 = 6; // 정확히 1ms를 세기 위해 초기값을 0이 아니라 6으로 해준다. (250 펄스 이후에 인터럽트)
	
	// 분주비 설정 (64)
	TCCR0 |= 1 << CS02 | 0 << CS01 | 0 << CS00;
	
	// timer overflow interrupt 허용 (TIMER0 OVF)
	TIMSK |= 1 << TOIE0;	// 지역 인터럽트 허용

	
}


void manul_mode(void) // 수동 mode
{
	switch (bt_data)
	{
		case 'F':
		case 'f':
			forward(700);	// 4us X 500 = 0.002sec(2ms)
			break;
		case 'B':
		case 'b':
			backward(700);	// 4us X 500 = 0.002sec(2ms)
			break;
		case 'L':
		case 'l':
			turn_left(700);
			break;
		case 'R':
		case 'r':
			turn_right(700);
			break;
		case 'S':
		case 's':
			stop();
			break;
		default:
			break;
	}
	
	func_index=DISTANCE_CHECK;
}

void distance_check(void)		// 초음파 거리 측정
{
	func_index=MODE_CHECK;
}


void auto_mode(void)	// 자율주행 모드
{
	forward(300);
	
	func_index = MANUAL_MODE;
}
