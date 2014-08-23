//
//  SDLClasses.cpp
//  SDLandOpenGL
//
//  Created by Kristof Niederholtmeyer on 21.11.13.
//  Copyright (c) 2013 Kristof Niederholtmeyer. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include "SDLClasses.h"
#include <fstream>
#include <iostream>
#include <cstring>
#ifdef __APPLE__
#include <SDL2_image/SDL_image.h>
#else
#include <SDL2/SDL_image.h>
#include <GL/gl.h>
#endif

////////////////////////////////////////////////////////////////////////////////

SDLSystem::SDLSystem(std::string const& resource_path)
: _resource_path(resource_path + "/"), _error(false) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) _error = true;
}
SDLSystem::~SDLSystem() {
    SDL_Quit();
}

void SDLSystem::set_relative_mouse_mode(bool enabled) {
    SDL_SetRelativeMouseMode( enabled ? SDL_TRUE : SDL_FALSE );
}
bool SDLSystem::relative_mouse_mode() const {
    return SDL_GetRelativeMouseMode() == SDL_TRUE ? true : false;
}
void SDLSystem::set_show_cursor(bool enabled) {
    SDL_ShowCursor( enabled ? 1 : 0 );
}
bool SDLSystem::show_cursor() const {
    return SDL_ShowCursor(-1) == 1 ? true : false;
}

bool SDLSystem::poll_event(SDL_Event& event) const {
    return SDL_PollEvent(&event);
}

std::string const& SDLSystem::resource_path() const {
    return _resource_path;
}

bool SDLSystem::valid() const {
    return !_error;
}

////////////////////////////////////////////////////////////////////////////////

SDLGLWindow::SDLGLWindow(SDLSystem const& system, int width, int height)
: _error(false) {
	SDL_ClearError();

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
    
    _mainwindow = SDL_CreateWindow("Main Window",
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   width, height,
                                   SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
								   
	std::string error = SDL_GetError();
	if (error.length() > 0) std::cout << error << std::endl;
    if (!_mainwindow) {
        _error = true;
		return;
    }
    
	_maincontext = SDL_GL_CreateContext(_mainwindow);
    if (!_maincontext) {
		_error = true;
		return;
	}
#ifndef __APPLE__
		std::cout << "OpenGL Version:" << glGetString(GL_VERSION) << std::endl;
#endif
	error = SDL_GetError();
	if (error.length() > 0) std::cout << error << std::endl;
}

SDLGLWindow::~SDLGLWindow() {
    SDL_GL_DeleteContext(_maincontext);
    SDL_DestroyWindow(_mainwindow);
}

void SDLGLWindow::set_vsync(bool enabled) {
    SDL_GL_SetSwapInterval( enabled ? 1 : 0 );
}

void SDLGLWindow::swap() {
    SDL_GL_SwapWindow(_mainwindow);
}

void SDLGLWindow::set_fullscreen(bool enabled) {
    SDL_SetWindowFullscreen(_mainwindow, enabled ? 1 : 0);
}

void SDLGLWindow::set_size(int width, int height) {
    SDL_SetWindowSize(_mainwindow, width, height);
}

void SDLGLWindow::get_window_size(int& width, int& height) const {
    SDL_GetWindowSize(_mainwindow, &width, &height);
}

bool SDLGLWindow::valid() const {
    return !_error;
}

////////////////////////////////////////////////////////////////////////////////

SDLMixer::SDLMixer(SDLSystem const& system, int channels)
: _resource_path(system.resource_path()), _error(false) {
    int flags = MIX_INIT_OGG;
    if (Mix_Init(flags) != flags) {
        _error = true;
        return;
    }
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
        _error = true;
        return;
    }
    
    if (Mix_ReserveChannels(channels) != channels) {
        _error = true;
        return;
    }
}

SDLMixer::~SDLMixer() {
    Mix_CloseAudio();
    Mix_Quit();
}

std::string const& SDLMixer::resource_path() const {
    return _resource_path;
}

int SDLMixer::play(SDLMixerChunk const& chunk, int loop, int on_channel) {
    return Mix_PlayChannel(on_channel, chunk.chunk(), loop);
}

bool SDLMixer::playing(int channel) {
    return Mix_Playing(channel) > 0;
}

void SDLMixer::pause(int channel) {
    Mix_Pause(channel);
}

bool SDLMixer::paused(int channel) {
    return Mix_Paused(channel) > 0;
}

void SDLMixer::resume(int channel) {
    Mix_Resume(channel);
}

void SDLMixer::stop(int channel) {
    Mix_HaltChannel(channel);
}

bool SDLMixer::valid() const {
    return !_error;
}

////////////////////////////////////////////////////////////////////////////////

SDLMixerChunk::SDLMixerChunk(SDLMixer const& mixer, std::string const& filename) {
    _chunk = Mix_LoadWAV((mixer.resource_path() + filename).c_str());
}

SDLMixerChunk::~SDLMixerChunk() {
    Mix_FreeChunk(_chunk);
}

Mix_Chunk* SDLMixerChunk::chunk() const {
    return _chunk;
}

int SDLMixerChunk::volume() const {
    return Mix_VolumeChunk(_chunk, -1);
}

void SDLMixerChunk::set_volume(int v) {
    Mix_VolumeChunk(_chunk, v);
}

bool SDLMixerChunk::valid() const {
    return _chunk != 0;
}

////////////////////////////////////////////////////////////////////////////////

SDLImage::SDLImage(SDLSystem const& system)
: _resource_path(system.resource_path()), _error(false) {
    if (IMG_Init(IMG_INIT_PNG) < 0) _error = true;
}

SDLImage::~SDLImage() {
    IMG_Quit();
}

std::vector<uint8_t> SDLImage::load_image(std::string const& filename,
                                          int& width,
                                          int& height,
                                          int& bytes_per_pixel) const {
    width = 0;
    height = 0;
    bytes_per_pixel = 0;
    
    std::vector<uint8_t> image;
    SDL_Surface *surface = IMG_Load((_resource_path + filename).c_str());
    if (surface) {
        width = surface->w;
        height = surface->h;
        bytes_per_pixel = surface->format->BytesPerPixel;
        int bytes = width * height * bytes_per_pixel;
        
        image.resize(bytes);
        memcpy(&image[0], surface->pixels, bytes);
    }
    SDL_FreeSurface(surface);
    return image;
}

bool SDLImage::valid() const {
    return !_error;
}

////////////////////////////////////////////////////////////////////////////////
