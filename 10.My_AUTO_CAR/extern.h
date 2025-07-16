/*
 * extern.h
 *
 * Created: 2025-03-20 오전 11:29:18
 *  Author: microsoft
 */ 


#ifndef EXTERN_H_
#define EXTERN_H_


//---uart---
extern void init_uart0(void);
extern void init_uart1(void);

extern void UART0_transmit(uint8_t data);
extern void UART1_transmit(uint8_t data);


extern void bt_command_processing(void);
extern void distance_ultrasonic();
extern void init_ultrasonic();
extern void led_ultrasonic();
//---버튼---
extern void init_button(void);
extern int get_button(int button_num, int button_pin);
extern void auto_mode_check(void);
//---타이머---
extern void init_timer1(void);
//---pwm---
extern void init_L298N(void);
extern void stop(void);
extern void forward(int speed);
extern void backward(int speed);
extern void turn_left(int speed);
extern void turn_right(int speed);
//---led---
extern void init_led(void);

//--buzzer--
extern void init_speaker(void);
extern void Siren(int repeat);
extern void Beep(int  repeat);


extern volatile uint8_t bt_data;
extern volatile int rear; // push (ISR에서)
extern volatile int front; // pop (main에서)

extern int func_index;

#endif /* EXTERN_H_ */