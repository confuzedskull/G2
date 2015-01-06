/*  This file is a part of G2 - The Generic 2D Game Engine
    Copyright (C) 2014  James Nakano

    G2 is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    G2 is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with the rest of G2.  If not, see <http://www.gnu.org/licenses/>.*/

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
        std::cerr<<"Image file: '"<<filename<<"' does not exist.\n";
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
        std::cerr<<"Image file: '"<<filename<<"' not found.\n";
        return;
    }
    image_file.seekg(18,image_file.cur);//skip beginning of header
    image_file.read(file_info,4);//width
    image_width = utilities::to_int32(file_info,4);//convert raw data to integer
    image_file.read(file_info,4);//height
    image_height = utilities::to_int32(file_info,4);//convert raw data to integer
    image_file.seekg(28,image_file.cur);//skip rest of header
    int image_area = image_width*image_height;//calculate area now since it'll be used 3 times
    data = new char[image_area*3];//set the buffer size
    image_file.read(data, image_area*3);//get the pixel matrix
    image_file.close();
    //next we need to rearrange the color values from BGR to RGB
    for(int i=0; i<image_area; ++i)//iterate through each cell of the matrix
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
    std::cerr<<"Image file: '"<<filename<<"' loaded.\n";
}

void graphics::load_all()
{
    std::clog<<"loading images...\n";
    for(auto i:images)
        load(i.first);
}
