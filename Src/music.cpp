/*
 * music.cpp
 * 
 * Copyright 2012 Michael Davenport
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
static int SoundTrack;

static pthread_t MusicThread;

static const string tracks[5] = 
{"Music/title1.ogg","Music/track1.ogg","Music/track2.ogg","Music/track3.ogg","Music/track4.ogg"};

void *playerthread(void *n) {
	
	playerstart();
	
	pthread_exit(NULL);
}

void playerstart() {
	
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
		
		fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
		return;
		
	}
	int audio_rate = 22050;
	Uint16 audio_format = AUDIO_S16SYS;
	int audio_channels = 2;
	int audio_buffers = 4096;
 
	if (Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers) != 0) {
		
		fprintf(stderr, "Unable to initialize audio: %s\n", Mix_GetError());
		return;
		
	}

	Mix_Music *music = NULL;
	
	while (ContinueMusic) {
		
		if(Mix_PlayingMusic() == 0) {
		
			switch (SoundTrack) {
		
				case TITLE:
				case MAP1:
				case MAP2: 		music = Mix_LoadMUS(tracks[SoundTrack].c_str()); break;
				case RANDOM:	music = Mix_LoadMUS(tracks[1+rand()%NUMTRACKS].c_str()); break;
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
	Mix_CloseAudio(); 
	
}
void create_music_thread(int track) {

	ContinueMusic 	= true;
	SoundTrack		= track;
	pthread_create(&MusicThread, NULL , playerthread , NULL);
	
}
void stop_music_thread() {

	ContinueMusic = false;
	pthread_join(MusicThread, NULL);
	
}
