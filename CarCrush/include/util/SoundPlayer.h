#include <ResourceHolder.h>

//singelton class

class SoundPlayer : private sf::NonCopyable
{
public:
	static SoundPlayer& instance();

	~SoundPlayer();
	void playCrash();
	void playPickup();
	void playClockTic();
	void pauseClockTic();
private:
	SoundPlayer();

	sf::Sound		m_crashSound;
	sf::Sound		m_pickupSound;
	sf::Sound		m_clockTicSound;
};
