#include "AnimatedSprite.h"

MeridorGraphics::AnimatedSprite::AnimatedSprite(DirectX::SpriteBatch * sprite_batch, RECT source, short pos_x, short pos_y, short width, short height, float depth, float rotation) : Sprite(sprite_batch, source, pos_x, pos_y, width, height, depth, rotation)
{

}
void MeridorGraphics::AnimatedSprite::AddFrame(RECT frame)
{
	frames.push_back(frame);
}
void MeridorGraphics::AnimatedSprite::Draw()
{
	MeridorGraphics::Sprite::Draw();
}
void MeridorGraphics::AnimatedSprite::SetFrame(int frame)
{
	source = frames[frame % static_cast<int>(frames.size())];
}

int MeridorGraphics::AnimatedSprite::GetNumberOfFrames()
{
	return static_cast<int>(frames.size());
}

