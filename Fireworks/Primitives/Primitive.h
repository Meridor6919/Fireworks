#pragma once
#include <PrimitiveBatch.h>
#include <VertexTypes.h>
#include <vector>
#include <array>
#include <numbers>

template <int T>
struct PrimitiveInfo
{
	DirectX::PrimitiveBatch<DirectX::VertexPositionColor>* primitive_batch;
	DirectX::XMFLOAT2 origin;
	std::vector<DirectX::XMVECTORF32> registered_colors;
	std::array<std::uint8_t, T> color_table;
	const double radius;
};