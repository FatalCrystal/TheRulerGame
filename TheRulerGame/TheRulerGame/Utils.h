#pragma once
#include <SFML/Graphics.hpp>

namespace Utils
{
    // Window Width
    const int WinSizeX = 800;
    // Window Height
    const int WinSizeY = 800;
    // Window Center (X Axis)
    const int WinCenterX = WinSizeX / 2;
    // Window Center (Y Axis)
    const int WinCenterY = WinSizeY / 2;
    // Maximum Frame Rate
    const int FrameLimit = 60;

    // Commonly used vector operations
    //--------------------------------

    // Return magnitude of the vector
    inline float Magnitude(sf::Vector2f _vector)
    {
        return sqrt(powf(_vector.x, 2) + powf(_vector.y, 2));
    }

    // Return the normalized vector (allows for vectors of zero)
    inline sf::Vector2f Normalize(sf::Vector2f _vector)
    {
        if (_vector.x != 0.0f)
        {
            _vector.x /= Magnitude(_vector);
        }

        if (_vector.y != 0.0f)
        {
            _vector.y /= Magnitude(_vector);
        }

        return _vector;
    }

    // Return the Dot Product of the two vectors
    inline float DotProduct(sf::Vector2f _vectorA, sf::Vector2f _vectorB)
    {
        return (_vectorA.x * _vectorB.x) + (_vectorA.y * _vectorB.y);
    }

    // Return the angle between the two vectors
    inline float AngleBetween(sf::Vector2f _vectorA, sf::Vector2f _vectorB)
    {
        return DotProduct(_vectorA, _vectorB) / (Magnitude(_vectorA) * Magnitude(_vectorB));
    }

    // Return the distance between the two vectors
    inline float Distance(sf::Vector2f _vectorA, sf::Vector2f _vectorB)
    {
        return sqrt(powf(_vectorB.x - _vectorA.x, 2) + powf(_vectorB.y - _vectorA.y, 2));
    }

    // Return the rotated vector
    inline sf::Vector2f Rotate(sf::Vector2f _vector, float _angle)
    {
        return sf::Vector2f(_vector.x * cos(_angle) - _vector.y * sin(_angle), _vector.x * sin(_angle) + _vector.y * cos(_angle));
    }

    // Return the vector with magnitude truncated to the given value
    inline sf::Vector2f Truncate(sf::Vector2f _vector, float _max)
    {
        if (Magnitude(_vector) > _max)
        {
            _vector = _vector * _max / Magnitude(_vector);
        }

        return _vector;
    }
}