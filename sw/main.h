////////////////////////////////////////////////////////////////////////////////
// main.h                                                                     //
////////////////////////////////////////////////////////////////////////////////

#ifndef __MAIN_H
#define __MAIN_H

__CONFIG(CPD & PROTECT & BOREN & MCLRDIS & PWRTEN & WDTDIS & INTIO & LVPDIS);
//__CONFIG(PROTECT & BOREN & MCLRDIS & PWRTEN & WDTDIS & INTIO & LVPDIS);
//__CONFIG(CPD & PROTECT & BOREN & MCLRDIS & PWRTEN & WDTDIS & INTCLK & LVPDIS);
__CONFIG(BORV21);

// PARA VER CLOCKOUT = INTCLK EN LUGAR DE INTIO
/* data protect on */ 
/* code protection on */
/* brown out reset enabled */
/* master clear reset function disabled */
/* power up timer enabled */
/* watchdog timer disabled */
/* internal osc/GP4 = IO//GP5 = IO */

// La macro que setea los bits de configuraci�n, debe ser invocada �nicamente 1
// sola vez en todo el programa, porque de otro modo, el compilador detecta un
// error.

__IDLOC7(0x20,0x11,0x02,0x22);
// ID Locations son un peque�o espacio de memoria en el cual el usuario puede
// (en tiempo de programaci�n) almacenar el checksum, informaci�n de la versi�n
// del programa, o lo que quiera.
// Almaceno la fecha de generaci�n del HEX. El formato es: a�o[2], mes[1],
// d�a[1].

#endif
// __MAIN_H