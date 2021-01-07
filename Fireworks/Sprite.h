#pragma once
#include "SpriteBatch.h"
#include <SpriteFont.h>
#include <WICTextureLoader.h>
#include <vector>
#include <string>
#include <wrl.h>

namespace MeridorGraphics {
	class Sprite {

	protected:
		DirectX::SpriteBatch* sprite_batch;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> rc_view;
		float depth;
		float rotation;
		RECT source;
		short pos_x;
		short pos_y;
		short width;
		short height;
		DirectX::XMFLOAT2 orgin;
		DirectX::SpriteEffects effect;

	public:

		Sprite(DirectX::SpriteBatch* sprite_batch, RECT source, short pos_x, short pos_y, short width, short height, float depth = 0.0f, float rotation = 0.0f);
		virtual void AddTexture(const wchar_t* file_name, ID3D11Device *device);
		virtual void Draw();
		void SetRotation(float rotation);
		void SetSourceRect(RECT source);
		void SetY(short pos_y);
		void SetX(short pos_x);
		void SetWidth(short width);
		void SetHeight(short height);
		void SetEffect(DirectX::SpriteEffects effect);
		void SetDepth(float depth);

		float GetRotation() { return rotation; }
		RECT GetSourceRect() { return source; }
		short GetX() { return pos_x; }
		short GetY() { return pos_y; }
		short GetWidth() { return width; }
		short GetHeight() { return height; }
		float GetDepth() { return depth; }
		DirectX::SpriteEffects GetEffect() { return effect; }
	};

	class Text {

		DirectX::SpriteBatch* sprite_batch;
		ID3D11ShaderResourceView* rc_view;
		DirectX::SpriteFont* sprite_font;
		float depth;
		float rotation;
		float scale;
		DirectX::XMVECTOR color;
		DirectX::XMFLOAT2 position;
		DirectX::SpriteEffects effect;

	public:

		Text(DirectX::SpriteFont* sprite_font, DirectX::SpriteBatch* sprite_batch, float fontsize, DirectX::XMFLOAT2 position, float depth = 0.0f, float rotation = 0.0f);
		void Draw(const wchar_t* text);
		void SetRotation(float rotation);
		void SetPosition(DirectX::XMFLOAT2 position);
		void SetFontSize(float font_size);
		void SetEffect(DirectX::SpriteEffects effect);
		void SetDepth(float depth);
		void SetColor(DirectX::XMVECTOR color);

		float GetRotation() { return rotation; }
		DirectX::XMFLOAT2 GetPosition() { return position; }
		float GetScale() { return scale; }
		DirectX::SpriteEffects GetEffect() { return effect; }
		float GetDepth() { return depth; }
	};
}