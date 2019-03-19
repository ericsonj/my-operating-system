/**
 * File:   main.c
 * Author: Ericson Joseph
 *
 * Created on October 14, 2018, 11:14 PM
 */

#include "main.h"
#include "board.h"
#include "sapi.h"
#include <stdint.h>
#include <strings.h>

#define STACK_SIZE_B 512

uint32_t tickCount = 0;

typedef void *(*task_type)(void *);

uint32_t stack1[STACK_SIZE_B / 4];
uint32_t stack2[STACK_SIZE_B / 4];
uint32_t sp1, sp2;
uint32_t current_task;

void tickDelay(uint32_t delay) {
    uint32_t tickStart = tickCount;
    while ((tickCount - tickStart) < (delay - 1)) {
    }
}

void *task1(void *args) {
    while (1) {
        gpioToggle(LED1);
        tickDelay(1000);
    }
    return NULL;
}

void *task2(void *args) {
    while (1) {
        gpioToggle(LED2);
        tickDelay(500);
    }
    return NULL;
}

void taskReturnHook(void *arg) {
    while (1) {
        __WFI();
    }
}

void addTickCount(void) { tickCount++; }

uint32_t get_next_context(uint32_t current_sp) {

    uint32_t next_sp;

    switch (current_task) {
    case 0:
        next_sp      = sp1;
        current_task = 1;
        break;
    case 1:
        sp1          = current_sp;
        next_sp      = sp2;
        current_task = 2;
        break;
    case 2:
        sp2          = current_sp;
        next_sp      = sp1;
        current_task = 1;
        break;
    default:
        while (1) {
            __WFI();
        }
        break;
    }

    return next_sp;
}

void initStack(uint32_t stack[],
               uint32_t stackSizeBytes,
               uint32_t *sp,
               task_type entry_point,
               void *args) {

    bzero(stack, stackSizeBytes);

    stack[stackSizeBytes / 4 - 1] = 1 << 24;                  // xPSR
    stack[stackSizeBytes / 4 - 2] = (uint32_t)entry_point;    // PC
    stack[stackSizeBytes / 4 - 3] = (uint32_t)taskReturnHook; // LR
    stack[stackSizeBytes / 4 - 8] = (uint32_t)args;           // R0
    stack[stackSizeBytes / 4 - 9] = 0xFFFFFFF9;               // LR IRQ

    //    // considerando los 8 registros pusheados
    void *stackDir = &(stack[stackSizeBytes / 4 - 17]);
    *sp            = (uint32_t)stackDir;
}

int main() {

    initStack(stack1, STACK_SIZE_B, &sp1, task1, (void *)0x11223344);
    initStack(stack2, STACK_SIZE_B, &sp2, task2, (void *)0x55667788);

    Board_Init();
    SystemCoreClockUpdate();
    SysTick_Config(SystemCoreClock / 1000);

    while (1) {
    }

    return 0;
}
