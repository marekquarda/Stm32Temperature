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