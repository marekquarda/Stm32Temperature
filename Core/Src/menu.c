/*
 *    MICRO-MENU V3.6
 *
 * @file        menu.c
 * @brief       Menu Library
 * @author      Marek Quarda
 * @version     1.0.0
 */

#include "menu.h"
#include "display.h"
#include "micromenu.h"


MenuButton_t redMenuButton;
MenuButton_t greenMenuButton;

ButtonValues choose = BTN_NONE;
MenuPosition position = DEFAULT_POS;


void initMenu(void) {
    redMenuButton.buttonFlag.data = RESET;
    redMenuButton.buttonStatus = MenuButtonStatus_notPressed;

    greenMenuButton.buttonFlag.data = RESET;
    greenMenuButton.buttonStatus = MenuButtonStatus_notPressed;
};

ButtonValues GetButtonPress(void) {
    return choose;
};

MenuPosition GetMenuPostion(void) {
    return position;
};

void SetMenuPosition(MenuPosition pos) {
    position = pos;
};

void ChooseItem(void) {
    switch (GetButtonPress())
    {
    case BTN_GREEN_CLK:
        Menu_Navigate(MENU_PREVIOUS);
        break;
    case BTN_GREEN_LONG_CLK:
        Menu_Navigate(MENU_PARENT);
        break;
    case BTN_GREEN_DBL_CLK:
        // TODO: Need to insert
        break;
    case BTN_RED_CLK:
        Menu_Navigate(MENU_NEXT);
        break;
    case BTN_RED_LONG_CLK:
        Menu_Navigate(MENU_CHILD);
        break;
    case BTN_RED_DBL_CLK:
        // TODO: Need to insert
        break;        
    default:
        break;
    }
}

void setTimeVal(ButtonSet value) {
    switch (value)
    {
    case TIME_SET_UP:
        //TODO: need to insert
        break;
    case TIME_SET_DOWN:
        //TODO: need to insert
        break;
    default:
        break;
    }
    printValue(PRINT_TIME);
}

void setDateVal(ButtonSet value) {
    switch(value)
    {
    case DATE_SET_UP:
        //TODO: need to insert
        break;
    case DATE_SET_DOWN:
        //TODO: need to insert
        break;
    default:
        break;        
    }
    printValue(PRINT_DATE);
}

void printValue(PrintValues value) {
    switch (value)
    {
    case PRINT_TIME:
        //TODO: need to insert
        break;
    case PRINT_DATE:
        //TODO: need to insert
        break;
    default:

        break;
    }
}

static void Time_Select(void) {
    // TODO: need to insert
}

static void Date_Select(void) {
    // TODO: need to insert
}

static void Time_Setting_Up(void) {
    // TODO: need to insert
}

static void Time_Setting_Down(void) {
    // TODO: need to insert
}

static void Date_Setting_Up(void) {
    // TODO: need to insert
}

static void Date_Setting_Down(void) {
    // TODO: need to insert
}

static void Time_Save() {
    // TODO: need to insert
}

static void Date_Save() {
    // TODO: need to insert
}

// Menu Initialization
MENU_ITEM(Menu_1, Menu_2, Menu_1, NULL_MENU, Menu_1_1, Time_Select, NULL, NULL, NULL, "1");
MENU_ITEM(Menu_2, Menu_2, Menu_1, NULL_MENU, Menu_2_2, Date_Select, NULL, NULL, NULL, "2");

// Time SubMenu initialization
MENU_ITEM(Menu_1_1, Menu_1_2, Menu_1_1, Menu_ST, NULL_MENU, Time_Setting_Up, NULL, NULL, NULL, "1.1");
MENU_ITEM(Menu_1_2, Menu_1_1, Menu_1_1, Menu_ST, NULL_MENU, Time_Setting_Down, NULL, NULL, NULL, "1.2");

// Date SubMenu initialization
MENU_ITEM(Menu_2_1, Menu_2_2, Menu_2_1, Menu_SD, NULL_MENU, Date_Setting_Up, NULL, NULL, NULL, "2.1");
MENU_ITEM(Menu_2_2, Menu_2_1, Menu_2_1, Menu_SD, NULL_MENU, Date_Setting_Down, NULL, NULL, NULL, "2.2");

MENU_ITEM(Menu_ST, NULL_MENU, NULL_MENU, Menu_1, NULL_MENU, Time_Save, NULL, NULL, NULL, "3.0");
MENU_ITEM(Menu_SD, NULL_MENU, NULL_MENU, Menu_2, NULL_MENU, Date_Save, NULL, NULL, NULL, "3.0");

void InitMenu() {
    // Init menu 
    Menu_Navigate(&Menu_1);
}

