#include "SceneBase.h"

void SceneBase::Update()
{
	// アクター
	for (Actor2D* actor: m_actors)
	{
		actor->Update();
	}

	// アクターの削除
	for (Actor2D* actor : m_removeActors)
	{
		m_actors.remove(actor);
		delete actor;
		actor = nullptr;
	}
	m_removeActors.clear();
}

void SceneBase::Draw()
{
	// アクター
	for (Actor2D* actor : m_actors)
	{
		actor->Draw();
	}
}