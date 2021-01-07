#pragma once
#include "Sprite.h"
#include <vector>

namespace MeridorGraphics {

	class AnimatedSprite : public Sprite {

		std::vector<RECT> frames;

	public:

		AnimatedSprite(DirectX::SpriteBatch* sprite_batch, RECT source, short pos_x, short pos_y, short width, short height, float depth = 0.0f, float rotation = 0.0f);
		void AddFrame(RECT frame);
		void Draw();
		void SetFrame(int frame);
		int GetNumberOfFrames();
	};
}