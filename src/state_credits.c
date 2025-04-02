
#include <SDL.h>
#include <SDL_framerate.h>
#include <SDL_rotozoom.h>
#include "gamefuncs.h"
#include "common.h"
#include "state_credits.h"

void Credits()
{
    SDL_Rect Rect1;
    SDL_Event Event;
    Rect1.x = 147;
    Rect1.y = 119;
    Rect1.w = IMGCredits->w;
    Rect1.h = IMGCredits->h;
    while (GameState == GSCredits)
    {
        if(MusicCount > 0)
            if(GlobalSoundEnabled)
                if(!Mix_PlayingMusic())
                {
                    SelectedMusic = 0;
                    Mix_PlayMusic(Music[SelectedMusic],0);
                    SetVolume(Volume);
                }
        while (SDL_PollEvent(&Event))
		{

            if (Event.type == SDL_QUIT)
                GameState=GSQuit;

            if (Event.type == SDL_JOYBUTTONDOWN)
                switch (Event.jbutton.button)
                {
                    case GP2X_BUTTON_VOLUP:
						IncVolume();
						break;
					case GP2X_BUTTON_VOLDOWN:
						DecVolume();
						break;
                    default :
                        GameState = GSTitleScreen;
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
                    default :
                        GameState = GSTitleScreen;
                        break;
                }

        }

        SDL_BlitSurface(IMGTitleScreen,NULL,Buffer,NULL);
        SDL_BlitSurface(IMGCredits,NULL,Buffer,&Rect1);
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
			SDL_Surface *ScreenBufferZoom = zoomSurface(Buffer,wscale,wscale,0);
			SDL_BlitSurface(ScreenBufferZoom,NULL,Screen,&dst);
			SDL_FreeSurface(ScreenBufferZoom);
		}
		else
		{
			SDL_BlitSurface(Buffer, NULL, Screen, NULL);
		}
        HandleFPS();
        SDL_Flip(Screen);
        if(!noDelay)
            SDL_framerateDelay(&Fpsman);
    }
}
