//==============================================================================
// Archivo: fsm_actions.h
// Autor: Federico Ramos
// Modificado: 05-11-2023
//
// En este archivo:
// - INCLUDE
// - CONSTANT DEFINITIONS
// - ACCIONES PARA LA FSM
// - SUBMENUES PARA ACTION -> MAIN MANU -> CANT MEMORIAS
//==============================================================================


//==============================================================================
// INCLUDE
#include <t0.h>
#include <t1.h>
#include <tmp_11.h>
#include <d7sm.h>
#include <eeprom16f.h>
#include <system.h>// Para la inicialización del sistema.
#include <string.h>
//==============================================================================


//==============================================================================
// CONSTANT DEFINITIONS
#define MAX_MEMORIAS 40 // [0..39]
//==============================================================================


//==============================================================================
// ACCIONES PARA LA FSM
//==============================================================================


// ACTION:
//==============================================================================
void a_doNothing(void) {}


// ACTION:
//==============================================================================
void a_testDisplaySetup(void)
    {
    T0_START(T0_TESTDISPLAY);// String ya bootea con "8.8.8.8."
    }


// ACTION:
// Luego de test, va a estado IDLE y ejecuta a_showTime() ciclicamente (EV_TABLE
// _END), por lo que establece correctamente todo lo relativo al display, no req
// uiero inicializar nada.
//==============================================================================
void a_initializeDevice(void)
    {
    tmp_11.flag_locked=LOCK;
    LED0=!tmp_11.flag_locked;// Visualiza cuando unlocked.

	// Inicialización de seteos eeprom
	EEPROM_READ_CHAR(EEADDR__00_00__INPUT,tmp_11.mem_input);
    EEPROM_READ_CHAR(EEADDR__01_00__VISOR_PARPADEO,tmp_11.mem_visor_parpadeo);
    EEPROM_READ_CHAR(EEADDR__02_00__NMEM,tmp_11.mem_cantMemorias);
    EEPROM_READ_CHAR(EEADDR__04_00__FIRST,tmp_11.mem_first);

    if(!tmp_11.mem_first) tmp_11.p2eepromAddr += sizeof(short long); // Ajuste p
    // ara que apunte a toff si es toff first.

    T1_TIMEOUT_FORCE(T1_TIME);// Fuerza fin ciclo, para q empiece del comienzo.
    }


// ACTION:
//==============================================================================
// Estructura memoria tiempos (siempre, independientemente de seteo "first"):
// +-------+-------+-------+-------+-------+-------+---
// | ton0  | toff0 | ton1  | toff1 | ton2  | toff2 |...
// +-------+-------+-------+-------+-------+-------+---
//     0       3       6       9      12    (no incluye offset de inicio vector)
void a_temporizar(void)
    {
    EEPROM_READ_SHORTLONG_INT(tmp_11.p2eepromAddr,t1DelayConstant[T1_TIME]);// L
    // evanto siguiente tiempo.

    if(tmp_11.mem_first)// Deteccion de ultimo tiempo y cantidad de bytes a avan
    // zar en el vector de tiempos, depende del seteo "first": on u off.
        {
        tmp_11.p2eepromAddr+=sizeof(short long);// Apunto al siguiente tiempo.

        if( tmp_11.p2eepromAddr==
            EEADDR__16_00__TON_OFF+sizeof(short long)*tmp_11.mem_cantMemorias)
            tmp_11.p2eepromAddr=EEADDR__16_00__TON_OFF;//Recordar que cantMemori
            // as es 2*Cantidad de tiempos (es decir 1 memoria para ton y otra p
            // ara toff)
        }
    else// First = toff
        {
        if( (tmp_11.p2eepromAddr-EEADDR__16_00__TON_OFF)%
            (2*(char)sizeof(short long)))
            tmp_11.p2eepromAddr -= sizeof(short long);
        else
            tmp_11.p2eepromAddr += 2*sizeof(short long);

        if( tmp_11.p2eepromAddr==
            EEADDR__16_00__TON_OFF+sizeof(short long)*tmp_11.mem_cantMemorias)
            tmp_11.p2eepromAddr = EEADDR__16_00__TON_OFF+sizeof(short long);//Re
            // cordar que cantMemorias es 2*Cantidad de tiempos (es decir 1 memoria para ton y ot
            // ra para toff)
        }
    
    if(t1DelayConstant[T1_TIME])
        {
        T1_START(T1_TIME);// Si !0 arranca timer.

        if(!tmp_11.flag_outForce)// In1 fuerza. Si fuerza, deshabilita que vuelv
        // a a cambiar de estado hasta que haya un fp en la in1 (quite forzado).
            {
            OUT = tmp_11.p2eepromAddr%2;// Todos los address TON son impares.
            // LED5 = OUT; ya no lo controlo aqui porque necesito más capacidad
            // de refresco para los casos de blink de este led.
            }
        }
    else
        {
        T1_TIMEOUT_FORCE(T1_TIME);// De otro modo, va directo al timeout
        }
    }


