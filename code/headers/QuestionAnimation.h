#pragma once
//SDL2
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
//C++
#include <iostream>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <fstream>
#include <string>
//Headers
#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "SDL2SoundEffects.h"

#include "animation.h"

using namespace std;

void questionanimation(SDL_Texture* questionTexture, SDL_Texture* optionsTexture, RenderWindow window, string preg, string res[4], int respuestacorrecta, SDL2SoundEffects se, Mix_Music* bgm);

//void questionanimation(SDL_Texture* questionTexture, SDL_Texture* optionsTexture, RenderWindow window, string Question, string answers[]);