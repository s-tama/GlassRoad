//
// OBJLoader.cpp
// Actor: Tamamura Shuuki
//

#include "OBJLoader.h"

using namespace DirectX;
using namespace MyLibrary;


/// <summary>
/// コンストラクタ
/// </summary>
OBJLoader::OBJLoader():
	m_indexCount(0)
{
}

/// <summary>
/// デストラクタ
/// </summary>
OBJLoader::~OBJLoader()
{
}

/// <summary>
/// OBJファイルを読み込む
/// </summary>
/// <param name="pFileName"></param>
/// <returns></returns>
bool OBJLoader::LoadOBJ(const wchar_t* pFileName)
{

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
				XMFLOAT3 v;
				sscanf_s(str.data(), "v  %f %f %f", &v.x, &v.y, &v.z);
				m_vertices.push_back(v);
			}
			// 法線
			else if (str[1] == 'n')
			{
				XMFLOAT3 vn;
				sscanf_s(str.data(), "vn  %f %f %f", &vn.x, &vn.y, &vn.z);
				m_vertexNormals.push_back(vn);
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
				// 0
				m_vertexIndices.push_back(va - 1);
				m_normalIndices.push_back(na - 1);
				m_indexCount++;
				// 1
				m_vertexIndices.push_back(vb - 1);
				m_normalIndices.push_back(nb - 1);
				m_indexCount++;
				// 2
				m_vertexIndices.push_back(vc - 1);
				m_normalIndices.push_back(nc - 1);
				m_indexCount++;
			}
		}
	}
	ifs.close();

	return true;
}
