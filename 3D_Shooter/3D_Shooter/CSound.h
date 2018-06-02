#pragma once
class CSound
{
public:
	CSound();
	~CSound();

	bool InitFmod();
	const bool LoadAudio();
	void PlaySound();
	void SetSoundAdress(char _charAdress);

private:
	float m_intMasterVolume;
	std::vector<char*> m_pSoundAdress;
	std::vector<FMOD::Sound*> m_pSoundPointers;
};

