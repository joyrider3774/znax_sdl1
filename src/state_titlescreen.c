
#include <SDL.h>
#include <SDL_framerate.h>
#include <SDL_rotozoom.h>
#include "gamefuncs.h"
#include "common.h"
#include "cmainmenu.h"
#include "state_titlescreen.h"

void TitleScreen()
{
    int alpha = 0;
    SDL_Event Event;
    CMainMenu *Menu = CMainMenu_Create();
    while (GameState == GSTitleScreen)
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
            if (Event.type == SDL_JOYHATMOTION)
            {
                switch (Event.jhat.value)
                {
                    case 1: //up
                        CMainMenu_PreviousItem(Menu);
                        break;
                    case 4: //down
                        CMainMenu_NextItem(Menu);
                        break;
                    case 8: //left
                    case 2: //right
                    default:
                        break;            
                }
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
                        if(CMainMenu_GetSelection(Menu) != 4)
                            if (GlobalSoundEnabled)
                                Mix_PlayChannel(-1,Sounds[SND_SELECT],0);
                        switch(CMainMenu_GetSelection(Menu))
                        {
                            case 1:
                                GameState = GSGameTypeMenu;
                                break;
                            case 2:
                                GameState = GSShowHighScores;
                                break;
                            case 3:
                                GameState = GSCredits;
                                break;
                            case 4:
                                GameState = GSQuit;
                                Mix_HaltMusic();
                                if (GlobalSoundEnabled)
                                    Mix_PlayChannel(-1,Sounds[SND_GOODBYE],0);
                                SDL_Delay(750);
                                break;
                        }
                        break;
                /*  case GP2X_BUTTON_B:
                        GameState = GSQuit;
                        Mix_HaltMusic();
                        if (GlobalSoundEnabled)
                            Mix_PlayChannel(-1,Sounds[SND_GOODBYE],0);
                        SDL_Delay(750);
                        break;
                */
                    default:
                        break;
                }
            
            if (Event.type == SDL_KEYDOWN)
                switch (Event.key.keysym.sym)
                {
                    case KEY_BUTTON_UP:
                        CMainMenu_PreviousItem(Menu);
                        break;
                    case KEY_BUTTON_DOWN:
                        CMainMenu_NextItem(Menu);
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
                        if(CMainMenu_GetSelection(Menu) != 4)
                            if (GlobalSoundEnabled)
                                Mix_PlayChannel(-1,Sounds[SND_SELECT],0);
                        switch(CMainMenu_GetSelection(Menu))
                        {
                            case 1:
                                GameState = GSGameTypeMenu;
                                break;
                            case 2:
                                //so that it shows both gameplay modes
                                GameType = Fixed;
                                GameState = GSShowHighScores;
                                break;
                            case 3:
                                GameState = GSCredits;
                                break;
                            case 4:
                                GameState = GSQuit;
                                Mix_HaltMusic();
                                if (GlobalSoundEnabled)
                                    Mix_PlayChannel(-1,Sounds[SND_GOODBYE],0);
                                SDL_Delay(750);
                                break;
                        }
                        break;
                /*    case KEY_BUTTON_B:
                        GameState = GSQuit;
                        Mix_HaltMusic();
                        if (GlobalSoundEnabled)
                            Mix_PlayChannel(-1,Sounds[SND_GOODBYE],0);
                        SDL_Delay(750);
                        break;
                */
                    default:
                        break;
                }
        }
        CMainMenu_Draw( Menu, Buffer);
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


    }
    CMainMenu_Destroy(Menu);
}
