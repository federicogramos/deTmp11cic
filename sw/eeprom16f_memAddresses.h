//==============================================================================
// Archivo: eeprom16f_memAddresses.h
// Autor: Federico Ramos
// Modificado: 16-11-2023 1539
//
// La inicialización de eeprom se hace al lado de la invocación de la librería, 
// de otro modo inicializa repetidamente la memoria, generando duplicados.
//==============================================================================


#ifndef __EEPROM16F__MEM_ADDRESSES_H
#define __EEPROM16F__MEM_ADDRESSES_H


//==============================================================================
// MAPA DE MEMORIA Y UBICACIÓN SEGUN TAMAÑO DE DATOS EN EEPROM
// Nombres siguen la regla: __ para separación de "espacio" y _ para separar 2 p
// alabras.
//==============================================================================
enum e_eeprom
	{
	EEADDR__00_00__INPUT,
	EEADDR__01_00__VISOR_PARPADEO = EEADDR__00_00__INPUT+sizeof(char),
	EEADDR__02_00__NMEM = EEADDR__01_00__VISOR_PARPADEO+sizeof(char),
    EEADDR__03_00__INTERMITENCIA_OUTPUT = EEADDR__02_00__NMEM+sizeof(char),
    EEADDR__04_00__FIRST = EEADDR__03_00__INTERMITENCIA_OUTPUT+sizeof(char),

	EEADDR__16_00__TON_OFF=16,

	};


#endif // __EEPROM16F__MEM_ADDRESSES_H