// ACTION:
//==============================================================================
void a_inputActionFn(void)
    {
    LED3 = 1;// Led in1.
    switch(tmp_11.mem_input)
        {
        case M0_INPUT_NADA: break;// El único que no toca la salida.
        case M0_INPUT_PAUSE_ON:
        case M0_INPUT_PAUSE_OFF:
            T1_PAUSE(T1_TIME);
            tmp_11.flag_showTimeBlink = 1;
        case M0_INPUT_DISABLE:
        case M0_INPUT_FUERZA:
            OUT = tmp_11.mem_input%2;// Como ordené las constantes e_m0_input pa
            // ra que la opción que encienda sea impar, entonces, puedo hacer es
            // to.
            // LED5 = OUT;// Led del output. No se hace aquí. Este es un caso muy
            // particular porque el led indicador de la salida no necesariamente
            // sigue a la salida: a veces parpadea. Entonces, debo accionarlo en 
            // una accion que tenga más frecuencia de refresco.
            tmp_11.flag_outForce = 1;// Fuerza. Avisa para q timeout no modifique OUT.
            tmp_11.flag_outForceVal = OUT;// A que sea el out recien puesto.
        }
    }


// ACTION:
//==============================================================================
void a_inputActionFp(void)
    {
    LED3 = 0;// Led in1.
    switch(tmp_11.mem_input)
        {
        case M0_INPUT_NADA: break;
        case M0_INPUT_PAUSE_ON:
        case M0_INPUT_PAUSE_OFF:
            T1_UNPAUSE(T1_TIME);
            tmp_11.flag_showTimeBlink = 0;
        case M0_INPUT_DISABLE:
        case M0_INPUT_FUERZA:
            OUT = tmp_11.p2eepromAddr%2;// Lo mismo que cuando acciona timer. Es
            // una habilitación/restauración asincrónica.
            //LED5 = OUT; idem funcion de fp.
            tmp_11.flag_outForce = 0;// Ya no fuerza.
            //tmp_11.flag_outForceVal = XXX // No importa.
            break;
        }
    }

// ACTION:
//==============================================================================
// Apaga todo.
void a_input2ActionFn(void)
    {
    LED2 = 1;// Led in2. Indica estado de in2.

    T1_STOP(T1_TIME);// Fuerza fin de funcionamiento
    OUT = 0;
    LED5 = 0;
    tmp_11.p2eepromAddr = EEADDR__16_00__TON_OFF;// Address con el que bootea si
    // stema, lo repongo para que cuendo recomience igual que al booteo.

    if(!tmp_11.mem_first) tmp_11.p2eepromAddr += sizeof(short long); // Ajuste p
    // ara que apunte a toff si es toff first.


    // Muestro en pantalla el aviso de reset.
    tmp_11.flag_showHyphens=1;// Debería cambiarle el nombre a este flag, porque
    // ahora lo uso para escribir algo permanente que no son solo los hyphens.

	disp.d0_dp=0;
	disp.d1_dp=0;
	disp.d2_dp=0;
	disp.d3_dp=0;

    tmp_11.str[0]='R';
    tmp_11.str[1]='S';
    tmp_11.str[2]='t';
    tmp_11.str[3]=' ';
    disp.str=tmp_11.str;
    }

