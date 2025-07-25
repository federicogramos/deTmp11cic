//==============================================================================
// ARCHIVO: t0_delays.h
//==============================================================================


#ifndef __T0_DELAYS_H
#define __T0_DELAYS_H


//==============================================================================
// DEFINICION DE TIEMPOS POR PARTE DEL USUARIO
//==============================================================================
type_t0DelayConstant t0DelayConstant[T0_CANT]=
    {
    2*4,//TMR_TEST_DISPLAY=2s (base de tiempo timer=0.25s)
    10*4,//TMR_RETURN(base de tiempo timer=0.25s)
    4*4,//TMR_PULSADO_LARGO_HOLD(base de tiempo timer=0.25s)
    2*4,//TMR_PULSADO_LARGO_SILENT(base de tiempo timer=0.25s)
    1//TMR_7SEG_SCROLL(base de tiempo timer=0.25s)
    };


#endif//__T0_DELAYS_H