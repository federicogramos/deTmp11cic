//==============================================================================
// Archivo: fsm_events.h
// Autor: Federico Ramos
// Modificado: 05-11-2023
//==============================================================================


//==============================================================================
// INCLUDE
#include <t0.h>
#include <t1.h>
#include <kPin.h>
#include <tmp_11.h>
#include <system.h>
//==============================================================================


//==============================================================================
// RETORNA EVENTO SEGUN ESTADO
//==============================================================================
char fsmGetEvent(void)
    {
    char event=EV_TABLE_END;// Si dentro del estado correspondiente, no ocurre u
    // n evento específico, ocurrirá EVENT_TABLE_END, por defecto.

    switch(estadoFsm)
        {
        case S__TESTDISPLAY_SETUP: break;// Siempre devuelve el evento por defec
        // to: EV_TABLE_END y por lo tanto, siendo la única transición de estado
        // , funciona como "always".

        case S__TESTDISPLAY:
            if(T0_TIMEOUT(T0_TESTDISPLAY)) event = EV_TESTDISPLAY_TIMEOUT;
            break;

        case S__IDLE:
            if(KPIN_EVENT_FN_ID(IN1_FORCE)) event = EV_IN_FN;
            else if(KPIN_EVENT_FP_ID(IN1_FORCE)) event = EV_IN_FP;
            else if(KPIN_EVENT_FN_ID(P0_MENU))
                {
                if(tmp_11.flag_locked) event = EV_KM_FN_LOCKED;
                else event = EV_KM;
                }
            else if(KPIN_EVENT_FP_ID(P0_MENU))
                {
                if(tmp_11.flag_locked) event = EV_KM_FP_LOCKED;
                }
            else if(T1_TIMEOUT(T1_TIME)) event = EV_T1_TIME_TIMEOUT;
            else if(KPIN_EVENT_FN_ID(P2_ACCEPT)) event = EV_K_ACCEPT_FN;
            else if(KPIN_EVENT_FP_ID(P2_ACCEPT)) event = EV_K_ACCEPT_FP;
            else if(KPIN_EVENT_FN_ID(IN2_RST)) event = EV_IN2_FN;
            break;

        case S__RST:
            if(KPIN_EVENT_FP_ID(IN2_RST)) event = EV_IN2_FP;
            break;

        case S__M0__FIRST:
            if(T0_TIMEOUT(T0_MENU_RETURN)) event = EV_MENU_RETURN_TIMEOUT;
            else if(KPIN_EVENT_FN_ID(P0_MENU)) event = EV_KM;
            else if(KPIN_EVENT_FN_ID(P2_ACCEPT)) event = EV_K_ACCEPT;
            break;

        case S__M0__FIRST__SET:
            if(T0_TIMEOUT(T0_MENU_RETURN)) event = EV_MENU_RETURN_TIMEOUT;
            else if(KPIN_EVENT_FN_ID(P1_SET)) event = EV_K_SET;
            else if(KPIN_EVENT_FN_ID(P0_MENU)) event = EV_KM;
            else if(KPIN_EVENT_FN_ID(P2_ACCEPT)) event = EV_K_ACCEPT;
            break;

        case S__M0__INPUT:
            if(T0_TIMEOUT(T0_MENU_RETURN)) event = EV_MENU_RETURN_TIMEOUT;
            else if(KPIN_EVENT_FN_ID(P0_MENU)) event = EV_KM;
            else if(KPIN_EVENT_FN_ID(P2_ACCEPT)) event = EV_K_ACCEPT;
            break;

        case S__M0__INPUT__SET:
            if(T0_TIMEOUT(T0_MENU_RETURN)) event = EV_MENU_RETURN_TIMEOUT;
            else if(KPIN_EVENT_FN_ID(P1_SET)) event = EV_K_SET;
            else if(KPIN_EVENT_FN_ID(P0_MENU)) event = EV_KM;
            else if(KPIN_EVENT_FN_ID(P2_ACCEPT)) event = EV_K_ACCEPT;
            break;

        case S__M0__NMEM:
            if(T0_TIMEOUT(T0_MENU_RETURN)) event = EV_MENU_RETURN_TIMEOUT;
            else if(KPIN_EVENT_FN_ID(P0_MENU)) event = EV_KM;
            else if(KPIN_EVENT_FN_ID(P2_ACCEPT)) event = EV_K_ACCEPT;
            break;

        case S__M0__NMEM__SET:
            if(T0_TIMEOUT(T0_MENU_RETURN)) event = EV_MENU_RETURN_TIMEOUT;
            else if(KPIN_EVENT_FN_ID(P1_SET)) event = EV_K_SET;
            else if(KPIN_EVENT_FN_ID(P0_MENU)) event = EV_KM;
            else if(KPIN_EVENT_FN_ID(P2_ACCEPT)) event = EV_K_ACCEPT;
            break;

        case S__M0__TON_OFF:
            if(T0_TIMEOUT(T0_MENU_RETURN)) event = EV_MENU_RETURN_TIMEOUT;
            else if(KPIN_EVENT_FN_ID(P0_MENU))
                {
                if(tmp_11.mainMenuState==tmp_11.mem_cantMemorias-1)
                    event = EV_KM_TON_OFF_EXIT;
                else event = EV_KM;
                }
            else if(KPIN_EVENT_FN_ID(P2_ACCEPT)) event = EV_K_ACCEPT;
            break;

        case S__M0__TON_OFF__SET_HH_0:
        case S__M0__TON_OFF__SET_HH_1:
        case S__M0__TON_OFF__SET_MM_0:
        case S__M0__TON_OFF__SET_MM_1:
        case S__M0__TON_OFF__SET_SS_0:
        case S__M0__TON_OFF__SET_SS_1:
            if(T0_TIMEOUT(T0_MENU_RETURN)) event = EV_MENU_RETURN_TIMEOUT;
            else if(KPIN_EVENT_FN_ID(P0_MENU)) event = EV_KM;
            else if(KPIN_EVENT_FN_ID(P2_ACCEPT)) event = EV_K_ACCEPT;
            else if(KPIN_EVENT_FN_ID(P1_SET)) event = EV_K_SET;
            break;
        }

    return event;
    }