// ACTION:
//==============================================================================
////////////////////////////////////////////// A revisar: si se hace cambios ext
////////////////////////////////////////////// remadamente rapidos de in2, se lo
////////////////////////////////////////////// gra cada tanto, que se "joda" la
////////////////////////////////////////////// lógica de la entrada. No he jugad
////////////////////////////////////////////// o mucho mas como para ver como so
////////////////////////////////////////////// lucionarlo.
// Si hace el fp mientras in1 está accionado, no considerará el estado lógico de
// in1, sino que solo usará la acción que ocurra durante el próximo flanco.
void a_input2ActionFp(void)
    {
    LED2 = 0;// Led in2. Indica estado de in2.
    tmp_11.flag_showHyphens = 0;

    T1_TIMEOUT_FORCE(T1_TIME);// Fuerza fin del ciclo, para que empiece desde el
    // comienzo, lo mismo que hace al bootear.

    }


// ACTION:
//==============================================================================
void a_showTimerIdOn(void)
    {
    tmp_11.flag_showTimerId=1;

    char id;

    if(tmp_11.p2eepromAddr==EEADDR__16_00__TON_OFF)
        id=tmp_11.mem_cantMemorias-1;// Es el último. Recordar que cantMemorias 
    // es 2*Cantidad de tiempos (es decir 1 memoria para ton y otra para toff).
    else
        id=(tmp_11.p2eepromAddr-EEADDR__16_00__TON_OFF)/
           (char)sizeof(short long)-1;// p2eepromAddr apunta al proximo, por eso
            // se que el actual es el anterior al apuntado.

    switch(id%2)
        {
        case 0:
            d7sm_buffer[0]='t';
            d7sm_buffer[1]='o';
            d7sm_buffer[2]='n';
            d7sm_buffer[3]='_';
            //d7sm_buffer[4]='0'+id/2;
            //d7sm_buffer[5]='0'+id/2;
            d7sm_buffer[6]=0;

UCHAR_TO_STR(id/2,&d7sm_buffer[4],2);//--->TRASLADADO A PREVIO A INVOCAR disp7segMux_set_number() DEBIDO A POSSIBLE STACK OVR
            break;
        case 1:
            d7sm_buffer[0]='t';
            d7sm_buffer[1]='o';
            d7sm_buffer[2]='f';
            d7sm_buffer[3]='f';
            d7sm_buffer[4]='_';
            //d7sm_buffer[5]='0'+(id-1)/2;
            //d7sm_buffer[6]='0'+(id-1)/2;
            d7sm_buffer[7]=0;

UCHAR_TO_STR((id-1)/2,&d7sm_buffer[5],2);//--->TRASLADADO A PREVIO A INVOCAR disp7segMux_set_number() DEBIDO A POSSIBLE STACK OVR
            break;
        }

    //disp7segMux_scroll_charString(&d7sm_buffer);
    d7sm_puts_scroll(&d7sm_buffer);
    }


// ACTION:
//==============================================================================
void a_showHyphensOn(void)
    {
    tmp_11.flag_showHyphens=1;

    //d7sm_buffer[0]='-';
    //d7sm_buffer[1]='-';
    //d7sm_buffer[2]='-';
    //d7sm_buffer[3]='-';

    //d7sm_scroll_charString(&d7sm_buffer);

	disp.d0_dp=0;
	disp.d1_dp=0;
	disp.d2_dp=0;
	disp.d3_dp=0;

    tmp_11.str[0]='-';
    tmp_11.str[1]='-';
    tmp_11.str[2]='-';
    tmp_11.str[3]='-';
    disp.str=tmp_11.str;

    }


// ACTION:
//==============================================================================
void a_showHyphensOff(void)
    {
    tmp_11.flag_showHyphens=0;
    //T0_STOP_LOOP(T0_DISP7SEGMUX_SCROLL);
    }


// ACTION:
//==============================================================================
void a_showTimerIdOff(void)
    {
    tmp_11.flag_showTimerId=0;
    T0_STOP_LOOP(T0_D7SM_SCROLL);
    }


