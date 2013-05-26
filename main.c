/*
Copyright © 2013 Cătălin Dogaru

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 51 Franklin
Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#define BUFLEN        16       /* Buffer size. */
#define COORD_X       0        /* X coordinate. */
#define COORD_Y       1        /* Y coordinate. */
#define DIR_LEFT      -1       /* Left movement direction. */
#define DIR_RIGHT     1        /* Right movement direction. */
#define F_CPU         16000000 /* 16MHz crystal oscillator. */
#define SCREEN_HEIGHT 64       /* Screen height. */
#define SCREEN_WIDTH  128      /* Screen width. */

#include "assets/fonts.h"
#include "assets/img.h"
#include <avr/io.h>
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

/* Application screens. */
enum SCREENS
{
    SCREEN_WELCOME,
    SCREEN_GAME,
    SCREEN_MENU,
    SCREEN_GAME_OVER,
    NUM_SCREENS
};

/* Menu buttons. */
enum BUTTONS
{
    BTN_RESUME,
    BTN_LEAVE,
    NUM_BUTTONS
};

/* Key states. */
unsigned char key_left_state;
unsigned char key_right_state;
unsigned char key_escape_state;
unsigned char key_enter_state;

/* Misc. */
unsigned char screen;              /* Application screen. */
unsigned char score;               /* Player score. */
unsigned char lives;               /* Player lives. */
unsigned char invader_pos[2];      /* Invader coordinates. */
unsigned char invader_dir;         /* Invader movement direction. */
unsigned char player_pos[2];       /* Player coordinates. */
unsigned char player_laser_pos[2]; /* Player laser coordinates. */
unsigned char focused_btn;         /* Focused menu button. */

/**
 * Initializes the input buttons.
 */
void init_input()
{
    /* Sets buttons data direction registers as digital input. */
    DDRB &= ~( 1 << PB0 );
    DDRB &= ~( 1 << PB1 );
    DDRB &= ~( 1 << PB2 );
    DDRB &= ~( 1 << PB3 );
    DDRD &= ~( 1 << PD6 );

    /* Turns on internal pull-up resistors for buttons. */
    PORTB |= ( 1 << PB0 );
    PORTB |= ( 1 << PB1 );
    PORTB |= ( 1 << PB2 );
    PORTD |= ( 1 << PD6 );
}

/**
 * Initializes the display device.
 */
void init_display()
{
    /* Initializes the display device. */
    GLI_Initialize();
}

/**
 * Initializes the environment.
 */
void init_env()
{
    /* Sets the application screen to the welcome screen. */
    screen = SCREEN_WELCOME;
}

/**
 * Initializes the game.
 */
void init_game()
{
    /* Sets player score to default. */
    score = 0;

    /* Sets player lives to default. */
    lives = 3;

    /* Sets invader coordinates to default. */
    invader_pos[ COORD_X ] = ( SCREEN_WIDTH - invader.Width ) / 2 - 1;
    invader_pos[ COORD_Y ] = 15;

    /* Sets invader movement direction to default. */
    invader_dir = DIR_LEFT;

    /* Sets player coordinates to default. */
    player_pos[ COORD_X ] = ( SCREEN_WIDTH - player.Width ) / 2 - 1;
    player_pos[ COORD_Y ] = SCREEN_HEIGHT - player.Height - 5;

    /* Sets player laser coordinates to default. */
    player_laser_pos[ COORD_X ] = 0;
    player_laser_pos[ COORD_Y ] = 0;
}

/**
 * Initializes the menu.
 */
void init_menu()
{
    /* Sets focused menu button to default. */
    focused_btn = BTN_RESUME;
}

/**
 * Initializes the application.
 */
void init()
{
    /* Initializes the input buttons. */
    init_input();

    /* Initializes the display device. */
    init_display();

    /* Initializes the environment. */
    init_env();
}

/**
 * Handles user input on welcome screen.
 */
void handle_welcome_input()
{
    /* */
    if ( ( ! ( PINB & ( 1 << PB0 ) ) ) ||
         ( ! ( PIND & ( 1 << PD6 ) ) ) ||
         ( ! ( PINB & ( 1 << PB2 ) ) ) ||
         ( ! ( PINB & ( 1 << PB3 ) ) ) )
    {
        /* Initializes the game. */
        init_game();

        /* Sets the application screen to the game screen. */
        screen = SCREEN_GAME;
    }
}

/**
 * [shoot description]
 */
void shoot()
{
    /* */
    player_laser_pos[ COORD_X ] = player_pos[ COORD_X ] + player.Width / 2;
    player_laser_pos[ COORD_Y ] = player_pos[ COORD_Y ] + player_laser.Height;
}

/**
 * Handles user input on game screen.
 */
