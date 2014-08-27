//
//  Sprite.cpp
//  LD30Xcode
//
//  Created by Kristof Niederholtmeyer on 23.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//

#include "Sprite.h"

Sprite::Sprite(SDLImage const& image_loader, std::string const& filename) {
    _width = 0;
    _height = 0;
    int bytes_per_pixel = 0;
    std::vector<uint8_t> raw_image_data = image_loader.load_image(filename, _width, _height, bytes_per_pixel);
    if (bytes_per_pixel != 4) {
        std::cout << "WARNING: Unexpected color format in sprite: " << filename << std::endl;
    }
    
    // convert to out color type
    std::vector<Color> image_data(_width * _height);
    for (int i = 0; i < _width * _height; ++i) {
        image_data[i](3) = 255;
        for (int o = 0; o < bytes_per_pixel; ++o) {
            image_data[i](o) = raw_image_data[i * bytes_per_pixel + o];
        }
        uint8_t tmp = image_data[i](0);
        image_data[i](0) = image_data[i](2);
        image_data[i](2) = tmp;
    }
    
    {
        GLBindTexture<GL_TEXTURE0> bind_texture(_texture);
        bind_texture.set(image_data, _width, _height, GL_RGBA8);
        bind_texture.set_parameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        bind_texture.set_parameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        bind_texture.set_parameter(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        bind_texture.set_parameter(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
    
    {
        float x = 0.5f * _width;
        float y = 0.5f * _height;
        GLBindBuffer bind_buffer(_buffer);
        std::vector<Mth::CVector<float, 2>> v(6);
        v[0] = Mth::make_cvector(-x, -y);
        v[1] = Mth::make_cvector(x, -y);
        v[2] = Mth::make_cvector(x, y);
        v[3] = Mth::make_cvector(-x, -y);
        v[4] = Mth::make_cvector(x, y);
        v[5] = Mth::make_cvector(-x, y);
        std::vector<Mth::CVector<float, 2>> t(6);
        t[0] = Mth::make_cvector(0.0f, 1.0f);
        t[1] = Mth::make_cvector(1.0f, 1.0f);
        t[2] = Mth::make_cvector(1.0f, 0.0f);
        t[3] = Mth::make_cvector(0.0f, 1.0f);
        t[4] = Mth::make_cvector(1.0f, 0.0f);
        t[5] = Mth::make_cvector(0.0f, 0.0f);
        bind_buffer.set(0, (int)v.size(), GL_STATIC_DRAW, v, t);
    }
    
    /*{
        GLBindVertexArray bind_vertex_array(_vertex_array);
        bind_vertex_array.set(_buffer, {
            std::tuple<GLuint, size_t, bool>(0,0,true),
            std::tuple<GLuint, size_t, bool>(1,1,true)
        });
    }*/
    
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cout << "GL error (scene): " << error << std::endl;
    }
}

Sprite::~Sprite() {
    
}

void Sprite::draw() {
    GLBindTexture<GL_TEXTURE0> bind_texture(_texture);
    //GLBindBuffer bind_buffer(_buffer);
    GLBindVertexArray bind_vertex_array(_vertex_array);
    bind_vertex_array.set(_buffer, {
        std::tuple<GLuint, size_t, bool>(0,0,true),
        std::tuple<GLuint, size_t, bool>(1,1,true)
    });
    
    //GLBindVertexArray bind_vertex_array(_vertex_array);
    bind_vertex_array.draw(GL_TRIANGLES);
}