/*! \mainpage myOS Documentation
 *
 * \section intro_sec Introduction
 *
 * Enthusiast Operating System (myOS) for embedded system ARM Cortex-M.
 *
 */

/**
 * @file    main.c
 * @author  Ericson Joseph
 * @date    March 2019
 *
 * @brief   Main program body
 */

/* Include ----------------------------------------- */

#include <stdlib.h>
#include <stdint.h>
#include <strings.h>

/* Private Include --------------------------------- */

#include "main.h"
#include "board.h"
#include "myOS.h"
#include "sapi.h"
#include "semphr.h"
#include "double_buffer.h"
#include "queue.h"
#include "sapi_uart.h"

/* Private typedef --------------------------------- */

typedef enum { UP, DOWN } ButtonState;

/* Private define ---------------------------------- */

#define EJ0
#define EJ1
//#define EJ2
#define EJ3
#define EJ5

#define STACK_SIZE_1024 1024
#define STACK_SIZE_512 512
#define DOUBLE_BUFFER_SIZE 240

/* Private variables ------------------------------- */

uint32_t ledOnTimeTick;
semaphore_t xSemEj1;

semaphore_t xSemEj2;
int16_t Buffer_Rest[240];

queueHandler queue;

/* Private function prototypes --------------------- */

#ifdef EJ0
void *task1(void *args) {
    while (1) {
        gpioToggle(LED1);
        taskDelay(200);
    }
    return NULL;
}

void *task2(void *args) {
    while (1) {
        gpioToggle(LED2);
        taskDelay(500);
    }
    return NULL;
}

void *task3(void *args) {
    while (1) {
        gpioToggle(LED3);
        taskDelay(100);
    }
    return NULL;
}
#endif

#ifdef EJ1
void *buttonTask(void *taskParm) {

    ButtonState state = UP;
    uint32_t onTime;

    while (TRUE) {

        taskDelay(10);

        if (!gpioRead(TEC1) && state == UP) {
            taskDelay(20);
            if (!gpioRead(TEC1)) {
                state  = DOWN;
                onTime = getTickCount();
            }
        }

        if (gpioRead(TEC1) && state == DOWN) {
            taskDelay(20);
            if (gpioRead(TEC1)) {
                state         = UP;
                onTime        = getTickCount() - onTime;
                ledOnTimeTick = onTime;
                semaphoreGive(&xSemEj1);
            }
        }
    }
}

void *ledTask2(void *taskParmPtr) {
    while (TRUE) {
        semaphoreTakeBlocking(&xSemEj1);
        gpioWrite(LEDB, ON);
        taskDelay(ledOnTimeTick);
        gpioWrite(LEDB, OFF);
    }
}

#endif

#ifdef EJ2
void uDelay(uint32_t microsec) {
    uint32_t start = DWT->CYCCNT / 204;
    uint32_t end   = DWT->CYCCNT / 204;
    while ((end - start) < microsec) {
        end = DWT->CYCCNT / 204;
    }
}

void *fillBuffer(void *taskParamPtr) {
    DWT->CTRL |= 0x00000001; // enable the counter
    DBUFF_initBuffer(DOUBLE_BUFFER_SIZE * (sizeof(int16_t)));
    while (1) {
        for (uint32_t i = 0; i < DOUBLE_BUFFER_SIZE; ++i) {
            int16_t val = rand() & 0xFFFF;
            DBUFF_setValue(i, val);
            uDelay(25);
        }
        DBUFF_flush();
        semaphoreGive(&xSemEj2);
    }
}

void *multBuffer(void *taskParamPtr) {
    while (1) {
        semaphoreTakeBlocking(&xSemEj2);
        for (uint32_t i = 0; i < DOUBLE_BUFFER_SIZE; ++i) {
            Buffer_Rest[i] = DBUFF_getValue(i) * 2;
        }
    }
}
#endif

#ifdef EJ3

void *qButtonTask(void *taskParamPtr) {

    ButtonState state = UP;
    uint32_t onTime;

    while (TRUE) {

        taskDelay(10);

        if (!gpioRead(TEC1) && state == UP) {
            taskDelay(20);
            if (!gpioRead(TEC1)) {
                state  = DOWN;
                onTime = getTickCount();
            }
        }

        if (gpioRead(TEC1) && state == DOWN) {
            taskDelay(20);
            if (gpioRead(TEC1)) {
                state  = UP;
                onTime = getTickCount() - onTime;
                queueSend(queue, &onTime);
            }
        }
    }
}

void *qLedTask(void *taskParamPtr) {
    while (TRUE) {
        uint32_t onTime;
        queueReceiveBlocking(queue, &onTime);
        gpioWrite(LEDB, ON);
        taskDelay(onTime);
        gpioWrite(LEDB, OFF);
        taskDelay(1000); // PARA MOSTRAR SI SE ENCOLAN VIAS PULSACIONES
    }
}

#endif

#ifdef EJ5

char bufferOut[50];
char numFloat[10];

void *uartTxTask(void *taskParamPtr) {
    while (TRUE) {
        taskDelay(1000);
        os_monitor_s monitor = getMonitor();
        float idlePerc       = ((float)(monitor.idle_ticks) / 1000) * 100.0;
        gcvt(idlePerc, 4, numFloat);
        sprintf(bufferOut, "IDLE: %s %%", numFloat);
        monitorReset();
        uartWriteString(UART_USB, bufferOut);
    }
}

void usbRXCallback(void *nSnR) {
    while (uartRxReady(UART_USB)) {
        uint8_t byteRx;
        byteRx = uartRxRead(UART_USB);
        uartWriteByte(UART_USB, byteRx);
    }
}

#endif

/* Code -------------------------------------------- */

int main() {

    MyOSInit();

#ifdef EJ0
    taskCreate(STACK_SIZE_512, task1, 2, (void *)0x11223344);
    taskCreate(STACK_SIZE_512, task2, 2, (void *)0x55667788);
    taskCreate(STACK_SIZE_512, task3, 2, (void *)0x55667788);
#endif

#ifdef EJ1
    semaphoreCreate(&xSemEj1);
    taskCreate(STACK_SIZE_512, buttonTask, 2, (void *)0x11223344);
    taskCreate(STACK_SIZE_512, ledTask2, 2, (void *)0x55667788);
#endif

#ifdef EJ2
    semaphoreCreate(&xSemEj2);
    taskCreate(STACK_SIZE_512, fillBuffer, 2, (void *)0);
    taskCreate(STACK_SIZE_512, multBuffer, 2, (void *)0);
#endif

#ifdef EJ3
    queue = queueCreate(10, sizeof(uint32_t));
    taskCreate(STACK_SIZE_512, qButtonTask, 3, (void *)0);
    taskCreate(STACK_SIZE_512, qLedTask, 4, (void *)0);
#endif

#ifdef EJ5
    taskCreate(STACK_SIZE_1024, uartTxTask, 1, (void *)0);
#endif

    Board_Init();
    SystemCoreClockUpdate();
    NVIC_SetPriority(PendSV_IRQn, PRIORITY_PENDSV);

#ifdef EJ5
    uartConfig(UART_USB, 115200);
    uartCallbackSet(UART_USB, UART_RECEIVE, usbRXCallback, NULL);
    //    uartInterrupt(UART_USB, true);
#endif

    SysTick_Config(SystemCoreClock / 1000);

    while (1) {
    }

    return 0;
}
