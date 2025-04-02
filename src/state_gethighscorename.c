
#include <SDL.h>
#include <SDL_framerate.h>
#include <SDL_rotozoom.h>
#include <stdbool.h>
#include "gamefuncs.h"
#include "common.h"
#include "state_gethighscorename.h"

void GetHighScoreName(char NameIn[21],int Place, long PScore)
{
	char Name[21];
	char Msg[500];
	bool End=false,SubmitChanges=false;
	int Teller,MaxSelection=0, Selection = 0,asci=97;
	SDL_Event Event;
	SDL_Color TextColor = {102,115,152,255}, TextColor1 = {255,115,152,255};;
    memset(&Name[0], 0, 21 * sizeof(char));
	SDL_PollEvent(&Event);
	sprintf(Name,"%s",NameIn);
	MaxSelection = strlen(NameIn);
	Name[Selection+1]='\0';
	if (MaxSelection == 0)
		Name[MaxSelection]=chr(asci);
	char Tekst[100];
	while (!End)
	{
        if(MusicCount > 0)
        {
            if(GlobalSoundEnabled)
            {
                if(!Mix_PlayingMusic())
                {
                    SelectedMusic = 0;
                    Mix_PlayMusic(Music[SelectedMusic],0);
                    SetVolume(Volume);
                }
            }
        }
		while (SDL_PollEvent(&Event))
		{
            if (Event.type == SDL_JOYHATMOTION)
            {
                switch (Event.jhat.value)
                {
                    case 8: //left
						if (Selection > 0)
						{	Selection--;
							asci = ord(Name[Selection]);
						}
						break;
					case 2: //right
						if (Selection < 19)
						{
							Selection++;
							if (Selection > MaxSelection)
							{
								Name[Selection] = chr(97);
								Name[Selection+1] = '\0';
								MaxSelection=Selection;
							}
							asci = ord(Name[Selection]);
						}
						break;
					case 1: // up
						asci++;
						if (asci==123)
                        {
							asci=32;
                        }
						if (asci==33)
                        {
							(asci=48);
                        }
						if (asci==58)
                        {
							asci=97;
                        }
						Name[Selection] = chr(asci);
						break;
					case 4: //down
						asci--;
						if(asci==96)
                        {
						    asci=57;
                        }
						if(asci==47)
                        {
							asci=32;
                        }
						if(asci==31)
                        {
							asci=122;
                        }
						Name[Selection] = chr(asci);
						break;
                    default:
                        break;            
                }
            }

			if (Event.type == SDL_JOYBUTTONDOWN)
			{
				switch(Event.jbutton.button)
				{					
					case GP2X_BUTTON_A:
						if (GlobalSoundEnabled)
							Mix_PlayChannel(-1,Sounds[SND_SELECT],0);
						End = true;
						SubmitChanges=true;
						break;
                    case GP2X_BUTTON_B:
						End=true;
						SubmitChanges=false;
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
				switch(Event.key.keysym.sym)
				{
					case KEY_BUTTON_LEFT:
						if (Selection > 0)
						{	Selection--;
							asci = ord(Name[Selection]);
						}
						break;
					case KEY_BUTTON_RIGHT:
						if (Selection < 19)
						{
							Selection++;
							if (Selection > MaxSelection)
							{
								Name[Selection] = chr(97);
								Name[Selection+1] = '\0';
								MaxSelection=Selection;
							}
							asci = ord(Name[Selection]);
						}
						break;
					case KEY_BUTTON_UP: // up
						asci++;
						if (asci==123)
                        {
							asci=32;
                        }
						if (asci==33)
                        {
							(asci=48);
                        }
						if (asci==58)
                        {
							asci=97;
                        }
						Name[Selection] = chr(asci);
						break;
					case KEY_BUTTON_DOWN:
						asci--;
						if(asci==96)
                        {
						    asci=57;
                        }
						if(asci==47)
                        {
							asci=32;
                        }
						if(asci==31)
                        {
							asci=122;
                        }
						Name[Selection] = chr(asci);
						break;					
					case KEY_BUTTON_A:
						if (GlobalSoundEnabled)
							Mix_PlayChannel(-1,Sounds[SND_SELECT],0);
						End = true;
						SubmitChanges=true;
						break;
                    case KEY_BUTTON_B:
						End=true;
						SubmitChanges=false;
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
        SDL_BlitSurface(IMGHighScores,NULL,Buffer,NULL);

        for(Teller = 0;Teller<9;Teller++)
        {
            if(Teller < Place)
            {
                sprintf(Msg,"%2d.%s",Teller+1,HighScores[GameType][Teller].PName);
                WriteText(Buffer,MonoFont,Msg,strlen(Msg),110*SCALE,(62+Teller*16)*SCALE,0,TextColor);
                sprintf(Msg,"%7ld",HighScores[GameType][Teller].PScore);
                WriteText(Buffer,MonoFont,Msg,strlen(Msg),280*SCALE,(62+Teller*16)*SCALE,0,TextColor);
            }
            else
            {
                sprintf(Msg,"%2d.%s",Teller+2,HighScores[GameType][Teller].PName);
                WriteText(Buffer,MonoFont,Msg,strlen(Msg),110*SCALE,(62+(Teller+1)*16)* SCALE,0,TextColor);
                sprintf(Msg,"%7ld",HighScores[GameType][Teller].PScore);
                WriteText(Buffer,MonoFont,Msg,strlen(Msg),280*SCALE,(62+(Teller+1)*16)*SCALE,0,TextColor);
            }
        }
		sprintf(Msg,"%2d.%s",Place+1,Name);
		WriteText(Buffer,MonoFont,Msg,strlen(Msg),110*SCALE,(62+Place*16)*SCALE,0,TextColor1);
		sprintf(Msg,"%7ld",PScore);
        WriteText(Buffer,MonoFont,Msg,strlen(Msg),280*SCALE,(62+Place*16)*SCALE,0,TextColor1);
		if (Selection > 0)
		{
			strcpy(Tekst,"    ");
			for (Teller=1;Teller<Selection;Teller++)
				strcat(Tekst," ");
			strcat(Tekst,"_");
		}
		else
			sprintf(Tekst,"   _");
		WriteText(Buffer,MonoFont,Tekst,strlen(Tekst),110*SCALE,(62+(Place)*16)*SCALE,2,TextColor1);
		sprintf(Tekst,"Use Up,Down,Left,right. A = Ok X = Cancel" );
		WriteText(Buffer,font,Tekst,strlen(Tekst),105*SCALE,227*SCALE,0,TextColor);
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
	Name[MaxSelection+1] = '\0';
	while ((Name[0] == ' ') && (MaxSelection>-1))
	{
		for (Teller=0;Teller<MaxSelection;Teller++)
			Name[Teller] = Name[Teller+1];
		MaxSelection--;
	}
	if (MaxSelection>-1)
		while ((Name[MaxSelection] == ' ') && (MaxSelection>0))
		{
			Name[MaxSelection] = '\0';
			MaxSelection--;
		}
	if (!SubmitChanges)
		sprintf(NameIn,"%s"," ");
    else
        sprintf(NameIn,"%s",Name);
}