// ACCIONES:
//==============================================================================
// Se ejecuta en el TABLE_END del estado IDLE.
void a_showTime(void)
    {
    // Ojo, este es un agregado que me gustaria separarlo metiendolo en macro.
    // La tabla de verdad que implementa es la siguiente:
    // +-------+--------+--------+----------+
    // | force | addr%2 | ledOut | forceVal |
    // +-------+--------+--------+----------+
    // |   1   |   0    |   0 <------ 0     |
    // |   1   |   1    | titila |    0     |
    // |   1   |   0    |   1 <------ 1     |
    // |   1   |   1    |   1 <------ 1     |
    // |   0   |   0 -----> 0    |    0     |
    // |   0   |   1 -----> 1    |    0     |
    // |   0   |   0 -----> 0    |    1     |
    // |   0   |   1 -----> 1    |    1     |
    // +-------+--------+--------+----------+

    if(tmp_11.flag_outForce)
        {
        if(tmp_11.p2eepromAddr%2 && !tmp_11.flag_outForceVal)
            LED5 = bitTitila;
        else LED5 = tmp_11.flag_outForceVal;
        }
    else LED5 = tmp_11.p2eepromAddr%2;
 
    // Desde aquí, showTime.
    if(!tmp_11.flag_showTimerId && !tmp_11.flag_showHyphens)
        {
        char hh,mm,ss;
    
        hh = (1+t1Mem[T1_TIME].prescaler/4)/3600;
    	mm = ((1+t1Mem[T1_TIME].prescaler/4)%3600)/60;
        ss = (1+t1Mem[T1_TIME].prescaler/4)%60;
    
        if(hh>=10)//FGR: HH.MM
            {
            ucharToStr(hh, &tmp_11.str[0], 2);
            ucharToStr(mm, &tmp_11.str[2], 2);
            disp.d0_dp = 0;
            disp.d1_dp = 0;
            disp.d2_dp = 1;
            disp.d3_dp = 0;
            }
        else if(hh<10 && hh>0)//FGR: H.MM.S
            {
            ucharToStr(hh, &tmp_11.str[0], 1);
            ucharToStr(mm, &tmp_11.str[1], 2);
            ucharToStr(ss/10, &tmp_11.str[3], 1);
            disp.d0_dp = 0;
            disp.d1_dp = 1;
            disp.d2_dp = 0;
            disp.d3_dp = 1;
            }
        else//FGR: HH==0 => MM.SS
            {
            ucharToStr(mm, &tmp_11.str[0], 2);
            ucharToStr(ss, &tmp_11.str[2], 2);
            disp.d0_dp = 0;
            disp.d1_dp = 0;
            disp.d2_dp = 1;
            disp.d3_dp = 0;
            }
    
        if(tmp_11.flag_showTimeBlink)
            {
            disp.d0_titila = 1;
            disp.d1_titila = 1;
            disp.d2_titila = 1;
            disp.d3_titila = 1;
            }
        else
            {
            disp.d0_titila = 0;
            disp.d1_titila = 0;
            disp.d2_titila = 0;
            disp.d3_titila = 0;
            }

    	disp.strOffs = D7SM_LENGTH;// Configura display para mostrar string.
    	disp.strLen = D7SM_LENGTH;
        disp.str = tmp_11.str;
        }
    }


// ACTION
//==============================================================================
// Return va a estado IDLE y ejecuta a_showTime() por lo que establece correctam
// ente todo lo relativo al display. No requiero inicializar nada de eso.
void a_m0_return(void)
	{
    T0_STOP_LOOP(T0_D7SM_SCROLL);
    T1_TIMEOUT_FORCE(T1_TIME);// Fuerza fin del ciclo, para que empiece desde el
    // comienzo, lo mismo que hace al bootear.
    tmp_11.flag_inputSettingLedBlink = 0;
	}


//==============================================================================
// ACTION: MAIN MANU -> FIRST
//==============================================================================
// Primer menu que aparece cuando se va de idle a main menu.
// Apaga salida.
void a_m0_first(void)
	{
    T0_START(T0_MENU_RETURN);

    T1_STOP(T1_TIME);// Fuerza fin de funcionamiento
    OUT = 0;
    LED5 = 0;// Produce menos código si pongo la constante en lugar de OUT. Pens
    // aba que el código se optimizaba, pero no, así que directo 0 ahora.

	tmp_11.mainMenuState = TEXT__M0__FIRST;// Asigna elemento dentro de un array
    // de strings.
    d7sm_puts_scroll((char *)menu_text_main[tmp_11.mainMenuState]);
	}


