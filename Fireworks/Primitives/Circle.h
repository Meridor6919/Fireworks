#pragma once
#include "Primitive.h"

template<int T>
class Circle
{
	PrimitiveInfo<T> primitive_info;
	std::array<DirectX::VertexPositionColor, T> points;

public:
	void Init(const PrimitiveInfo<T>& primitive_info);
	void Draw();
	void Move(DirectX::XMFLOAT2 direction);
};

template<int T>
inline void Circle<T>::Init(const PrimitiveInfo<T>& primitive_info)
{
	{
		this->primitive_info = primitive_info;

		const double angle = 1 / static_cast<double>(T - 1) * std::numbers::pi * 2;

		for (int i = 0; i < T; ++i)
		{
			points[i] = DirectX::VertexPositionColor({ primitive_info.orgin.x + sin(angle * i) * primitive_info.radius,
				primitive_info.orgin.y + cos(angle * i) * primitive_info.radius, 0 },
				primitive_info.registered_colors[primitive_info.color_table[i]]);
		}
	}
}

template<int T>
inline void Circle<T>::Draw()
{
	primitive_info.primitive_batch->Draw(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP, points, T);
}

template<int T>
inline void Circle<T>::Move(DirectX::XMFLOAT2 direction)
{
	for (int i = 0; i < T; ++i)
	{
		points[i].x += direction.x;
		points[i].y += direction.y;
	}
}