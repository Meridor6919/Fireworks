#pragma once
#include "RootObject.h"

class ExemplaryObject : public MeridorGraphics::RootObject
{	
public:
	ExemplaryObject(std::shared_ptr<MeridorGraphics::AnimatedSprite> my_animation);
	void Draw();
	void Update(float delta_time);
};

