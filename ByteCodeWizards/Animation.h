#pragma once
#include "SFML/Graphics.hpp"
#include <vector>

class Animation
{
public:
	Animation();

	void addFrame(sf::IntRect rect);
	void setFrameSpeed(float speed);
	int getSize();

	void animate(float dt);
	void reset();

	sf::IntRect getCurrentFrame();

	float getFrameSpeed() { return animationSpeed; };

	void setFlipped(bool flip) { flipped = flip; };
	bool getFlipped() { return flipped; }

	void setLooping(bool loop) { isLooping = loop; };
	bool getLooping() { return isLooping; };

	void setPlaying(bool play) { isPlaying = play; };
	bool getPlaying() { return isPlaying; };

protected:
	std::vector<sf::IntRect>frames;
	sf::IntRect frame;
	int currentFrame;
	float animationSpeed;
	bool flipped;
	bool isLooping;
	bool isPlaying;
	float elapsedTime;
};
