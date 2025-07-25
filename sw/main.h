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

// La macro que setea los bits de configuración, debe ser invocada únicamente 1
// sola vez en todo el programa, porque de otro modo, el compilador detecta un
// error.

__IDLOC7(0x20,0x11,0x02,0x22);
// ID Locations son un pequeño espacio de memoria en el cual el usuario puede
// (en tiempo de programación) almacenar el checksum, información de la versión
// del programa, o lo que quiera.
// Almaceno la fecha de generación del HEX. El formato es: año[2], mes[1],
// día[1].

#endif
// __MAIN_H