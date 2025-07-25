//==============================================================================
// Archivo: fsm_table.h
// Autor: Federico Ramos
// Modificado: 13-11-2023
//
// En este archivo:
// - EVENTOS
// - DECLARACION DE FUNCIONES QUE SON ACCIONES FSM
// - TABLA DE ESTADOS INDEXES
// - TRANSICIONES DE ESTADOS
// - TABLA DE ESTADOS
// - DEFINICION DE ESTADO INICIAL FSM
//==============================================================================


//==============================================================================
// EVENTOS
// fsmGetEvent() retorna por defecto EV_TABLE_END, por lo que si lo que se busca
// es que no ocurra ningun evento, se puede usar esa entrada de la tabla de tran
// siciones.
//==============================================================================
enum e_events
    {
    EV_TESTDISPLAY_TIMEOUT,
    EV_T1_TIME_TIMEOUT,
    EV_MENU_RETURN_TIMEOUT,

    EV_KM,
    EV_KM_FN_LOCKED,
    EV_KM_FP_LOCKED,
    EV_KM_TON_OFF_EXIT,// TON_OFF es un menú que apretando varias veces el pulsa
    // dor "menu", cambia de variable a modificar (0..n). cuando llega a la últi
    // ma variable, debe continuar con el siguiente menu "normal". Este evento s
    // e lo indica.
    EV_K_SET,

    EV_K_ACCEPT,
    EV_K_ACCEPT_FP,
    EV_K_ACCEPT_FN,

    EV_IN_FP,
    EV_IN_FN,

    EV_IN2_FP,
    EV_IN2_FN,

    EV_TABLE_END// Driver event, do not change
    };


//==============================================================================
// DECLARACION DE FUNCIONES QUE SON ACCIONES FSM
// No es necesario doble espacio en identificadores porque se usa minúsculas.
//==============================================================================
void a_doNothing(void);
void a_testDisplaySetup(void);
void a_initializeDevice(void);

void a_temporizar(void);
void a_inputActionFp(void);
void a_inputActionFn(void);
void a_input2ActionFp(void);
void a_input2ActionFn(void);
void a_showTimerIdOn(void);
void a_showTimerIdOff(void);
void a_showHyphensOn(void);
void a_showHyphensOff(void);

void a_m0_return(void);

void a_m0_first(void);// Muestra descripción principal.
void a_m0_first_set(void); // Muestra valor seteo.
void a_m0_first_inc(void); // Cambia valor seteo.
void a_m0_first_save(void); // Guarda valor seteo.

void a_m0_input(void);// Muestra descripción principal.
void a_m0_input_set(void); // Muestra valor seteo.
void a_m0_input_inc(void); // Cambia valor seteo.
void a_m0_input_save(void); // Guarda valor seteo.

void a_m0_nMem(void);// Despliega descripción de MAIN_MENU/CANT_MEMORIAS
void a_m0_nMem_set(void);
void a_m0_nMem_inc(void);
void a_m0_nMem_dec(void);
void a_m0_nMem_save(void);

void a_m0_tOnOff_entrance(void);// Despliega descripción de MAIN_MENU/TON_TOFF
void a_m0_tOnOff_showString(void);// Despliega descripción de MAIN_MENU/TON_TOFF
void a_m0_tOnOff_showString_next(void);
void a_m0_tOnOff_set(void);
void a_m0_tOnOff_inc(void);
void a_m0_tOnOff_save(void);

void a_showTime(void);


