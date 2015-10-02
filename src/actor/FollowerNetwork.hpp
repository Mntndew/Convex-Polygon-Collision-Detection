#pragma once

#include <map>
#include <memory>
#include <vector>

#include "actor/Actor.hpp"


class FollowerNetwork
{
public:
	FollowerNetwork();
	~FollowerNetwork();

	void setLeader(std::shared_ptr<Actor> actor);
	void addFollower(std::shared_ptr<Actor> actor);

	void update(const float deltaTime); // Handle collisions (follower-follower and follower-leader)

private:
	std::weak_ptr<Actor> m_leader;
	std::vector<std::weak_ptr<Actor>> m_followers;
};

