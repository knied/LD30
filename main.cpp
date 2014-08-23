//
//  main.cpp
//
//  Created by Kristof Niederholtmeyer on 19.08.14.
//  Copyright (c) 2014 Kristof Niederholtmeyer. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "SDLClasses.h"
#include "gl3w.h"
#include "Game.h"

#ifdef __APPLE__
#include "MacOSX.h"
#endif

////////////////////////////////////////////////////////////////////////////////

int main(int argc, char* argv[]) {
    typedef std::chrono::system_clock Clock;
    typedef std::chrono::time_point<Clock> TimeStamp;
    typedef std::chrono::duration<float> Seconds;
    
#ifdef __APPLE__
    std::string resource_path = macosx_resources_path();
#endif
    
    SDLSystem system(resource_path);
    if (!system.valid()) {
        std::cout << "ERROR: SDL could not be initialized." << std::endl;
        std::cout << "exiting..." << std::endl;
        return -1;
    }
    SDLGLWindow gl_window(system, 1024, 768);
    if (!gl_window.valid()) {
        std::cout << "ERROR: SDL OpenGL window or context could not be initialized." << std::endl;
        std::cout << "exiting..." << std::endl;
        return -1;
    }
    
    SDLMixer mixer(system);
    if (!mixer.valid()) {
        std::cout << "ERROR: SDL_mixer could not be initialized." << std::endl;
        std::cout << "exiting..." << std::endl;
        return -1;
    }
    /*SDLMixerChunk chunk(mixer, "Rayman_2_music_sample.ogg");
    int channel = -1;
    if (chunk.valid()) {
        channel = mixer.play(chunk, 1, 3);
        if (channel >= 0) {
            std::cout << "playing on channel: " << channel << std::endl;
        }
    }*/
    
    if (gl3wInit()) {
        std::cout << "ERROR: gl3w could not be initialized." << std::endl;
        std::cout << "exiting..." << std::endl;
        return -1;
    }
    if (!gl3wIsSupported(3, 2)) {
        std::cout << "ERROR: This system does not support OpenGL 3.2." << std::endl;
        std::cout << "exiting..." << std::endl;
        return -1;
    }
    
    Game game(system);
    
    TimeStamp old_time = Clock::now();
    
    bool done = false;
    while (!done) {
        TimeStamp new_time = Clock::now();
        Seconds elapsed = new_time - old_time;
        old_time = new_time;
        
        done = game.update(system, elapsed.count());
        
        // end the frame
        gl_window.swap();
    }
    
    std::cout << "exiting..." << std::endl;
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
