#include "Math.hpp"
#include <iostream>


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

		float minIntervalDistance = std::numeric_limits<float>::infinity();
		sf::Vector2f translationAxis, edge, centerA = a.getCenter(), centerB = b.getCenter();

		for (int edgeIndex = 0; edgeIndex < a.getEdgeCount() + b.getEdgeCount(); edgeIndex++)
		{
			if (edgeIndex < a.getEdgeCount())
				edge = a.getEdge(edgeIndex);
			else
				edge = b.getEdge(edgeIndex - a.getEdgeCount());

			sf::Vector2f axis = sf::Vector2f(-edge.y, edge.x);
			math::normalize(axis);

			float minA = 0; float minB = 0; float maxA = 0; float maxB = 0;
			math::projectPolygon(axis, a, minA, maxA);
			math::projectPolygon(axis, b, minB, maxB);

			if (math::intervalDistance(minA, maxA, minB, maxB) > 0)
				result.intersect = false;

			float velocityProjection = math::dotProduct<float>(axis, velocity);

			if (velocityProjection < 0)
				minA += velocityProjection;
			else
				maxA += velocityProjection;

			float intervalDistance = math::intervalDistance(minA, maxA, minB, maxB);

			if (intervalDistance > 0)
				result.willIntersect = false;

			if (!result.intersect && !result.willIntersect)
				break;

			intervalDistance = std::abs(intervalDistance);

			if (intervalDistance < minIntervalDistance)
			{
				minIntervalDistance = intervalDistance;
				translationAxis = axis;

				sf::Vector2f d = sf::Vector2f(centerA.x - centerB.x, centerA.y - centerB.y);
				if (math::dotProduct<float>(d, translationAxis) < 0)
					translationAxis = sf::Vector2f(-translationAxis.x, -translationAxis.y);
			}
		}

		if (result.willIntersect)
			result.minimumTranslationVector = sf::Vector2f(translationAxis.x*minIntervalDistance, translationAxis.y*minIntervalDistance);

//		std::cout << result.minimumTranslationVector.x << ':' << result.minimumTranslationVector.y << std::endl; 

		return result;
	}
}

