#include "OLED.h"
#include "fonts.h"

// Creating menus HERE:
menu_entry main_menu[4] = {{"Play", 4}, {"Credits", 7}, {"About", 5}};
menu_entry play_menu[2] = {{"Playing", 7}, {"Return", 6}};
menu_entry credits_menu[4] = {{"Hans", 4}, {"Leonardo", 8}, {"Pragaash", 8}, {"Tobi", 4}};
menu_entry about_menu[4] = {{"TTK4155", 7}, {"Group 39", 8}, {"2021", 4}, {"2022", 4}};

// Current cursor position on the screen (line number)
volatile uint8_t menu_pos = 1;
uint8_t is_main_menu = 1;

volatile char *OLED_COMMAND = (char *)0x1000;
volatile char *OLED_DATA = (char *)0x1200;

void OLED_write_command(uint8_t c)
{
    // Writing command to OLED
    OLED_COMMAND[0] = c;
}

void OLED_write_data(uint8_t d)
{
    // Writing data to OLED
    OLED_DATA[0] = d;
}

void OLED_init()
{
    // Part adapted from the OLED datasheet
    OLED_write_command(0xAE); // Display OFF

    // Had to change this from A0 to A1 otherwise the horizontal axis would have been inverted
    OLED_write_command(0xA1); // Segment remap

    OLED_write_command(0xDA); // Common pads hardware: alternative
    OLED_write_command(0x12);

    OLED_write_command(0xC8); // Common output scan direction com63~com0

    OLED_write_command(0xA8); // Multiplex ration mode: 63
    OLED_write_command(0x3F);

    OLED_write_command(0xD5); // Display divide ratio/osc. freq. mode
    OLED_write_command(0x80);

    OLED_write_command(0x81); // Contrast control
    OLED_write_command(0x50);

    OLED_write_command(0xD9); // Set pre-change period
    OLED_write_command(0x21);

    OLED_write_command(0x20); // Set memory addressing mode
    OLED_write_command(0x02);

    OLED_write_command(0xDB); // VCOM deselect level mode
    OLED_write_command(0x30);

    OLED_write_command(0xAD); // Master configuration
    OLED_write_command(0x00);

    OLED_write_command(0xA4); // Out follows RAM content

    OLED_write_command(0xA6); // Set normal display

    OLED_write_command(0xAF); // Set display on

    OLED_clear_all();
}

void OLED_goto_line(uint8_t line)
{

    OLED_write_command(0xB0 | line);
}

void OLED_goto_column(uint8_t column)
{

    uint8_t numLow = column % 16;
    uint8_t numHigh = column / 16;
    OLED_write_command(numLow);
    OLED_write_command(0x10 + numHigh);
}

void OLED_set_pos(uint8_t line, uint8_t column)
{
    OLED_goto_line(line);
    OLED_goto_column(column);
}

void OLED_fill_line(uint8_t line)
{
    OLED_set_pos(line, 0);

    for (int col = 0; col < 128; col++)
    {
        OLED_write_data(~0b00000000);
    }
    OLED_goto_line(line);
}

void OLED_clear_all()
{
    OLED_set_pos(0, 0);
    for (uint8_t lin = 0; lin < 8; lin++)
    {
        OLED_set_pos(lin, 0);
        for (uint8_t col = 0; col < 128; col++)
        {
            OLED_write_data(0x00);
        }
    }

    OLED_set_pos(0, 0);
}

void OLED_print_char(char c, uint8_t line, uint8_t col)
{
    OLED_set_pos(line, col);

    for (uint8_t i = 0; i < 8; i++)
    {
        // (c-32) is mapping the ascii table to the PROGMEM matrix
        // ex. space character is ASCII 32, 0 in the matrix
        // ex. 'A' is ASCII 65, 65-32=33 in the matrix
        OLED_write_data(pgm_read_byte(&(font8[c - 32][i])));
    }
}

void OLED_print_string(char *s, uint8_t length, uint8_t line)
{
    // Check if the string is too long, prints ~
    if (length * 8 > 128)
    {
        OLED_print_char('~', line, 0);
        return 0;
    }

    // Printing character by character
    for (uint8_t i = 0; i < length; i++)
    {
        OLED_print_char(s[i], line, 8 * i);
    }
}

void OLED_update_menu(uint8_t pos)
{
    // Updating menu position and drawing a '<' on the right side
    // of the screen
    if (pos > 0 && pos < 7)
    {
        OLED_print_char(' ', menu_pos, 120);
        menu_pos = pos;
        OLED_print_char('<', menu_pos, 120);
    }
}

void OLED_print_menu(uint8_t menutype)
{
	// Clearing the OLED before printing
	OLED_clear_all();
    // Selecting type of menu
    switch (menutype)
    {
    case MAIN:
        OLED_fill_line(0);
        // Drawing menu entries
        for (uint8_t i = 0; i < 4; i++)
        {
            OLED_print_string(main_menu[i].name, main_menu[i].length, i + 1);
        }
        OLED_fill_line(7);
        // Setting initial position
        OLED_update_menu(1);
        break;
	case PLAYMENU:
		OLED_fill_line(0);
		// Drawing menu entries
		OLED_print_string(play_menu[0].name, play_menu[0].length, 1);
		OLED_fill_line(7);
		break;
	case CREDITS:
	    OLED_fill_line(0);
	    // Drawing menu entries
	    for (uint8_t i = 0; i < 4; i++)
	    {
		    OLED_print_string(credits_menu[i].name, credits_menu[i].length, i + 1);
	    }
	    OLED_fill_line(7);
	    break;
	case ABOUT:
		OLED_fill_line(0);
		// Drawing menu entries
		for (uint8_t i = 0; i < 4; i++)
		{
			OLED_print_string(about_menu[i].name, about_menu[i].length, i + 1);
		}
		OLED_fill_line(7);
		break;

    default:
        break;
    }
}