/**
 * @file   debounce.h
 * @author Ericson Joseph
 * @date   Apr 1, 2019
 *
 * @brief Debounce
 */

#include "sapi.h"
#include "debounce.h"

void debounceMEF(gpioMap_t pin, debounce_t *debonce) {

    bool_t tecValue = gpioRead(pin);

    switch (debonce->state) {
    case BUTTON_UP:
        if (tecValue == OFF) {
            debonce->state = BUTTON_FALLING;
        }
        break;
    case BUTTON_FALLING:
        if (tecValue == OFF) {
            debonce->state = BUTTON_DOWN;
        } else {
            debonce->state = BUTTON_UP;
        }
        break;
    case BUTTON_DOWN:
        if (tecValue == ON) {
            debonce->state = BUTTON_RASING;
        }
        break;
    case BUTTON_RASING:
        if (tecValue == ON) {
            debonce->state = BUTTON_UP;
        } else {
            debonce->state = BUTTON_DOWN;
        }
        break;
    default: break;
    }

    return;
}
