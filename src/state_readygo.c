
#include <SDL.h>
#include <SDL_framerate.h>
#include <SDL_rotozoom.h>
#include "gamefuncs.h"
#include "common.h"
#include "cworldparts.h"
#include "state_readygo.h"

void ReadyGo()
{
    int alpha = 0;
    SDL_Rect Dst;
    SDL_Event Event;
    CWorldParts_NewGame(World);
    Score = 0;
    Uint32 Time2 = SDL_GetTicks();
    SDL_Color TextColor = {255,255,255,255};
    int Timer = 600,Counter=0;
    char Text[500];
    if(GameType == Relative)
        Timer = 150;
    else
        Timer = 300;
    if (MusicCount > 1)
    {
        SelectedMusic =	1+rand()%(MusicCount-1);
        Mix_PlayMusic(Music[SelectedMusic],0);
        SetVolume(Volume);
    }
    else
        if(MusicCount ==1)
        {
            if(!Mix_PlayingMusic())
            {
                SelectedMusic =	0;
                Mix_PlayMusic(Music[SelectedMusic],0);
                SetVolume(Volume);
            }
        }
    while (GameState == GSReadyGo)
    {
        if(!Mix_PlayingMusic())
        if(GlobalSoundEnabled)
        {
            if (MusicCount > 1)
            {
                SelectedMusic =	1+rand()%(MusicCount-1);
                Mix_PlayMusic(Music[SelectedMusic],0);
                SetVolume(Volume);
            }
            else
                if(MusicCount ==1)
                {
                    SelectedMusic =	0;
                    Mix_PlayMusic(Music[SelectedMusic],0);
                    SetVolume(Volume);
                }

        }
        while (SDL_PollEvent(&Event))
		{
            if(Event.type == SDL_QUIT)
                GameState = GSQuit;
			if (Event.type == SDL_JOYBUTTONDOWN)
			{
				switch (Event.jbutton.button)
				{
					case GP2X_BUTTON_B:
						GameState = GSTitleScreen;
						break;
                    case GP2X_BUTTON_VOLUP:
						IncVolume();
						break;
					case GP2X_BUTTON_VOLDOWN:
						DecVolume();
						break;
                    default:
                        break;
				}
			}

            if (Event.type == SDL_KEYDOWN)
			{
				switch (Event.key.keysym.sym)
				{
					case KEY_BUTTON_B:
						GameState = GSTitleScreen;
						break;
                    case KEY_BUTTON_VOLUP:
						IncVolume();
						break;
					case KEY_BUTTON_VOLDOWN:
						DecVolume();
						break;
                    default:
                        break;
				}
			}
		}
		CWorldParts_Draw(World, Buffer);
		switch(Counter)
		{
		    case 1 :
                Dst.x = ((NrOfCols * TileWidth+10) - IMGReady->w) / 2;
                Dst.y = (ORIG_WINDOW_HEIGHT - IMGReady->h) / 2;
                Dst.w = IMGReady->w;
                Dst.h = IMGReady->h;
                SDL_BlitSurface(IMGReady,NULL,Buffer,&Dst);
                break;
            case 2 :
                Dst.x = ((NrOfCols * TileWidth+10) - IMGGo->w) / 2;
                Dst.y = (ORIG_WINDOW_HEIGHT - IMGGo->h) / 2;
                Dst.w = IMGGo->w;
                Dst.h = IMGGo->h;
                SDL_BlitSurface(IMGGo,NULL,Buffer,&Dst);
                break;
            case 3 :
                GameState = GSGame;
                break;
		}
        sprintf(Text,"Timer:\n%2d:%02d\n\nScore:\n%d\n\nLeft:\n%d",Timer/60,Timer%60,Score,movesLeft);
        WriteText(Buffer,BigFont,Text,strlen(Text),345*SCALE,10*SCALE,0,TextColor);
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
        if (Time2 < SDL_GetTicks())
        {
            Counter++;
            if(Counter == 1)
                if(GlobalSoundEnabled)
                    Mix_PlayChannel(-1,Sounds[SND_READYGO],0);
            if (Counter == 2)
            {
                Time2 = SDL_GetTicks() + 400;
            }
            else
                Time2 = SDL_GetTicks() + 900;
        }

    }
}
