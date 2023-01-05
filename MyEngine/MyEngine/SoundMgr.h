#pragma once
#include "Singleton.h"
class Sound;
class SoundMgr :
    public Singleton< SoundMgr >
{
public:
	SoundMgr();
	~SoundMgr();

public:
	bool Initialize();
	LPDIRECTSOUND8 GetDevice() { return mSoundDevice; }

	void ChangeBGM(SCENE_TYPE _type);
	void ChangeBGM(Sound* _sound);

	void StopBGM();

private:
	LPDIRECTSOUND8 mSoundDevice;
	Sound* mBGMSound;

};

