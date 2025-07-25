//==============================================================================
// ARCHIVO: pulsadorPinFast_1ms_aliases.h
// AUTOR: Federico Ramos
// ULT. MODIF: 2022-10-12
// PROYECTO: TMP:11:CIC
//==============================================================================


#ifndef __K_PIN__ALIASES_H
#define __K_PIN__ALIASES_H


//==============================================================================
// ALIAS
// Lo único que necesita para establecer el alias, es que sea coincidente con el
// nro de elemento del KEY con el que se invoca el driver del pulsador:
// Por ejemplo (definido en "kPin_pindef.h"):
// volatile bit KEY_0 @ ((unsigned)&PORTA*8)+0;//P0N_MENU
// Entonces, P0N_MENU va a ser el elemento definido como 0 en el alias.
enum e_kPinAlias
    {
	P0_MENU,
	P1_SET,
    P2_ACCEPT,
    IN1_FORCE,
    IN2_RST,
	PULS_PIN_CANT
    };
//==============================================================================


#endif//__K_PIN__ALIASES_H
