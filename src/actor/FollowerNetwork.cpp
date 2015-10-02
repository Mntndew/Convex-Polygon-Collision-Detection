#include "actor/FollowerNetwork.hpp"


FollowerNetwork::FollowerNetwork()
{
}

FollowerNetwork::~FollowerNetwork()
{
}

void FollowerNetwork::setLeader(std::shared_ptr<Actor> actor)
{
	m_leader = actor;
}

void FollowerNetwork::addFollower(std::shared_ptr<Actor> actor)
{
	m_followers.push_back(actor);
}

void FollowerNetwork::update(const float deltaTime)
{
	if (auto leader = m_leader.lock())
	{
		for (int i = 0; i < m_followers.size(); ++i)
		{
			if (auto follower = m_followers[i].lock())
			{
				if (std::abs(leader->getPosition().x - follower->getPosition().x) >= 45*follower->getId().id)
				{
					follower->setVelocity({(leader->getPosition().x - follower->getPosition().x), follower->getVelocity().y});
					if (std::abs(follower->getVelocity().x) > 500)
						follower->setVelocity({follower->getVelocity().x/std::abs(follower->getVelocity().x)*500, follower->getVelocity().y});
				}
				else
					follower->setVelocity({0, follower->getVelocity().y});
			}
		}
	}
}

