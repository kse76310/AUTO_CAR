/*
 * ultrasonic.c
 *
 * Created: 2025-03-12 오후 2:49:28
 *  Author: microsoft
 */ 

#include "ultrasonic.h"
extern volatile int ultrasonic_check_timer;

void init_ultrasonic();
void trigger_ultrasonic();
void distance_ultrasonic();
void led_ultrasonic();

volatile int ultrasonic_dis_L=0;
volatile int ultrasonic_dis_M=0;
volatile int ultrasonic_dis_R=0;
volatile char scm_L[50];
volatile char scm_M[50];
volatile char scm_R[50];
//P278 표 12-3
//PE4: 외부INT4 초음파 센서의 상승, 하강 엣지 둘다 INT가 ISR(INT4_vect)로 들어온다.
//결국 2번(상승: 1 하강: 1) 들어온다.


ISR(INT4_vect)
{
	// 1 상승엣지
	if(ECHO_PIN & 1 << ECHO_LEFT)
	{
		TCNT2=0; // Timer 1 H/W counter를 clear
	}
	// 2 하강엣지
	else
	{
		//ECHO핀에 들어온 펄스 갯수를 us로 환산
		ultrasonic_dis_L = 1000000.0 * TCNT2 * 64 / F_CPU;
		//예) TCINT에 10이 들어있다고 가정
		//15.625KHz의 1주기 64us이다
		//0.000064sec(64us) * 10 ==> 0.00064sec(640us)
		//640us / 58us(1cm이동하는데 소요 시간) ==> 11cm이다
		// --- 1cm : 58us
		ultrasonic_dis_L /= 58;
		sprintf(scm_L,"dis_L= %dcm", ultrasonic_dis_L);	//cm환산
		
	}
	
}

ISR(INT5_vect)
{
	// 1 상승엣지
	if(ECHO_PIN & 1 << ECHO_FRONT)
	{
		TCNT2=0; // Timer 1 H/W counter를 clear
	}
	// 2 하강엣지
	else
	{
		//ECHO핀에 들어온 펄스 갯수를 us로 환산
		ultrasonic_dis_M = 1000000.0 * TCNT2 * 64 / F_CPU;
		//예) TCINT에 10이 들어있다고 가정
		//15.625KHz의 1주기 64us이다
		//0.000064sec(64us) * 10 ==> 0.00064sec(640us)
		//640us / 58us(1cm이동하는데 소요 시간) ==> 11cm이다
		// --- 1cm : 58us
		ultrasonic_dis_M /= 58;
		sprintf(scm_M,"dis_M= %dcm", ultrasonic_dis_M);	//cm환산
		
	}
	
}

ISR(INT6_vect)
{
	// 1 상승엣지
	if(ECHO_PIN & 1 << ECHO_RIGHT)
	{
		TCNT2=0; // Timer 1 H/W counter를 clear
	}
	// 2 하강엣지
	else
	{
		//ECHO핀에 들어온 펄스 갯수를 us로 환산
		ultrasonic_dis_R = 1000000.0 * TCNT2 * 64 / F_CPU;
		//예) TCINT에 10이 들어있다고 가정
		//15.625KHz의 1주기 64us이다
		//0.000064sec(64us) * 10 ==> 0.00064sec(640us)
		//640us / 58us(1cm이동하는데 소요 시간) ==> 11cm이다
		// --- 1cm : 58us
		ultrasonic_dis_R /= 58;
		sprintf(scm_R,"dis_R= %dcm", ultrasonic_dis_R);	//cm환산
		
	}
	
}

void init_ultrasonic(void)
{
	TRIG_DDR |= 1 << TRIG_LEFT | 1 << TRIG_FRONT | 1 << TRIG_RIGHT;
	ECHO_DDR &= ~(1 << ECHO_LEFT | 1 << ECHO_FRONT | 1 << ECHO_RIGHT); // input mode ECHO_DDR &= 0b11110111; 
	//p289 표  12-6
	//0 1 : 상승엣지(rising edge)와 하강(falling edge)둘다 INT 를 띄우도록 요청
	EICRB |= 0 << ISC41 | 1 << ISC40 | 0 << ISC51 | 1 << ISC50 | 0 << ISC61 | 1 << ISC60;
	//16bit timer1번을 설정을 해서 사용 65535(max) : 0xffff
	//16MHz를 1024로 분주 16000000Hz/1024 --> 15625Hz --> 15.625KHz
	//1주기 T(즈기) = 1/f = 1/15625 ==> 64us
	TCCR2 |= 1<< CS21 |1 << CS20;	//1024로 분주
	//p 287 표 14-1
	EIMSK |= 1 << INT4 | 1 << INT5 | 1 << INT6;	//EXTERNAL int 4(ECHO핀)
}

void trigger_ultrasonic()
{
	TRIG_PORT &= ~(1 << TRIG_LEFT | 1 << TRIG_FRONT | 1 << TRIG_RIGHT);	//low
	_delay_us(10);
	TRIG_PORT |= 1 << TRIG_LEFT | 1 << TRIG_FRONT | 1 << TRIG_RIGHT;		//high
	_delay_us(15);		//규격에는 10us인데 여유를 뒤서 15us 세팅
	TRIG_PORT &= ~(1 << TRIG_LEFT | 1 << TRIG_FRONT | 1 << TRIG_RIGHT);	//low
}

void distance_ultrasonic()
{
	if(ultrasonic_check_timer >= 5000)	//1초
	{
		ultrasonic_check_timer=0;
		printf("%s\n%s\n%s\n",scm_L,scm_M,scm_R);
		trigger_ultrasonic();
	}
}
