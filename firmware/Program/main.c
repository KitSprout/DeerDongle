/**
 *      __            ____
 *     / /__ _  __   / __/                      __  
 *    / //_/(_)/ /_ / /  ___   ____ ___  __ __ / /_ 
 *   / ,<  / // __/_\ \ / _ \ / __// _ \/ // // __/ 
 *  /_/|_|/_/ \__//___// .__//_/   \___/\_,_/ \__/  
 *                    /_/   github.com/KitSprout    
 * 
 *  @file    main.c
 *  @author  KitSprout
 *  @brief   main function
 * 
 */

/* Includes --------------------------------------------------------------------------------*/
#include "kitsprout\kSystem.h"
#include "drivers\stm32l0_tim.h"
#include "modules\serial.h"

#include <stdio.h>
#include "stm32x_bsp.h"

/* Define ----------------------------------------------------------------------------------*/

#define T   1000000             //   1 MHz
#define DDO (5000 - T/262)      //  262 Hz
#define DRE (5000 - T/294)      //  294 Hz
#define DMI (5000 - T/330)      //  330 Hz
#define DFA (5000 - T/349)      //  349 Hz
#define DSO (5000 - T/392)      //  392 Hz
#define DLA (5000 - T/440)      //  440 Hz
#define DSI (5000 - T/494)      //  494 Hz

#define DO  (5000 - T/523)      //  523 Hz
#define RE  (5000 - T/587)      //  587 Hz
#define MI  (5000 - T/659)      //  659 Hz
#define FA  (5000 - T/698)      //  698 Hz
#define SO  (5000 - T/784)      //  784 Hz
#define LA  (5000 - T/880)      //  880 Hz
#define SI  (5000 - T/988)      //  988 Hz

#define UDO (5000 - T/1046)     // 1046 Hz
#define URE (5000 - T/1175)     // 1175 Hz
#define UMI (5000 - T/1318)     // 1318 Hz
#define UFA (5000 - T/1480)     // 1480 Hz
#define USO (5000 - T/1568)     // 1568 Hz
#define ULA (5000 - T/1760)     // 1760 Hz
#define USI (5000 - T/1976)     // 1976 Hz

#define NP  (0)                 // 
#define NP2 (1)                 // 
#define NP4 (2)                 // 
#define NP8 (3)                 // 

/* Macro -----------------------------------------------------------------------------------*/
/* Typedef ---------------------------------------------------------------------------------*/
/* Variables -------------------------------------------------------------------------------*/

const uint16_t PLAY[21] =
{
  // 1    2    3    4    5    6    7
    DDO, DRE, DMI, DFA, DSO, DLA, DSI,
     DO,  RE,  MI,  FA,  SO,  LA,  SI,
    UDO, URE, UMI, UFA, USO, ULA, USI
};

#define LENS_BIRTHDAY 31
const uint16_t BIRTHDAY[LENS_BIRTHDAY] =
{
    DSO, DSO, DLA, DSO,  DO, DSI,  NP,              // 7
    DSO, DSO, DLA, DSO,  RE,  DO,  NP,              // 7
    DSO, DSO,  SO,  MI,  DO, DSI, DLA, DLA,  NP,    // 9
     FA,  FA,  MI,  DO,  RE,  DO,  NP,              // 7
};

#define LENS_XRMS   (32+32+32+32)
const uint16_t XRMS[LENS_XRMS] =
{
    DSO,  MI,  RE,  DO, DSO, DSO,  NP,  NP,
    DSO,  MI,  RE,  DO, DLA, DLA,  NP,  NP,
    DLA,  FA,  MI,  RE, DSI, DSI,  NP,  NP,
     SO,  SO,  FA,  RE,  MI,  DO,  NP,  NP,     // 32

    DSO,  MI,  RE,  DO, DSO, DSO,  NP,  NP,
    DSO,  MI,  RE,  DO, DLA, DLA,  NP,  NP,
    DLA,  FA,  MI,  RE,  SO,  SO,  SO,  SO,
     LA,  SO,  FA,  RE,  DO,  DO,  SO,  NP,     // 32

     MI,  MI,  MI,  NP,  MI,  MI,  MI,  NP,
     MI,  SO,  DO,  RE,  MI,  MI,  MI,  NP,
     FA,  FA,  FA,  FA,  FA,  MI,  MI,  MI,
     MI,  RE,  RE,  MI,  RE,  RE,  SO,  NP,     // 32

     MI,  MI,  MI,  NP,  MI,  MI,  MI,  NP,
     MI,  SO,  DO,  RE,  MI,  NP,  MI,  NP,
     FA,  FA,  FA,  FA,  FA,  MI,  MI,  MI,
     SO,  SO,  FA,  RE,  DO,  DO,  DO,  NP,     // 32
};

