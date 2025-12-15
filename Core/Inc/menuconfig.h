/**
              MICRO-MENU V3.6
              
          (C) Marek Quarda, 2025

                                      */

#ifndef _MICRO_MENU_CONFIG_H_
#define _MICRO_MENU_CONFIG_H_

#define MICRO_MENU_V3

#ifdef MICRO_MENU_V3
#define USE_DATA
#ifdef USE_DATA
#define USE_DATA_RANGE
#ifdef USE_DATA_RANGE
#define JUMP_MIN_TO_MAX_TO_MIN // Comment out this line to prevent the jumps from maxValue to MinValue and backward when editing data.
#endif

#define USE_FLOAT_TYPE // Comment out this line if you do not plan to use float, double and long double type variables.
#define USE_CHAR_TYPE  // Comment out this line if you do not plan to use char type variables.
#endif
#endif

/** Configuration for the desired memory storage location of created menu items.
 *  This may be configured to locate the menus into FLASH memory space, SRAM, or
 *  any other suitable memory space.
 */
#define MENU_ITEM_STORAGE const

/** Configuration for the macro or function required to read out a pointer from
 *  the memory storage space set by \ref MENU_ITEM_STORAGE.
 *
 *  \param[in] Addr  Address of the pointer to read
 */
#elif defined(__arm__) // && defined(__GNUC__)

#endif