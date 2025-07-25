//==============================================================================
// Archivo: t1_setupUser.h
//==============================================================================


#ifndef __T1__SETUP_USER_H
#define __T1__SETUP_USER_H


//==============================================================================
// ALIAS
// 02-12-2022 0408: aparentemente, si pongo unsigned short long, no funciona por
// que se equivoca al hacer la resta en el prescaker. Parece un error del compil
// ador. Estuve siguiendo el disassembly listing, y falla el codigo.

typedef short long type_t1Size;// Tamaño de variable que va a contabilizar el ti
// empo: char, int, long (unsigned or not)
typedef type_t1Size type_t1DelayConstant;// Se genera un array que contiene los 
// tiempos de duración de cada timer. Se puede declarar "const" a este tipo de d
// ato para que no ocupe RAM (en caso de no necesitar alterar el tiempo de los t
// emporizadores).
//==============================================================================


#endif//__T1__SETUP_USER_H