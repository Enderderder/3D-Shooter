//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2016 Media Design School
//
// File Name    : Utility.h
// Description	: 
// Author       : Richard Wulansari & Jacob (Last Name?)
// Mail         : richard.wul7481@mediadesign.school.nz (Email?)
//

#ifndef UTILITY_H
#define UTILITY

// OpenGL Include *****************************************************************************
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <fmod.hpp>

// Library Include *****************************************************************************
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <string>

#include <vld.h> // Memory Leak Detector

//**********************************************************************************************


// Define Struct *******************************************************************************

struct DebugTimer
{
	std::chrono::time_point<std::chrono::steady_clock> start, end;
	std::chrono::duration<float> duration;

	DebugTimer()
	{
		start = std::chrono::high_resolution_clock::now();
	}

	~DebugTimer()
	{
		end = std::chrono::high_resolution_clock::now();
		duration = end - start;

		float ms = duration.count();
		std::cout << "Debug Timer took " << ms << " ms \n";
	}
};

//**********************************************************************************************



#endif // !UTILITY_H
