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

#include "audio.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>

std::ifstream audio::sound_file;
ALCdevice* audio::device;
ALCcontext* audio::context;
ALuint audio::source;
ALuint audio::buffer;
char* audio::data;

//this function checks endianness
bool audio::is_big_endian()
{
    int i=1;
    return !((char*)&i)[0];
}

//this function retrieves the appropriate value according to endianness
int16_t audio::to_int16(char* buffer, int length)
{
    int16_t i=0;
    if(!is_big_endian())
        for(int j=0;j<length;j++)
            ((char*)&i)[j]=buffer[j];
    else
        for(int j=0;j<length;j++)
            ((char*)&i)[3-j]=buffer[j];
    return i;
}

//this function retrieves the appropriate value according to endianness
int32_t audio::to_int32(char* buffer, int length)
{
    int32_t i=0;
    if(!is_big_endian())
        for(int j=0;j<length;j++)
            ((char*)&i)[j]=buffer[j];
    else
        for(int j=0;j<length;j++)
            ((char*)&i)[sizeof(int)-1-j]=buffer[j];
    return i;
}

void audio::load()
{
    std::clog<<"loading audio..\n";
    char file_info[4];
    int16_t format_type, channels, byte_sample, bit_sample;
    int32_t chunk_size, sample_rate, byte_rate, data_size;
    //open wave file
    sound_file.open("./audio/collision.wav",std::ios::binary);
    if(sound_file.bad())
        std::cerr<<"error opening sound file\n";
    sound_file.read(file_info,4);
    //read file information
    sound_file.read(file_info,4);//"RIFF" label
    sound_file.read(file_info,4);//"WAVE" label
    sound_file.read(file_info,4);//"fmt" label
    sound_file.read(file_info,4);//chunk size
    chunk_size=to_int32(file_info,4);
    sound_file.read(file_info,2);//format type
    format_type=to_int16(file_info,2);
    sound_file.read(file_info,2);//channels
    channels=to_int16(file_info,2);
    sound_file.read(file_info,4);//sample rate
    sample_rate=to_int32(file_info,4);
    sound_file.read(file_info,4);//byte rate
    byte_rate=to_int32(file_info,4);
    sound_file.read(file_info,2);//byte sample
    byte_sample=to_int16(file_info,2);
    sound_file.read(file_info,2);//bit sample
    bit_sample=to_int16(file_info,2);
    sound_file.read(file_info,4);//"data" label
    sound_file.read(file_info,4);//data size
    data_size=to_int32(file_info,4);
    data= new char[data_size];//create a buffer to store sound data
    sound_file.read(data,data_size);//retrieve sound data

    //initialize OpenAL
    device = alcOpenDevice(NULL);
    if(!device)
        std::cerr<<"no sound device\n";
    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);
    if(!context)
        std::cerr<<"no sound context\n";
    ALuint format=0;
    alGenBuffers(1, &buffer);
    alGenSources(1, &source);
    if(alGetError() != AL_NO_ERROR)
        std::cerr<<"error generating source\n";

    //identify wave format
    if(bit_sample == 8)
    {
        if(channels == 1)
            format = AL_FORMAT_MONO8;
        else if(channels == 2)
            format = AL_FORMAT_STEREO8;
    }
    else if(bit_sample == 16)
    {
        if(channels == 1)
            format = AL_FORMAT_MONO16;
        else if(channels == 2)
            format = AL_FORMAT_STEREO16;
    }
    if(!format)
        std::cerr<<"wrong bit sample\n";

    alBufferData(buffer, format, data, data_size, sample_rate);
    if(alGetError() != AL_NO_ERROR)
        std::cerr<<"error loading buffer\n";

    //sound settings
    ALfloat source_position[] = {0.0, 0.0, 0.0};
    ALfloat source_velocity[] = {0.0, 0.0, 0.0};
    ALfloat listener_position[] = {0.0, 0.0, 0.0};
    ALfloat listener_velocity[] = {0.0, 0.0, 0.0};
    ALfloat listener_orientation[] = {0.0, 0.0, -1.0, 0.0, 1.0, 0.0};

    //listener
    alListenerfv(AL_POSITION, listener_position);
    alListenerfv(AL_VELOCITY, listener_velocity);
    alListenerfv(AL_ORIENTATION, listener_orientation);

    //source
    alSourcei(source, AL_BUFFER, buffer);
    alSourcef(source, AL_PITCH, 1.0f);
    alSourcef(source, AL_GAIN, 1.0f);
    alSourcefv(source, AL_POSITION, source_position);
    alSourcefv(source, AL_VELOCITY, source_velocity);
    alSourcei(source, AL_LOOPING, AL_FALSE);
    std::clog<<"audio loaded.\n";
}

void audio::play()
{
    alSourcePlay(source);
    if(alGetError() != AL_NO_ERROR)
        std::cerr<<"error playing sound\n";
}

void audio::close()
{
    sound_file.close();
    delete[] data;
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
}
