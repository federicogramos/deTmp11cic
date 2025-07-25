//********************************************************************************
// ARCHIVO: disp7segMux_user_settings.h
// ULT: MODIF: 2022-12-02
//********************************************************************************


#ifndef __DISP7SEG_USER_SETTINGS_H
#define __DISP7SEG_USER_SETTINGS_H


//********************************************************************************
// INCLUDES
#include <t0.h>//LIBRERÍA DONDE DEFINO TMR0_DISP7SEGMUX_SCROLL
//********************************************************************************


//********************************************************************************
// INCLUDES USUARIO
#include <tmp_11.h>//REQUERIDA PARA DISP7SEGMUX_DEFAULT_STRING tmp_11_xxxv.str
//********************************************************************************


//********************************************************************************
// DEFINICION POR PARTE DEL USUARIO, EL STRING QUE VA A BARRER Y MOSTRAR EN PANTALLA
#define DISP7SEGMUX_DEFAULT_STRING tmp_11_xxxv.str
//********************************************************************************


//********************************************************************************
//FGR: REQUISITOS, DEFINIR CONSTANTES
#define D7SM_LENGTH 4
#define OFF_PERIODS 12 //FGR: CUANTO MAS GRANDE, MAS ATENUA BRILLO
#define D7SM_SCROLL_STRING_LENGTH 8 //PARA STRINGS EN RAM, QUE USAN disp7segMux_charString[]
//********************************************************************************


//********************************************************************************
// FGR: ESTRUCTURAS
// SE COLOCA EN USER SETTINGS PORQUE DEPENDIENDO DE CANTIDAD DE DISPLAYS DEBO AJUSTAR CANTIDAD DE TITILA Y DOTS
typedef struct
    {
    char *str;//STRING POINTER TO MEMORY THAT WILL BE DISPLAYED (ARRAY SIZE = DISPLAY LENGTH)
    char strOffs;
    char strLen;//NO NECESARIAMENTE ES LA CANTIDAD DE DISPLAYS, PORQUE EN SCROLL PUEDE SER CUALQUIER COSA
    char mux_state;
    char d0_titila:1;//SI DISPLAY LENGTH ES VARIABLE, ESTO DEBERÍA SER VARIABLE
    char d1_titila:1;
    char d2_titila:1;
    char d3_titila:1;
    char d0_dp:1;//IDEM ANTERIOR
    char d1_dp:1;
    char d2_dp:1;
    char d3_dp:1;
    }t_disp7segMux;
//********************************************************************************


//==============================================================================
// FLAGS CUSTOMIZACION COMPILACIÓN
//==============================================================================
#define D7SM_PRINTF_ENABLE_FMT_U

#endif//__DISP7SEG_USER_SETTINGS_H