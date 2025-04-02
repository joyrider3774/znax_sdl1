
#include <SDL.h>
#include <SDL_framerate.h>
#include <SDL_rotozoom.h>
#include "gamefuncs.h"
#include "common.h"
#include "state_intro.h"

void Intro()
{
    int alpha = 0;
    SDL_Event Event;
    Uint32 Time=0;
    int IntroScreenNr = 1;
    Time = SDL_GetTicks();
    while (GameState == GSIntro)
    {
        while (SDL_PollEvent(&Event))
		{
            if(Event.type == SDL_QUIT)
                GameState = GSQuit;

            if (Event.type == SDL_JOYBUTTONDOWN)
                switch (Event.jbutton.button)
                {
                   case GP2X_BUTTON_VOLUP:
						IncVolume();
						break;
					case GP2X_BUTTON_VOLDOWN:
						DecVolume();
						break;
                    case GP2X_BUTTON_A:
                    case GP2X_BUTTON_B:
                    case GP2X_BUTTON_X:
                    case GP2X_BUTTON_Y:
                    case GP2X_BUTTON_START:
                        GameState = GSTitleScreen;
                        break;
                    default:
                        break;
                }
            
            if (Event.type == SDL_KEYDOWN)
                switch (Event.key.keysym.sym)
                {
                   case KEY_BUTTON_VOLUP:
						IncVolume();
						break;
					case KEY_BUTTON_VOLDOWN:
						DecVolume();
						break;
                    case KEY_BUTTON_A:
                    case KEY_BUTTON_B:
                    case KEY_BUTTON_X:
                    case KEY_BUTTON_Y:
                    case KEY_BUTTON_START:
                        GameState = GSTitleScreen;
                        break;
                    default:
                        break;
                }
        }

        switch(IntroScreenNr)
        {
            case 1 :
                SDL_BlitSurface(IMGIntro1,NULL,Buffer,NULL);
                break;
            case 2 :
                SDL_BlitSurface(IMGIntro2,NULL,Buffer,NULL);
                break;
            case 3 :
                SDL_BlitSurface(IMGIntro3,NULL,Buffer,NULL);
                break;
        }
        if (alpha < 255)
        {
            if(alpha+AlphaInc > MaxAlpha)
            {
                alpha = 255;
                SDL_SetAlpha(Buffer,SDL_SRCALPHA | SDL_RLEACCEL,alpha);
            }
            else
            {
                alpha+=AlphaInc;
                SDL_SetAlpha(Buffer,SDL_SRCALPHA | SDL_RLEACCEL,alpha);
            }
        }
        SDL_BlitSurface(Buffer,NULL,Buffer2,NULL);
        if ((WINDOW_WIDTH != ORIG_WINDOW_WIDTH) || (WINDOW_HEIGHT != ORIG_WINDOW_HEIGHT))
		{
			double wscale = (double)WINDOW_WIDTH / ORIG_WINDOW_WIDTH;
			if(ORIG_WINDOW_HEIGHT * wscale > WINDOW_HEIGHT)
				wscale = (double)WINDOW_HEIGHT / ORIG_WINDOW_HEIGHT;
			SDL_Rect dst;
			dst.x = (WINDOW_WIDTH - (ORIG_WINDOW_WIDTH * wscale)) / 2;
			dst.y = (WINDOW_HEIGHT - (ORIG_WINDOW_HEIGHT * wscale)) / 2,
			dst.w = ORIG_WINDOW_WIDTH * wscale;
			dst.h = ORIG_WINDOW_HEIGHT * wscale;
			SDL_Surface *ScreenBufferZoom = zoomSurface(Buffer2,wscale,wscale,0);
			SDL_BlitSurface(ScreenBufferZoom,NULL,Screen,&dst);
			SDL_FreeSurface(ScreenBufferZoom);
		}
		else
		{
			SDL_BlitSurface(Buffer2, NULL, Screen, NULL);
		}
        HandleFPS();
        SDL_Flip(Screen);
        if(!noDelay)
            SDL_framerateDelay(&Fpsman);

        if(Time + 3700 < SDL_GetTicks())
        {
            alpha = 0;
            IntroScreenNr++;
            if(IntroScreenNr > 3)
                GameState = GSTitleScreen;
            Time = SDL_GetTicks();
        }

    }
    if (GlobalSoundEnabled)
        Mix_PlayChannel(-1,Sounds[SND_WELCOME],0);
}
