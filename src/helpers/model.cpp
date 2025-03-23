#include <vector>
#include <math.h>
using namespace std;

struct Vertex
{
    float x;
    float y;
    float z;
    int id;
};

struct Triangle
{
    int p1;
    int p2;
    int p3;
    int id;
};

struct face
{
    vector<int> triangles;
    string color;
};

struct DrawnPoint
{
    string color;
    float z;
};

class Model
{
    vector<Vertex> points;
    vector<Triangle> triangles; // list of point ids that make up a Triangle
    vector<face> faces;

public:
    Model(char *filename)
    {
        // load model from file
    }

    Model()
    {
        // load a cube
        points = {
            {-0.5, -0.5, -0.5, 0},
            {0.5, -0.5, -0.5, 1},
            {0.5, 0.5, -0.5, 2},
            {-0.5, 0.5, -0.5, 3},
            {-0.5, -0.5, 0.5, 4},
            {0.5, -0.5, 0.5, 5},
            {0.5, 0.5, 0.5, 6},
            {-0.5, 0.5, 0.5, 7},
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
            {{0, 1}, "\033[31m█"},  // Bottom face (Red)
            {{2, 3}, "\033[32m█"},  // Top face (Green)
            {{4, 5}, "\033[33m█"},  // Front face (Yellow)
            {{6, 7}, "\033[34m█"},  // Right face (Blue)
            {{8, 9}, "\033[35m█"},  // Back face (Magenta)
            {{10, 11}, "\033[36m█"} // Left face (Cyan)
        };
    }

    vector<Vertex> getPoints()
    {
        return points;
    }

    vector<Triangle> getTriangles()
    {
        return triangles;
    }

    void render2d(vector<vector<DrawnPoint>> *screen, int size, int posx, int posy, int rotx, int roty, int rotz)
    {
        // vector<vector<DrawnPoint>> result = vector<vector<DrawnPoint>>(height, vector<DrawnPoint>(width, {" ", -INFINITY}));
        int height = screen->size();
        int width = screen->at(0).size();
        float aspect = (float)width / (float)height;
        for (auto face : faces)
        {
            vector<Triangle> faceTriangles;

            // get all the triangles for a face
            for (auto triangleId : face.triangles)
            {
                faceTriangles.insert(faceTriangles.begin(), triangles[triangleId]);
            }

            for (auto Triangle : faceTriangles)
            {
                auto p1 = points[Triangle.p1];
                auto p2 = points[Triangle.p2];
                auto p3 = points[Triangle.p3];

                Vertex sizedP1, sizedP2, sizedP3;
                Vertex rotatedP1 = p1;
                Vertex rotatedP2 = p2;
                Vertex rotatedP3 = p3;

                // take all vertices and rotate them accordingly
                this->rotate(&rotatedP1, rotx, roty, rotz);
                this->rotate(&rotatedP2, rotx, roty, rotz);
                this->rotate(&rotatedP3, rotx, roty, rotz);

                // then scale them and center them in the screen
                sizedP1.x = rotatedP1.x * size + (height / 2) + posx;
                sizedP1.y = rotatedP1.y * size + (width / 2) + posy;
                sizedP1.z = rotatedP1.z * size;
                sizedP1.id = rotatedP1.id * size;

                sizedP2.x = rotatedP2.x * size + (height / 2) + posx;
                sizedP2.y = rotatedP2.y * size + (width / 2) + posy;
                sizedP2.z = rotatedP2.z * size;
                sizedP2.id = rotatedP2.id * size;

                sizedP3.x = rotatedP3.x * size + (height / 2) + posx;
                sizedP3.y = rotatedP3.y * size + (width / 2) + posy;
                sizedP3.z = rotatedP3.z * size;
                sizedP3.id = rotatedP3.id * size;

                // get the normal vector, and the distance from origin
                auto normal = this->getNormalVector(sizedP1, sizedP2, sizedP3);

                if (normal[0] + normal[1] + normal[2] == 0)
                {
                    continue;
                }

                for (int y = 0; y < height; y++)
                {
                    for (int x = 0; x < width; x++)
                    {
                        if (this->isPointInTriangle(
                                x, y, sizedP1, sizedP2, sizedP3))
                        {
                            if (normal[2] == 0)
                            {
                                continue;
                            }
                            // use the normal vector to get the z-coordinate and if it is greater than the exisiting one at this point x,y, replace it whtn the new point
                            float z = (normal[3] - normal[0] * x - normal[1] * y) / (normal[2]);
                            if (z > screen->at(y)[x].z)
                            {
                                screen->at(y)[x] = DrawnPoint({face.color,
                                                               z});
                            }
                        }
                    }
                }
            }
        }
    }

private:
    bool isPointInTriangle(int px, int py, Vertex p1, Vertex p2, Vertex p3)
    {
        // Check if the Triangle is degenerate (all points are collinear)
        int area = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);
        if (area == 0)
            return false;

        // Compute barycentric coordinates
        double denominator = ((p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y));
        double w1 = ((p2.y - p3.y) * (px - p3.x) + (p3.x - p2.x) * (py - p3.y)) / denominator;
        double w2 = ((p3.y - p1.y) * (px - p3.x) + (p1.x - p3.x) * (py - p3.y)) / denominator;
        double w3 = 1 - w1 - w2;

        // The point is inside the Triangle if all barycentric coordinates are non-negative
        return (w1 >= 0) && (w2 >= 0) && (w3 > 0);
    }

    vector<float> getNormalVector(Vertex p1, Vertex p2, Vertex p3)
    {
        auto AB = vector<float>({p2.x - p1.x,
                                 p2.y - p1.y,
                                 p2.z - p1.z});

        auto AC = vector<float>({p3.x - p1.x,
                                 p3.y - p1.y,
                                 p3.z - p1.z});

        auto cross = this->crossProduct(
            AB, AC);
        float magnitude = getMagnitude(cross);

        if (magnitude == 0)
        {
            return vector<float>(
                {0,
                 0,
                 0,
                 0});
        }
        cross[0] /= magnitude;
        cross[1] /= magnitude;
        cross[2] /= magnitude;

        auto d = cross[0] * p1.x + cross[1] * p1.y + cross[2] * p1.z;
        return vector<float>(
            {cross[0],
             cross[1],
             cross[2],
             d});
    }

    vector<float> crossProduct(vector<float> a, vector<float> b)
    {
        return vector<float>({a[1] * b[2] - a[2] * b[1],
                              a[2] * b[0] - a[0] * b[2],
                              a[0] * b[1] - a[1] * b[0]});
    }

    float getMagnitude(vector<float> v)
    {
        return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    }

    void rotate(Vertex *v, float rotx, float roty, float rotz)
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