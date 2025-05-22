#include "Animation.h"

Animation::Animation()
{
	animationSpeed = 0.0f;
	currentFrame = 0;
	elapsedTime = 0.0f;
	isPlaying = true;
	isLooping = true;
	flipped = false;
}

void Animation::addFrame(sf::IntRect rect)
{
	frames.push_back(rect);
}

void Animation::setFrameSpeed(float speed)
{
	animationSpeed = speed;
}

int Animation::getSize()
{
	return frames.size();
}

void Animation::animate(float dt)
{
	if (isPlaying) {
		elapsedTime += dt;
		if (elapsedTime >= animationSpeed) {
			currentFrame++;
			if (currentFrame >= (int)frames.size()) {
				if (isLooping) {
					currentFrame = 0;
				}
				else {
					currentFrame--;
				}
			}
			elapsedTime = 0;
		}
	}
}

void Animation::reset()
{
	currentFrame = 0;
	elapsedTime = 0;
}

sf::IntRect Animation::getCurrentFrame()
{
	frame = frames[currentFrame];
	if (flipped) {
		frame = sf::IntRect(
			{ frame.position.x + frame.size.x, frame.position.y }, 
			{ -frame.size.x, frame.size.y }
		);
	}
	return frame;
}
