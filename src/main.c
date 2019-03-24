/**
 * File:   main.c
 * Author: Ericson Joseph
 *
 * Created on October 14, 2018, 11:14 PM
 */

#include "main.h"
#include "board.h"
#include "myOS.h"
#include "sapi.h"
#include <stdint.h>
#include <strings.h>

#define STACK_SIZE_B 512

uint32_t stack1[STACK_SIZE_B / 4];
uint32_t stack2[STACK_SIZE_B / 4];
uint32_t stack3[STACK_SIZE_B / 4];

void *task1(void *args) {
    while (1) {
        gpioToggle(LED1);
        taskDelay(500);
    }
    return NULL;
}

void *task2(void *args) {
    while (1) {
        gpioToggle(LED2);
        taskDelay(100);
    }
    return NULL;
}

void *task3(void *args) {
    while (1) {
        gpioToggle(LED3);
        taskDelay(200);
    }
    return NULL;
}

int main() {

    MyOSInit();

    taskCreate(stack1, STACK_SIZE_B, task1, (void *)0x11223344);
    taskCreate(stack2, STACK_SIZE_B, task2, (void *)0x55667788);

    Board_Init();
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 1000);

    while (1) {
    }

    return 0;
}
