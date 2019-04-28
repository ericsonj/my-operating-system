/**
 * @file   debounce.h
 * @author Ericson Joseph
 * @date   Apr 1, 2019
 *
 * @brief Debounce
 */

/*
 * debounce.h
 *
 *  Created on: Mar 29, 2018
 *      Author: Ericson Joseph
 */

#ifndef TPS_MYPROJECTTP3_INC_DEBOUNCE_H_
#define TPS_MYPROJECTTP3_INC_DEBOUNCE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "sapi.h"

typedef enum {
    BUTTON_UP,
    BUTTON_FALLING,
    BUTTON_DOWN,
    BUTTON_RASING
} buttonState_t;

typedef struct {
    buttonState_t state;
    uint32_t touchs;
} debounce_t;

void debounceMEF(gpioMap_t pin, debounce_t *debonce);

#ifdef __cplusplus
}
#endif

#endif /* TPS_MYPROJECTTP3_INC_DEBOUNCE_H_ */
