
// COS30008, Tutorial 2, 2023

#include "Polygon.h"

#include <cassert>

Polygon::Polygon() noexcept :
    fNumberOfVertices()
{}

void Polygon::readData( std::istream& aIStream )
{
    // read input file containing 2D vector data
    // if no data can be read, then exit loop
    // lInput >> lVectors[lIndex] evaluates to false on EOF
    while ( aIStream >> fVertices[fNumberOfVertices] )
    {
        fNumberOfVertices++;
    }
}

size_t Polygon::getNumberOfVertices() const noexcept
{
    return fNumberOfVertices;
}

const Vector2D& Polygon::getVertex( size_t aIndex ) const
{
    assert( aIndex < fNumberOfVertices );

    return fVertices[aIndex];
}

float Polygon::getPerimeter() const noexcept
{
    float Result = 0.0f;

    // There have to be at least three vertices
    if ( fNumberOfVertices > 2 )
    {
        // solution without modulus and explicit temporary variables
        for ( size_t i = 1; i < fNumberOfVertices; i++ )
        {
            Result += (fVertices[i] - fVertices[i - 1]).length();
        }

        Result += (fVertices[0] - fVertices[fNumberOfVertices - 1]).length();
    }

    return Result;
}

Polygon Polygon::scale( float aScalar ) const noexcept
{
    Polygon Result = *this;
    
    for ( size_t i = 0; i < fNumberOfVertices; i++ )
    {
        Result.fVertices[i] = fVertices[i] * aScalar;
    }
    
    return Result;
}


//*********************Problem set 1 extension**************************

float Polygon::getSignedArea() const noexcept {
    float area = 0.0f;
    for (int i = 0; i < fNumberOfVertices; i++) {
        Vector2D v1 = fVertices[i];
        Vector2D v2 = fVertices[(i+1)% fNumberOfVertices];
        //The magnitude of the cross product is equal to 
        //the area of the parallelogram formed by the two vectors

        area += v1.cross(v2);

   }
    area *= 0.5f;
    return area;
}

Polygon Polygon::transform(const Matrix3x3& aMatrix) const noexcept {
    Polygon transformedPolygon;
    for (size_t i = 0; i < fNumberOfVertices; i++) {
        transformedPolygon.fNumberOfVertices = fNumberOfVertices;
        const Vector2D& point = getVertex(i);
        Vector3D vector = Vector3D(point.x(), point.y(), 1.0f);
        // Transform the vertex using matrix-vector multiplication
        Vector3D vector2 = aMatrix * vector;
        // Convert the transformed vertex back to a 2D vector
        transformedPolygon.fVertices[i] = Vector2D(vector2.x(), vector2.y());
    }
 
    // Store the transformed vertex in the new polygon
    return transformedPolygon;
}
