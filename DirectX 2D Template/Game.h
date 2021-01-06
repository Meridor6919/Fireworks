#pragma once
#include <d3d11.h>
#include "Keyboard.h"
#include "Mouse.h"
#include "SimpleMath.h"
#include "PrimitiveBatch.h"
#include "VertexTypes.h"
#include "AnimationHeaders.h"
#include "ObjectHeaders.h"
#include "SpriteBatch.h"
#include "DirectXApplication.h"

class Game : public DirectXApplication
{

	std::shared_ptr<ExemplaryAnimation> my_animation;
	std::shared_ptr<ExemplaryObject> my_object;

public:
	Game(HINSTANCE hinstance) : DirectXApplication(hinstance){}
	bool Init();
	void DrawPrimitiveBatch(DirectX::PrimitiveBatch<DirectX::VertexPositionColor> *primitive_batch, float delta_time);
	void DrawSpriteBatch(DirectX::SpriteBatch *sprite_batch, float delta_time);
	void Update(double delta_time);
	void Render(double delta_time);
};

