#include "pch.h"
#include "Sound.h"
#include "SoundMgr.h"

bool Sound::Load(const std::wstring& path)
{
	if (nullptr == SoundMgr::GetInstance().GetDevice())
		assert(nullptr); // ���� ��ü �������� ����

	// Ȯ���� �̸� �����ϱ�
	wchar_t szExt[10] = { 0 };
	_wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExt, 10);

	if (!wcscmp(szExt, L".wav")) // WAV ���� �ε�
	{
		if (false == LoadWavFile(path))
			assert(nullptr);
	}
	else
		assert(nullptr);

	return S_OK;
}

bool Sound::LoadWavFile(const std::wstring& path)
{
	HMMIO	hFile; // File Handle

	std::wstring strFilePath = path;

	//CreateFile
	hFile = mmioOpen((wchar_t*)strFilePath.c_str(), NULL, MMIO_READ);//wave������ ����.

	if (nullptr == hFile)
	{
		MessageBox(NULL, L"���� ���ҽ� ��ο� ���� ����", L"���� �ε� ����", MB_OK);
		return false;
	}

	//Chunk ûũ ����ü, ���ڿ��� ������ �ν��ؼ� WaveFormat �� ���ۼ��������� �о�´�.
	MMCKINFO	pParent;
	memset(&pParent, 0, sizeof(pParent));
	pParent.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmioDescend(hFile, &pParent, NULL, MMIO_FINDRIFF);

	MMCKINFO	pChild;
	memset(&pChild, 0, sizeof(pChild));
	pChild.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmioDescend(hFile, &pChild, &pParent, MMIO_FINDCHUNK);

	WAVEFORMATEX	wft;
	memset(&wft, 0, sizeof(wft));
	mmioRead(hFile, (char*)&wft, sizeof(wft));

	mmioAscend(hFile, &pChild, 0);
	pChild.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmioDescend(hFile, &pChild, &pParent, MMIO_FINDCHUNK);

	memset(&mBufferDesc, 0, sizeof(DSBUFFERDESC));
	mBufferDesc.dwBufferBytes = pChild.cksize;
	mBufferDesc.dwSize = sizeof(DSBUFFERDESC);
	mBufferDesc.dwFlags = DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE | DSBCAPS_CTRLVOLUME;
	mBufferDesc.lpwfxFormat = &wft;

	if (FAILED(SoundMgr::GetInstance().GetDevice()->CreateSoundBuffer(&mBufferDesc, &mSoundBuffer, NULL)))
	{
		MessageBox(NULL, L"������ۻ�������", L"", MB_OK);
		return false;
	}

	void* pWrite1 = NULL;
	void* pWrite2 = NULL;
	DWORD dwlength1, dwlength2;

	mSoundBuffer->Lock(0, pChild.cksize, &pWrite1, &dwlength1
		, &pWrite2, &dwlength2, 0L);

	if (pWrite1 != nullptr)
		mmioRead(hFile, (char*)pWrite1, dwlength1);
	if (pWrite2 != nullptr)
		mmioRead(hFile, (char*)pWrite2, dwlength2);

	mSoundBuffer->Unlock(pWrite1, dwlength1, pWrite2, dwlength2);

	mmioClose(hFile, 0);

	// �ʱ� ���� �������� ����
	SetVolume(50.f);

	return true;
}
void Sound::Play(bool loop)
{
	mSoundBuffer->SetCurrentPosition(0);

	if (loop)
		mSoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
	else
		mSoundBuffer->Play(0, 0, 0);
}
void Sound::Stop(bool reset)
{
	mSoundBuffer->Stop();

	if (reset)
		mSoundBuffer->SetCurrentPosition(0);
}
void Sound::SetPosition(float position, bool loop)
{
	Stop(true);

	DWORD dwBytes = (DWORD)((position / 100.f) * (float)mBufferDesc.dwBufferBytes);
	mSoundBuffer->SetCurrentPosition(dwBytes);

	if (loop)
		mSoundBuffer->Play(0, 0, DSBPLAY_LOOPING);
	else
		mSoundBuffer->Play(0, 0, 0);
}
void Sound::SetVolume(float volume)
{
	mVolume = GetDecibel(volume);
	mSoundBuffer->SetVolume(mVolume);
}
int Sound::GetDecibel(float volume)
{
	if (volume > 100.f)
		volume = 100.f;
	else if (volume <= 0.f)
		volume = 0.00001f;

	// 1 ~ 100 ���̰��� ���ú� ������ ����
	int iVolume = (LONG)(-2000.0 * log10(100.f / volume));

	if (iVolume < -10000)
		iVolume = -10000;
	return  iVolume;
}