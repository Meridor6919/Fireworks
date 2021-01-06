#pragma once
#include "AnimatedSprite.h"

namespace ExemplaryAnimationParameters {
	const RECT source = { 0,0,250,250 };
	const int pos_x = 0;
	const int pos_y = 0;
	const int width = 100;
	const int height = 100;
	const float depth = 0.5f;
	const int rotation = 0;
	const int number_of_frames = 8;
}
class ExemplaryAnimation : public MeridorGraphics::AnimatedSprite {

	const wchar_t* path = L"exemplary_animation.png";

public:
	ExemplaryAnimation(DirectX::SpriteBatch *sprite_batch, ID3D11Device *device) : 
		MeridorGraphics::AnimatedSprite(sprite_batch, ExemplaryAnimationParameters::source, ExemplaryAnimationParameters::pos_x, ExemplaryAnimationParameters::pos_y, ExemplaryAnimationParameters::width,
			ExemplaryAnimationParameters::height, ExemplaryAnimationParameters::depth, ExemplaryAnimationParameters::rotation)
	{
		AddTexture(path, device);
		for (int i = 0; i < ExemplaryAnimationParameters::number_of_frames; ++i)
		{
			//horizontal frames
			//AddFrame({ i * ExemplaryAnimationParameters::source.right, 0, (i + 1) * ExemplaryAnimationParameters::source.right, ExemplaryAnimationParameters::source.bottom });

			//vertical frames
			AddFrame({ 0, i * ExemplaryAnimationParameters::source.bottom, ExemplaryAnimationParameters::source.right, (i + 1) * ExemplaryAnimationParameters::source.bottom });
		}
	}
	
};