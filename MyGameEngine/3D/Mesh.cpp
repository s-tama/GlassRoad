//
// Mesh.h
// 作成者: Tamamura Shuuki
// 作成日: 2019/03/10(日)
//


// ヘッダーファイルのインクルード -----------------------------------------------------------------
#include "Mesh.h"

#include <string>
#include <iostream>
#include <fstream>

#include "..\Common\DeviceResources.h"

#include "..\Utility\Macro.h"
#include "MeshRenderer.h"

#include "..\Utility\Time.h"


// usingディレクティブ -------------------------------------------------------------------------
using namespace DirectX;
using namespace DirectX::SimpleMath;
using namespace MyLibrary;


// 頂点インプットレイアウトを定義 ---------------------------------------------------------------
const D3D11_INPUT_ELEMENT_DESC Mesh::INPUT_LAYOUT[] =
{
	{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0xffffffff, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};


// メンバ関数の定義 --------------------------------------------------------------------------
/// <summary>
/// コンストラクタ
/// </summary>
Mesh::Mesh(GameObject* pGameObject):
	Component(pGameObject),
	m_pInputLayout(nullptr),
	m_pVertexShader(nullptr),
	m_pPixelShader(nullptr),
	m_pGeometryShader(nullptr),
	m_pVertexBuffer(nullptr),
	m_pIndexBuffer(nullptr)
{
	MeshRenderer::GetInstance()->AddMesh(this);
}

/// <summary>
/// デストラクタ
/// </summary>
Mesh::~Mesh()
{
	SAFE_RELEASE(m_pInputLayout);
	SAFE_RELEASE(m_pVertexShader);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pGeometryShader);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}

/// <summary>
/// シェーダーを作成する
/// </summary>
/// <param name="pVS">頂点シェーダ</param>
/// <returns></returns>
HRESULT Mesh::CreateShaderFromCSO(const wchar_t* pVS)
{
	DeviceResources* pDeviceResources = DeviceResources::GetInstance();
	auto device = pDeviceResources->GetD3DDevice();

	HRESULT hr;

	// コンパイルされたデータ
	BinaryFile compiledVS = BinaryFile::Load(pVS);

	// 入力レイアウトを作成
	UINT numElements = sizeof(INPUT_LAYOUT) / sizeof(INPUT_LAYOUT[0]);
	hr = device->CreateInputLayout(INPUT_LAYOUT, numElements, compiledVS.GetData(), compiledVS.GetSize(), &m_pInputLayout);

	// 頂点シェーダを作成
	hr = device->CreateVertexShader(compiledVS.GetData(), compiledVS.GetSize(), nullptr, &m_pVertexShader);
	if (FAILED(hr)) return E_FAIL;

	return S_OK;
}

/// <summary>
/// シェーダーを作成する
/// </summary>
/// <param name="pVS">頂点シェーダ</param>
/// <param name="pPS">ピクセルシェーダ</param>
/// <returns></returns>
HRESULT Mesh::CreateShaderFromCSO(const wchar_t* pVS, const wchar_t* pPS)
{
	DeviceResources* pDeviceResources = DeviceResources::GetInstance();
	auto device = pDeviceResources->GetD3DDevice();

	HRESULT hr;

	// コンパイルされたデータ
	BinaryFile compiledVS = BinaryFile::Load(pVS);
	BinaryFile compiledPS = BinaryFile::Load(pPS);

	// 入力レイアウトを作成
	UINT numElements = sizeof(INPUT_LAYOUT) / sizeof(INPUT_LAYOUT[0]);
	hr = device->CreateInputLayout(INPUT_LAYOUT, numElements, compiledVS.GetData(), compiledVS.GetSize(), &m_pInputLayout);

	// 頂点シェーダを作成
	hr = device->CreateVertexShader(compiledVS.GetData(), compiledVS.GetSize(), nullptr, &m_pVertexShader);
	if (FAILED(hr)) return E_FAIL;

	// ピクセルシェーダを作成
	hr = device->CreatePixelShader(compiledPS.GetData(), compiledPS.GetSize(), nullptr, &m_pPixelShader);
	if (FAILED(hr)) return E_FAIL;

	return S_OK;
}

