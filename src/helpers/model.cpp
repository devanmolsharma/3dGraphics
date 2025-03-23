#include <vector>
#include <math.h>
using namespace std;

struct vertex
{
    float x;
    float y;
    float z;
    int id;
};

struct triangle
{
    int p1;
    int p2;
    int p3;
    int id;
};

class Model
{
    vector<vertex> points;
    vector<triangle> triangles; // list of point ids that make up a triangle
    vector<vector<int>> faces;

public:
    Model(char *filename)
    {
        // load model from file
    }

    Model()
    {
        // load a cube
        points = {
            {0, 0, 0, 0},
            {1, 0, 0, 1},
            {1, 1, 0, 2},
            {0, 1, 0, 3},
            {0, 0, 1, 4},
            {1, 0, 1, 5},
            {1, 1, 1, 6},
            {0, 1, 1, 7},
        };

        triangles = {
            {0, 1, 2, 0}, {0, 2, 3, 1}, // Bottom face
            {4, 5, 6, 2},
            {4, 6, 7, 3}, // Top face
            {0, 1, 5, 4},
            {0, 5, 4, 5}, // Front face
            {1, 2, 6, 6},
            {1, 6, 5, 7}, // Right face
            {2, 3, 7, 8},
            {2, 7, 6, 9}, // Back face
            {3, 0, 4, 10},
            {3, 4, 7, 11} // Left face
        };

        faces = {
            {0, 1},  // Bottom face
            {2, 3},  // Top face
            {4, 5},  // Front face
            {6, 7},  // Right face
            {8, 9},  // Back face
            {10, 11} // Left face
        };
    }

    vector<vertex> getPoints()
    {
        return points;
    }

    vector<triangle> getTriangles()
    {
        return triangles;
    }

    vector<vector<int>> render2d(int width, int height, int size, int posx, int posy, int rotx, int roty, int rotz)
    {
        vector<vector<int>> result = vector<vector<int>>(height, vector<int>(width, 0));

        for (auto triangle : triangles)
        {
            auto p1 = points[triangle.p1];
            auto p2 = points[triangle.p2];
            auto p3 = points[triangle.p3];
            int face = 0;
            for (auto f : faces)
            {
                if (f[0] == triangle.id || f[1] == triangle.id)
                {
                    break;
                }
                face++;
            }

            vertex sizedP1, sizedP2, sizedP3;
            sizedP1.x = p1.x * size + posx + (height / 2);
            sizedP1.y = p1.y * size + posy + (width / 2);
            sizedP1.z = p1.z * size;
            sizedP1.id = p1.id * size;
            this->rotate(&sizedP1, rotx, roty, rotz);

            sizedP2.x = p2.x * size + posx + (height / 2);
            sizedP2.y = p2.y * size + posy + (width / 2);
            sizedP2.z = p2.z * size;
            sizedP2.id = p2.id * size;
            this->rotate(&sizedP2, rotx, roty, rotz);

            sizedP3.x = p3.x * size + posx + (height / 2);
            sizedP3.y = p3.y * size + posy + (width / 2);
            sizedP3.z = p3.z * size;
            sizedP3.id = p3.id * size;
            this->rotate(&sizedP3, rotx, roty, rotz);

            for (int y = 0; y < height; y++)
            {
                for (int x = 0; x < width; x++)
                {
                    if (this->isPointInTriangle(
                            x, y, sizedP1, sizedP2, sizedP3))
                    {
                        result[y][x] = face;
                    }
                }
            }
        }

        return result;
    }

private:
    bool isPointInTriangle(int px, int py, vertex p1, vertex p2, vertex p3)
    {
        // Check if the triangle is degenerate (all points are collinear)
        int area = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
        if (area == 0)
            return false;

        // Compute barycentric coordinates
        double denominator = ((p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y));
        double w1 = ((p2.y - p3.y) * (px - p3.x) + (p3.x - p2.x) * (py - p3.y)) / denominator;
        double w2 = ((p3.y - p1.y) * (px - p3.x) + (p1.x - p3.x) * (py - p3.y)) / denominator;
        double w3 = 1 - w1 - w2;

        // The point is inside the triangle if all barycentric coordinates are non-negative
        return (w1 >= 0) && (w2 >= 0) && (w3 > 0);
    }

    void rotate(vertex *v, float rotx, float roty, float rotz)
    {
        // Convert degrees to radians
        float radX = rotx * (M_PI / 180.0);
        float radY = roty * (M_PI / 180.0);
        float radZ = rotz * (M_PI / 180.0);

        // Store original values
        float originalX = v->x;
        float originalY = v->y;
        float originalZ = v->z;

        // Rotate around X-axis
        v->y = originalY * cos(radX) - originalZ * sin(radX);
        v->z = originalY * sin(radX) + originalZ * cos(radX);

        // Rotate around Y-axis
        originalX = v->x;
        originalZ = v->z;
        v->x = originalX * cos(radY) + originalZ * sin(radY);
        v->z = -originalX * sin(radY) + originalZ * cos(radY);

        // Rotate around Z-axis
        originalX = v->x;
        originalY = v->y;
        v->x = originalX * cos(radZ) - originalY * sin(radZ);
        v->y = originalX * sin(radZ) + originalY * cos(radZ);
    }
};