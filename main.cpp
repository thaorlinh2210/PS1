
#include <iostream>
#include <cmath>

#include "Matrix3x3.h"

void testProblem1()
{
    Matrix3x3 M(Vector3D(2.0f, 3.0f, 8.0f),
        Vector3D(6.0f, 0.0f, -3.0f),
        Vector3D(-1.0f, 3.0f, 2.0f));

    std::cout << "Test matrix M:" << std::endl;
    std::cout << M << std::endl;

    // test multiplication

    std::cout << "M * M = " << std::endl;
    std::cout << M * M << std::endl;

    // test determinate

    std::cout << "det M = " << M.det() << std::endl;

    // test hasInverse

    std::cout << "Has M a inverse? " << (M.hasInverse() ? "Yes" : "No") << std::endl;

    // test transpose
    std::cout << "transpose of M:" << std::endl;
    std::cout << M.transpose() << std::endl;

    // test inverse
    std::cout << "inverse of M:" << std::endl;
    std::cout << M.inverse() << std::endl;

    std::cout << "inverse of M * 45:" << std::endl;
    std::cout << M.inverse() * 45.0f << std::endl;
}

#include <fstream>

#include "Polygon.h"

int testProblem2(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Arguments missing." << std::endl;
        std::cerr << "Usage: VectorOperations <filename>" << std::endl;

        // return failure, not enough arguments
        return 1;
    }

    // create text input stream connected to file named in argv[1]
    std::ifstream lInput(argv[1], std::ifstream::in);

    // operation can fail
    if (!lInput.good())
    {
        std::cerr << "Cannot open input file: " << argv[1] << std::endl;

        return 2;    // program failed (cannot open input)
    }

    Polygon lPolygon;

    lPolygon.readData(lInput);

    // close input file
    lInput.close();

    std::cout << "Signed area: " << lPolygon.getSignedArea() << std::endl;

    Matrix3x3 lRotate = Matrix3x3::rotate(90.0f);

    Polygon lRotatedPolygon = lPolygon.transform(lRotate);

    std::cout << "Signed area of rotated polygon: " << lRotatedPolygon.getSignedArea() << std::endl;

    for (size_t i = 0; i < lRotatedPolygon.getNumberOfVertices(); i++)
    {
        if ((std::round(lPolygon.getVertex(i).dot(lRotatedPolygon.getVertex(i) * 10.0f) / 10.0f) != 0.0f))
        {
            std::cout << "Rotation error of vertex " << lPolygon.getVertex(i) << std::endl;

            return 3;
        }
    }

    std::cout << "Polygon transformation successful." << std::endl;

    return 0;
}

int main(int argc, char* argv[])
{
        testProblem1();

        return testProblem2(argc, argv);
}
    

