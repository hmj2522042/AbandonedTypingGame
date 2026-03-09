#pragma once
#include "Actor2D.h"
#include "list"

class SceneBase
{
private:
	std::list<Actor2D*> m_actors;
	std::list<Actor2D*> m_removeActors;

public:
	~SceneBase() {}

	void AddActor(Actor2D* actor) { m_actors.push_back(actor); }
	void RemoveActor(Actor2D* actor) { m_removeActors.push_back(actor); }

	virtual void Initialize() = 0;	// ‰Šú‰»
	virtual void Finalize() = 0;	// I—¹
	virtual void Update() = 0;		// XV
	virtual void Draw() = 0;		// •`‰æ
};