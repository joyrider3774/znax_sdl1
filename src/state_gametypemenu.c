
#include <SDL.h>
#include <SDL_framerate.h>
#include <SDL_rotozoom.h>
#include "cgametypemenu.h"
#include "gamefuncs.h"
#include "common.h"
#include "state_gametypemenu.h"

void GameTypeMenu()
{
    SDL_Event Event;
    CGameTypeMenu *Menu = CGameTypeMenu_Create();
    while (GameState == GSGameTypeMenu)
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
            if(Event.type == SDL_QUIT)
                GameState = GSQuit;

            if(Event.type == SDL_JOYHATMOTION)
                switch (Event.jhat.value)
                {                   
                    case 1: //up
                        CGameTypeMenu_NextItem(Menu);
                        break;
                    case 4: //down
                        CGameTypeMenu_PreviousItem(Menu);
                        break;
                    default:
                        break;
                }
            
            if (Event.type == SDL_JOYBUTTONDOWN)
                switch (Event.jbutton.button)
                {                   
                   case GP2X_BUTTON_VOLUP:
						IncVolume();
						break;
					case GP2X_BUTTON_VOLDOWN:
						DecVolume();
						break;                   
                    case GP2X_BUTTON_X:
                    case GP2X_BUTTON_Y:
                    case GP2X_BUTTON_A:
                    case GP2X_BUTTON_START:
                        if (GlobalSoundEnabled)
                            Mix_PlayChannel(-1,Sounds[SND_SELECT],0);
                        switch(CGameTypeMenu_GetSelection(Menu))
                        {
                            case Fixed:
                                GameType = Fixed;
                                break;
                            case Relative:
                                GameType = Relative;
                                break;
                        }
                        GameState = GSReadyGo;
                        break;
                    case GP2X_BUTTON_B:
                        GameState = GSTitleScreen;
                        break;
                    default:
                        break;
                }

            if (Event.type == SDL_KEYDOWN)
                switch (Event.key.keysym.sym)
                {
                    case KEY_BUTTON_UP:
                        CGameTypeMenu_NextItem(Menu);
                        break;
                    case KEY_BUTTON_DOWN:
                        CGameTypeMenu_PreviousItem(Menu);
                        break;                   
                    case KEY_BUTTON_VOLUP:
						IncVolume();
						break;
					case KEY_BUTTON_VOLDOWN:
						DecVolume();
						break;                   
                    case KEY_BUTTON_X:
                    case KEY_BUTTON_Y:
                    case KEY_BUTTON_A:
                    case KEY_BUTTON_START:
                        if (GlobalSoundEnabled)
                            Mix_PlayChannel(-1,Sounds[SND_SELECT],0);
                        switch(CGameTypeMenu_GetSelection(Menu))
                        {
                            case Fixed:
                                GameType = Fixed;
                                break;
                            case Relative:
                                GameType = Relative;
                                break;
                        }
                        GameState = GSReadyGo;
                        break;
                    case KEY_BUTTON_B:
                        GameState = GSTitleScreen;
                        break;
                    default:
                        break;
                }
        }
        CGameTypeMenu_Draw(Menu, Buffer);
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
    CGameTypeMenu_Destroy(Menu);
}

