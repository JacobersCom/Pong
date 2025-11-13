#pragma once

#include <iostream>
#define TICKS_PASSED(A, B)  ((Sint32)((B) - (A)) <= 0)

constexpr int screenH = 500;
constexpr int screenW = 500;

//Thickeness of wall
constexpr int paddleW = 15;
constexpr int paddleH = 100;
constexpr float targetFPS = float(1000 / 60);


struct vector2 
{
	float x;
	float y;
};
