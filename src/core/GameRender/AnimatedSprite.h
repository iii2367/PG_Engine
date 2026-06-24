#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#include "Animation.h"
#include "SpriteSheet.h"

class AnimatedSprite
{
public:

    AnimatedSprite(SpriteSheet* sheet) : sheet(sheet) {}

    void play(const Animation& anim)
    {
        if (currentAnim == &anim)
            return;

        currentAnim = &anim;
        currentFrame = 0;
        accumulator = 0.0f;
        playing = true;
    }

    void stop()
    {
        playing = false;
    }

    void update(float dt)
    {
        if (!playing || !currentAnim)
            return;

        accumulator += dt;

        while (accumulator >= currentAnim->frameTime)
        {
            accumulator -= currentAnim->frameTime;
            currentFrame++;

            if (currentFrame >= currentAnim->frames)
            {
                if (currentAnim->loop)
                    currentFrame = 0;
                else
                {
                    currentFrame = currentAnim->frames - 1;
                    playing = false;
                }
            }
        }
    }

    Rect getSourceRect() const
    {
        if (!sheet)
            return {0,0,0,0};

        return sheet->getFrame(currentFrame, currentAnim->row);
    }

public:

    SpriteSheet* sheet = nullptr;

private:

    const Animation* currentAnim = nullptr;

    int currentFrame = 0;
    float accumulator = 0.0f;
    bool playing = false;
};

#endif
