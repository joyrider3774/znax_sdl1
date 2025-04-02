#ifndef DEFINES_H
#define DEFINES_H

#define ORIG_WINDOW_WIDTH 640
#define ORIG_WINDOW_HEIGHT 360
#define FPS 60

#define GP2X_BUTTON_UP              (20)
#define GP2X_BUTTON_DOWN            (21)
#define GP2X_BUTTON_LEFT            (22)
#define GP2X_BUTTON_RIGHT           (23)
#define GP2X_BUTTON_UPLEFT          (24)
#define GP2X_BUTTON_UPRIGHT         (25)
#define GP2X_BUTTON_DOWNLEFT        (26)
#define GP2X_BUTTON_DOWNRIGHT       (27)
#define GP2X_BUTTON_A               (0)
#define GP2X_BUTTON_B               (1)
#define GP2X_BUTTON_Y               (3)
#define GP2X_BUTTON_X               (2)
#define GP2X_BUTTON_L               (4)
#define GP2X_BUTTON_R               (5)
#define GP2X_BUTTON_START           (6)
#define GP2X_BUTTON_SELECT          (7)
#define GP2X_BUTTON_VOLUP           (28)
#define GP2X_BUTTON_VOLDOWN         (29)

#ifdef MIYOO
    #define KEY_BUTTON_UP              (SDLK_UP)
    #define KEY_BUTTON_DOWN            (SDLK_DOWN)
    #define KEY_BUTTON_LEFT            (SDLK_LEFT)
    #define KEY_BUTTON_RIGHT           (SDLK_RIGHT)
    #define KEY_BUTTON_A               (SDLK_SPACE)
    #define KEY_BUTTON_B               (SDLK_LCTRL)
    #define KEY_BUTTON_Y               (SDLK_LALT)
    #define KEY_BUTTON_X               (SDLK_LSHIFT)
    #define KEY_BUTTON_L               (SDLK_e)
    #define KEY_BUTTON_R               (SDLK_t)
    #define KEY_BUTTON_START           (SDLK_RETURN)
    #define KEY_BUTTON_SELECT          (SDLK_RCTRL)
    #define KEY_BUTTON_VOLUP           (SDLK_BACKSPACE)
    #define KEY_BUTTON_VOLDOWN         (SDLK_TAB)
#else
    #define KEY_BUTTON_UP              (SDLK_UP)
    #define KEY_BUTTON_DOWN            (SDLK_DOWN)
    #define KEY_BUTTON_LEFT            (SDLK_LEFT)
    #define KEY_BUTTON_RIGHT           (SDLK_RIGHT)
    #define KEY_BUTTON_A               (SDLK_SPACE)
    #define KEY_BUTTON_B               (SDLK_ESCAPE)
    #define KEY_BUTTON_Y               (SDLK_y)
    #define KEY_BUTTON_X               (SDLK_x)
    #define KEY_BUTTON_L               (SDLK_PAGEDOWN)
    #define KEY_BUTTON_R               (SDLK_PAGEUP)
    #define KEY_BUTTON_START           (SDLK_RETURN)
    #define KEY_BUTTON_SELECT          (SDLK_b)
    #define KEY_BUTTON_VOLUP           (SDLK_KP_PLUS)
    #define KEY_BUTTON_VOLDOWN         (SDLK_KP_MINUS)
#endif

//gamestates
#define GSQuit 0 
#define GSIntro 1 
#define GSGame 2 
#define GSTitleScreen 3 
#define GSTimeOver 4 
#define GSReadyGo 5 
#define GSCredits 6 
#define GSGameTypeMenu 7 
#define GSShowHighScores 8

//gametypes
#define Fixed 0
#define Relative 1

#define NrOfSounds 14
#define NrOfRows 10
#define NrOfCols 14
#define NrOfBlockColors 5
#define BlockBlue 0
#define BlockYellow 1
#define BlockOrange 2
#define BlockGreen 3
#define BlockRed 4
#define MaxMusicFiles 26
#define TileWidth 35
#define TileHeight 35
#define SND_READYGO 0
#define SND_5MINUTE 1
#define SND_1MINUTE 2
#define SND_3 3
#define SND_2 4
#define SND_1 5
#define SND_TIMEOVER 6
#define SND_MENU 7
#define SND_SELECT 8
#define SND_WELCOME 9
#define SND_GOODBYE 10
#define SND_DELETE 11
#define SND_BLOCKSELECT 12
#define SND_ERROR 13

#define SCALE 1.5f


struct SHighScore
{
    char PName[21];
    long PScore;
};
typedef struct SHighScore SHighScore;

struct SPoint
{
    int X,Y;
};

typedef struct SPoint SPoint;

#endif