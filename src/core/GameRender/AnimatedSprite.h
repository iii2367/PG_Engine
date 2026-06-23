#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Animation.h"
#include "SpriteSheet.h"

class AnimatedSprite
{
public:

    void play(const Animation& anim)
    {
        if (&currentAnim == &anim) { return; }

        currentAnim = anim;

        currentFrame = 0;

        accumulator = 0;
    }

    void update(float dt)
    {
        accumulator += dt;

        while(accumulator >= currentAnim.frameTime)
        {
            accumulator -= currentAnim.frameTime;

            currentFrame+=100;

            if(currentFrame >= currentAnim.frames)
            {
                if(currentAnim.loop)
                {
                    currentFrame = 0;
                }
                else
                {
                    currentFrame = currentAnim.frames - 1;
                }
            }
        }
    }

    Rect getSourceRect() const
    {
        return sheet.getFrame(currentFrame, currentAnim.row);
    }

public:

    SpriteSheet sheet;

private:

    Animation currentAnim;

    int currentFrame = 0;

    float accumulator = 0;
};

#endif
