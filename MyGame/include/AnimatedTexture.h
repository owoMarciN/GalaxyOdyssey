#ifndef ANIMATED_TEXTURE_H_
#define ANIMATED_TEXTURE_H_

#include "Timer.h"
#include "Texture.h"

class AnimatedTexture : public Texture{
public:

    enum WRAP_MODE { once = 0, loop = 1 };
    enum ANIM_DIR { horizontal = 0, vertical = 1 };

private:

    //Used to get the deltatime to update the animation
	Timer* mTimer;
	//the first frame's starting pixel's X values on the spritesheet
	int mStartX;
	//the first frame's starting pixel's Y values on the spritesheet
	int mStartY;
    //Used to keep track of how long the current animation frame has been on screen
	float mAnimationTimer;
	//Used to determine the speed of the animation
	float mAnimationSpeed;
	//Stores how long each animation frame should be on screen
	float mTimePerFrame;
	//Stores the number of animation frames in the animation
	int mFrameCount;
	//Stores the wrap mode
	WRAP_MODE mWrapMode;
	//Stores the animation direction
	ANIM_DIR mAnimationDirection;
	//Is set to true only if the wrap mode is once and the last frame of the animation is reached
	bool mAnimationDone;

public:

    //Loads a texture from from file (relative to the exe path)
		//Supports spritesheets
		//x - Starting pixel's X on the spritesheet
		//y - Starting pixel's Y on the spritesheet
		//w - The width of the clipped sprite
		//h - The height of the clipped sprite
		//frameCount - The number of frames in the animation
		//animationSpeed - How long it takes to run the animation in seconds
		//animationDirection - How the animation sprites are arranges in the spritesheet
		//---------------------------------------------------------------------------------
		AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir);
		~AnimatedTexture();

        void WrapMode(WRAP_MODE mode);

        void Update();
};

#endif