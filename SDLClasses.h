//
//  SDLClasses.h
//
//  Created by Kristof Niederholtmeyer on 21.11.13.
//  Copyright (c) 2013 Kristof Niederholtmeyer. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __SDLClasses__
#define __SDLClasses__

////////////////////////////////////////////////////////////////////////////////

#include <SDL2/SDL.h>
#ifdef __APPLE__
#include <SDL2_mixer/SDL_mixer.h>
#else
#include <SDL2/SDL_mixer.h>
#endif
#include <stdexcept>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////////////////////

class SDLSystem {
    std::string _resource_path;
    bool _error;
    
public:
    SDLSystem(std::string const& resource_path);
    ~SDLSystem();
    
    void set_relative_mouse_mode(bool enabled);
    bool relative_mouse_mode() const;
    void set_show_cursor(bool enabled);
    bool show_cursor() const;
    bool poll_event(SDL_Event& event) const;
    std::string const& resource_path() const;
    bool valid() const;
}; // SDLSystem

////////////////////////////////////////////////////////////////////////////////

class SDLGLWindow {
    SDL_Window *_mainwindow;
    SDL_GLContext _maincontext;
    bool _error;
    
public:
    SDLGLWindow(SDLSystem const& system, int width = 1024, int height = 768);
    ~SDLGLWindow();
    
    void set_vsync(bool enabled);
    void swap();
    void set_fullscreen(bool enabled);
    void set_size(int width, int height);
    void get_window_size(int& width, int& height) const;
    bool valid() const;
}; // SDLGLWindow

////////////////////////////////////////////////////////////////////////////////

class SDLMixerChunk;

class SDLMixer {
    std::string _resource_path;
    bool _error;
    
public:
    SDLMixer(SDLSystem const& system, int channels = 1);
    ~SDLMixer();
    
    std::string const& resource_path() const;
    
    int play(SDLMixerChunk const& chunk, int loop = 1, int on_channel = -1);
    bool playing(int channel);
    void pause(int channel);
    bool paused(int channel);
    void resume(int channel);
    void stop(int channel);
    
    bool valid() const;
};

////////////////////////////////////////////////////////////////////////////////

class SDLMixerChunk {
    Mix_Chunk* _chunk;
    
public:
    SDLMixerChunk(SDLMixer const& mixer, std::string const& filename);
    ~SDLMixerChunk();
    
    Mix_Chunk* chunk() const;
    
    int volume() const;
    void set_volume(int v);
    
    bool valid() const;
};

////////////////////////////////////////////////////////////////////////////////

class SDLImage {
    std::string _resource_path;
    bool _error;
    
public:
    SDLImage(SDLSystem const& system);
    ~SDLImage();
    
    std::vector<uint8_t> load_image(std::string const& filename,
                                    int& width,
                                    int& height,
                                    int& bytes_per_pixel) const;
    
    bool valid() const;
};

////////////////////////////////////////////////////////////////////////////////

#endif /* defined(__SDLClasses__) */

////////////////////////////////////////////////////////////////////////////////
