#ifndef OLED_H
#define OLED_H

#include <avr/delay.h>

#include "fonts.h"

#define OLED_COMMAND_PIN 3
volatile char *OLED_COMMAND;
volatile char *OLED_DATA;

#define HEIGHT 64
#define WIDTH 128

// Types of available menu
typedef enum
{
	MAIN,
	PLAYMENU,
	SETTINGS,
	CREDITS,
	ABOUT
} menu_name;

// Struct to have both text and length of string on the same place
typedef struct
{
	char *name;
	uint8_t length;
} menu_entry;

// Creating menus HERE:
menu_entry main_menu[4];

// Current cursor position on the screen (line number)
volatile uint8_t menu_pos;

/**
 * @brief Send command to the OLED controller
 * 
 * @param c Command to be sent
 */
void OLED_write_command(uint8_t c);

/**
 * @brief Write data to the OLED
 * 
 * @param d Data to write
 */
void OLED_write_data(uint8_t d);

/**
 * @brief Initialization function for the OLED
 * 
 */
void OLED_init();

/**
 * @brief Set cursor to a certain line of the OLEd
 * 
 * @param line Line number
 */
void OLED_goto_line(uint8_t line);

/**
 * @brief Set the cursor to a certain column
 * 
 * @param column Column number
 */
void OLED_goto_column(uint8_t column);

/**
 * @brief Set the cursor to a certain line and column
 * 
 * @param line Line number
 * @param column Column number
 */
void OLED_set_pos(uint8_t line, uint8_t column);

/**
 * @brief Fill line with white pixels
 * 
 * @param line Line number
 */
void OLED_fill_line(uint8_t line);

/**
 * @brief Clear the screen
 * 
 */
void OLED_clear_all();

/**
 * @brief Print character on the OLED
 * 
 * @param c Character
 * @param line line number
 * @param col Column number
 */
void OLED_print_char(char c, uint8_t line, uint8_t col);

/**
 * @brief Print string to the OLED
 * 
 * @param s String
 * @param length Length of the string
 * @param line Line number
 */
void OLED_print_string(char *s, uint8_t length, uint8_t line);

/**
 * @brief Update the cursor on the menu
 * 
 * @param pos 
 */
void OLED_update_menu(uint8_t pos);

/**
 * @brief Print menu on the OLED
 * 
 * @param menutype 
 */
void OLED_print_menu(uint8_t menutype);

#endif