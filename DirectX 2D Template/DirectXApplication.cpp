#include "DirectXApplication.h"
#include "resource.h"


int DirectXApplication::GetQualityLevel(int sample_count)
{
	//Creating dummy device to access CheckMultisampleQualityLevels method
	ComPtr<ID3D11Device> dummy_device;
	if (D3D11CreateDevice(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, 0, 0, D3D11_SDK_VERSION, dummy_device.ReleaseAndGetAddressOf(), 0, 0) != S_OK)
	{
		return -1;
	}
	UINT max_quality_level;
	dummy_device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, sample_count, &max_quality_level);
	return max_quality_level - 1;
}
DirectXApplication::DirectXApplication(HINSTANCE instance)
{
	this->instance_handle = instance;
}
bool DirectXApplication::Init()
{
	return InitWindow() * InitD3D11() * InitInput();
}
int DirectXApplication::Run()
{
	double delta_time = 0.0f;
	double current_time = static_cast<double>(clock()) / static_cast<double>(CLOCKS_PER_SEC);

	HANDLE timer;
	LARGE_INTEGER large_int;
	large_int.QuadPart = -166666; //60Hz

	timer = CreateWaitableTimer(0, TRUE, "WaitableTimer");
	if (timer)
	{
		SetWaitableTimer(timer, &large_int, 0, 0, 0, 0);
	}
	else
	{
		MessageBox(0, "Couldn't set waitible timer - fatal error", "Error", 0);
		exit(0);
	}


	MSG msg = { 0 };
	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			SetWaitableTimer(timer, &large_int, 0, 0, 0, 0);
			Update(delta_time);
			Render(delta_time);
			WaitForSingleObject(timer, INFINITE);

			delta_time = static_cast<double>(clock()) / 1000.0f - current_time;
			current_time = static_cast<double>(clock()) / static_cast<double>(CLOCKS_PER_SEC);
		}
	}
	return static_cast<int>(msg.wParam);
}
LRESULT CALLBACK DirectXApplication::DefaultMsgProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{

	switch (msg)
	{
	case WM_NCCREATE:
	{
		const CREATESTRUCTW* const struct_w = reinterpret_cast<CREATESTRUCTW*>(lparam);
		DirectXApplication* window = reinterpret_cast<DirectXApplication*>(struct_w->lpCreateParams);
		SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(MsgRedirect));
		return window->EventHandler(hwnd, msg, wparam, lparam);
	}
	default:
	{
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}
	}
}
LRESULT CALLBACK DirectXApplication::MsgRedirect(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		return 0;
	}
	case WM_INPUT:
	case WM_MOUSEMOVE:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
	case WM_MOUSEWHEEL:
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	case WM_MOUSEHOVER:
	{
		DirectX::Mouse::ProcessMessage(msg, wparam, lparam);
		break;
	}
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	case WM_KEYUP:
	case WM_SYSKEYUP:
	{
		DirectX::Keyboard::ProcessMessage(msg, wparam, lparam);
		break;
	}
	default:
	{
		return reinterpret_cast<DirectXApplication*>(GetWindowLongPtr(hwnd, GWLP_USERDATA))->EventHandler(hwnd, msg, wparam, lparam);
	}
	}
}
LRESULT DirectXApplication::EventHandler(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(hwnd, msg, wparam, lparam);
}
void DirectXApplication::Clear()
{
	/*
	device_context->ClearRenderTargetView(render_target_view.Get(), DirectX::Colors::White);
	device_context->ClearDepthStencilView(depth_stencil_view.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	device_context->OMSetRenderTargets(1, render_target_view.GetAddressOf(), depth_stencil_view.Get());
	device_context->RSSetViewports(1, &viewport);
	device_context->OMSetBlendState(common_states->Opaque(), nullptr, 0xFFFFFFFF);
	device_context->OMSetDepthStencilState(common_states->DepthNone(), 0);
	device_context->RSSetState(rasterizer_state.Get());
	basic_effect->SetWorld(world);
	basic_effect->Apply(device_context.Get());
	device_context->IASetInputLayout(input_layout.Get());
	*/
	device_context->ClearRenderTargetView(render_target_view.Get(), DirectX::Colors::White);
	device_context->ClearDepthStencilView(depth_stencil_view.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	device_context->OMSetRenderTargets(1, render_target_view.GetAddressOf(), depth_stencil_view.Get());
	device_context->RSSetViewports(1, &viewport);
	device_context->OMSetBlendState(common_states->Opaque(), nullptr, 0xFFFFFFFF);
	device_context->OMSetDepthStencilState(common_states->DepthNone(), 0);
	device_context->RSSetState(rasterizer_state.Get());
	basic_effect->SetWorld(world);
	basic_effect->Apply(device_context.Get());
	device_context->IASetInputLayout(input_layout.Get());
}
bool DirectXApplication::InitWindow()
{	
	if (!this->Register())
	{
		return false;
	}
	RECT window_rect = { 0, 0, window_width, window_height };
	if (!AdjustWindowRect(&window_rect, WS_OVERLAPPEDWINDOW, true))
	{
		MessageBox(0, "window rect error", "Error", 0);
		return false;
	}
	RECT screen_rect;
	GetWindowRect(GetDesktopWindow(), &screen_rect);

	hwnd = CreateWindowEx(
		NULL,
		class_name.c_str(),
		title.c_str(),
		WS_OVERLAPPEDWINDOW,
		(screen_rect.right - window_width) / 2,
		(screen_rect.bottom - window_height) / 2,
		window_rect.right - window_rect.left,
		window_rect.bottom - window_rect.top,
		0,
		0,
		instance_handle,
		this
	);
	if (!hwnd)
	{
		MessageBox(0, "CreateWindowEx call failed", "Error", 0);
		return false;
	}
	if (ShowWindow(hwnd, SW_SHOW))
	{
		MessageBox(0, "ShowWindow call failed", "Error", 0);
		return false;
	}
	if (!UpdateWindow(hwnd))
	{
		MessageBox(0, "UpdateWindow call failed", "Error", 0);
		return false;
	}
	

	return true;
}

bool DirectXApplication::Register()
{
	
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = this->DefaultMsgProc;
	wc.hInstance = instance_handle;
	wc.hCursor = LoadCursor(0, IDC_ARROW);
	wc.lpszClassName = class_name.c_str();
	wc.lpszMenuName = MAKEINTRESOURCE(DXT_MAIN);
	if (!RegisterClassEx(&wc))
	{
		return false;
	}
	
	return true;
}

bool DirectXApplication::InitInput()
{
	RAWINPUTDEVICE Input[2];

	//keyboard
	Input[0].usUsagePage = 0x01;
	Input[0].usUsage = 0x06;
	Input[0].dwFlags = 0;
	Input[0].hwndTarget = 0;
	//mouse
	Input[1].usUsagePage = 0x01;
	Input[1].usUsage = 0x02;
	Input[1].dwFlags = 0;
	Input[1].hwndTarget = 0;
	return RegisterRawInputDevices(Input, 2, sizeof(Input[0]));
}

bool DirectXApplication::InitD3D11()
{
	const int sample_count = 4;
	int quality_level = GetQualityLevel(sample_count);
	if (quality_level < 0)
	{
		MessageBox(0, "Coundn't create the dummy device", "Fatal error", 0);
		return false;
	}
	DXGI_SWAP_CHAIN_DESC swap_desc = { 0 };
	swap_desc.BufferCount = 1;
	swap_desc.BufferDesc.Width = window_width;
	swap_desc.BufferDesc.Height = window_height;
	swap_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_desc.BufferDesc.RefreshRate.Numerator = 60;
	swap_desc.BufferDesc.RefreshRate.Denominator = 1;
	swap_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_desc.OutputWindow = hwnd;
	swap_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swap_desc.Windowed = true;
	swap_desc.SampleDesc.Count = sample_count;
	swap_desc.SampleDesc.Quality = quality_level;
	swap_desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	
	if (D3D11CreateDeviceAndSwapChain(0, D3D_DRIVER_TYPE_HARDWARE, 0, 0, 0, 0, D3D11_SDK_VERSION, &swap_desc,
		swap_chain.ReleaseAndGetAddressOf(), device.ReleaseAndGetAddressOf(), &feature_level, device_context.ReleaseAndGetAddressOf()) != S_OK)
	{
		MessageBox(0, "Coundn't create the swap chain and device", "Fatal error", 0);
		return false;
	}
	//Creating render_target_view
	swap_chain->GetBuffer(0, IID_PPV_ARGS(render_target.ReleaseAndGetAddressOf()));
	if (device->CreateRenderTargetView(render_target.Get(), nullptr, &render_target_view) != S_OK)
	{
		MessageBox(0, "Coundn't create render target view", "Fatal error", 0);
		return false;
	}

	//Creating Depth stencil view
	CD3D11_TEXTURE2D_DESC depth_stencil_desc(DXGI_FORMAT_D24_UNORM_S8_UINT, window_width, window_height,
		1, 1, D3D11_BIND_DEPTH_STENCIL, D3D11_USAGE_DEFAULT, 0, 4, 0);

	ComPtr<ID3D11Texture2D> depth_stencil;
	device->CreateTexture2D(&depth_stencil_desc, NULL, depth_stencil.ReleaseAndGetAddressOf());
	CD3D11_DEPTH_STENCIL_VIEW_DESC depth_stencil_view_desc(D3D11_DSV_DIMENSION_TEXTURE2DMS);
	if (device->CreateDepthStencilView(depth_stencil.Get(), &depth_stencil_view_desc, depth_stencil_view.ReleaseAndGetAddressOf()) != S_OK)
	{
		MessageBox(0, "Coundn't create depth stencil view", "Fatal error", 0);
		return false;
	}

	//Creating rasterizer
	CD3D11_RASTERIZER_DESC rasterizer_desc(D3D11_FILL_SOLID, D3D11_CULL_NONE, FALSE,
		D3D11_DEFAULT_DEPTH_BIAS, D3D11_DEFAULT_DEPTH_BIAS_CLAMP,
		D3D11_DEFAULT_SLOPE_SCALED_DEPTH_BIAS, TRUE, FALSE, TRUE, FALSE);
	if (device->CreateRasterizerState(&rasterizer_desc, rasterizer_state.ReleaseAndGetAddressOf()) != S_OK)
	{
		MessageBox(0, "Coundn't create rasterizer", "Fatal error", 0);
		return false;
	}

	//Setting remaining variables
	viewport.Width = (float)window_width;
	viewport.Height = (float)window_height;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	common_states = std::make_unique<DirectX::CommonStates>(device.Get());
	basic_effect = std::make_unique<DirectX::BasicEffect>(device.Get());
	basic_effect->SetVertexColorEnabled(true);
	sprite_batch = std::make_unique<DirectX::SpriteBatch>(device_context.Get());
	primitive_batch = std::make_unique<DirectX::PrimitiveBatch<DirectX::VertexPositionColor>>(device_context.Get());
	sprite_font = std::make_unique<DirectX::SpriteFont>(device.Get(), L"myfile.spritefont", false);

	//Creating Input layout
	void const* shaderByteCode;
	size_t byteCodeLength;
	basic_effect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);
	if (device->CreateInputLayout(
		DirectX::VertexPositionColor::InputElements,
		DirectX::VertexPositionColor::InputElementCount,
		shaderByteCode, byteCodeLength,
		input_layout.ReleaseAndGetAddressOf()) != S_OK)
	{
		MessageBox(0, "Coundn't create input layout", "Fatal error", 0);
		return false;
	}

	DirectX::XMMATRIX proj = DirectX::XMMatrixOrthographicOffCenterLH(0.f, float(window_width), float(window_height), 0.f, 0.f, 1.f);
	basic_effect->SetProjection(proj);

	//Input support
	mouse = std::make_unique<DirectX::Mouse>();
	mouse->SetWindow(hwnd);
	mouse_tracker = std::make_unique<DirectX::Mouse::ButtonStateTracker>();
	keyboard = std::make_unique<DirectX::Keyboard>();
	keyboard_tracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();
	return true;
}
