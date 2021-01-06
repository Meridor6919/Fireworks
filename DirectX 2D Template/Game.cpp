#include "Game.h"

bool Game::Init()
{
	if (DirectXApplication::Init())
	{
		my_animation = std::make_shared<ExemplaryAnimation>(sprite_batch.get(), device.Get());
		my_object = std::make_shared<ExemplaryObject>(my_animation);
		return true;
	}
	return false;
}

void Game::DrawPrimitiveBatch(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* primitive_batch, float delta_time)
{
	primitive_batch->Begin();
	primitive_batch->DrawLine(DirectX::VertexPositionColor({ 0,0,0 }, DirectX::Colors::Black), DirectX::VertexPositionColor({ 1110,1110,0 }, DirectX::Colors::Black));
	
	primitive_batch->End();
}

void Game::DrawSpriteBatch(DirectX::SpriteBatch * sprite_batch, float delta_time)
{
	sprite_batch->Begin(DirectX::SpriteSortMode_FrontToBack);
	my_object->Draw();
	sprite_batch->End();
}

void Game::Update(double delta_time)
{
	DirectXApplication::Update(delta_time);
	my_object->Update(delta_time);
}

void Game::Render(double delta_time)
{
	Clear();
	DrawPrimitiveBatch(primitive_batch.get(), delta_time);
	DrawSpriteBatch(sprite_batch.get(), delta_time);
	swap_chain->Present(0, 0);
}
