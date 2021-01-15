#pragma once
#include <d3d11.h>
#include "Keyboard.h"
#include "Mouse.h"
#include "SimpleMath.h"
#include "PrimitiveBatch.h"
#include "VertexTypes.h"
#include "SpriteBatch.h"
#include "DirectXApplication.h"
#include "Primitives/PrimitiveHeaders.h"

class Game : public DirectXApplication
{
public:
	Game(HINSTANCE hinstance) : DirectXApplication(hinstance){}
	bool Init();
	void DrawPrimitiveBatch(DirectX::PrimitiveBatch<DirectX::VertexPositionColor> *primitive_batch, float delta_time);
	void DrawSpriteBatch(DirectX::SpriteBatch *sprite_batch, float delta_time);
	void Update(double delta_time);
	void Render(double delta_time);
};

