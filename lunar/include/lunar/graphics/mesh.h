#pragma once

#include <cstdint>

namespace hippo::graphics
{
	class Mesh
	{
	public:
		Mesh(float* vertexArray, uint32_t vertexCount, uint32_t dimensions);
		Mesh(float* vertexArray, uint32_t vertexCount, uint32_t dimensions, uint32_t* elementArray, uint32_t elementCount);
		~Mesh();

		void Bind();
		void Unbind();

		inline uint32_t GetVertexCount() const { return _vertexCount; }
		inline uint32_t GetElementCount() const { return _elementCount; }

	private:
		uint32_t _vertexCount, _elementCount;
		uint32_t _Vao, _Ebo;
		uint32_t _positionVbo;
	};
}