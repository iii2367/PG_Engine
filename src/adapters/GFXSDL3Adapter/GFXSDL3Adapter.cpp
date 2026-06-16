#include "GFXSDL3Adapter.h"

GFXSDL3Adapter::~GFXSDL3Adapter()
{

}

bool GFXSDL3Adapter::init(WindowHandle& handle)
{

}
void GFXSDL3Adapter::quitGFX()
{

}

int GFXSDL3Adapter::addImage(const std::string& path, std::string& tag) {}
bool GFXSDL3Adapter::removeImage(int id) {}

bool GFXSDL3Adapter::drawImageById(int id, Vec4 dst) {}
bool GFXSDL3Adapter::drawImageByTag(const std::string& tag, Rect dst) {}

bool GFXSDL3Adapter::drawImageRegionById(int id, Rect src, Rect dst) {}
bool GFXSDL3Adapter::drawImageRegionByTag(const std::string& tag, Rect src, Rect dst) {}

bool GFXSDL3Adapter::drawRect(Rect r, Color c) {}
bool GFXSDL3Adapter::clear(Color c) {}

bool GFXSDL3Adapter::setImageAlphaById(int id, float alpha) {}
bool GFXSDL3Adapter::setImageAlphaByTag(const std::string& tag, float alpha) {}

bool GFXSDL3Adapter::setImageBlendModeById(int id, int blendMode) {}
bool GFXSDL3Adapter::setImageBlendModeByTag(const std::string& tag, int blendMode) {}

bool GFXSDL3Adapter::setImagePositionById(int id, Vec2 pos) {}
bool GFXSDL3Adapter::setImagePositionByTag(const std::string& tag, Vec2 pos) {}

bool GFXSDL3Adapter::setImageScaleById(int id, Vec2 scale) {}
bool GFXSDL3Adapter::setImageScaleByTag(const std::string& tag, Vec2 scale) {}

bool GFXSDL3Adapter::hideImageById(int id) {}
bool GFXSDL3Adapter::hideImageByTag(const std::string& tag) {}

bool GFXSDL3Adapter::showImageById(int id) {}
bool GFXSDL3Adapter::showImageByTag(const std::string& tag) {}

bool GFXSDL3Adapter::isImageVisibleById(int id) {}

void GFXSDL3Adapter::bindTag(int id, const std::string& tag)
{

}
void GFXSDL3Adapter::removeFromTag(int id, const std::string& tag)
{

}
std::vector<int> GFXSDL3Adapter::getIdsByTag(const std::string& tag)
{

}
GFXSDL3Adapter::GFXEntry* GFXSDL3Adapter::getById(int id)
{

}