//==============================================================================
// TABLA DE ESTADOS INDEXES
// Esta tabla de "enums" se debe crear (para evitar errores) de la siguiente man
// era:
// - Se copia el contenido de la definición de la variable: t_fsmState *const fs
// mStateTable (es decir, la tabla de estados).
// - Se fuerza a que todos los textos se escriban en MAYUSCULAS (por ejemplo, us
// ando "mayusculas" del Microsoft Word).
// - Se coloca ese texto en mayusculas en la definición del enum.
//
// Usa doble espacio en identificadores para establecer jerarquía.
//==============================================================================
enum fsm_table_ix
    {
    S__TESTDISPLAY_SETUP,
    S__TESTDISPLAY,

    S__IDLE,
    S__RST,

    S__M0__FIRST,
    S__M0__FIRST__SET,

    S__M0__INPUT,
    S__M0__INPUT__SET,

    S__M0__NMEM,
    S__M0__NMEM__SET,

    S__M0__TON_OFF,
    S__M0__TON_OFF__SET_HH_0,
    S__M0__TON_OFF__SET_HH_1,
    S__M0__TON_OFF__SET_MM_0,
    S__M0__TON_OFF__SET_MM_1,
    S__M0__TON_OFF__SET_SS_0,
    S__M0__TON_OFF__SET_SS_1
    };


//==============================================================================
// TRANSICIONES DE ESTADOS
//==============================================================================

// S__TESTDISPLAY_SETUP
//==============================================================================
t_fsmState s_testDisplaySetup[]=
    {
    {EV_TABLE_END, &a_testDisplaySetup, S__TESTDISPLAY}
    };

// S__TESTDISPLAY
//==============================================================================
t_fsmState s_testDisplay[]=
    {
    {EV_TESTDISPLAY_TIMEOUT, &a_initializeDevice, S__IDLE},
    {EV_TABLE_END, &a_doNothing, S__TESTDISPLAY}
    };

// S__IDLE
//==============================================================================
t_fsmState s_idle[]=
    {
    {EV_KM, &a_m0_first, S__M0__FIRST},
    {EV_KM_FP_LOCKED, &a_showHyphensOff, S__IDLE},
    {EV_KM_FN_LOCKED, &a_showHyphensOn, S__IDLE},
    {EV_T1_TIME_TIMEOUT, &a_temporizar, S__IDLE},
    {EV_K_ACCEPT_FP, &a_showTimerIdOff, S__IDLE},
    {EV_K_ACCEPT_FN, &a_showTimerIdOn, S__IDLE},
    {EV_IN_FP, &a_inputActionFp, S__IDLE},
    {EV_IN_FN, &a_inputActionFn, S__IDLE},
    {EV_IN2_FN, &a_input2ActionFn, S__RST},
    {EV_TABLE_END, &a_showTime, S__IDLE}
    };

// S__RST
//==============================================================================
t_fsmState s_rst[]=
    {
    {EV_IN2_FP, &a_input2ActionFp, S__IDLE},
    {EV_TABLE_END, &a_doNothing, S__RST}
    };

// S__M0__FIRST
//==============================================================================
// Si el primer estado al bootear es salida = on o salida = off.
t_fsmState s_m0_first[]=
    {
    {EV_KM, &a_m0_input, S__M0__INPUT},
    {EV_K_ACCEPT, &a_m0_first_set, S__M0__FIRST__SET},
    {EV_MENU_RETURN_TIMEOUT, &a_m0_return, S__IDLE},
    {EV_TABLE_END, &a_doNothing, S__M0__FIRST}
    };

// S__M0__FIRST__SET
//==============================================================================
// En este caso especial, cualquiera de los 2 pulsadores (SET/KM) sirve para el
// a_m0_first_inc dado que solo hay 2 valores posibles, no se requiere una funci
// on dec.
t_fsmState s_m0_first_set[]=
    {
    {EV_K_SET, &a_m0_first_inc, S__M0__FIRST__SET},
    {EV_KM, &a_m0_first_inc, S__M0__FIRST__SET},
    {EV_K_ACCEPT, &a_m0_first_save, S__M0__FIRST},
    {EV_MENU_RETURN_TIMEOUT, &a_m0_return, S__IDLE},
    {EV_TABLE_END, &a_doNothing, S__M0__FIRST__SET}
    };


// S__M0__INPUT
//==============================================================================
// Establece función de la entrada optocoplada.
t_fsmState s_m0_input[]=
    {
    {EV_KM, &a_m0_nMem, S__M0__NMEM},
    {EV_K_ACCEPT, &a_m0_input_set, S__M0__INPUT__SET},
    {EV_MENU_RETURN_TIMEOUT, &a_m0_return, S__IDLE},
    {EV_TABLE_END, &a_doNothing, S__M0__INPUT}
    };

