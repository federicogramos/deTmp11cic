//==============================================================================
// Archivo: tmp_11.c
// Autor: Federico Ramos
// Modificado: 03-11-2023
//==============================================================================


//==============================================================================
// INCLUDE
#include <projectHeader.h>
#include <tmp_11.h>
#include <system.h>// Para la inicialización del sistema.
#include <t0.h>
#include <kPin.h>
#include <d7sm.h>
#include <string.h>
#include <eeprom16f.h>
//==============================================================================


//==============================================================================
// DEFINICION DE VARIABLES
t_temporizador tmp_11=
	{
    0,// unsigned char flag_showTimerId:1;// Permite identificar si muestro tiem
    // po o id del timer en curso.
    0,// unsigned char flag_showHyphens:1;// Cuando locked, si aprieto algo, mue
    // stra "----" y no hace nada.
    0,// unsigned char flag_locked:1; // Bloquea seteos. Toma RB6 al booteo.
    0,// unsigned char flag_inputSettingLedBlink:1;// Ingese valor del seteo.
    0,// unsigned char flag_outForce:1;// Indica si output is forced. Antes de c
    // ambiar el estado de la salida, revisa si se encuentra forzada.
    0,// unsigned char flag_outForceVal:1;// Force value if forced.
    0,// unsigned char flag_showTimeBlink:1;// Action showTime, que se da dentro de e

    0,// unsigned char mem_input:2;
	0,// unsigned char mem_visor_parpadeo:1;
    0,// unsigned char mem_first:1;
	0,// unsigned char mem_cantMemorias;// Cant máxima de memorias = 40 (0..39)

	0,// char mainMenuState;
	0,// char menuCharAuxiliar;
    0,// menuShortLongAuxiliar

	0,// char configSetting;

    EEADDR__16_00__TON_OFF,// p2eepromAddr

	{0}// char str[TMP11_MAX_STRLEN];
    };


char bitTitila;
//==============================================================================


//==============================================================================
// 6789 => str[0] str[1] str[2] str[3] str[4] str[5] => ? ? 6 7 8 9
//==============================================================================
void ucharToStr(unsigned char num,char *p2str,char strLen)
	{
	char i;
	
	p2str+=strLen-1;
	for(i=0;i<strLen;i++)
		{
		*(p2str--)='0'+(num%10);
		num/=10;
		}
	}
