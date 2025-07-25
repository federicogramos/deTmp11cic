//==============================================================================
// Archivo: d7sm.h
// Autor: Federico Ramos
// Modificado: 2023-11-03
//==============================================================================


#ifndef __D7SM_PINDEF_H
#define __D7SM_PINDEF_H


//==============================================================================
// DEFINIR PINES DE ANODE
// Formato:
// #define D7SM_AN = RXX
// Donde N=0..5, N=0 -> less significant display
//==============================================================================
#define D7SM_A0 RC1
#define D7SM_A1 RA4
#define D7SM_A2 RC0
#define D7SM_A3 RC7


//==============================================================================
//FGR: REQUISITOS, DEFINIR PINES DE SEGMENTOS
//==============================================================================
#define D7SM_SA  RA5
#define D7SM_SB  RA7
#define D7SM_SC  RC3
#define D7SM_SD  RA6
#define D7SM_SE  RC4
#define D7SM_SF  RC6
#define D7SM_SG  RC5
#define D7SM_SDP RC2


#endif//__D7SM_PINDEF_H