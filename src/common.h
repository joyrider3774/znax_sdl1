#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <SDL_framerate.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include "defines.h"
#include "cworldparts.h"

extern SDL_Surface *IMGBackground,*IMGBlocks,*IMGCursor,*IMGReady,*IMGGo,*IMGTimeOver,*IMGIntro1, *IMGIntro2,*IMGIntro3,
            *IMGTitleScreen,*IMGQuit1,*IMGQuit2,*IMGPlay1,*IMGPlay2,*IMGHighScores1,*IMGHighScores2,*IMGCredits1,*IMGCredits2,
            *IMGCredits,*IMGSelectGame,*IMGFixedTimer1,*IMGFixedTimer2,*IMGRelativeTimer1,*IMGRelativeTimer2,*IMGHighScores;



extern Mix_Chunk *Sounds[NrOfSounds];
extern Mix_Music *Music[MaxMusicFiles];

extern bool GlobalSoundEnabled;

extern SDL_Surface *Screen, *Buffer;
extern TTF_Font* font,*BigFont,*MonoFont;
extern SDL_Joystick *Joystick;
extern int GameState;
extern int MusicCount,SelectedMusic,Volume,Score;
extern int GameType;
extern SHighScore HighScores[2][10];
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;
extern Uint32 FrameTicks;
extern Uint32 FrameCount;
extern Uint32 LastFps;
extern bool ShowFps;
extern bool noDelay;
extern bool fullscreen;
extern FPSmanager Fpsman;
#endif