/// <summary>
/// シェーダーを作成する
/// </summary>
/// <param name="pVS">頂点シェーダ</param>
/// <param name="pGS">ジオメトリシェーダ</param>
/// <param name="pPS">ピクセルシェーダ</param>
/// <returns></returns>
HRESULT Mesh::CreateShaderFromCSO(const wchar_t* pVS, const wchar_t* pGS, const wchar_t* pPS)
{
	DeviceResources* pDeviceResources = DeviceResources::GetInstance();
	auto device = pDeviceResources->GetD3DDevice();

	HRESULT hr;

	// コンパイルされたデータ
	BinaryFile compiledVS = BinaryFile::Load(pVS);
	BinaryFile compiledGS = BinaryFile::Load(pGS);
	BinaryFile compiledPS = BinaryFile::Load(pPS);

	// 入力レイアウトを作成
	UINT numElements = sizeof(INPUT_LAYOUT) / sizeof(INPUT_LAYOUT[0]);
	hr = device->CreateInputLayout(INPUT_LAYOUT, numElements, compiledVS.GetData(), compiledVS.GetSize(), &m_pInputLayout);

	// 頂点シェーダを作成
	hr = device->CreateVertexShader(compiledVS.GetData(), compiledVS.GetSize(), nullptr, &m_pVertexShader);
	if (FAILED(hr)) return E_FAIL;

	// ジオメトリシェーダを作成
	hr = device->CreateGeometryShader(compiledGS.GetData(), compiledGS.GetSize(), nullptr, &m_pGeometryShader);
	if (FAILED(hr)) return E_FAIL;

	// ピクセルシェーダを作成
	hr = device->CreatePixelShader(compiledPS.GetData(), compiledPS.GetSize(), nullptr, &m_pPixelShader);
	if (FAILED(hr)) return E_FAIL;

	return S_OK;
}

/// <summary>
/// メッシュを作成する
/// </summary>
/// <param name="pFileName"></param>
/// <returns></returns>
HRESULT Mesh::CreateMeshFromOBJ(const wchar_t* pFileName)
{
	DeviceResources* pDeviceResources = DeviceResources::GetInstance();
	auto device = pDeviceResources->GetD3DDevice();

	std::vector<Vertex> vertices;	// 頂点データ配列
	std::vector<Vector3> positions;		// 頂点格納用
	std::vector<Vector3> normals;		// 法線格納用
	std::vector<uint16_t> indices;		// 頂点インデックス配列
	std::vector<uint16_t> vIndices;
	std::vector<uint16_t> nIndices;
	size_t vCount = 0;		// 格納した頂点数
	size_t vnCount = 0;		// 格納した法線数
	size_t iCount = 0;		// 格納したインデックス数

	// objファイル読み込み
	std::ifstream ifs(pFileName);

	std::string str;
	while (getline(ifs, str))
	{
		// 頂点情報
		if (str[0] == 'v')
		{
			// 頂点座標
			if (str[1] == ' ')
			{
				Vector3 v;
				sscanf_s(str.data(), "v  %f %f %f", &v.x, &v.y, &v.z);
				positions.push_back(v);
				vCount++;
			}
			// 法線
			else if (str[1] == 'n')
			{
				Vector3 vn;
				sscanf_s(str.data(), "vn  %f %f %f", &vn.x, &vn.y, &vn.z);
				normals.push_back(vn);
				vnCount++;
			}
		}
		// インデックス情報
		if (str[0] == 'f')
		{
			int va, vb, vc;
			int na, nb, nc;
			sscanf_s(str.data(), "f %d//%d %d//%d %d//%d", &va, &na, &vb, &nb, &vc, &nc);
			// 三角形の頂点インデックス番号が同じ物を含む場合は無視する
			if (va != vb && va != vc && vb != vc)
			{
				Index index;

				// 0
				index.positions = va - 1;
				index.normals = na - 1;
				indices.push_back(index.positions);
				vIndices.push_back(va - 1);
				nIndices.push_back(na - 1);
				iCount++;
				// 1
				index.positions = vb - 1;
				index.normals = nb - 1;
				indices.push_back(index.positions);
				vIndices.push_back(vb - 1);
				nIndices.push_back(nb - 1);
				iCount++;
				// 2
				index.positions = vc - 1;
				index.normals = nc - 1;
				indices.push_back(index.positions);
				vIndices.push_back(vc - 1);
				nIndices.push_back(nc - 1);
				iCount++;
			}
		}
	}
	ifs.close();

	// 頂点データを作成する
	for (size_t i = 0; i < iCount / 3; i++)
	{
		// 一時頂点バッファ
		Vertex vertex[3];

		// 位置情報を作成
		Vector3 v0, v1, v2;
		v0 = positions[vIndices[i * 3 + 0]];
		v1 = positions[vIndices[i * 3 + 1]];
		v2 = positions[vIndices[i * 3 + 2]];

		vertex[0].position = v0;
		vertex[1].position = v1;
		vertex[2].position = v2;

		// 法線を作成
		vertex[0].normal = normals[nIndices[i * 3 + 0]];
		vertex[1].normal = normals[nIndices[i * 3 + 1]];
		vertex[2].normal = normals[nIndices[i * 3 + 2]];

		// 頂点バッファに追加
		vertices.push_back(vertex[0]);
		vertices.push_back(vertex[1]);
		vertices.push_back(vertex[2]);
	}
	m_indexCount = iCount;
	m_vertexCount = vertices.size();

	// 頂点バッファの作成
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * vertices.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem = &vertices[0];
	device->CreateBuffer(&bd, &InitData, &m_pVertexBuffer);

	return S_OK;
}

/// <summary>
/// 初期化
/// </summary>
void Mesh::Create()
{
}

/// <summary>
/// 描画
/// </summary>
void Mesh::Draw()
{
}
