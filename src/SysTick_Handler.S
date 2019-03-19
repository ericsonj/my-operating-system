    .syntax unified
    .text
    .global SysTick_Handler
    .extern get_next_context
    .extern addTickCount
    .thumb_func

SysTick_Handler:
        push    {r4-r11, lr}
        bl		addTickCount
        mrs     r0, msp
        bl      get_next_context
        msr     msp, r0
     	pop	{r4-r11, lr}
return:
        bx      lr
