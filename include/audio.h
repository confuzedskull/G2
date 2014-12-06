/*  This file is a part of 2DWorld - The Generic 2D Game Engine
    Copyright (C) 2014  James Nakano
    2DWorld is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    2DWorld is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with the rest of 2DWorld.  If not, see <http://www.gnu.org/licenses/>.*/

#ifndef AUDIO_H
#define AUDIO_H
#ifdef __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif
#include <cstdint>
#include <fstream>

namespace audio
{
extern ALCdevice *device;
extern ALCcontext *context;
extern std::ifstream sound_file;
extern ALuint source;
extern ALuint buffer;
extern char* data;
bool is_big_endian();
int16_t to_int16(char* buffer, int length);
int32_t to_int32(char* buffer, int length);
void load();
void play();
void close();
};

#endif // AUDIO_H
