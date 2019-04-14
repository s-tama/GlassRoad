//
// Mesh.h
// 作成者: Tamamura Shuuki
// 作成日: 2019/03/10(日)
//
#pragma once


// ヘッダーファイルのインクルード ----------------------------------------------------------------
#include "../Component/Component.h"

#include <CommonStates.h>
#include <PrimitiveBatch.h>
#include <VertexTypes.h>

#include "..\Component\Transform.h"
#include "..\Utility\BinaryFile.h"
#include "../Shader/MyShader.h"

#include <functional>


namespace MyLibrary
{
	/// <summary>
	/// メッシュデータ
	/// </summary>
	class Mesh : public Component
	{
	private:

		static const D3D11_INPUT_ELEMENT_DESC INPUT_LAYOUT[];	// 頂点レイアウト


	public:

		// 頂点情報
		struct Vertex
		{
			Vertex()
			{
				ZeroMemory(this, sizeof(Vertex));
			}

			DirectX::SimpleMath::Vector3 position;
			DirectX::SimpleMath::Vector3 normal;
		};

		// インデックスデータ
		struct Index
		{
			Index()
			{
				ZeroMemory(this, sizeof(Index));
			}

			uint16_t positions;
			uint16_t normals;
		};

		// メッシュの三角形ポリゴンデータ
		struct Triangle
		{
			Triangle(DirectX::SimpleMath::Vector3 p0, DirectX::SimpleMath::Vector3 p1, DirectX::SimpleMath::Vector3 p2):
				point{ p0, p1, p2 },
				world(DirectX::SimpleMath::Matrix::Identity)
			{	
				// 3頂点から面法線を計算する
				DirectX::SimpleMath::Vector3 v0, v1;
				v0 = p0 - p1;
				v1 = p2 - p1;
				normal = v0.Cross(v1);
			}

			DirectX::SimpleMath::Vector3 point[3];	
			DirectX::SimpleMath::Vector3 normal;
			DirectX::SimpleMath::Matrix world;	
		};


	public:

		Mesh(GameObject* pGameObject);
		virtual ~Mesh();

		virtual void Create();	// 作成
		virtual void Draw();	// 描画

		// プロパティ
		const std::vector<Triangle>& GetTriangles() { return m_triangles; }


	protected:

		HRESULT CreateShaderFromCSO(const wchar_t* pVS);
		HRESULT CreateShaderFromCSO(const wchar_t* pVS, const wchar_t* pPS);
		HRESULT CreateShaderFromCSO(const wchar_t* pVS, const wchar_t* pGS, const wchar_t* pPS);
		HRESULT CreateMeshFromOBJ(const wchar_t* pFileName);


	protected:

		ID3D11InputLayout* m_pInputLayout;			// 入力レイアウト
		ID3D11VertexShader* m_pVertexShader;		// 頂点シェーダ
		ID3D11PixelShader* m_pPixelShader;			// ピクセルシェーダ
		ID3D11GeometryShader* m_pGeometryShader;	// ジオメトリシェーダ

		ID3D11Buffer* m_pVertexBuffer;			// 頂点データを格納するバッファ
		ID3D11Buffer* m_pIndexBuffer;			// 頂点インデックスデータを格納するバッファ

		std::vector<Triangle> m_triangles;		// 三角形ポリゴンデータ

		size_t m_indexCount;	// 頂点インデックス数
		size_t m_vertexCount;	// 頂点数
	};
}
