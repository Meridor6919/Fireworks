#pragma once
#pragma warning(disable : 4996)
#pragma comment(lib, "d3d11.lib")

#include <wrl/client.h>
#include <windows.h>
#include <string>
#include <directxmath.h>
#include <d3d11_1.h>
#include <Keyboard.h>
#include <SpriteFont.h>
#include <Mouse.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <CommonStates.h>
#include <Effects.h>
#include <SimpleMath.h>
#include <VertexTypes.h>
#include <chrono>

#include "resource.h""

using Microsoft::WRL::ComPtr;

class DirectXApplication {

protected:
	HINSTANCE instance_handle;
	HWND hwnd = 0;
	UINT window_width = 1200;
	UINT window_height = 800;
	std::string title = "Application title";
	std::string class_name = "Application_class";

	ComPtr<ID3D11Device> device;
	ComPtr<ID3D11DeviceContext> device_context;
	ComPtr<IDXGISwapChain> swap_chain;
	ComPtr<ID3D11RasterizerState> rasterizer_state;
	ComPtr<ID3D11Texture2D> render_target;
	ComPtr<ID3D11DepthStencilView> depth_stencil_view;
	ComPtr<ID3D11RenderTargetView> render_target_view;
	ComPtr<ID3D11InputLayout> input_layout;
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	std::unique_ptr<DirectX::Mouse> mouse;
	std::unique_ptr<DirectX::Mouse::ButtonStateTracker> mouse_tracker;
	std::unique_ptr<DirectX::Keyboard> keyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker> keyboard_tracker;
	std::unique_ptr<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>> primitive_batch;
	std::unique_ptr<DirectX::SpriteBatch> sprite_batch;
	std::unique_ptr<DirectX::CommonStates> common_states;
	std::unique_ptr<DirectX::BasicEffect> basic_effect;
	std::unique_ptr<DirectX::SpriteFont> sprite_font;
	D3D_DRIVER_TYPE driver_type;
	D3D_FEATURE_LEVEL feature_level;
	D3D11_VIEWPORT viewport;
	
	static LRESULT CALLBACK DefaultMsgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	static LRESULT CALLBACK MsgRedirect(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
	LRESULT EventHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	bool InitWindow();
	bool InitD3D11();
	bool InitInput();
	bool Register();
	int GetQualityLevel(int sample_count);

	void Clear();
public:
	DirectXApplication(HINSTANCE instance);
	bool Init();
	virtual void Update(double delta_time) {};
	virtual void Render(double delta_time) {};
	virtual int Run();
};