// ACTION: MAIN MANU -> FIRST -> SET
//==============================================================================
// Muestra en pantalla el dato que debo ver para hacer el seteo requerido.
void a_m0_first_set(void)
	{
    T0_START(T0_MENU_RETURN);
    tmp_11.flag_inputSettingLedBlink = 1;

    if(estadoFsm==S__M0__FIRST)// Solo a la entrada del menu "first set".
        tmp_11.menuCharAuxiliar = tmp_11.mem_first;

    if(tmp_11.menuCharAuxiliar) d7sm_puts_scroll((char *)"ON");
    else d7sm_puts_scroll((char *)"OFF");

    //D7SM_SET_NUMBER(1,tmp_11.menuCharAuxiliar);// titila=1, num=mem_cantMemorias
    // /2. Se podría usar d7sm_set_number(1,tmp_11.menuCharAuxiliar) en caso
    // de que no avisara de possible stack overflow.
	}


// ACTION: MAIN MANU -> FIRST -> INC
//==============================================================================
void a_m0_first_inc(void)
	{
    tmp_11.menuCharAuxiliar = !tmp_11.menuCharAuxiliar;
    a_m0_first_set();
	}


// ACTION: MAIN MANU -> FIRST -> SAVE
//==============================================================================
void a_m0_first_save(void)
    {
    T0_START(T0_MENU_RETURN);
    tmp_11.flag_inputSettingLedBlink = 0;

    tmp_11.mem_first = tmp_11.menuCharAuxiliar;
    EEPROM_WRITE_CHAR(EEADDR__04_00__FIRST,tmp_11.mem_first);
    a_m0_first();// Exit from set, but re-entrance.
    }


//==============================================================================
// ACTION: MAIN MANU -> INPUT
//==============================================================================
// No apaga salida, porque ya la apaga el 1er menu al entrar.
void a_m0_input(void)
	{
    T0_START(T0_MENU_RETURN);

	tmp_11.mainMenuState = TEXT__M0__INPUT;// Array de strings.
    d7sm_puts_scroll((char *)menu_text_main[tmp_11.mainMenuState]);
	}


// ACTION: MAIN MANU -> INPUT -> SET
//==============================================================================
// Muestra en pantalla el dato que debo ver para hacer el seteo requerido.
void a_m0_input_set(void)
	{
    T0_START(T0_MENU_RETURN);
    tmp_11.flag_inputSettingLedBlink = 1;

    if(estadoFsm==S__M0__INPUT)// Solo a la entrada del menu "first set".
        tmp_11.menuCharAuxiliar = tmp_11.mem_input;

    switch(tmp_11.menuCharAuxiliar)
        {
        case M0_INPUT_NADA: d7sm_puts_scroll((char *)"NAdA"); break;
        case M0_INPUT_PAUSE_ON: d7sm_puts_scroll((char *)"PAUSE ON"); break;
        case M0_INPUT_PAUSE_OFF: d7sm_puts_scroll((char *)"PAUSE OFF"); break;
        case M0_INPUT_DISABLE: d7sm_puts_scroll((char *)"dESHAbILItA"); break;
        case M0_INPUT_FUERZA: d7sm_puts_scroll((char *)"FUERZA"); break;
        }
	}


// ACTION: MAIN MANU -> FIRST -> INC
//==============================================================================
void a_m0_input_inc(void)
	{
    if(tmp_11.menuCharAuxiliar==(M0_INPUT_CANT-1))
        tmp_11.menuCharAuxiliar = 0;
    else
        tmp_11.menuCharAuxiliar++;

    a_m0_input_set();
	}


// ACTION: MAIN MANU -> FIRST -> SAVE
//==============================================================================
void a_m0_input_save(void)
    {
    T0_START(T0_MENU_RETURN);
    tmp_11.flag_inputSettingLedBlink = 0;

    tmp_11.mem_input = tmp_11.menuCharAuxiliar;
    EEPROM_WRITE_CHAR(EEADDR__00_00__INPUT,tmp_11.mem_input);
    a_m0_input();// Exit from set, but re-entrance.
    }


