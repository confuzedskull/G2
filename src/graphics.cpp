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

#include "graphics.h"
#include "utilities.h"
#include <iostream>
#include <fstream>

std::map<std::string, GLuint> graphics::images;

void graphics::add_image(std::string filename)
{
    std::string filepath="./graphics/"+filename;
    std::ifstream image_file(filepath.c_str());
    if(image_file.good())
    {
        images[filename]=0;
        image_file.close();
    }
    else
        std::cerr<<filename<<" does not exist.\n";
}

void graphics::load(std::string filename)
{
    char* data;
    char file_info[4];
    int32_t image_width, image_height;
    std::string filepath="./graphics/"+filename;
    std::ifstream image_file;
    if(images.find(filename)!=images.end())//check if image has been added to collection
        image_file.open(filepath.c_str(), std::ios::binary);
    else
    {
        std::cerr<<filename<<" not found.\n";
        return;
    }
    //read file information
    image_file.read(file_info,2);//signature
    image_file.read(file_info,4);//file size
    image_file.read(file_info,2);//reserved
    image_file.read(file_info,2);//reserved
    image_file.read(file_info,4);//offset
    image_file.read(file_info,4);//size of header
    image_file.read(file_info,4);//width
    image_width = utilities::to_int32(file_info,4);
    image_file.read(file_info,4);//height
    image_height = utilities::to_int32(file_info,4);
    data = new char[image_width*image_height*3];
    image_file.read(data, image_width*image_height*3);
    image_file.close();
    for(int i=0; i<image_width*image_height; ++i)
    {
        int index = i*3;
        unsigned char B,R;
        B = data[index];
        R = data[index+2];
        data[index] = R;
        data[index+2] = B;
    }
    glGenTextures(1, &images[filename]);
    glBindTexture(GL_TEXTURE_2D, images[filename]);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image_width, image_height, GL_RGB, GL_UNSIGNED_BYTE, data);
    delete[] data;
    std::clog<<filename<<" loaded.\n";
}

void graphics::load_all()
{
    std::clog<<"loading images...\n";
    for(auto i:images)
        load(i.first);
}
