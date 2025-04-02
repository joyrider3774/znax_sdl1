
#include <SDL.h>
#include <SDL_framerate.h>
#include <SDL_rotozoom.h>
#include <stdbool.h>
#include "gamefuncs.h"
#include "common.h"
#include "state_timeover.h"
#include "cworldparts.h"
#include "state_gethighscorename.h"

void TimeOver()
{
    char Name[21];
    int Teller1,Teller2;
    SDL_Rect Dst;
    SDL_Event Event;
    Uint32 Time2 = SDL_GetTicks() + 1250;
    SDL_Color TextColor = {255,255,255,255};
    int Timer = 0,Counter=0;
    char Text[500];
    memset(&Name[0], 0, 21 * sizeof(char));
    CWorldParts_DeSelect(World, false);

    while (GameState == GSTimeOver)
    {
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
		    case 0 :
                Dst.x = ((NrOfCols * TileWidth+10) - IMGTimeOver->w) / 2;
                Dst.y = (ORIG_WINDOW_HEIGHT - IMGTimeOver->h) / 2;                
                Dst.w = IMGTimeOver->w;
                Dst.h = IMGTimeOver->h;
                SDL_BlitSurface(IMGTimeOver,NULL,Buffer,&Dst);
                break;
		}
        sprintf(Text,"Timer:\n%2d:%02d\n\nScore:\n%d",Timer/60,Timer%60,Score);
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
        if (Time2 < SDL_GetTicks())
        {
            GameState = GSShowHighScores;
        }

    }
    for(Teller1 =0;Teller1<10;Teller1++)
        if(HighScores[GameType][Teller1].PScore < Score)
        {
            GetHighScoreName(Name,Teller1,Score);
            for(Teller2=8;Teller2>=Teller1;Teller2--)
                HighScores[GameType][Teller2+1] = HighScores[GameType][Teller2];
            if((strcmp(Name," ") == 0))
                sprintf(HighScores[GameType][Teller1].PName,"%s","player");
            else
                sprintf(HighScores[GameType][Teller1].PName,"%s",Name);
            HighScores[GameType][Teller1].PScore = Score;
            break;
        }
}
