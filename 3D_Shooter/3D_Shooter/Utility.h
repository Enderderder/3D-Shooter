/*
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2018 Media Design School
//
// File Name    : Utility.h
// Description	: 
// Author       : Richard Wulansari & Jacob Dewse
// Mail         : richard.wul7481@mediadesign.school.nz, jacob.dew7364@mediadesign.school.nz
*/

#ifndef UTILITY_H
#define UTILITY_H

// OpenGL Include ------------------------------------------------------------------------------
#include <glew.h>
#include <freeglut.h>
#include <SOIL.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include <fmod.hpp>

// Library Include -----------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <WS2tcpip.h>
#include <strstream>
#include <Windows.h>
#include <cassert>
#include <thread>
#include "CSound.h"
#include "TextLabel.h"
#include <sstream>

//#include <vld.h> // Memory Leak Detector



// Converting IP Adresses to string and Networking ----------------------------------------------

#define VALIDATE(a) if (!a) return (false)

namespace {
	std::string ToString(sockaddr_in _sockAddress)
	{
		//INET_ADDRSTRLEN - maximum length for IPv4 addresses
		char _pcAddress[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &_sockAddress.sin_addr, _pcAddress, INET_ADDRSTRLEN);

		std::string _strAddress = _pcAddress;
		std::string _strPort = std::to_string(ntohs(_sockAddress.sin_port));
		std::string _strAddressPort = _strAddress + ':' + _strPort;

		return _strAddressPort;
	}
}

template<typename T>
std::string ToString(const T& _value)
{
	std::strstream theStream;
	theStream << _value << std::ends;
	return (theStream.str());
}

//----------------------------------------------------------------------------------------------


namespace util
{
	// Define the screen size
	static int SCR_WIDTH = 1366;
	static int SCR_HEIGHT = 768;
}

// Define Struct -------------------------------------------------------------------------------

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

enum ESCENES
{
	MAINMENU = 0,
	GAME,
	GAMEOVER,
	MULTIPLAYER,
	LOBBY
};

enum EMESH
{
	CUBE,
	SPHERE,
	MENUCUBEMAP,
	GAMECUBEMAP
};

enum EMODEL
{
	TANK,
};

enum InputState 
{
	INPUT_FIRST_RELEASE,	// First frame of Up state 
	INPUT_RELEASED,			// Default State (Up) 
	INPUT_FIRST_PRESS,		// First frame of Down state 
	INPUT_HOLD,				// Key is held Down 
};

enum InputMouse 
{ 
	MOUSE_LEFT, 
	MOUSE_MIDDLE, 
	MOUSE_RIGHT 
};

enum EGAMEMODE
{

};

//----------------------------------------------------------------------------------------------



#endif // !_UTILITY_H
