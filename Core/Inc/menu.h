#ifndef __MENU_H
#define __MENU_H


#include "main.h"
#include "stm32l1xx_hal.h"
#include "stdbool.h"

#define Acceptance_Level    3000
#define Restart_Level       500

typedef union 
{
    uint8_t data;
    struct
    {
        uint8_t B0   :1;
        uint8_t B1   :1;
        uint8_t B2   :1;
        uint8_t B3   :1;
        uint8_t B4   :1;
        uint8_t B5   :1;
        uint8_t B6   :1;
        uint8_t B7   :1;
    } bit;
    
} Flag8_t;

typedef enum {
    BTN_NONE,
    BTN_GREEN_CLK,
    BTN_GREEN_DBL_CLK,
    BTN_GREEN_LONG_CLK,
    BTN_RED_CLK,
    BTN_RED_DBL_CLK,
    BTN_RED_LONG_CLK
} ButtonValues;

typedef enum {
    DEFAULT_POS,
    SETTING_MODE
} MenuPosition;

// Menu settings
ButtonValues GetButtonPress(void);
MenuPosition GetMenuPostion(void);
void SetMenuPosition(MenuPosition);
void ChooseItem(void);

typedef enum 
{
    MenuButtonStatus_oneClick = 0,
    MenuButtonStatus_doubleClick, 
    MenuButtonStatus_heldPressed, 
    MenuButtonStatus_notPressed
} MenuButtonStatus_e;

typedef struct 
{
   uint32_t             buttonTimer;
   bool                 buttonTimerEnable;
   MenuButtonStatus_e   buttonStatus;
   Flag8_t              buttonFlag;
   uint8_t              buttonHeldPressedCounter;
} MenuButton_t;

extern MenuButton_t redMenuButton;
extern MenuButton_t greenMenuButton;

void initMenu(void);
void testPress(void);
uint8_t MenuButton_Debounce(void);
void setTimer(uint32_t* timer);
uint8_t checkTimer(uint32_t* timer, uint32_t msTime);


#endif