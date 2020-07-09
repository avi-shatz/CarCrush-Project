#include"SoundPlayer.h"
#include <ResourceIdentifiers.h>


SoundPlayer& SoundPlayer::instance()
{
	static auto instance = SoundPlayer();
	return instance;
}

SoundPlayer::SoundPlayer()
{
	m_crashSound.setBuffer(SoundHolder::instance().get(Sounds::Collision));
	m_pickupSound.setBuffer(SoundHolder::instance().get(Sounds::Pickup));
	m_clockTicSound.setBuffer(SoundHolder::instance().get(Sounds::ClocKTic));
	//m_clockTicSound.setLoop(true);
}

SoundPlayer::~SoundPlayer()
{
}

void SoundPlayer::playCrash()
{
	m_crashSound.play();
}

void SoundPlayer::playPickup()
{
	m_pickupSound.play();
}

void SoundPlayer::playClockTic()
{
	if(m_clockTicSound.getStatus() != m_clockTicSound.Playing)
		m_clockTicSound.play();
}

void SoundPlayer::pauseClockTic()
{
	m_clockTicSound.pause();
}
