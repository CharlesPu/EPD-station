#include <Arduino.h>

void TIM_ISR(void)
{
   Serial.printf("AAAAAAAA\r\n");
}

void timer_init(uint32_t arr, void (*f)())
{
    hw_timer_t *timer = timerBegin(0, 80, true);         /* 初始化定时器0 */

    timerAlarmWrite(timer, arr*1000, true);               /* 设置中断时间 */

    timerAttachInterrupt(timer, f, true);    /* 配置定时器中断回调函数 */

    timerAlarmEnable(timer);                         /* 使能定时器中断 */
	printf("timer0 init success!\r\n");
}


