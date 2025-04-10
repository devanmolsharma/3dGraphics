#include <vector>
#include <math.h>
#include <fstream>
using namespace std;

vector<string> split(string s, char splitBy)
{
    vector<string> splitted = {};
    string buffer = "";
    for (char c : s)
    {
        if (c == splitBy)
        {
            splitted.push_back(buffer);
            buffer = "";
            continue;
        }
        buffer += c;
    }

    if (buffer.length())
    {
        splitted.push_back(buffer);
    }

    return splitted;
}

struct Vertex
{
    double x;
    double y;
    double z;
};

struct Triangle
{
    int p1;
    int p2;
    int p3;
};

struct DrawnPoint
{
    vector<double> normal;
    double z;
};

class Model
{
    vector<Vertex> points;
    vector<Triangle> triangles; // list of point ids that make up a Triangle

public:
    Model(string filename)
    {
        // Create a text string, which is used to output the text file

        string myText;
        triangles = vector<Triangle>({});
        points = vector<Vertex>({});
        float max_x = -INFINITY;
        float max_y = -INFINITY;
        float max_z = -INFINITY;

        // Read from the text file
        ifstream MyReadFile(filename);
        // Use a while loop together with the getline() function to read the file line by line
        while (getline(MyReadFile, myText))
        {
            // Output the text from the file
            // cout << myText << endl;
            if (myText.length() > 0 && myText.at(0) == 'f')
            {

                auto splitted = split(myText, ' ');
                auto f1 = atoi(splitted[1].substr(0, splitted[1].find('/')).c_str()) - 1;
                auto f2 = atoi(splitted[2].substr(0, splitted[2].find('/')).c_str()) - 1;
                auto f3 = atoi(splitted[3].substr(0, splitted[3].find('/')).c_str()) - 1;
                triangles.push_back(Triangle({f1, f2, f3}));
                if (splitted.size() == 5)
                {
                    auto f4 = atoi(splitted[4].substr(0, splitted[4].find('/')).c_str()) - 1;
                    triangles.push_back(Triangle({f3, f4, f1}));
                }
                if (splitted.size() == 6)
                {
                    auto f4 = atoi(splitted[4].substr(0, splitted[4].find('/')).c_str()) - 1;
                    auto f5 = atoi(splitted[5].substr(0, splitted[5].find('/')).c_str()) - 1;
                    triangles.push_back(Triangle({f3, f4, f5}));
                    triangles.push_back(Triangle({f3, f4, f1}));
                }
            }
            else if (myText.length() > 0 && myText.at(0) == 'v' && myText.at(1) == ' ')
            {
                auto splitted = split(myText, ' ');
                double p1 = atof(splitted[1].c_str());
                double p2 = atof(splitted[2].c_str());
                double p3 = atof(splitted[3].c_str());
                points.push_back(Vertex({p1, p2, p3}));
                if (p1 > max_x)
                {
                    max_x = p1;
                }
                if (p2 > max_y)
                {
                    max_y = p2;
                }
                if (p3 > max_z)
                {
                    max_z = p3;
                }
            }
        }

        // normalize the points
        for (int i = 0; i < points.size(); i++)
        {
            points[i].x = points[i].x / max_x;
            points[i].y = points[i].y / max_y;
            points[i].z = points[i].z / max_z;
        }

        // Close the file
        MyReadFile.close();
    };

