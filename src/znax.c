#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL_framerate.h>
#include <SDL.h>
#include "defines.h"
#include "common.h"
#include "cgametypemenu.h"
#include "cmainmenu.h"
#include "cselector.h"
#include "cworldparts.h"
#include "gamefuncs.h"
#include "state_gametypemenu.h"
#include "state_credits.h"
#include "state_titlescreen.h"
#include "state_timeover.h"
#include "state_readygo.h"
#include "state_intro.h"
#include "state_game.h"
#include "state_showhighscores.h"

int main(int argc, char **argv)
{
    for (int i=0; i < argc; i++)
    {
        
        if(strcasecmp(argv[i], "-nd") == 0)
            noDelay = true;
        if(strcasecmp(argv[i], "-fps") == 0)
            ShowFps = true;
        if(strcasecmp(argv[i], "-f") == 0)
            fullscreen = true;
        if(strcasecmp(argv[i], "-s2") == 0)
        {
            WINDOW_WIDTH = 640 * 2;
            WINDOW_HEIGHT = 360 * 2;
        }

        if(strcasecmp(argv[i], "-s3") == 0)
        {
            WINDOW_WIDTH = 640 * 3;
            WINDOW_HEIGHT = 360 * 3;
        }

        if(strcasecmp(argv[i], "-s4") == 0)
        {
            WINDOW_WIDTH = 640 * 4;
            WINDOW_HEIGHT = 360 * 4;
        }

        if(strcasecmp(argv[i], "-s5") == 0)
        {
            WINDOW_WIDTH = 640 * 5;
            WINDOW_HEIGHT = 360 * 5;
        }
    }

	if (SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_VIDEO | SDL_INIT_AUDIO ) == 0)
	{
		printf("SDL Succesfully initialized\n");
        Uint32 flags = SDL_SWSURFACE;
		if (fullscreen)
		{
			WINDOW_WIDTH = 0;
			WINDOW_HEIGHT = 0;
			flags |= SDL_FULLSCREEN;
		}
        
        Screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT,0, flags);
		if(Screen)
		{
            WINDOW_WIDTH = Screen->w;
            WINDOW_HEIGHT = Screen->h;
            SDL_Surface *Tmp = SDL_CreateRGBSurface(SDL_SWSURFACE, ORIG_WINDOW_WIDTH, ORIG_WINDOW_HEIGHT, 0, 
                Screen->format->Rmask, Screen->format->Gmask, Screen->format->Bmask, Screen->format->Amask);
            Buffer = SDL_DisplayFormat(Tmp);
            SDL_FreeSurface(Tmp);
		    printf("Succesfully Set %dx%dx16\n",WINDOW_WIDTH,WINDOW_HEIGHT);
		    SDL_FillRect(Screen,NULL,SDL_MapRGB(Screen->format,0,0,0));
            SDL_ShowCursor(SDL_DISABLE);
            if (Mix_OpenAudio(11025,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,256) < 0)
            {
                GlobalSoundEnabled = false;
                printf("Failed to initialise sound!\n");
                printf("%s\n",Mix_GetError());
            }
            else
            {
                printf("Audio Succesfully initialised!\n");
            }
            if (TTF_Init() == 0)
            {
                printf("Succesfully initialized TTF\n");
                font = TTF_OpenFont("./fonts/font.ttf",16);
                BigFont = TTF_OpenFont("./fonts/font.ttf",24);
                MonoFont = TTF_OpenFont("./fonts/font1.ttf",25);
                if (font&&BigFont&&MonoFont)
                {
                    if(SDL_JoystickOpen(0) == NULL)
                        printf("No Joystick: %s\n", SDL_GetError());
                    SDL_JoystickEventState(SDL_ENABLE);
                    srand(time(NULL));
                    printf("Succesfully Loaded fonts\n");
                    SDL_initFramerate(&Fpsman);
					SDL_setFramerate(&Fpsman,FPS);
                    TTF_SetFontStyle(font,TTF_STYLE_NORMAL);
                    SearchForMusic();
                    LoadSettings();
                    LoadGraphics();
                    LoadSounds();
                    LoadHighScores();
                    World = CWorldParts_Create();
                    while (GameState != GSQuit)
                    {
                        switch(GameState)
                        {
                            case GSGame :
                                Game();
                                break;
                            case GSTitleScreen:
                                TitleScreen();
                                break;
                            case GSIntro :
                                Intro();
                                break;
                            case GSReadyGo:
                                ReadyGo();
                                break;
                            case GSTimeOver:
                                TimeOver();
                                break;
                            case GSCredits:
                                Credits();
                                break;
                            case GSGameTypeMenu:
                                GameTypeMenu();
                                break;
                            case GSShowHighScores:
                                ShowHighScores();
                                break;
                            default :
                                break;
                        }
                    }
                    CWorldParts_Destroy(World);
                    SaveHighScores();
                    UnloadSounds();
                    UnloadMusic();
                    UnLoadGraphics();
                    SaveSettings();
                    Mix_CloseAudio();
                    TTF_CloseFont(font);
                    TTF_CloseFont(MonoFont);
                    TTF_CloseFont(BigFont);
                    font=NULL;
                }
                else
                {
                    printf("Failed to Load fonts\n");
                }
                TTF_Quit();
            }
            else
            {
                printf("Failed to initialize TTF\n");
            }
            SDL_FreeSurface(Screen);
            Screen=NULL;
		}
		else
		{
			printf("Failed to Set Videomode %dx%dx16\n",WINDOW_WIDTH, WINDOW_HEIGHT);
		}
		SDL_Quit();
	}
	else
	{
		printf("Couldn't initialise SDL!\n");
	}
	return 0;

}
