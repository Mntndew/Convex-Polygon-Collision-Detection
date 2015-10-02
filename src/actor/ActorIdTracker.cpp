#include "actor/ActorIdTracker.hpp"


ActorIdTracker::ActorIdTracker()
{
}

ActorIdTracker::~ActorIdTracker()
{
}

ActorId ActorIdTracker::registerNewActor()
{
	auto id = getFirstAvailavleId();
	m_ids.push_back(id);
	return id;
}

void ActorIdTracker::removeActor(const ActorId& id)
{
}

ActorId ActorIdTracker::getFirstAvailavleId() const
{
	if (m_ids.empty())
		return {0};

	auto id = m_ids[0];
	for (int i = 0; i < m_ids.size(); ++i)
	{
		if (m_ids[i].id - id.id > 1)
		{
			auto _id = id.id + 1;
			return {_id};
		}

		id = m_ids[i];
	}

	auto _id = m_ids.back().id + 1;
	return {_id};
}