void handle_game_input()
{
    /* */
    if ( ! ( PINB & ( 1 << PB2 ) ) )
    {
        /* */
        player_pos[ COORD_X ] = ( player_pos[ COORD_X ] > 3 )
            ? player_pos[ COORD_X ] - 4
            : 3;
    }

    /* */
    if ( ! ( PINB & ( 1 << PB3 ) ) )
    {
        /* */
        player_pos[ COORD_X ] = ( player_pos[ COORD_X ] < SCREEN_WIDTH - player.Width - 5 )
            ? player_pos[ COORD_X ] + 4
            : SCREEN_WIDTH - player.Width - 5;
    }

    /* */
    if ( ! ( PIND & ( 1 << PD6 ) ) )
    {
        /* Initializes the menu. */
        init_menu();

        /* Sets the application screen to the menu screen. */
        screen = SCREEN_MENU;
    }

    /* */
    if ( ! ( PINB & ( 1 << PB0 ) ) )
    {
        /* */
        if ( player_laser_pos[ COORD_Y ] <= 15 )
        {
            /* */
            shoot();
        }
    }
}

/**
 * Handles user input on menu screen.
 */
void handle_menu_input()
{
    /* */
    if ( ! ( PINB & ( 1 << PB2 ) ) )
    {
        /* */
        focused_btn = ( focused_btn > 0 ) ? focused_btn - 1 : NUM_BUTTONS - 1;
    }

    /* */
    if ( ! ( PINB & ( 1 << PB3 ) ) )
    {
        /* */
        focused_btn = ( focused_btn < NUM_BUTTONS - 1 ) ? focused_btn + 1 : 0;
    }

    /* */
    if ( ! ( PIND & ( 1 << PD6 ) ) )
    {
        /* Sets the application screen to the game screen. */
        screen = SCREEN_GAME;
    }

    /* */
    if ( ! ( PINB & ( 1 << PB0 ) ) )
    {
        /* */
        switch ( focused_btn )
        {
            case BTN_RESUME:
                /* Sets the application screen to the game screen. */
                screen = SCREEN_GAME;

                break;

            case BTN_LEAVE:
                /* Sets the application screen to the welcome screen. */
                screen = SCREEN_WELCOME;

                break;
        }
    }
}

/**
 * Handles user input on game over screen.
 */
void handle_game_over_input()
{
    /* */
    if ( ( ! ( PINB & ( 1 << PB0 ) ) ) ||
         ( ! ( PIND & ( 1 << PD6 ) ) ) ||
         ( ! ( PINB & ( 1 << PB2 ) ) ) ||
         ( ! ( PINB & ( 1 << PB3 ) ) ) )
    {
        /* Sets the application screen to the welcome screen. */
        screen = SCREEN_WELCOME;
    }
}

/**
 * Handles user input.
 */
void handle_input()
{
    switch( screen )
    {
        case SCREEN_WELCOME:
            /* Handles user input on welcome screen. */
            handle_welcome_input();

            break;

        case SCREEN_GAME:
            /* Handles user input on game screen. */
            handle_game_input();

            break;

        case SCREEN_MENU:
            /* Handles user input on menu screen. */
            handle_menu_input();

            break;

        case SCREEN_GAME_OVER:
            /* Handles user input on game over screen. */
            handle_game_over_input();

            break;
    }
}

/**
 * Updates the game state.
 */
void update_game()
{
    /* */
    invader_pos[ COORD_X ] += 2 * invader_dir;

    /* */
    if ( invader_pos[ COORD_X ] <= 3 )
    {
        /* */
        invader_pos[ COORD_X ] = 3;

        /* */
        invader_dir = DIR_RIGHT;
    }

    /* */
    if ( invader_pos[ COORD_X ] >= SCREEN_WIDTH - invader.Width - 5 )
    {
        /* */
        invader_pos[ COORD_X ] = SCREEN_WIDTH - invader.Width - 5;

        /* */
        invader_dir = DIR_LEFT;
    }

    /* */
    if ( ( player_laser_pos[ COORD_X ] >= invader_pos[ COORD_X ] ) &&
         ( player_laser_pos[ COORD_X ] <= invader_pos[ COORD_X ] + invader.Width ) &&
         ( player_laser_pos[ COORD_Y ] >= invader_pos[ COORD_Y ] ) &&
         ( player_laser_pos[ COORD_Y ] <= invader_pos[ COORD_Y ] + invader.Height ) )
    {
        /* */
        score += 10;

        /* Sets the application screen to the game over screen. */
        screen = SCREEN_GAME_OVER;
    }

    /* */
    if ( player_laser_pos[ COORD_Y ] > 15 )
    {
        /* */
        player_laser_pos[ COORD_Y ] -= 4;
    }
}

/**
 * Draws the welcome screen.
 */
void draw_welcome_screen()
{
    char msg[ BUFLEN ];

    /* Draws the invader (large) bitmap. */
    GLI_DrawBitmap(
        ( SCREEN_WIDTH - invader_large.Width ) / 2 - 1,
        11,
        &invader_large
    );

    sprintf( msg, "PRESS ANY KEY" );

    /* Prints the 'PRESS ANY KEY' text message. */
    GLI_DrawString(
        ( SCREEN_WIDTH - lucida_console.CharWidth * strlen( msg ) ) / 2 - 1,
        43,
        &lucida_console,
        msg
    );
}

/**
 * Draws the player score.
 */
