#ifndef INPUTMANAGER_H_
#define INPUTMANAGER_H_

#include <SDL2/SDL.h>
#include "MathHelper.h"

class InputManager{
public:
    enum MOUSE_BUTTON{
        LEFT = 0,
        RIGHT,
        MIDDLE,
        BACK,
        FORWARD
    };

private:

    static InputManager * sInstance;
    const Uint8 * mKeyboardState;
    Uint8 * mPreviousKeyState;
    int mKeyLength;

    Uint32 mPreviousMouseState;
    Uint32 mMouseState;

    int mMouseXPos;
    int mMouseYPos;

public:

    static InputManager * Instance();
    static void Release();
    bool KeyDown(SDL_Scancode scancode);
    bool KeyPressed(SDL_Scancode scancode);
    bool KeyReleased(SDL_Scancode scancode);

    bool MouseButtonDown(MOUSE_BUTTON button);
    bool MouseButtonPressed(MOUSE_BUTTON button);
    bool MouseButtonReleased(MOUSE_BUTTON button);

    Vector2 MousePos();

    void Update();
    void UpdatePrevInput();

private:
    
    InputManager();
    ~InputManager();

};

#endif