/*
 * music.cpp
 * 
 * Copyright 2012-2015 Michael Davenport
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include "music.h"

static bool ContinueMusic;
static enum Track SoundTrack;

static pthread_t MusicThread;

#if __unix

static const string tracks[] = 
{"Data/Music/title1.ogg",
 "Data/Music/track1.ogg",
 "Data/Music/track2.ogg",
 "Data/Music/track3.ogg",
 "Data/Music/track4.ogg",
 "Data/Music/credits.ogg"};

#elif __WIN32

static const string tracks[] =
{"Data\\Music\\title1.ogg", 
 "Data\\Music\\track1.ogg", 
 "Data\\Music\\track2.ogg",
 "Data\\Music\\track3.ogg",
 "Data\\Music\\track4.ogg",
 "Data\\Music\\credits.ogg"};
 
#endif


static const int audio_rate = 22050;
static const int audio_channels = 2;
static const int audio_buffers = 4096;
static const Uint16 audio_format = AUDIO_S16SYS;

static Mix_Music *music = NULL;

void *playerthread(void *n) {
	
	playerstart();
	
	pthread_exit(NULL);
}

void init_sound_engine() {

	if (SDL_Init(SDL_INIT_AUDIO) != 0) {
	
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return;
		
	}
	
	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		
		fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
		return;
		
	}
	
}

void quit_sound_engine() {

	Mix_CloseAudio();
	
}

void playerstart() {
	
	while (ContinueMusic) {
		
		if(Mix_PlayingMusic() == 0) {
		
			switch (SoundTrack) {
		
				case TITLETRACK:
				case TRACK1:
				case TRACK2:
				case TRACK3:
				case TRACK4:
				case CREDITSTRACK: 
				
					music = Mix_LoadMUS(tracks[SoundTrack].c_str()); 
					break;
					
				case RANDOM:
				
					music = Mix_LoadMUS(tracks[1 + rand() % NUMTRACKS].c_str());
					break;
					
				default: return; break;
		
			}
			
			if (music == NULL) {
		 
				printf("Unable to load Ogg file: %s\n", Mix_GetError()); 
				return;
		
			}
			
			if (Mix_PlayMusic(music, 1) == -1) {
		
				printf("Unable to play Ogg file: %s\n", Mix_GetError());
				return;
		 
			}
		
		}
	
		SDL_Delay(100);
	}
	
	Mix_HaltMusic();
	Mix_FreeMusic(music); 
	
}
void create_music_thread(enum Track track) {

	ContinueMusic 	= true;
	SoundTrack		= track;
	pthread_create(&MusicThread, NULL , playerthread , NULL);
	
}

void stop_music_thread() {

	ContinueMusic = false;
	pthread_join(MusicThread, NULL);
	
}

enum Track GetCurrentTrack() {

	return SoundTrack;
	
}