//==============================================================================
// ACTION -> MAIN MANU -> CANT MEMORIAS
//==============================================================================
// Apaga salida.
void a_m0_nMem(void)
	{
    T0_START(T0_MENU_RETURN);

    T1_STOP(T1_TIME);// Fuerza fin de funcionamiento
    OUT = 0;
    LED5 = 0;
    tmp_11.p2eepromAddr = EEADDR__16_00__TON_OFF;// Address con el que bootea si
    // stema, lo repongo para que cuendo recomience igual que al booteo.

    if(!tmp_11.mem_first) tmp_11.p2eepromAddr += sizeof(short long); // Ajuste p
    // ara que apunte a toff si es toff first.

	tmp_11.mainMenuState = TEXT__M0__NMEM;// Asigna elemento dentro de un array
    // de strings.
    d7sm_puts_scroll((char *)menu_text_main[tmp_11.mainMenuState]);
	}

//==============================================================================
// SUBMENUES PARA ACTION -> MAIN MANU -> CANT MEMORIAS
//==============================================================================


// ACTION -> MAIN MANU -> CANT MEMORIAS
// ACCIONES: SET CANT MEMORIAS
// MUESTRA EN PANTALLA EL DATO QUE DEBO VER PARA HACER EL SETEO REQUERIDO.
// LO QUE SE MOSTRARÁ EN PANTALLA ES:
// titila = dígito numérico que va a titilar dependiendo de lo que estoy seteando
// num = numero/variable a mostrar
//==============================================================================
void a_m0_nMem_set(void)
	{
    T0_START(T0_MENU_RETURN);
    tmp_11.flag_inputSettingLedBlink = 1;

    if(estadoFsm==S__M0__NMEM)// Unicamente a la entrance se hace.
        tmp_11.menuCharAuxiliar = tmp_11.mem_cantMemorias/2;

    D7SM_SET_NUMBER(1,tmp_11.menuCharAuxiliar);// titila=1, num=mem_cantMemorias
    // /2. Se podría usar d7sm_set_number(1,tmp_11.menuCharAuxiliar) en caso
    // de que no avisara de possible stack overflow.
	}


// ACTION -> MAIN MANU -> CANT MEMORIAS
//==============================================================================
// Agrega memoria en el menu variable (cantidad de tiempos configurables).
void a_m0_nMem_inc(void)
	{
    if(tmp_11.menuCharAuxiliar<MAX_MEMORIAS) tmp_11.menuCharAuxiliar++;
    a_m0_nMem_set();
	}


// ACTION -> MAIN MANU -> CANT MEMORIAS
//==============================================================================
// Quita memoria en el menu variable (cantidad de tiempos configurables).
void a_m0_nMem_dec(void)
	{
    if(tmp_11.menuCharAuxiliar>1) tmp_11.menuCharAuxiliar--;
    a_m0_nMem_set();
	}


// ACTION -> MAIN MANU -> CANT MEMORIAS
// ACCIONES: SAVE
//==============================================================================
void a_m0_nMem_save(void)
    {
    T0_START(T0_MENU_RETURN);
    tmp_11.flag_inputSettingLedBlink = 0;

    tmp_11.mem_cantMemorias=tmp_11.menuCharAuxiliar*2;
    EEPROM_WRITE_CHAR(EEADDR__02_00__NMEM,tmp_11.mem_cantMemorias);
    a_m0_nMem();//EXIT FROM SET BUT RE-ENTRANCE TO CANT MEMORIAS
    }


//==============================================================================
// ACTION -> MAIN MANU -> TON_OFF
//==============================================================================


// ACTION -> MAIN MANU -> TON_OFF
//==============================================================================
// Configura ingreso a submenu tiempos on/off de cantidad de memorias variable.
void a_m0_tOnOff_entrance(void)
	{
    T0_START(T0_MENU_RETURN);
    tmp_11.mainMenuState=0;// Inicializa apuntando a la 1er memoria.
    a_m0_tOnOff_showString();
	}


