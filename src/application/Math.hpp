#pragma once

#include <SFML/System/Vector2.hpp>

#include <math.h>
#include <cmath>
#include <limits>
#include <vector>
#include <cassert>


namespace math
{

	template <typename T>
	float distance(const sf::Vector2<T>& a, const sf::Vector2<T>& b)
	{
		return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
	}

	template <typename T>
	float angle(const sf::Vector2<T>& a, const sf::Vector2<T>& b)
	{
		return std::atan2(a.y - b.y, a.x - b.x);
	}

	template <typename T>
	T toDegrees(const T& radians)
	{
		return T(radians*(180/M_PI));
	}

	template <typename T>
	T toRadians(const T& degrees)
	{
		return T(degrees*(M_PI/180));
	}

	template <typename T>
	T dotProduct(const sf::Vector2<T>& a, const sf::Vector2<T>& b)
	{
		return a.x*b.x + a.y*b.y;
	}

	template <typename T>
	T magnitude(const sf::Vector2<T>& vector)
	{
		return (T)(std::sqrt(std::pow(vector.x, 2) + std::pow(vector.y, 2)));
	}

	class Polygon
	{
	private:
		std::vector<sf::Vector2f> m_points, m_edges;

	public:
		void constructEdges()
		{
			sf::Vector2f a, b;
			m_edges.clear();

			for (int i = 0; i < m_points.size(); ++i)
			{
				a = m_points[i];

				if (i + 1 >= m_points.size())
					b = m_points[0];
				else
					b  = m_points[i + 1];

				m_edges.push_back(sf::Vector2f(b.x - a.x, b.y - a.y));
			}
		}

		int getPointCount() const
		{
			return m_points.size();
		}

		int getEdgeCount() const
		{
			return m_edges.size();
		}

		sf::Vector2f getPoint(const int& index) const
		{
			assert(index < m_points.size());
			return m_points[index];
		}

		sf::Vector2f getEdge(const int& index) const
		{
			assert(index < m_edges.size());
			return m_edges[index];
		}

		sf::Vector2f getCenter() const
		{
			float x = 0, y = 0;
			
			for (int i = 0; i < m_points.size(); ++i)
			{
				x += m_points[i].x;
				y += m_points[i].y;
			}

			return sf::Vector2f(x/(float)m_points.size(), y/(float)m_points.size());
		}

		void offset(const float& x, const float& y)
		{
			for (int i = 0; i < m_points.size(); ++i)
				m_points[i] = sf::Vector2f(m_points[i].x + x, m_points[i].y + y);
		}

		void addPoint(const sf::Vector2f& point)
		{
			m_points.push_back(point);
		}

		void clear()
		{
			m_points.clear();
			m_edges.clear();
		}
	};

	struct Intersection
	{
		bool intersect;
		bool willIntersect;
		sf::Vector2f minimumTranslationVector;
	};

	void normalize(sf::Vector2f& vector);
	void projectPolygon(const sf::Vector2f& axis, const Polygon& polygon, float& min, float& max);
	float intervalDistance(const float& minA, const float& maxA, const float& minB, const float& maxB);
	Intersection intersect(const Polygon& a, const Polygon& b, const sf::Vector2f& velocity);
}

