//==============================================================================
// Archivo: tmp_11.h
// Autor: Federico Ramos
// Modificado: 17-11-2023 1738
// Proyecto: TMP:11:CIC
//==============================================================================


#ifndef __TMP_11_H
#define __TMP_11_H


//==============================================================================
// MENU PRINCIPAL IX
//==============================================================================
enum e_text_mainMenu_ix
	{
    TEXT__M0__FIRST,// First on or first off.
    TEXT__M0__INPUT,// Funcion de la entrada.
	TEXT__M0__NMEM,// Cantidad de memorias (tiempos)
	// TEXT__M0__TON_OFF --> No requerido. String se genera dinámicamente, depen
    // diendo de la cantidad de memorias (tiempos) que el usuario selecciona.
	TEXT__M0__CANT
	};


//==============================================================================
// MENU PRINCIPAL TEXTOS
//==============================================================================
const char *menu_text_main[]=
	{
    "FIRSt",
    "FUNCION ENtRAdA",
    "CANtIdAd tIEMPOS",
	// TEXT__M0__TON_OFF --> No requerido. String se genera dinámicamente, depen
    // diendo de la cantidad de memorias (tiempos) que el usuario selecciona.
	};

//	"b- PULSO REGRESIvA O tRANSCURRIDO"/*09 MENU_MOSTRAR_VISOR_PULSO*/

//	"1- dESHAbILItA",/*FP_DURANTE_PULSO_NADA*/
//	"2- FUERZA ENCENdIdO"/*FP_DURANTE_PULSO_CANCELA_PULSO*/

//	"1- REGRESIvA",/*MOSTRAR_VISOR_PULSO_REGRESIVA*/
//	"2- tRANSCURRIdO"/*MOSTRAR_VISOR_PULSO_TRANSCURRIDO*/

#define TMP11_DISP_LEN 4



//==============================================================================
// ENUMS
//==============================================================================
// Opciones "Función entrada" usadas para switch de reconocimiento de valores. C
// uidado con meter cosas en el medio: están ordenados tal que "encender" la sal
// ida lo puedo hacer con M0_INPUT_XXX%2 porque son impares, y apagar pares.
enum e_m0_input
    {
    M0_INPUT_NADA,
    M0_INPUT_PAUSE_ON,
    M0_INPUT_PAUSE_OFF,
    M0_INPUT_FUERZA,
    M0_INPUT_DISABLE,
    M0_INPUT_CANT
    };


//==============================================================================
// ESTRUCTURAS
//==============================================================================
// Ojo: esta estructura, si no compila por "no space for _isr temps", puede hace
// rse que compile agrandando el espacio ocupado en memoria (me ha ocurrido).
// Aquellos campos que tienen prefijo "mem_" son seteos que se guardan en mem.
typedef struct
    {
    unsigned char flag_showTimerId:1;// Permite identificar si muestro tiempo o 
    // id del timer en curso.
    unsigned char flag_showHyphens:1;// Cuando locked, si aprieto algo, muestra 
    // "----" y no hace nada.

    unsigned char flag_locked:1;// Bloquea seteos. Toma RB6 al booteo.
    unsigned char flag_inputSettingLedBlink:1;// Señaliza que usuario está en el
    // estado de "ingrese el valor del seteo".
    unsigned char flag_outForce:1;// Indica si output is forced. Antes de cambia
    // r el estado de la salida, revisa si se encuentra forzada.
    unsigned char flag_outForceVal:1;// Force value if forced.
    unsigned char flag_showTimeBlink:1;// Action showTime, que se da dentro de e
    // stado IDLE, muestra el tiempo en condiciones de funcionamiento normal. Ne
    // cesito indicar que parpadee en ese momento, para mostrar por ejemplo si e
    // l dispositivo fue pausado. Este flag cumple esa función.

    unsigned char mem_input:3;// Función entrada: none-pauseOn-pauseOff-deshabil
    // ita-fuerza.
	unsigned char mem_visor_parpadeo:1;// Opciones: pulso-demora-ninguno.
    unsigned char mem_first:1;// Opciones: on_first-off_first. Decide si al boot
    // eo el primer estado logico de la salida es ton o toff
    unsigned char mem_cantMemorias;// Max=40 (0..39) Opciones: sube de 2 en 2 po
    // rque usa 1 para ton y otro para toff.

	char mainMenuState;// Usado para saber lo que tiene que mostrar dentro del M
    // AIN MENU (textos).
	char menuCharAuxiliar;// Usado como variable temporal mientras modifico un s
    // eteo escalar.
    short long menuShortLongAuxiliar;// Usado como variable temporal mientras mo
    // difico seteo escalar.

	char configSetting;

    char p2eepromAddr;// Apunta a TON_OFF en EEPROM. Lo requiere para ir cicland
    // o un tiempo tras otro. Siempre apunta al siguiente a utilizar.
    
	char str[TMP11_DISP_LEN];
	}t_temporizador;


//==============================================================================
// GLOBALS
extern t_temporizador tmp_11;
extern char bitTitila;
//==============================================================================


//==============================================================================
// PROTOTIPOS
void tmp_11_test_display(void);
void tmp_11_init(void);
void tmp_11_driver(void);
void tmp_11_action(char new_event);
char tmp_11_get_event(void);
short long delay_constant_hhmmss(char hh,char mm,char ss);
void returnToIdle(void);
void ucharToStr(unsigned char num,char *str,char strLen);
//==============================================================================


#endif//__TMP_11_H