void draw_score()
{
    char msg[ BUFLEN ];

    sprintf( msg, "%d", score );

    /* Prints the player score text message. */
    GLI_DrawString(
        3,
        3,
        &lucida_console,
        msg
    );
}

/**
 * Draws the player lives.
 */
void draw_lives()
{
    unsigned char i;

    for ( i = 1; i <= lives; ++i )
    {
        /* Draws the player bitmap. */
        GLI_DrawBitmap(
            SCREEN_WIDTH - i * player.Width - 4 * i - 1,
            3,
            &player
        );
    }
}

/**
 * Draws the invader.
 */
void draw_invader()
{
    /* Draws the invader bitmap. */
    GLI_DrawBitmap(
        invader_pos[ COORD_X ],
        invader_pos[ COORD_Y ],
        &invader
    );
}

/**
 * Draws the player.
 */
void draw_player()
{
    /* Draws the player bitmap. */
    GLI_DrawBitmap(
        player_pos[ COORD_X ],
        player_pos[ COORD_Y ],
        &player
    );
}

/**
 * Draws the player laser.
 */
void draw_player_laser()
{
    /* Draws the player laser bitmap. */
    GLI_DrawBitmap(
        player_laser_pos[ COORD_X ],
        player_laser_pos[ COORD_Y ],
        &player_laser
    );
}

/**
 * Draws the game screen.
 */
void draw_game_screen()
{
    /* Draws the player score. */
    draw_score();

    /* Draws the player lives. */
    draw_lives();

    /* Draws the invader. */
    draw_invader();

    /* Draws the player. */
    draw_player();

    /* */
    if ( player_laser_pos[ COORD_Y ] > 15 )
    {
        /* Draws the player laser. */
        draw_player_laser();
    }
}

/**
 * Draws the menu screen.
 */
void draw_menu_screen()
{
    if ( focused_btn == BTN_RESUME )
    {
        /* Draws the resume button (hover state) bitmap. */
        GLI_DrawBitmap(
            SCREEN_WIDTH / 2 - btn_resume_hover.Width - 5,
            ( SCREEN_HEIGHT - btn_resume_hover.Height ) / 2 - 1,
            &btn_resume_hover
        );
    }
    else
    {
        /* Draws the resume button (normal state) bitmap. */
        GLI_DrawBitmap(
            SCREEN_WIDTH / 2 - btn_resume.Width - 5,
            ( SCREEN_HEIGHT - btn_resume.Height ) / 2 - 1,
            &btn_resume
        );
    }

    if ( focused_btn == BTN_LEAVE )
    {
        /* Draws the leave button (hover state) bitmap. */
        GLI_DrawBitmap(
            SCREEN_WIDTH / 2 + 3,
            ( SCREEN_HEIGHT - btn_leave_hover.Height ) / 2 - 1,
            &btn_leave_hover
        );
    }
    else
    {
        /* Draws the leave button (normal state) bitmap. */
        GLI_DrawBitmap(
            SCREEN_WIDTH / 2 + 3,
            ( SCREEN_HEIGHT - btn_leave.Height ) / 2 - 1,
            &btn_leave
        );
    }
}

/**
 * Draws the game over screen.
 */
void draw_game_over_screen()
{
    char msg[ BUFLEN ];

    /* Draws the invader (large) bitmap. */
    GLI_DrawBitmap(
        ( SCREEN_WIDTH - invader_large.Width ) / 2 - 1,
        7,
        &invader_large
    );

    sprintf( msg, "GAME OVER" );

    /* Prints the 'GAME OVER' text message. */
    GLI_DrawString(
        ( SCREEN_WIDTH - lucida_console.CharWidth * strlen( msg ) ) / 2 - 1,
        39,
        &lucida_console,
        msg
    );

    sprintf( msg, "Score: %d", score );

    /* Prints the player score text message. */
    GLI_DrawString(
        ( SCREEN_WIDTH - lucida_console.CharWidth * strlen( msg ) ) / 2 - 1,
        47,
        &lucida_console,
        msg
    );
}

/**
 * Draws the application screen.
 */
void draw_screen()
{
    /* Clears the display device. */
    GLI_Clear( GLI_COLOR_BLACK );

    switch ( screen )
    {
        case SCREEN_WELCOME:
            /* Draws the welcome screen. */
            draw_welcome_screen();

            break;

        case SCREEN_GAME:
            /* Draws the game screen. */
            draw_game_screen();

            break;

        case SCREEN_MENU:
            /* Draws the menu screen. */
            draw_menu_screen();

            break;

        case SCREEN_GAME_OVER:
            /* Draws the game screen. */
            draw_game_over_screen();

            break;
    }

    /* Sends draw data to the display device. */
    GLI_Present();
}

/**
 * Main function of the program.
 *
 * @return Exit status.
 */
int main( void )
{
    /* Initializes the application. */
    init();

    for ( ; ; )
    {
        /* Handles user input. */
        handle_input();

        /* */
        if ( screen == SCREEN_GAME )
        {
            /* Updates the game state. */
            update_game();
        }

        /* Draws the application screen. */
        draw_screen();

        /* */
        _delay_ms( 250 );
    }

    return 0;
}
