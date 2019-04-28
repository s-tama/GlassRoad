//
// Scene.h
//
#pragma once

#include <string>


namespace MyLibrary
{
	class ObjectManager;
	class CollisionManager;
	class MeshRenderer;
	class SpriteRenderer;

	/// <summary>
	/// シーン基底クラス
	/// </summary>
	class SceneBase
	{
	public:

		SceneBase();
		virtual ~SceneBase();

		void Initialize();
		void Update();
		void Render();
		void Finalize();

		// プロパティ
		std::string GetName() { return m_name; }
		void SetName(std::string name) { m_name = name; }


	private:

		std::string m_name;		// シーン名

		ObjectManager* m_pObjectManager;
	};
}
