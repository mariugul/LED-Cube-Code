/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                     timer.h                           *
 *                                                       *
 * This file initializes the timer for use of interrupts *
 *                                                       *
 *                                                       *
 * By: Marius C. K. Gulbrandsen                          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

// Header Guard
//---------------------------------
#ifndef __TIMER_H__
#define __TIMER_H__

// Includes
//---------------------------------
#include <avr/io.h>

// Defines
//---------------------------------

// Function Prototypes
//---------------------------------
void timer_init();
void global_interrupt_enable();
void global_interrupt_disable();

#endif