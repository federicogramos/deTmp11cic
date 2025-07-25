//==============================================================================
// Archivo: main.c
// Autor: Federico Ramos
// Modificado: 03-11-2023
//==============================================================================


//==============================================================================
// INCLUDE
#include <projectHeader.h>
#include <eeprom16f_memInitialization.h>
#include <eeprom16f.h>

#include <main.h>// Contiene fuses y otras cosas.
#include <system.h>// Para la inicialización del sistema.
#include <interrupts.h>
#include <t0.h>

#include <kPin.h>
#include <tmp_11.h>
#include <d7sm.h>
#include <fsm.h>
//==============================================================================

#include <t1.h>

// No lo puedo poner dentro de la acción a_showTime porque ésta solamente corre
// cuando está en "idle".
void driver_ledSet(void)
    {
    // Otro agregado: titileo led setting.
    if(tmp_11.flag_inputSettingLedBlink) LED14N = bitTitila;
    else LED14N = 0;
    }

//==============================================================================
// FUNCTION
//==============================================================================
void main(void)
	{
	char new_event;

	systemInit();
    FSM_INIT();

//tmp_11.flag_inputSettingLedBlink = 1;

	while(1)
		{
        //fsmParser();

        driver_ledSet();

        FSM_PARSER();

        D7SM_SCROLL_DRIVER();
		}
	}
