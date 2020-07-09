#include <Application.h>

#include <stdexcept>
#include <iostream>


int main()
{
	try
	{
		sf::Music music;
		if (!music.openFromFile("Tobu1.ogg"))
			throw std::exception("couldn't play music"); // error
		music.setLoop(true);
		music.setVolume(15.f);
		music.play();

		Application app;
		app.run();
	}
	catch (std::exception & e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}
