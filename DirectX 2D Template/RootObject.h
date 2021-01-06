#pragma once
#include "ExemplaryAnimation.h"

namespace MeridorGraphics {
	class RootObject
	{
	protected:
		std::shared_ptr<MeridorGraphics::AnimatedSprite> my_animation;
		float frame_time;
		int current_frame = 0;
		float time_to_next_frame;
		int number_of_frames;

	public:
		RootObject(std::shared_ptr<MeridorGraphics::AnimatedSprite> my_animation, float frame_time);
		void Draw();
		void Update(float delta_time);
	};
}

