#include "Math.hpp"


namespace math
{
	void normalize(sf::Vector2f& vector)
	{
		float magnitude = math::magnitude<float>(vector);
		vector.x /= magnitude;
		vector.y /= magnitude;
	}

	void projectPolygon(const sf::Vector2f& axis, const Polygon& polygon, float& min, float& max)
	{
		float dotProduct = math::dotProduct<float>(axis, polygon.getPoint(0));
		min = dotProduct;
		max = dotProduct;

		for (int i = 0; i < polygon.getPointCount(); ++i)
		{
			dotProduct = math::dotProduct<float>(axis, polygon.getPoint(i));

			if (dotProduct < min)
				min = dotProduct;
			else if (dotProduct > max)
				max = dotProduct;
		}
	}

	float intervalDistance(const float& minA, const float& maxA, const float& minB, const float& maxB)
	{
		if (minA < minB)
			return minB - maxA;
		else
			return minA - maxB;
	}

	Intersection intersect(const Polygon& a, const Polygon& b, const sf::Vector2f& velocity)
	{
		Intersection result{true, true, {0, 0}};

		int edgeCountA = a.getEdgeCount();
		int edgeCountB = b.getEdgeCount();
		float minIntervalDistance = std::numeric_limits<float>::infinity();
		sf::Vector2f translationAxis, edge;

		for (int edgeIndex = 0; edgeIndex < edgeCountA + edgeCountB; ++edgeIndex)
		{
			if (edgeIndex < edgeCountA)
				edge = a.getEdge(edgeIndex);
			else
				edge = b.getEdge(edgeIndex - edgeCountA);

			sf::Vector2f axis = sf::Vector2f(-edge.y, edge.x);
			math::normalize(axis);

			float minA = 0, minB = 0, maxA = 0, maxB = 0;
			math::projectPolygon(axis, a, minA, maxA);
			math::projectPolygon(axis, b, minB, maxB);

			if (math::intervalDistance(minA, maxA, minB, maxB) > 0)
				result.intersect = false;
		}

		return result;
	}
}