// S__M0__INPUT__SET
//==============================================================================
// En este caso especial, cualquiera de los 2 pulsadores (SET/KM) sirve para el
// a_m0_first_inc dado que solo hay 3 valores posibles, no se requiere una funci
// on dec.
t_fsmState s_m0_input_set[]=
    {
    {EV_K_SET, &a_m0_input_inc, S__M0__INPUT__SET},
    {EV_KM, &a_m0_input_inc, S__M0__INPUT__SET},
    {EV_K_ACCEPT, &a_m0_input_save, S__M0__INPUT},
    {EV_MENU_RETURN_TIMEOUT, &a_m0_return, S__IDLE},
    {EV_TABLE_END, &a_doNothing, S__M0__INPUT__SET}
    };


// S__M0__NMEM
//==============================================================================
t_fsmState s_m0_nMem[]=
    {
    {EV_KM, &a_m0_tOnOff_entrance, S__M0__TON_OFF},
    {EV_K_ACCEPT, &a_m0_nMem_set, S__M0__NMEM__SET},
    {EV_MENU_RETURN_TIMEOUT, &a_m0_return, S__IDLE},
    {EV_TABLE_END, &a_doNothing, S__M0__NMEM}
    };

// S__M0__NMEM__SET
//==============================================================================
// Este es un menu especial (solo un valor escalar) que permite incrementar y de
// crementar usando K_SET(+) y KM(-).
t_fsmState s_m0_nMem_set[]=
    {
    {EV_K_SET, &a_m0_nMem_inc, S__M0__NMEM__SET},
    {EV_KM, &a_m0_nMem_dec, S__M0__NMEM__SET},
    {EV_K_ACCEPT, &a_m0_nMem_save, S__M0__NMEM},
    {EV_MENU_RETURN_TIMEOUT, &a_m0_return, S__IDLE},
    {EV_TABLE_END, &a_doNothing, S__M0__NMEM__SET}
    };

// S__M0__TON_OFF
//==============================================================================
t_fsmState s_m0_tonToff[]=
    {
    {EV_KM, &a_m0_tOnOff_showString_next, S__M0__TON_OFF},
    {EV_KM_TON_OFF_EXIT, &a_m0_first, S__M0__FIRST},
    {EV_K_ACCEPT, &a_m0_tOnOff_set, S__M0__TON_OFF__SET_HH_0},
    {EV_MENU_RETURN_TIMEOUT, &a_m0_return, S__IDLE},
    {EV_TABLE_END, &a_doNothing, S__M0__TON_OFF}
    };

// S__M0__TON_OFF__SET_HH_0
//==============================================================================
t_fsmState s_m0_tonToff_setHoras0[]=
    {
    {EV_KM, &a_m0_tOnOff_set, S__M0__TON_OFF__SET_HH_1},
    {EV_K_SET, &a_m0_tOnOff_inc, S__M0__TON_OFF__SET_HH_0},
    {EV_K_ACCEPT, &a_m0_tOnOff_save, S__M0__TON_OFF},// Graba memoria.
    {EV_MENU_RETURN_TIMEOUT, &a_m0_return, S__IDLE},// No graba.
    {EV_TABLE_END, &a_doNothing, S__M0__TON_OFF__SET_HH_0}
    };

// S__M0__TON_OFF__SET_HH_1
//==============================================================================
t_fsmState s_m0_tonToff_setHoras1[]=
    {
    {EV_KM, &a_m0_tOnOff_set, S__M0__TON_OFF__SET_MM_0},
    {EV_K_SET, &a_m0_tOnOff_inc, S__M0__TON_OFF__SET_HH_1},
    {EV_K_ACCEPT, &a_m0_tOnOff_save, S__M0__TON_OFF},// Graba memoria.
    {EV_MENU_RETURN_TIMEOUT, &a_m0_return, S__IDLE},// No graba.
    {EV_TABLE_END, &a_doNothing, S__M0__TON_OFF__SET_HH_1}
    };

