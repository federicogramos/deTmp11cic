//==============================================================================
// Archivo: system.c
// Autor: Federico Ramos
// Modificado: 03-11-2023
//==============================================================================


//==============================================================================
// INCLUDE
#include <projectHeader.h>
#include <system.h>
#include <interrupts.h>
//==============================================================================


//==============================================================================
// FUNCTION
//==============================================================================
void systemInit(void)
    {
    PIC16F886_8MHZ();
    
    CCP1M0=0;
    CCP1M1=0;
    CCP1M2=0;
    CCP1M3=0;
    
    CCP2M0=0;
    CCP2M1=0;
    CCP2M2=0;
    CCP2M3=0;
    
    //DISABLE_COMPARATOR();// De todos los periféricos que no se usan y existen en el microcontrolador, el único que arranca en un modo que no es convieniente, es el comparador, por lo que al iniciar, se lo pone en la configuración óptima para deshabilitarlo.
    
    IRQ_TIMER1_SETUP();// Setup interrupt. Timer1 16 bit timer.
    IRQ_TIMER0_SETUP();
    
    DISABLE_AD();
    
    RBPU=0;//Habilito pull-ups
    WPUB6=0;//RB6 deshabilito individualmente Pull-up porque es el lock, y no quiero que tire para arriba
    
    ANSEL=0;// deshabilito todos los analogicos para que todos los pull ups puedan estar
    ANSELH=0;
    
    INIT_DDR();// Establece los puertos de entrada/salida.
    INIT_PORTS()
    
    IRQ_TIMER1_ENABLE();
    IRQ_TIMER0_ENABLE();
    
    IRQ_PERIPHERAL_ENABLE();// Timer 1 interrupt entra dentro de las "peripheral interrupts", por lo que debo habilitarlas para que funcione.
    IRQ_ENABLE();// Enable all interrupts
    }

