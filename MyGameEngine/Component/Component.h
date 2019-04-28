//
// Component.h
//
#pragma once


// ヘッダーファイルのインクルード --------------------------------------------------------
#include <d3d11.h>
#include <SimpleMath.h>
#include <list>
#include <vector>
#include <functional>
#include <string>

#include "../Utility/Flag.h"


// 使用ライブラリ --------------------------------------------------------------------
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")


// クラスの宣言 ---------------------------------------------------------------------
namespace MyLibrary
{
	class GameObject;
	class Transform;
	class Collider;
}


// クラスの定義 ---------------------------------------------------------------------
namespace MyLibrary
{
	/// <summary>
	/// コンポーネントクラス
	/// </summary>
	class Component
	{
	public:

		// コンストラクタ
		Component(GameObject* pGameObject, int updateOrder = 100);
		// 仮想デストラクタ
		virtual ~Component();

		// 開始
		virtual void Awake(){}
		virtual void Start(){}
		// 更新
		virtual void Update(){}
		virtual void LateUpdate(){}

		// 当たった時の処理
		virtual void OnCollisionStay(Collider* pOther) {}
		virtual void OnCollisionEnter(Collider* pOther) {}
		virtual void OnCollisionExit(Collider* pOther) {}

		// プロパティ
		GameObject* GetGameObject() { return m_pGameObject; }
		Transform* GetTransform() { return m_pTransform; }


	protected:

		GameObject* m_pGameObject;		// ゲームオブジェクトへのポインタ
		Transform* m_pTransform;		// トランスフォームへのポインタ
	};
}
