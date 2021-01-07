#include "Game.h"

bool Game::Init()
{
	if (DirectXApplication::Init())
	{
		return true;
	}
	return false;
}

void Game::DrawPrimitiveBatch(DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* primitive_batch, float delta_time)
{
	primitive_batch->Begin();
	primitive_batch->DrawLine(DirectX::VertexPositionColor({ 0,0,0 }, DirectX::Colors::White), DirectX::VertexPositionColor({ 1110,1110,0 }, DirectX::Colors::Red));
	primitive_batch->DrawLine(DirectX::VertexPositionColor({ 0,0,0 }, DirectX::Colors::White), DirectX::VertexPositionColor({ 1110,1150,0 }, DirectX::Colors::Blue));
	primitive_batch->DrawLine(DirectX::VertexPositionColor({ 0,0,0 }, DirectX::Colors::White), DirectX::VertexPositionColor({ 1110,1050,0 }, DirectX::Colors::Green));
	primitive_batch->End();
}

void Game::DrawSpriteBatch(DirectX::SpriteBatch * sprite_batch, float delta_time)
{
	sprite_batch->Begin(DirectX::SpriteSortMode_FrontToBack);
	sprite_batch->End();
}

void Game::Update(double delta_time)
{
	DirectXApplication::Update(delta_time);
}

void Game::Render(double delta_time)
{
	Clear(DirectX::Colors::Black);
	DrawPrimitiveBatch(primitive_batch.get(), delta_time);
	DrawSpriteBatch(sprite_batch.get(), delta_time);
	swap_chain->Present(0, 0);
}
