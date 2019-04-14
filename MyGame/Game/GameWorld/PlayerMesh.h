//
// PlayerMesh.h
// Actor: Tamamura Shuuki
//
#pragma once

#include "MyLibrary.h"


/// <summary>
/// プレイヤー用のメッシュコンポーネント
/// </summary>
class PlayerMesh : public MyLibrary::Mesh
{
private:

	// プロパティ
	struct Property
	{
		ALIGN16 float destruction;
	};


public:

	PlayerMesh(MyLibrary::GameObject* pGameObject);
	~PlayerMesh();

	void Create() override;
	void Draw() override;

	// 破壊処理を呼び出す
	void CallOnDestruction();


private:

	ID3D11Buffer* m_pConstBuffer0;	// 変換行列用
	ID3D11Buffer* m_pConstBuffer1;	// カメラ・ライト用
	ID3D11Buffer* m_pConstBuffer2;	// Timer用
	ID3D11Buffer* m_pProperty;		// プレイヤー用に渡すデータ

	std::unique_ptr<DirectX::CommonStates> m_pCommonStates;

	std::function<void()> m_callOnDestruction = [] {};	// ポリゴン拡散用変数
	float m_destruction;
};