void testPress(void) {
    // Red Button
    if (redMenuButton.buttonFlag.bit.B0) {
        if(MenuButton_Debounce()) 
        {
            redMenuButton.buttonFlag.bit.B0 = RESET;
            if (redMenuButton.buttonTimerEnable != SET) 
            {
                redMenuButton.buttonTimerEnable = SET;
                redMenuButton.buttonStatus = MenuButtonStatus_oneClick;
                setTimer(&redMenuButton.buttonTimer);
            } else {
                redMenuButton.buttonStatus = MenuButtonStatus_doubleClick;
            }
        }
    }
    if((checkTimer(&redMenuButton.buttonTimer, 5*redMenuButton.buttonHeldPressedCounter)) && (redMenuButton.buttonStatus == MenuButtonStatus_oneClick)) 
    {
        if(!HAL_GPIO_ReadPin(BTN_RED_GPIO_Port, BTN_RED_Pin)) {
            ++redMenuButton.buttonHeldPressedCounter;
        }
        redMenuButton.buttonStatus = (redMenuButton.buttonHeldPressedCounter >= 65) ? MenuButtonStatus_heldPressed : redMenuButton.buttonStatus;
    }
    if ((checkTimer(&redMenuButton.buttonTimer, 350)) && redMenuButton.buttonTimerEnable)
    {

        switch (redMenuButton.buttonStatus)
        {
        case MenuButtonStatus_oneClick:
            // set button event
            choose = BTN_RED_CLK;
            // set display
            clearDisp(symbols_mem);
            getSymbol(NO_SYMBOL_C, POSITION_3, symbols_mem);
	        display(symbols_mem);
            break;
        case MenuButtonStatus_doubleClick:
            // set button event
            choose = BTN_RED_DBL_CLK;
            // set display
            clearDisp(symbols_mem);
            getSymbol(NUMBER_8, POSITION_3, symbols_mem);
	        display(symbols_mem);
            break;
        case MenuButtonStatus_heldPressed:
            // set button event
            choose = BTN_RED_LONG_CLK;
            // set display
            clearDisp(symbols_mem);
            getSymbol(NO_SYMBOL_H, POSITION_3, symbols_mem);
	        display(symbols_mem);
        case MenuButtonStatus_notPressed:
            clearDisp(symbols_mem);
            getSymbol(NO_SYMBOL_L, POSITION_3, symbols_mem);
	        display(symbols_mem);
            break;
        }
        redMenuButton.buttonTimerEnable = RESET;
        redMenuButton.buttonHeldPressedCounter = RESET;
        redMenuButton.buttonStatus = MenuButtonStatus_notPressed;
    }

    // Green Button
    if (greenMenuButton.buttonFlag.bit.B0) {
        if(MenuButton_Debounce()) 
        {
            greenMenuButton.buttonFlag.bit.B0 = RESET;
            if (greenMenuButton.buttonTimerEnable != SET) 
            {
                greenMenuButton.buttonTimerEnable = SET;
                greenMenuButton.buttonStatus = MenuButtonStatus_oneClick;
                setTimer(&greenMenuButton.buttonTimer);
            } else {
                greenMenuButton.buttonStatus = MenuButtonStatus_doubleClick;
            }
        }
    }
    if((checkTimer(&greenMenuButton.buttonTimer, 5*greenMenuButton.buttonHeldPressedCounter)) && (greenMenuButton.buttonStatus == MenuButtonStatus_oneClick)) 
    {
        if(!HAL_GPIO_ReadPin(BTN_GREEN_GPIO_Port, BTN_GREEN_Pin)) {
            ++greenMenuButton.buttonHeldPressedCounter;
        }
        greenMenuButton.buttonStatus = (greenMenuButton.buttonHeldPressedCounter >= 65) ? MenuButtonStatus_heldPressed : greenMenuButton.buttonStatus;
    }
    if ((checkTimer(&greenMenuButton.buttonTimer, 350)) && greenMenuButton.buttonTimerEnable)
    {
        
        switch (greenMenuButton.buttonStatus)
        {
        case MenuButtonStatus_oneClick:
            // set button event
            choose = BTN_GREEN_CLK;
            // set display
            clearDisp(symbols_mem);
            getSymbol(NO_SYMBOL_C, POSITION_1, symbols_mem);
	        display(symbols_mem);
            break;
        case MenuButtonStatus_doubleClick:
            // set button event
            choose = BTN_GREEN_DBL_CLK;
            // set display
            clearDisp(symbols_mem);
            getSymbol(NUMBER_8, POSITION_1, symbols_mem);
	        display(symbols_mem);
            break;
        case MenuButtonStatus_heldPressed:
            // set button event
            choose = BTN_GREEN_LONG_CLK;
            // set display
            clearDisp(symbols_mem);
            getSymbol(NO_SYMBOL_H, POSITION_1, symbols_mem);
	        display(symbols_mem);
        case MenuButtonStatus_notPressed:
            
            clearDisp(symbols_mem);
            getSymbol(NO_SYMBOL_L, POSITION_1, symbols_mem);
	        display(symbols_mem);
            break;
        }
        greenMenuButton.buttonTimerEnable = RESET;
        greenMenuButton.buttonHeldPressedCounter = RESET;
        greenMenuButton.buttonStatus = MenuButtonStatus_notPressed;
    }
    ChooseItem();
};

uint8_t MenuButton_Debounce(void) {
    uint8_t ret = DISABLE;
    static uint16_t level = Restart_Level;
    if (!HAL_GPIO_ReadPin(BTN_RED_GPIO_Port, BTN_RED_Pin) || !HAL_GPIO_ReadPin(BTN_GREEN_GPIO_Port, BTN_GREEN_Pin)) {
        ++level;
    } else {
        --level;
        if(level <= Restart_Level) {
            level = Restart_Level;
        }
    }
    if (level >= 4000) {
        level = Acceptance_Level;
        ret = ENABLE;
    }
    return ret;
};

void setTimer(uint32_t* timer) {
    *timer = HAL_GetTick();
};

uint8_t checkTimer(uint32_t* timer, uint32_t msTime) {
    uint8_t ret = RESET;
    ret = ((HAL_GetTick() - *timer) > msTime) ? ENABLE : DISABLE;
    return ret;
};