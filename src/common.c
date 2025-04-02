#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_framerate.h>
#include <stdbool.h>
#include "defines.h"


struct CWorldParts;

SDL_Surface *IMGBackground=NULL,*IMGBlocks=NULL,*IMGCursor=NULL,*IMGReady=NULL,*IMGGo=NULL,*IMGTimeOver=NULL,*IMGIntro1=NULL, *IMGIntro2=NULL,*IMGIntro3=NULL,
            *IMGTitleScreen=NULL,*IMGQuit1=NULL,*IMGQuit2=NULL,*IMGPlay1=NULL,*IMGPlay2=NULL,*IMGHighScores1=NULL,*IMGHighScores2=NULL,*IMGCredits1=NULL,*IMGCredits2=NULL,
            *IMGCredits=NULL,*IMGSelectGame=NULL,*IMGFixedTimer1=NULL,*IMGFixedTimer2=NULL,*IMGRelativeTimer1=NULL,*IMGRelativeTimer2=NULL,*IMGHighScores;



Mix_Chunk *Sounds[NrOfSounds];
Mix_Music *Music[MaxMusicFiles];

bool GlobalSoundEnabled = true;

SDL_Surface *Screen, *Buffer;
TTF_Font* font,*BigFont,*MonoFont;
SDL_Joystick *Joystick;
int GameState = GSIntro;
int MusicCount=0,SelectedMusic=0,Volume = 128,Score=0;
int GameType = Fixed;
SHighScore HighScores[2][10];
int WINDOW_WIDTH = ORIG_WINDOW_WIDTH;
int WINDOW_HEIGHT = ORIG_WINDOW_HEIGHT;
Uint32 FrameTicks = 0;
Uint32 FrameCount = 0;
Uint32 LastFps = 0;
bool ShowFps = false;
bool noDelay = false;
bool fullscreen = false;
FPSmanager Fpsman;
int movesLeft = 0;