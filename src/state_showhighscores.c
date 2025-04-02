
#include <SDL.h>
#include <SDL_framerate.h>
#include <SDL_rotozoom.h>
#include "gamefuncs.h"
#include "common.h"
#include "state_showhighscores.h"

void ShowHighScores()
{
    int alpha = 0;
    SDL_Event Event;
    SDL_Color TextColor = {102,115,152,255};
    int Teller = 0;
    char Text[250];
    int ScoreType = GameType;
    while (GameState == GSShowHighScores)
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
                    case GP2X_BUTTON_START:
                    case GP2X_BUTTON_X:
                    case GP2X_BUTTON_Y:
                        if (ScoreType == Fixed)
                        {
                            alpha = 0;
                            ScoreType = Relative;
                        }
                        else
                            GameState=GSTitleScreen;
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
                    case KEY_BUTTON_VOLUP:
						IncVolume();
						break;
					case KEY_BUTTON_VOLDOWN:
						DecVolume();
						break;
                    case KEY_BUTTON_A:
                    case KEY_BUTTON_START:
                    case KEY_BUTTON_X:
                    case KEY_BUTTON_Y:
                        if (ScoreType == Fixed)
                        {
                            alpha = 0;
                            ScoreType = Relative;
                        }
                        else
                            GameState=GSTitleScreen;
                        break;                    
                    case KEY_BUTTON_B:
                        GameState = GSTitleScreen;
                        break;
                    default:
                        break;
                }
        }
        SDL_BlitSurface(IMGHighScores,NULL,Buffer,NULL);
        switch(ScoreType)
        {
            case Fixed :
                sprintf(Text,"Gametype: Fixed Timer" );
                break;
            case Relative :
                sprintf(Text,"Gametype: Relative Timer" );
                break;
        }

		WriteText(Buffer,font,Text,strlen(Text),145*SCALE,227*SCALE,0,TextColor);
        for(Teller = 0;Teller<10;Teller++)
        {
            sprintf(Text,"%2d.%s",Teller+1,HighScores[ScoreType][Teller].PName);
            WriteText(Buffer,MonoFont,Text,strlen(Text),110*SCALE,(62+Teller*16)*SCALE,0,TextColor);
            sprintf(Text,"%7ld",HighScores[ScoreType][Teller].PScore);
            WriteText(Buffer,MonoFont,Text,strlen(Text),280*SCALE,(62+Teller*16)*SCALE,0,TextColor);
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


    }
}
