//
// OBJLOader.h
// Actor: Tamamura Shuuki
//
#pragma once

#include <d3d11.h>
#include <DirectXMath.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#pragma comment(lib, "d3d11.lib")


namespace MyLibrary
{
	/// <summary>
	/// OBJファイル読み込み専用クラス
	/// </summary>
	class OBJLoader
	{
	public:

		OBJLoader();
		~OBJLoader();

		bool LoadOBJ(const wchar_t* pFileName);

		// プロパティ
		const std::vector<DirectX::XMFLOAT3>& GetVertices() { return m_vertices; }
		const std::vector<DirectX::XMFLOAT3>& GetVertexNormals() { return m_vertexNormals; }
		const std::vector<uint32_t>& GetVertexIndices() { return m_vertexIndices; }
		const std::vector<uint32_t>& GetNormalIndices() { return m_normalIndices; }
		const uint32_t& GetIndexCount() { return m_indexCount; }


	private:

		std::vector<DirectX::XMFLOAT3> m_vertices;			// 頂点座標配列
		std::vector<DirectX::XMFLOAT3> m_vertexNormals;		// 頂点法線配列
		std::vector<uint32_t> m_vertexIndices;		// 頂点インデックス配列
		std::vector<uint32_t> m_normalIndices;		// 法線インデックス配列
		uint32_t m_indexCount;		// インデックス数
	};
}