//
// StageMesh.h
// Actor: Tamamura Shuuki
// Date: 2019/04.13(日)
//
#pragma once

#include "MyLibrary.h"


/// <summary>
/// ステージ用メッシュコンポーネント
/// </summary>
class StageMesh : public MyLibrary::Mesh
{
private:

	// プロパティ
	struct Property
	{
		ALIGN16 float destruction;
	};


public:

	StageMesh(MyLibrary::GameObject* pGameObject);
	~StageMesh();

	void Create() override;
	void Draw() override;


private:

	ID3D11Buffer* m_pConstBuffer0;	// 変換行列用
	ID3D11Buffer* m_pConstBuffer1;	// カメラ・ライト用
	ID3D11Buffer* m_pConstBuffer2;	// Timer用
	ID3D11Buffer* m_pProperty;		// プレイヤー用に渡すデータ

	std::unique_ptr<DirectX::CommonStates> m_pCommonStates;
};
