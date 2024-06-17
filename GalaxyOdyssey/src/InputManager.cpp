#include "InputManager.h"

InputManager * InputManager::sInstance = nullptr;

InputManager * InputManager::Instance() {
    if(sInstance == nullptr)
        sInstance = new InputManager;
    return sInstance;
}

void InputManager::Release() {
    delete sInstance;
    sInstance = nullptr;
}

InputManager::InputManager() {
    mKeyboardState = SDL_GetKeyboardState(&mKeyLength);
    mPreviousKeyState = new Uint8[mKeyLength];
    memcpy(mPreviousKeyState, mKeyboardState, mKeyLength);
}

InputManager::~InputManager() {
    delete [] mPreviousKeyState;
    mPreviousKeyState = nullptr;
}

bool InputManager::KeyDown(SDL_Scancode scanCode) {
	return (mKeyboardState[scanCode] != 0);
}

bool InputManager::KeyPressed(SDL_Scancode scanCode) {
	//returning true of the key was not pressed in the previous keyboard state but is pressed in the current one
	return (mPreviousKeyState[scanCode]) == 0 && (mKeyboardState[scanCode] != 0);
}

bool InputManager::KeyReleased(SDL_Scancode scanCode) {
	//returning true of the key was pressed in the previous keyboard state but is not pressed in the current one
	return (mPreviousKeyState[scanCode] != 0) && (mKeyboardState[scanCode] == 0);
}

Vector2 InputManager::MousePos() {
	//Converting the mouse position into a Vector2 for ease of use since all entities use Vector2
	return Vector2((float)mMouseXPos, (float)mMouseYPos);
}

bool InputManager::MouseButtonDown(MOUSE_BUTTON button) {
	//mask to be using for bit wise operations
	Uint32 mask = 0;

	switch (button) {
		case LEFT:
			mask = SDL_BUTTON_LMASK;
			break;
		case RIGHT:
			mask = SDL_BUTTON_RMASK;
			break;
		case MIDDLE:
			mask = SDL_BUTTON_MMASK;
			break;
		case BACK:
			mask = SDL_BUTTON_X1MASK;
			break;
		case FORWARD:
			mask = SDL_BUTTON_X2MASK;
			break;
	}
	//return true if the mask exists in the current mouse state
	return ((mMouseState & mask) != 0);
}

bool InputManager::MouseButtonPressed(MOUSE_BUTTON button) {
	//mask to be using for bit wise operations
	Uint32 mask = 0;

	switch (button) {
		case LEFT:
			mask = SDL_BUTTON_LMASK;
			break;
		case RIGHT:
			mask = SDL_BUTTON_RMASK;
			break;
		case MIDDLE:
			mask = SDL_BUTTON_MMASK;
			break;
		case BACK:
			mask = SDL_BUTTON_X1MASK;
			break;
		case FORWARD:
			mask = SDL_BUTTON_X2MASK;
			break;
	}
	//return true if the mask does not exist in the previous mouse state, but exists in the current one
	return ((mPreviousMouseState & mask) == 0) && ((mMouseState & mask) != 0);
}

bool InputManager::MouseButtonReleased(MOUSE_BUTTON button) {
	Uint32 mask = 0;
	switch (button) {
		case LEFT:
			mask = SDL_BUTTON_LMASK;
			break;
		case RIGHT:
			mask = SDL_BUTTON_RMASK;
			break;
		case MIDDLE:
			mask = SDL_BUTTON_MMASK;
			break;
		case BACK:
			mask = SDL_BUTTON_X1MASK;
			break;
		case FORWARD:
			mask = SDL_BUTTON_X2MASK;
			break;
	}
	//return true if the mask exists in the previous mouse state, but does not exist in the current one
	return ((mPreviousMouseState & mask) != 0) && ((mMouseState & mask) == 0);
}

void InputManager::Update(){
    mMouseState = SDL_GetMouseState(&mMouseXPos, &mMouseYPos);
}

void InputManager::UpdatePrevInput(){
    memcpy(mPreviousKeyState, mKeyboardState, mKeyLength);
    mPreviousMouseState = mMouseState;
}