static __IO uint16_t note = NP;
static uint8_t input = 0;

/* Prototypes ------------------------------------------------------------------------------*/

void ks_command( uint8_t *command );

void playScale( uint16_t scale, uint16_t time );
void event_timer_playmusic( void );
void event_uart_serial_recv( void );

/* Functions -------------------------------------------------------------------------------*/

void bsp_init( void )
{
    bsp_gpio_init();
    bsp_timer_init(event_timer_playmusic);
    bsp_uart_serial_init(event_uart_serial_recv);
}

int main( void )
{
    bsp_init();
    Timer2_Cmd(ENABLE);

    while (1)
    {
        LED_G_Toggle();
        if (KEY_READ())
        {
            LED_G_Off();
            for (uint32_t i = 0; i < LENS_XRMS; i++)
            {
                LED_B_Toggle();
                if (i < (32+32))
                {
                    playScale(XRMS[i], 500);
                }
                else if (i < (32+32+32))
                {
                    playScale(XRMS[i], 400);
                }
                else
                {
                    playScale(XRMS[i], 380);
                }
            }
            for (uint32_t i = 0; i < LENS_XRMS; i++)
            {
                LED_B_Toggle();
                if (i < (32+32))
                {
                    playScale(XRMS[i], 200);
                }
                else
                {
                    playScale(XRMS[i], 200);
                }
            }
            LED_B_Off();
            playScale(NP, 1000);
            playScale(DO, 200);
            delay_ms(50);
            playScale(DO, 200);
            playScale(NP, 2000);
            playScale(DO, 200);
            playScale(NP, 1000);
        }
        ks_command(&input);
    }
}

void playScale( uint16_t scale, uint16_t time )
{
    if (scale == NP)
    {
        Timer2_SetCounter(0);
        Timer2_Cmd(DISABLE);
        delay_ms(time);
    }
    else if (scale == NP2)
    {
        Timer2_SetCounter(0);
        Timer2_Cmd(DISABLE);
        delay_ms(time >> 1);
    }
    else if (scale == NP4)
    {
        Timer2_SetCounter(0);
        Timer2_Cmd(DISABLE);
        delay_ms(time >> 2);
    }
    else if (scale == NP8)
    {
        Timer2_SetCounter(0);
        Timer2_Cmd(DISABLE);
        delay_ms(time >> 3);
    }
    else
    {
//        if (note != scale)
//        {
            note = scale;
            Timer2_SetCounter(note);
            Timer2_Cmd(ENABLE);
//        }
        delay_ms(time);
    }
}

void ks_command( uint8_t *command )
{
    uint32_t cmd = *command;
    uint32_t scale = NP;
    *command = 0;

    switch (cmd)
    {
        case 'q':
        case 'Q':   {   scale = DDO;    break;  }
        case 'w':
        case 'W':   {   scale = DRE;    break;  }
        case 'e':
        case 'E':   {   scale = DMI;    break;  }
        case 'r':
        case 'R':   {   scale = DFA;    break;  }
        case 't':
        case 'T':   {   scale = DSO;    break;  }
        case 'y':
        case 'Y':   {   scale = DLA;    break;  }
        case 'u':
        case 'U':   {   scale = DSI;    break;  }

        case 'a':
        case 'A':   {   scale = DO;     break;  }
        case 's':
        case 'S':   {   scale = RE;     break;  }
        case 'd':
        case 'D':   {   scale = MI;     break;  }
        case 'f':
        case 'F':   {   scale = FA;     break;  }
        case 'g':
        case 'G':   {   scale = SO;     break;  }
        case 'h':
        case 'H':   {   scale = LA;     break;  }
        case 'j':
        case 'J':   {   scale = SI;     break;  }

        case 'z':
        case 'Z':   {   scale = UDO;    break;  }
        case 'x':
        case 'X':   {   scale = URE;    break;  }
        case 'c':
        case 'C':   {   scale = UMI;    break;  }
        case 'v':
        case 'V':   {   scale = UFA;    break;  }
        case 'b':
        case 'B':   {   scale = USO;    break;  }
        case 'n':
        case 'N':   {   scale = ULA;    break;  }
        case 'm':
        case 'M':   {   scale = USI;    break;  }

    }
    playScale(scale, 100);
}

void event_timer_playmusic( void )
{
    Timer2_SetCounter(note);
    if ((note == NP) || (note == NP2) || (note == NP4))
    {
        BUZ_Reset();
    }
    else
    {
        BUZ_Toggle();
    }
}

void event_uart_serial_recv( void )
{
    LED_B_Toggle();
    input = Serial_RecvByte();
}

/*************************************** END OF FILE ****************************************/
