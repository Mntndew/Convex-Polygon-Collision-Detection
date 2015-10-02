#include "actor/FollowerNetwork.hpp"

#include <iostream>


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
	bool found = false;
	for (int i = 0; i < m_followers.size(); ++i)
	{
		if (auto follower = m_followers[i].lock())
		{
			if (follower->getId() == actor->getId())
			{
				found = true;
				break;
			}
		}
	}
	
	if (!found)
		m_followers.push_back(actor);
}

void FollowerNetwork::update(const float deltaTime)
{
	if (auto leader = m_leader.lock())
	{
		auto jumpPoints = leader->getJumpPoints();
		leader->clearJumpPoints();
		for (int i = 0; i < m_followers.size(); ++i)
		{
			if (auto follower = m_followers[i].lock())
			{
				follower->addJumpPoints(jumpPoints);
				if (follower->isColliding())
				{
					std::cout << i << std::endl;
					if (std::abs(leader->getPosition().x - follower->getPosition().x) >= 45*(i + 1))
					{
						follower->setVelocity({(leader->getPosition().x - follower->getPosition().x), follower->getVelocity().y});
						if (std::abs(follower->getVelocity().x) > 900)
							follower->setVelocity({follower->getVelocity().x/std::abs(follower->getVelocity().x)*900, follower->getVelocity().y});
					}
					else
						follower->setVelocity({0, follower->getVelocity().y});
				}
			}
		}
	}
}