// ACTION -> MAIN MANU -> TON_OFF
// USADA COMO COMPLEMENTARIA, NO COMO INVOCADA DIRECTAMENTE.. AL MENOS POR EL MOMENTO
//==============================================================================
void a_m0_tOnOff_showString(void)
	{
    switch(tmp_11.mainMenuState%2)
        {
        case 0:
            d7sm_buffer[0]='t';
            d7sm_buffer[1]='o';
            d7sm_buffer[2]='n';
            d7sm_buffer[3]='_';
            //d7sm_buffer[4]='0'+tmp_11.mainMenuState/2;
            //d7sm_buffer[5]='0'+tmp_11.mainMenuState/2;
            d7sm_buffer[6]=0;

UCHAR_TO_STR(tmp_11.mainMenuState/2,&d7sm_buffer[4],2);//--->TRASLADADO A PREVIO A INVOCAR disp7segMux_set_number() DEBIDO A POSSIBLE STACK OVR

            break;
        case 1:
            d7sm_buffer[0]='t';
            d7sm_buffer[1]='o';
            d7sm_buffer[2]='f';
            d7sm_buffer[3]='f';
            d7sm_buffer[4]='_';
            //d7sm_buffer[5]='0'+(tmp_11.mainMenuState-1)/2;
            //d7sm_buffer[6]='0'+(tmp_11.mainMenuState-1)/2;
            d7sm_buffer[7]=0;

UCHAR_TO_STR((tmp_11.mainMenuState-1)/2,&d7sm_buffer[5],2);//--->TRASLADADO A PREVIO A INVOCAR disp7segMux_set_number() DEBIDO A POSSIBLE STACK OVR

            break;
        }

    //disp7segMux_scroll_charString(&d7sm_buffer);
    d7sm_puts_scroll((char *)&d7sm_buffer);
	}


// ACTION -> MAIN MANU -> TON_OFF
//==============================================================================
void a_m0_tOnOff_showString_next(void)
	{
    T0_START(T0_MENU_RETURN);

    tmp_11.mainMenuState++;// Primero muestra la memoria apuntada y luego al fin
    // al incrementa y apunta a la siguiente.
    if(tmp_11.mainMenuState==tmp_11.mem_cantMemorias) tmp_11.mainMenuState=0;

    a_m0_tOnOff_showString();
	}


// ACTION -> MAIN MANU -> TON_OFF
// ACCIONES: SET HORAS
// MUESTRA EN PANTALLA EL DATO QUE DEBO VER PARA HACER EL SETEO REQUERIDO.
// EL SETEO REQUERIDO VA A DEDUCIRSE DEL ESTADO ACTUAL.
// LO QUE SE MOSTRARÁ EN PANTALLA ES:
// titila = dígito numérico que va a titilar dependiendo de lo que estoy seteand
// o num = hh|mm|ss dependiendo de estadoFsm
// p2s = "h"|"m"|"s" dependiendo de si el num representa h/m/s
//==============================================================================
void a_m0_tOnOff_set(void)
	{
    char titila;
    unsigned char num;
    const char *p2s;

    T0_START(T0_MENU_RETURN);
    tmp_11.flag_inputSettingLedBlink = 1;

    switch(estadoFsm)// Este es el estado actual, pero para lo que voy a mostrar
    // importa cuál será el próximo, conociendo el actual.
        {
        case S__M0__TON_OFF:// Next state=S__M0__TON_OFF__SET_HH_0
                EEPROM_READ_SHORTLONG_INT(
                    (EEADDR__16_00__TON_OFF +
                    tmp_11.mainMenuState*sizeof(short long)),
                    tmp_11.menuShortLongAuxiliar);// Ejecutado únicamente en la 
                // entrance al seteo de HH.MM.SS. En a_m0_tOnOff_showString() vo
                // y ajustando tmp_11.mainMenuState=nro de la memoria que voy a 
                // modificar, por eso conozco cuál memoria tocar.
                tmp_11.menuShortLongAuxiliar/=4;
        case S__M0__TON_OFF__SET_HH_1:
        case S__M0__TON_OFF__SET_MM_1:
        case S__M0__TON_OFF__SET_SS_1:
            titila=0;
            break;
        case S__M0__TON_OFF__SET_HH_0:
        case S__M0__TON_OFF__SET_MM_0:
        case S__M0__TON_OFF__SET_SS_0:
            titila=1;
            break;
        }

    switch(estadoFsm)
        {
        case S__M0__TON_OFF:
        case S__M0__TON_OFF__SET_SS_1:
        case S__M0__TON_OFF__SET_HH_0:
            num=tmp_11.menuShortLongAuxiliar/3600;
            p2s=" h";
            break;
        case S__M0__TON_OFF__SET_HH_1:
        case S__M0__TON_OFF__SET_MM_0:
            //num=(tmp_11.menuShortLongAuxiliar/60)%3600;
            num=(tmp_11.menuShortLongAuxiliar%3600)/60;
            p2s=" m";
            break;    
        case S__M0__TON_OFF__SET_MM_1:
        case S__M0__TON_OFF__SET_SS_0:
            num=tmp_11.menuShortLongAuxiliar%60;
            p2s=" s";
            break;
        }

    d7sm_set_88xx(titila,num,p2s);
	}


