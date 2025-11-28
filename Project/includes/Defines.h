#pragma once
#include <iostream>
#include "SDL3/SDL.h"


#define TICKS_PASSED(A, B)  ((Sint32)((B) - (A)) <= 0)

constexpr int screenH = 500;
constexpr int screenW = 500;

constexpr int wallW = 500;
constexpr int wallH = 5;
 
constexpr int paddleW = 15;
constexpr int paddleH = 100;

struct vector2 
{
	float x;
	float y;
};


