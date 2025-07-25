//==============================================================================
// ARCHIVO: kPinFast_1ms_pindef.h
// AUTOR: Federico Ramos
// ULT. MODIF: 03-11-2023
// PROYECTO: TMP:11:CIC
//==============================================================================


#ifndef __KPIN_FAST_1MS_PINDEF_H
#define __KPIN_FAST_1MS_PINDEF_H


//==============================================================================
// CONFIGURACION TIEMPO ANTIREBOTE
// Tiempo recomendado de filtro antirebote = 20ms
// Tiempo resultante antirebote = tInterrupción * K_PIN__N_ANTIREBOTE
// Ejemplo: interrupción cada 1ms => 1ms * 10 = 10ms de antirebote
#define KPIN__N_ANTIREBOTE 25
//==============================================================================


//==============================================================================
// SETEAR PUERTOS UTILIZADOS COMO PULSADORES
// 23-09-2022 ESTO ESTA CONFIGURADO PARA PROYECTO "RPM"
volatile bit KEY_0 @ ((unsigned)&PORTA*8)+0;// P0_MENU
volatile bit KEY_1 @ ((unsigned)&PORTA*8)+2;// P1_SET
volatile bit KEY_2 @ ((unsigned)&PORTE*8)+3;// P2_ACCEPT
volatile bit KEY_3 @ ((unsigned)&PORTB*8)+0;// IN1_FORCE
volatile bit KEY_4 @ ((unsigned)&PORTB*8)+2;// IN2_RST

//UNUSED
//volatile bit KEY_5 @ ((unsigned)&PORTA*8)+1;
//volatile bit KEY_6 @ ((unsigned)&PORTD*8)+0;
//volatile bit KEY_7 @ ((unsigned)&PORTD*8)+1;
//volatile bit KEY_8 @ ((unsigned)&PORTC*8)+1;
//==============================================================================


//==============================================================================
// COMPLETAR ESTRUCTURA PRINCIPAL
// LA CANTIDAD DE ELEMENTOS CORRESPONDE A LA CANTIDAD DE PULSADORES
// {state,prevState,timer}={1,1,0} --> inicializan quietos
t_kPin kPin[PULS_PIN_CANT]=
    {
	{1,1,0},// P0_MENU
	{1,1,0},// P1_SET
    {1,1,0},// P2_ACCEPT
    {1,1,0},// IN1_FORCE
    {1,1,0} // IN2_RST
    };
//==============================================================================


#endif//__KPIN_FAST_1MS_PINDEF_H
