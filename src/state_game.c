
#include <SDL.h>
#include <SDL_framerate.h>
#include <SDL_rotozoom.h>
#include "gamefuncs.h"
#include "common.h"
#include "cworldparts.h"
#include "cselector.h"
#include "state_game.h"

void Game()
{
    SDL_Event Event;
    Uint32 Time = SDL_GetTicks();
    Uint32 ScoreTimer = 0;
    CSelector* Selector = CSelector_Create(NrOfCols / 2, NrOfRows / 2);
    SDL_Color TextColor = {255,255,255,255};
    int AddToScore = 0,Timer = 150;
    char Text[500];
    if(GameType == Relative)
        Timer = 150;
    else
        Timer = 300;
    while (GameState == GSGame)
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
            if (Event.type == SDL_JOYHATMOTION)
            {
                switch (Event.jhat.value)
                {
                    case 8: //left
                        CSelector_SetPosition(Selector, Selector->CurrentPoint.X -1,Selector->CurrentPoint.Y);
                        break;
                    case 2: //right
                        CSelector_SetPosition(Selector, Selector->CurrentPoint.X +1,Selector->CurrentPoint.Y);
                        break;
                    case 1: //up
                        CSelector_SetPosition(Selector, Selector->CurrentPoint.X,Selector->CurrentPoint.Y-1);
                        break;
                    case 4: //down
                        CSelector_SetPosition(Selector, Selector->CurrentPoint.X,Selector->CurrentPoint.Y+1);
                        break;
                    default:
                        break;
                }
            }    
			if (Event.type == SDL_JOYBUTTONDOWN)
			{
				switch (Event.jbutton.button)
				{
					case GP2X_BUTTON_B:
						GameState = GSTitleScreen;
						break;
                    case GP2X_BUTTON_A :
                    case GP2X_BUTTON_X :
                    case GP2X_BUTTON_Y :
                        AddToScore+= CWorldParts_Select(World, Selector->CurrentPoint.X,Selector->CurrentPoint.Y);
                        if(AddToScore != 0)
                        {
                            ScoreTimer = SDL_GetTicks() + 700;
                        }
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
                    case KEY_BUTTON_LEFT:
                        CSelector_SetPosition(Selector, Selector->CurrentPoint.X -1,Selector->CurrentPoint.Y);
                        break;
                    case KEY_BUTTON_RIGHT:
                        CSelector_SetPosition(Selector, Selector->CurrentPoint.X +1,Selector->CurrentPoint.Y);
                        break;
                    case KEY_BUTTON_UP:
                        CSelector_SetPosition(Selector, Selector->CurrentPoint.X,Selector->CurrentPoint.Y-1);
                        break;
                    case KEY_BUTTON_DOWN:
                        CSelector_SetPosition(Selector, Selector->CurrentPoint.X,Selector->CurrentPoint.Y+1);
                        break;
					case KEY_BUTTON_B:
						GameState = GSTitleScreen;
						break;
                    case KEY_BUTTON_A :
                    case KEY_BUTTON_X :
                    case KEY_BUTTON_Y :
                        AddToScore+= CWorldParts_Select(World, Selector->CurrentPoint.X,Selector->CurrentPoint.Y);
                        if(AddToScore != 0)
                        {
                            ScoreTimer = SDL_GetTicks() + 700;
                        }
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
        CSelector_Draw(Selector, Buffer);
        if(AddToScore !=0)
        {
            if(ScoreTimer > SDL_GetTicks())
            {
                sprintf(Text,"+%d",AddToScore);
                WriteText(Buffer,font,Text,strlen(Text),345*SCALE,115*SCALE,0,TextColor);
                if(GameType == Relative)
                {
                    sprintf(Text,"+%d",AddToScore/400);
                    WriteText(Buffer,font,Text,strlen(Text),345*SCALE,50*SCALE,0,TextColor);
                }
            }
            else
            {
                ScoreTimer = 0;
                Score +=AddToScore;
                if (GameType == Relative)
                    Timer += floor(AddToScore / 400);
                AddToScore = 0;
            }
        }
        sprintf(Text,"Timer:\n%2d:%02d\n\nScore:\n%d\n\nLeft:\n%d",Timer/60,Timer%60,Score,movesLeft);
        WriteText(Buffer,BigFont,Text,strlen(Text),345*SCALE,10*SCALE,0,TextColor);
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
        if (Time +1000 < SDL_GetTicks())
        {
            Timer-= 1;
            switch (Timer)
            {
                case 300 :
                    if (GlobalSoundEnabled)
                        Mix_PlayChannel(-1,Sounds[SND_5MINUTE],0);
                    break;
                case 60:
                    if (GlobalSoundEnabled)
                        Mix_PlayChannel(-1,Sounds[SND_1MINUTE],0);
                    break;
                case 3 :
                    if (GlobalSoundEnabled)
                        Mix_PlayChannel(-1,Sounds[SND_3],0);
                    break;
                case 2 :
                    if (GlobalSoundEnabled)
                        Mix_PlayChannel(-1,Sounds[SND_2],0);
                    break;
                case 1 :
                    if (GlobalSoundEnabled)
                        Mix_PlayChannel(-1,Sounds[SND_1],0);
                    break;
                case 0 :
                    if(ScoreTimer != 0)
                    {
                        Score += AddToScore;
                        if(GameType == Relative)
                            Timer += AddToScore / 200;
                    }
                    if(Timer == 0)
                    {
                        if (GlobalSoundEnabled)
                            Mix_PlayChannel(-1,Sounds[SND_TIMEOVER],0);
                        GameState = GSTimeOver;
                    }
                    break;
            }
            Time = SDL_GetTicks();
        }

    }
    CSelector_Destroy(Selector);
}