// S__M0__TON_OFF__SET_MM_0
//==============================================================================
t_fsmState s_m0_tonToff_setMinutos0[]=
    {
    {EV_KM, &a_m0_tOnOff_set, S__M0__TON_OFF__SET_MM_1},
    {EV_K_SET, &a_m0_tOnOff_inc, S__M0__TON_OFF__SET_MM_0},
    {EV_K_ACCEPT, &a_m0_tOnOff_save, S__M0__TON_OFF},// Graba memoria.
    {EV_MENU_RETURN_TIMEOUT, &a_m0_return, S__IDLE},// No graba.
    {EV_TABLE_END, &a_doNothing, S__M0__TON_OFF__SET_MM_0}
    };

// S__M0__TON_OFF__SET_MM_1
//==============================================================================
t_fsmState s_m0_tonToff_setMinutos1[]=
    {
    {EV_KM, &a_m0_tOnOff_set, S__M0__TON_OFF__SET_SS_0},
    {EV_K_SET, &a_m0_tOnOff_inc, S__M0__TON_OFF__SET_MM_1},
    {EV_K_ACCEPT, &a_m0_tOnOff_save, S__M0__TON_OFF},// Graba memoria.
    {EV_MENU_RETURN_TIMEOUT, &a_m0_return, S__IDLE},// No graba.
    {EV_TABLE_END, &a_doNothing, S__M0__TON_OFF__SET_MM_1}
    };

// S__M0__TON_OFF__SET_SS_0
//==============================================================================
t_fsmState s_m0_tonToff_setSegundos0[]=
    {
    {EV_KM, &a_m0_tOnOff_set, S__M0__TON_OFF__SET_SS_1},
    {EV_K_SET, &a_m0_tOnOff_inc, S__M0__TON_OFF__SET_SS_0},
    {EV_K_ACCEPT, &a_m0_tOnOff_save, S__M0__TON_OFF},// Graba memoria.
    {EV_MENU_RETURN_TIMEOUT, &a_m0_return, S__IDLE},// No graba.
    {EV_TABLE_END, &a_doNothing, S__M0__TON_OFF__SET_SS_0}
    };

// S__M0__TON_OFF__SET_SS_1
//==============================================================================
t_fsmState s_m0_tonToff_setSegundos1[]=
    {
    {EV_KM, &a_m0_tOnOff_set, S__M0__TON_OFF__SET_HH_0},
    {EV_K_SET, &a_m0_tOnOff_inc, S__M0__TON_OFF__SET_SS_1},
    {EV_K_ACCEPT, &a_m0_tOnOff_save, S__M0__TON_OFF},// Graba memoria.
    {EV_MENU_RETURN_TIMEOUT, &a_m0_return, S__IDLE},// No graba.
    {EV_TABLE_END, &a_doNothing, S__M0__TON_OFF__SET_SS_1}
    };


//==============================================================================
// TABLA DE ESTADOS
// fsmStateTable es un array de [const pointers] a t_fsmState (que a su vez, es 
// una const struct)
//==============================================================================
t_fsmState *const fsmStateTable[]=
    {
    s_testDisplaySetup,
    s_testDisplay,

    s_idle,
    s_rst,

    s_m0_first,
    s_m0_first_set,
    s_m0_input,
    s_m0_input_set,
    s_m0_nMem,
    s_m0_nMem_set,

    s_m0_tonToff,
    s_m0_tonToff_setHoras0,
    s_m0_tonToff_setHoras1,
    s_m0_tonToff_setMinutos0,
    s_m0_tonToff_setMinutos1,
    s_m0_tonToff_setSegundos0,
    s_m0_tonToff_setSegundos1
    };

    
//==============================================================================
// DEFINICION DE ESTADO INICIAL FSM
#define BOOT_STATE S__TESTDISPLAY_SETUP
//==============================================================================