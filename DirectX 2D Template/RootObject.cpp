#include "RootObject.h"

MeridorGraphics::RootObject::RootObject(std::shared_ptr<MeridorGraphics::AnimatedSprite> my_animation, float frame_time)
{
	this->my_animation = my_animation;
	this->number_of_frames = my_animation->GetNumberOfFrames();
	this->frame_time = frame_time;
	this->time_to_next_frame = frame_time;
}

void MeridorGraphics::RootObject::Draw()
{
	my_animation->Draw();
}

void MeridorGraphics::RootObject::Update(float delta_time)
{
	time_to_next_frame -= delta_time;
	if (time_to_next_frame <= 0)
	{
		current_frame = (current_frame + 1) % number_of_frames;
		time_to_next_frame = frame_time;
		my_animation->SetFrame(current_frame);
	}
}
