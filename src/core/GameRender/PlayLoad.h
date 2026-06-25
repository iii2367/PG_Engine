#pragma once

#include "SpriteSheet.h"
#include "Text.h"

struct SpritePayload
{
    Sprite sprite;
};

struct AnimatedPayload
{
    SpriteSheet sheet;
};

struct TextPayload
{
    Text text;
};
