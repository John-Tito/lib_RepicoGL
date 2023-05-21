
#include "gear.hpp"
#include <Arduino.h>

hw_timer_t *tim1 = NULL;
uint32_t tim1_IRQ_count = 0, cnt_cpy = 0;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
void IRAM_ATTR tim1Interrupt()
{
    portENTER_CRITICAL_ISR(&timerMux);
    tim1_IRQ_count++;
    portEXIT_CRITICAL_ISR(&timerMux);
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Start");

    // start init 3D scene
    int ret = ui_init(&scene_init, &scene_update);
    if (ret != 0)
    {
        Serial.printf("error: ui_init unexpected end with code %d!\n", ret);
    }

    // create timer
    tim1 = timerBegin(0, 80, true); // 80MHZ, ESP32 主频 80MHz --> 1M
    timerAttachInterrupt(tim1, tim1Interrupt, true);
    timerAlarmWrite(tim1, 10000, true); // 100
    timerAlarmEnable(tim1);

    Serial.println("Start looping!");
}

void loop()
{
    if (cnt_cpy != tim1_IRQ_count)
    {
        cnt_cpy = tim1_IRQ_count;
        if (0 == cnt_cpy % 3)
        {
            ui_loop();
        }
    }
}