    Model()
    {
        // load a cube
        points = {
            {-7.2539186, 26.294434, 1.2700961},
            {-0.015071035, 14.069983, 1.2700955},
            {7.2527227, 26.294464, 1.2700961},
            {3.2791958, 26.399958, 1.2700961},
            {-3.2791948, 26.39996, 1.2700961},
            {5.6286306, 41.93597, 1.2700968},
            {0, 37.092697, 1.2700965},
            {-5.6286306, 41.93597, 1.2700968},
            {0, 37.55496, -1.2700957},
            {
                0,
                37.55496,
                1.2700965,
            },
            {
                6.11639,
                42.81794,
                1.2700968,
            },
            {
                6.11639,
                42.81794,
                -1.2700955,
            },
            {
                -3.6849577,
                26.73971,
                -1.2700962,
            },
            {
                -3.6849577,
                26.73971,
                1.2700961,
            },
            {
                -6.11639,
                42.81794,
                1.2700968,
            },
            {
                -6.11639,
                42.81794,
                -1.2700955,
            },
            {
                0,
                37.092697,
                -1.2700957,
            },
            {
                5.6286306,
                41.93597,
                -1.2700955,
            },
            {
                3.2791958,
                26.39996,
                -1.2700962,
            },
            {
                -5.6286306,
                41.93597,
                -1.2700955,
            },
            {
                -3.2791948,
                26.399958,
                -1.2700962,
            },
            {
                7.2527227,
                26.294466,
                -1.2700962,
            },
            {
                -7.2539186,
                26.294434,
                -1.2700962,
            },
            {
                -0.015071111,
                14.069981,
                -1.2700968,
            },
            {
                7.859196,
                26.628887,
                -1.2700962,
            },
            {
                7.859196,
                26.628887,
                1.2700961,
            },
            {
                -0.015671963,
                13.383301,
                1.2700955,
            },
            {
                -0.015671963,
                13.3833,
                -1.2700968,
            },
            {
                -0.015671963,
                13.3833,
                -1.2700968,
            },
            {
                -0.015671963,
                13.383301,
                1.2700955,
            },
            {
                -7.859196,
                26.628887,
                1.2700961,
            },
            {
                -7.859196,
                26.628887,
                -1.2700962,
            },
            {
                3.6849585,
                26.73971,
                -1.2700962,
            },
            {
                3.6849585,
                26.739708,
                1.2700961,
            },
            {
                6.11639,
                42.81794,
                -1.2700955,
            },
            {
                6.11639,
                42.81794,
                1.2700968,
            },
            {
                -6.11639,
                42.81794,
                -1.2700955,
            },
            {
                -6.11639,
                42.81794,
                1.2700968,
            },
            {
                -6.11639,
                42.81794,
                1.2700968,
            },
            {
                -3.6849577,
                26.73971,
                1.2700961,
            },
            {
                -3.2791948,
                26.39996,
                1.2700961,
            },
            {
                -5.6286306,
                41.93597,
                1.2700968,
            },
            {
                -7.859196,
                26.628887,
                1.2700961,
            },
            {
                -7.2539186,
                26.294434,
                1.2700961,
            },
            {
                -0.015671963,
                13.383301,
                1.2700955,
            },
            {
                -0.015071035,
                14.069983,
                1.2700955,
            },
            {
                7.859196,
                26.628887,
                1.2700961,
            },
            {
                7.2527227,
                26.294464,
                1.2700961,
            },
            {
                3.6849585,
                26.739708,
                1.2700961,
            },
            {
                3.2791958,
                26.399958,
                1.2700961,
            },
            {
                6.11639,
                42.81794,
                1.2700968,
            },
            {
                5.6286306,
                41.93597,
                1.2700968,
            },
            {
                0,
                37.55496,
                1.2700965,
            },
            {
                0,
                37.092697,
                1.2700965,
            },
            {
                -6.11639,
                42.81794,
                -1.2700955,
            },
            {
                0,
                37.55496,
                -1.2700957,
            },
            {
                0,
                37.092697,
                -1.2700957,
            },
            {
                -5.6286306,
                41.93597,
                -1.2700955,
            },
            {
                6.11639,
                42.81794,
                -1.2700955,
            },
            {
                5.6286306,
                41.93597,
                -1.2700955,
            },
            {
                3.6849585,
                26.73971,
                -1.2700962,
            },
            {
                3.2791958,
                26.39996,
                -1.2700962,
            },
            {
                7.859196,
                26.628887,
                -1.2700962,
            },
            {
                7.2527227,
                26.294466,
                -1.2700962,
            },
            {
                -0.015671963,
                13.3833,
                -1.2700968,
            },
            {
                -0.015071111,
                14.069981,
                -1.2700968,
            },
            {
                -7.859196,
                26.628887,
                -1.2700962,
            },
            {
                -7.2539186,
                26.294434,
                -1.2700962,
            },
            {
                -3.6849577,
                26.73971,
                -1.2700962,
            },
            {-3.2791948, 26.399958, -1.2700962},
        };

        triangles = {
            {0, 1, 2},
            {0, 2, 3},
            {4, 0, 3},
            {4, 3, 5},
            {4, 5, 6},
            {7, 4, 6},
            {8, 9, 10},
            {10, 11, 8},
            {12, 13, 14},
            {14, 15, 12},
            {16, 17, 18},
            {19, 16, 18},
            {20, 19, 18},
            {20, 18, 21},
            {22, 20, 21},
            {22, 21, 23},
            {24, 25, 26},
            {26, 27, 24},
            {28, 29, 30},
            {30, 31, 28},
            {32, 33, 25},
            {25, 24, 32},
            {31, 30, 13},
            {13, 12, 31},
            {34, 35, 33},
            {33, 32, 34},
            {36, 37, 9},
            {9, 8, 36},
            {38, 39, 40},
            {40, 41, 38},
            {39, 42, 43},
            {43, 40, 39},
            {42, 44, 45},
            {45, 43, 42},
            {44, 46, 47},
            {47, 45, 44},
            {46, 48, 49},
            {49, 47, 46},
            {48, 50, 51},
            {51, 49, 48},
            {50, 52, 53},
            {53, 51, 50},
            {52, 38, 41},
            {41, 53, 52},
            {54, 55, 56},
            {56, 57, 54},
            {55, 58, 59},
            {59, 56, 55},
            {58, 60, 61},
            {61, 59, 58},
            {60, 62, 63},
            {63, 61, 60},
            {62, 64, 65},
            {65, 63, 62},
            {64, 66, 67},
            {67, 65, 64},
            {66, 68, 69},
            {69, 67, 66},
            {68, 54, 57},
            {57, 69, 68},
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
        double aspect = (double)width / (double)height;

        for (int i = 0; i < this->triangles.size(); i++)
        {
            auto triangle = this->triangles[i];
            auto p1 = points[triangle.p1];
            auto p2 = points[triangle.p2];
            auto p3 = points[triangle.p3];

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

            sizedP2.x = rotatedP2.x * size + (height / 2) + posx;
            sizedP2.y = rotatedP2.y * size + (width / 2) + posy;
            sizedP2.z = rotatedP2.z * size;

            sizedP3.x = rotatedP3.x * size + (height / 2) + posx;
            sizedP3.y = rotatedP3.y * size + (width / 2) + posy;
            sizedP3.z = rotatedP3.z * size;

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
                        double z = (normal[3] - normal[0] * x - normal[1] * y) / (normal[2]);
                        if (z > screen->at(y)[x].z)
                        {
                            screen->at(y)[x] = DrawnPoint({normal, // face.color,
                                                           z});
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

    vector<double> getNormalVector(Vertex p1, Vertex p2, Vertex p3)
    {
        auto AB = vector<double>({p2.x - p1.x,
                                  p2.y - p1.y,
                                  p2.z - p1.z});

        auto AC = vector<double>({p3.x - p1.x,
                                  p3.y - p1.y,
                                  p3.z - p1.z});

        auto cross = this->crossProduct(
            AB, AC);
        double magnitude = getMagnitude(cross);

        if (magnitude == 0)
        {
            return vector<double>(
                {0,
                 0,
                 0,
                 0});
        }
        cross[0] /= magnitude;
        cross[1] /= magnitude;
        cross[2] /= magnitude;

        auto d = cross[0] * p1.x + cross[1] * p1.y + cross[2] * p1.z;
        return vector<double>(
            {cross[0],
             cross[1],
             cross[2],
             d});
    }

    vector<double> crossProduct(vector<double> a, vector<double> b)
    {
        return vector<double>({a[1] * b[2] - a[2] * b[1],
                               a[2] * b[0] - a[0] * b[2],
                               a[0] * b[1] - a[1] * b[0]});
    }

    double getMagnitude(vector<double> v)
    {
        return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
    }

    void rotate(Vertex *v, double rotx, double roty, double rotz)
    {
        // Convert degrees to radians
        double radX = rotx * (M_PI / 180.0);
        double radY = roty * (M_PI / 180.0);
        double radZ = rotz * (M_PI / 180.0);

        // Store original values
        double originalX = v->x;
        double originalY = v->y;
        double originalZ = v->z;

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