#include "ExemplaryObject.h"

ExemplaryObject::ExemplaryObject(std::shared_ptr<MeridorGraphics::AnimatedSprite> my_animation) : RootObject(my_animation, 0.05f)
{

}

void ExemplaryObject::Draw()
{
	RootObject::Draw();
}

void ExemplaryObject::Update(float delta_time)
{
	RootObject::Update(delta_time);
}