// ACTION: MAIN MANU -> TON_OFF
//==============================================================================
void a_m0_tOnOff_inc(void)
	{
    T0_START(T0_MENU_RETURN);

    char hh,mm,ss;
    hh=(tmp_11.menuShortLongAuxiliar)/3600;
	mm=((tmp_11.menuShortLongAuxiliar)%3600)/60;
    ss=(tmp_11.menuShortLongAuxiliar)%60;

    switch(estadoFsm)
        {
        case S__M0__TON_OFF__SET_HH_0:
            if(hh%10==9) hh-=9;
            else hh++;
            break;
        case S__M0__TON_OFF__SET_HH_1:
            if(hh/10==9) hh-=90;
            else hh+=10;
//else mm+=10;
            break;
        case S__M0__TON_OFF__SET_MM_0:
            if(mm%10==9) mm-=9;
            else mm++;
            break;
        case S__M0__TON_OFF__SET_MM_1:
            if(mm/10==5) mm-=50;
            else mm+=10;
            break;
        case S__M0__TON_OFF__SET_SS_0:
            if(ss%10==9) ss-=9;
            else ss++;
            break;
        case S__M0__TON_OFF__SET_SS_1:
            if(ss/10==5) ss-=50;
            else ss+=10;
            break;
        }

    tmp_11.menuShortLongAuxiliar = (short long)hh*3600+
        (short long)mm*60+(short long)ss;// Sizeof(short long) = 3. El casteo es
        // importantisimo, porque si no se hace, toma 2 bytes por defecto, para
        // hacer la asignación a menuShortLongAuxiliar, y el 3er byte, te lo lle
        // na con 0xFF, o sea, es un compilador de mierda que hace cosas mal sin
        // avisar. Estuve un rato para darme cuenta.

    char titila;
    //unsigned char num;
long num;
    const char *p2s;

    switch(estadoFsm)// Este es el estado actual.
        {
        case S__M0__TON_OFF__SET_HH_1:
        case S__M0__TON_OFF__SET_MM_1:
        case S__M0__TON_OFF__SET_SS_1:
            titila=1;
            break;
        case S__M0__TON_OFF__SET_HH_0:
        case S__M0__TON_OFF__SET_MM_0:
        case S__M0__TON_OFF__SET_SS_0:
            titila=0;
            break;
        }

    switch(estadoFsm)
        {
        case S__M0__TON_OFF__SET_HH_0:
        case S__M0__TON_OFF__SET_HH_1:
            num = tmp_11.menuShortLongAuxiliar/(long)3600;
            p2s = " h";
            break;
        case S__M0__TON_OFF__SET_MM_0:
        case S__M0__TON_OFF__SET_MM_1:
            //num = (tmp_11.menuShortLongAuxiliar/60)%3600;
            num=(tmp_11.menuShortLongAuxiliar%(long)3600)/(long)60;
            p2s = " m";
            break;    
        case S__M0__TON_OFF__SET_SS_0:
        case S__M0__TON_OFF__SET_SS_1:
            num=tmp_11.menuShortLongAuxiliar%(long)60;
            p2s = " s";
            break;
        }

    //d7sm_set_88xx(titila,num,p2s);
d7sm_set_88xx(titila,(unsigned char)num,p2s);
	}


// ACTION: MAIN MANU -> TON_OFF
//==============================================================================
void a_m0_tOnOff_save(void)
    {
    T0_START(T0_MENU_RETURN);
    tmp_11.flag_inputSettingLedBlink = 0;

    EEPROM_WRITE_SHORTLONG_INT(
        (EEADDR__16_00__TON_OFF+tmp_11.mainMenuState*sizeof(short long)),
        tmp_11.menuShortLongAuxiliar*4);
    a_m0_tOnOff_showString();
    }


