#pragma once

#include "onepad.h"
#include "controller.h"
#ifdef SDL_BUILD
#include <SDL.h>
#endif

class GamePad
{
public:
    GamePad()
        : m_deadzone(1500)
    {
    }

    virtual ~GamePad()
    {
        return;
    }

    GamePad(const GamePad &);            // copy constructor
    GamePad &operator=(const GamePad &); // assignment

    /*
     * Find every interesting devices and create right structure for them(depend on backend)
     */
    static void EnumerateGamePads(std::vector<std::unique_ptr<GamePad>> &vgamePad);

    /*
     * Update state of every attached devices
     */
    virtual void UpdateGamePadState() = 0;

    /*
     * Causes devices to rumble
     * Rumble will differ according to type which is either 0(small motor) or 1(big motor)
     */
    virtual void Rumble(int type, int pad) { return; }
    /*
     * Safely dispatch to the Rumble method above
     */
    static void DoRumble(int type, int pad);

    virtual bool Init(int id) { return false; } // opens a handle and gets information

    /*
     * Used for GUI checkbox to give feedback to the user
     */
    virtual bool TestForce(float strength = 0.6) { return false; }

    virtual const char *GetName() = 0;

    virtual int GetInput(gamePadValues input) = 0;

    virtual int GetDeadzone()
    {
        return m_deadzone;
    }

protected:
    int m_deadzone;
};

extern std::vector<std::unique_ptr<GamePad>> s_vgamePad;
extern bool GamePadIdWithinBounds(int joyid);
