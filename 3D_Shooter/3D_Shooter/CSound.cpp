#include "Utility.h"

// Global Variable -----------------------------------------------------------------------------
FMOD::System* audioMgr; 
FMOD::Sound* bgmTheme;

CSound::CSound()
{
}


CSound::~CSound()
{
}

bool CSound::InitFmod()
{
	FMOD_RESULT result; 
	result = FMOD::System_Create(&audioMgr);

	if (result != FMOD_OK) 
	{ 
		return false; 
	}
	result = audioMgr->init(50, FMOD_INIT_NORMAL, 0);

	if (result != FMOD_OK)
	{ 
		return false; 
	} 
	return true;
}

void CSound::SetSoundAdress(char _charAdress)
{
	FMOD::Sound* SoundTemp = nullptr;

	m_pSoundAdress.push_back(&_charAdress);
	m_pSoundPointers.push_back(SoundTemp);
}

const bool CSound::LoadAudio()
{
	FMOD_RESULT result;
	// Sound Effects -------------------------------------------------------------------------------
	if (m_pSoundPointers.size() > 0)
	{
		for (int i = 0; i < m_pSoundPointers.size(); i++)
		{
			result = audioMgr->createSound(m_pSoundAdress[i], FMOD_DEFAULT, 0, &m_pSoundPointers[i]);
		}
		
	}

	// Theme music ---------------------------------------------------------------------------------
	result = audioMgr->createSound(" ", FMOD_DEFAULT, 0, &bgmTheme);

	bgmTheme->setMode(FMOD_LOOP_NORMAL);
}

void CSound::PlaySound()
{
	InitFmod();
	LoadAudio();

	FMOD::Channel* channel;
	channel->setVolume(m_intMasterVolume);	//master volume

	audioMgr->playSound(bgmTheme, 0, false, &channel);	//main theme loop

	for (int i = 0; i < m_pSoundPointers.size(); i++)
	{
		audioMgr->playSound(m_pSoundPointers[i], 0, false, &channel);	//sound FX
	}
	
}
