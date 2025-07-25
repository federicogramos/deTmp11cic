//==============================================================================
// Archivo: interrupts.c
// Autor: Federico Ramos
// Modificado: 20240613
//==============================================================================


//==============================================================================
// INCLUDE
//==============================================================================
#include <projectHeader.h>
#include <interrupts.h>
#include <t0.h>
#include <t1.h>
#include <kPin.h>
#include <d7sm.h>
#include <tmp_11.h>
#include <system.h>


//==============================================================================
// FUNCTION
//==============================================================================
void interrupt isr(void)
	{
	if(IRQ_TIMER0)//tmp_11_xxxv: 1ms
		{
		IRQ_TIMER0_SET(IRQ_TIMER0_RESET_VAL);

		D7SM_IRQ_DRIVER();

        kPin_driverDc(P0_MENU, KEY_0);
        kPin_driverDc(P1_SET, KEY_1);
        kPin_driverDc(P2_ACCEPT, KEY_2);
        kPin_driverDc(IN1_FORCE, KEY_3);
        kPin_driverDc(IN2_RST, KEY_4);

		IRQ_TIMER0_RESET_FLAG();
		}

	if(IRQ_TIMER1)//tmp_11_xxxv: 250ms
		{
		IRQ_TIMER1_SET(IRQ_TIMER1_RESET_VAL);

        t0Driver(T0_TESTDISPLAY);

		t0Driver(T0_MENU_RETURN);
		t0Driver(T0_PULSADO_LARGO_HOLD);
		t0Driver(T0_PULSADO_LARGO_SILENT);
		t0Driver(T0_D7SM_SCROLL);

        t1Driver(T1_TIME);

		bitTitila=bitTitila?0:1;

		IRQ_TIMER1_RESET_FLAG();
		}
	}
