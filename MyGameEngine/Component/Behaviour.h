//
// Behaviour.cs
// Actor: Tamamura Shuuki
//
#pragma once

#include <d3d11.h>

#include "Component.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "DirectXTK.lib")


namespace MyLibrary
{
	// ゲームオブジェクトの行動処理を記述する基底クラス
	class Behaviour : public Component
	{
	public:

		Behaviour(GameObject* pGameObject, int updateOrder = 100):
			Component(pGameObject, updateOrder){}
		virtual ~Behaviour(){}

		//void Start(){}
		//void Update(){}
		//void LateUpdate(){}
		//void FixedUpdate() {}
	};
}
