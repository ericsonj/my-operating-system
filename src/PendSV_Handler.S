/**
 * @file   PendSV_Handler.S
 * @author Ericson Joseph
 * @date   March 2019
 */

    .syntax unified
    .text
    .global PendSV_Handler
    .extern get_next_context
    .extern addTickCount
    .thumb_func

PendSV_Handler:

 		/* context FPU */
		tst		lr, 0x10 // lr & 0x10
		it		eq // si resultado da igual (cero)
		vpusheq	{s16-s31} /*  */

        push    {r4-r11, lr}
        mrs     r0, msp
        bl      get_next_context
        msr     msp, r0
     	pop	    {r4-r11, lr}

		tst		lr, 0x10
		it		eq
		vpopeq	{s16-s31}

return:
        bx      lr
