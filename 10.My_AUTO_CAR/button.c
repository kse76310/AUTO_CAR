/*
 * button.c
 *
 * Created: 2025-03-05 오후 2:30:27
 *  Author: microsoft
 */ 
#include "button.h"
#include "extern.h"
#include "led.h"
#include "def.h"

#define FUNC_NUMBER 3		
uint8_t button_state[2]={0};
  
void init_button(void);
int get_button(int button_num, int button_pin);
void auto_mode_check(void);
                                            
void init_button(void)
{
	BUTTON_DDR &= ~( 1 << BUTTON0PIN );
}
// 예) 
// BUTTON0 : S/W 번호  --> button_num
// BUTTON0PIN : button_pin  
// 리턴값 : 1 :  버튼을 눌렀다 떼면 1을 return 
//          0 :  ide 

int get_button(int button_num, int button_pin)
{
	static unsigned char button_status[BUTTON_NUMER] =
	{BUTTON_RELEASE};	
	// 	지역 변수에 static을 쓰면 전역 변수처럼 함수를 빠져 나갔다 다시 들어 와도 값을 유지 한다.  
	int currtn_state;
	
	currtn_state = BUTTON_PIN & (1 << button_pin);   // 버튼을 읽는다. 
	if (currtn_state && button_status[button_num] == BUTTON_RELEASE)  // 버튼이 처음 눌려진 noise high 
	{
		_delay_ms(60);   // noise가 지나가기를 기다린다. 
		button_status[button_num] = BUTTON_PRESS;   // noise가 지나간 상태의 High 상태 
		return 0;   // 아직은 완전히 눌렸다 떼어진 상태가 아니다. 
	}
	else if (currtn_state==BUTTON_RELEASE && button_status[button_num] == BUTTON_PRESS)
	{
		_delay_ms(60);
		button_status[button_num] = BUTTON_RELEASE;   // 다음 버튼 체크를 위해서 초기화
		return 1;   // 완전히 1번 눌렸다 떼어진 상태로 인정		
	}
	
	return 0;   // 버튼이 open상태 
}


void auto_mode_check(void)		// 버튼 상태 체크 및 모드 변경
{
	static uint8_t button_state = 0;  // 현재 모드 (0 = 수동, 1 = 자동)

	
	// 버튼이 눌렸을 때 (떼어졌을 때 상태 변화를 감지)
	if (get_button(BUTTON0, BUTTON0PIN))
	{
		button_state = !button_state;  // 모드 전환
		
		if (button_state)
		{
			AUTO_RUN_LED_PORT |= (1 << AUTO_RUN_LED_PIN);	// LED ON
			func_index = AUTO_MODE;  // 자율 주행 모드로 변경
		}
		else
		{
			AUTO_RUN_LED_PORT &= ~(1 << AUTO_RUN_LED_PIN);	// LED OFF
			stop();  // 모터 정지
			func_index = MANUAL_MODE;  // 수동 모드로 변경
		}
	}
}
