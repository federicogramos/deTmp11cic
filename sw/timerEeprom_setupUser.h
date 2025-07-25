//******************************************************************************
// ARCHIVO: timerEeprom_user_settings.h
//******************************************************************************


#ifndef __TIMEREEPROM_USER_SETTINGS_H
#define __TIMEREEPROM_USER_SETTINGS_H


//******************************************************************************
// ALIAS
typedef short long type_timerEepromSize;//TAMAÑO DE VARIABLE QUE VA A CONTABILIZAR EL TIEMPO: char, int, long (unsigned or not)
typedef const type_timerEepromSize type_timerEepromDelayConstant;//SE GENERA UN ARRAY QUE CONTIENE LOS TIEMPOS DE DURACIÓN DE CADA TIMER. SE PUEDE DECLARAR "const" A ESTE TIPO DE DATO, PARA QUE NO OCUPE RAM EN CASO DE NO NECESITAR ALTERAR EL TIEMPO DE LOS TEMPORIZADORES.
//******************************************************************************


#endif//__TIMEREEPROM