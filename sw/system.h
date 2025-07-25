//==============================================================================
// Archivo: system.h
// Autor: Federico Ramos
// Modificado: 16-11-2023 1359
//==============================================================================


//==============================================================================
// CONSTANT DEFINITIONS
#define INPUT 1
#define OUTPUT 0
//==============================================================================


//==============================================================================
// PINES UTILIZADOS
//==============================================================================
#define PUL0 RA0// Abajo derecha [SETEO]
#define LED5 RA1// Output led.
#define PUL1 RA2// Abajo izquierda [INCREMENTAR]
#define LED3 RA3// In1 led.
#define AN1 RA4
#define SEG_A RA5
#define SEG_D RA6
#define SEG_B RA7

#define IN1 RB0// In1 (optocoplada).
#define OUT RB1// Output.
#define IN2 RB2// In2 (optocoplada)
#define LED2 RB3// In2 led.
#define LED14N RB4// Input seting (led blink).
#define LED0 RB5// Desbloqueado.
#define LOCK RB6
#define UNUSED_RB7 RB7

#define AN2 RC0
#define AN0 RC1
#define SEG_DP RC2// In2 led (unused).
#define SEG_C RC3
#define SEG_E RC4
#define SEG_G RC5
#define SEG_F RC6
#define AN3 RC7

#define PUL2 RE3// Arriba derecha [ACEPTAR]


//==============================================================================
// DATA DIRECTION REGISTERS
//==============================================================================
#define DDR_PUL0 TRISA0
#define DDR_LED5 TRISA1
#define DDR_PUL1 TRISA2
#define DDR_LED3 TRISA3
#define DDR_AN1 TRISA4
#define DDR_SEG_A TRISA5
#define DDR_SEG_D TRISA6
#define DDR_SEG_B TRISA7

#define DDR_IN1 TRISB0
#define DDR_OUT TRISB1
#define DDR_IN2 TRISB2
#define DDR_LED2 TRISB3
#define DDR_LED14N TRISB4
#define DDR_LED0 TRISB5
#define DDR_LOCK TRISB6
#define DDR_UNUSED_RB7 TRISB7

#define DDR_AN2 TRISC0
#define DDR_AN0 TRISC1
#define DDR_SEG_DP TRISC2
#define DDR_SEG_C TRISC3
#define DDR_SEG_E TRISC4
#define DDR_SEG_G TRISC5
#define DDR_SEG_F TRISC6
#define DDR_AN3 TRISC7

#define DDR_PUL2 TRISE3


//==============================================================================
// MACROS
//==============================================================================
#define INIT_DDR()                                                             \
    {                                                                          \
    DDR_OUT=OUTPUT;                                                            \
    DDR_LED0=OUTPUT;                                                           \
    DDR_LED14N=OUTPUT;                                                         \
    DDR_LED2=OUTPUT;                                                           \
    DDR_LED3=OUTPUT;                                                           \
    DDR_LED5=OUTPUT;                                                           \
                                                                               \
    DDR_AN0=OUTPUT;                                                            \
    DDR_AN1=OUTPUT;                                                            \
    DDR_AN2=OUTPUT;                                                            \
    DDR_AN3=OUTPUT;                                                            \
                                                                               \
    DDR_SEG_A=OUTPUT;                                                          \
    DDR_SEG_B=OUTPUT;                                                          \
    DDR_SEG_C=OUTPUT;                                                          \
    DDR_SEG_D=OUTPUT;                                                          \
    DDR_SEG_E=OUTPUT;                                                          \
    DDR_SEG_F=OUTPUT;                                                          \
    DDR_SEG_G=OUTPUT;                                                          \
    DDR_SEG_DP=OUTPUT;                                                         \
                                                                               \
    DDR_PUL0=INPUT;                                                            \
    DDR_PUL1=INPUT;                                                            \
    DDR_PUL2=INPUT;                                                            \
    }

#define INIT_PORTS()                                                           \
    {                                                                          \
    PORTA=0XFF;                                                                \
    PORTB=0XFF;                                                                \
    PORTC=0XFF;                                                                \
    PORTE=0XFF;                                                                \
    OUT=0;                                                                     \
    LED0=0;                                                                    \
    LED14N=1;                                                                  \
    LED2=0;                                                                    \
    LED3=0;                                                                    \
    LED5=0;                                                                    \
    AN0=0;                                                                     \
    AN1=0;                                                                     \
    AN2=0;                                                                     \
    AN3=0;                                                                     \
    }


#define DISABLE_COMPARATOR()                                                   \
    {                                                                          \
    CM0=1;                                                                     \
    CM1=1;                                                                     \
    CM2=1;                                                                     \
    }

// Si no se va a usar el A/D, esta función se debe invocar, ya que por defecto,
// luego del reset, los puertos de entrada comienzan como entradas analógicas pa
// ra ser usadas con el A/D, lo cual deshabilita que funcionen como entradas/sal
// idas digitales.
#define DISABLE_AD() {                                                         \
    ANS0=0;                                                                    \
    ANS1=0;                                                                    \
    ANS2=0;                                                                    \
    ANS3=0;                                                                    \
    ANS4=0;                                                                    \
    }

#define ENABLE_AD()                                                            \
    {                                                                          \
    ANS0=1;                                                                    \
    ANS1=1;                                                                    \
    ANS2=0;                                                                    \
    ANS3=0;                                                                    \
                                                                               \
    ADCS0=1;                                                                   \
    ADCS1=0;                                                                   \
    ADCS2=0;                                                                   \
                                                                               \
    ADFM=0;                                                                    \
                                                                               \
    ADON=1;                                                                    \
    }


#define PIC12F683_8MHZ()                                                       \
    {                                                                          \
    IRCF0=1;                                                                   \
    IRCF1=1;                                                                   \
    IRCF2=1;                                                                   \
    }


#define PIC16F886_8MHZ()                                                       \
    {                                                                          \
    IRCF0=1;                                                                   \
    IRCF1=1;                                                                   \
    IRCF2=1;                                                                   \
    }


//==============================================================================
// PROTOTIPOS
void systemInit(void);
//==============================================================================