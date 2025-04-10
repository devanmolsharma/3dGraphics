#include <iostream>
#include "./helpers/model.cpp"
#include <unistd.h>

using namespace std;
int main(int argc, char const *argv[])
{
    string filename = "skull.obj";
    auto model = Model(filename);
    int i = 0;
    while (true)
    {
        string render = "";
        int angle = i % 360;
        vector cameraVector = vector<float>{
            0, 0, 1};
        vector<vector<DrawnPoint>> result = vector<vector<DrawnPoint>>(100, vector<DrawnPoint>(100, {{0, 0, 0}, -INFINITY}));
        model.render2d(&result, 40, 0, 0, 0, angle, 180);
        // model.render2d(&result, 20, 0, -30, 20, angle, 0);
        // model.render2d(&result, 20, 0, 30, 20, 20, angle);
        // return 0;
        for (auto x : result)
        {
            for (auto y : x)
            {
                string base = "";
                if (y.normal.size() >= 3 && y.normal[0] + y.normal[1] + y.normal[2] != 0)
                {
                    double dotProd = cameraVector[0] * y.normal[0] + cameraVector[1] * y.normal[1] + cameraVector[2] * y.normal[2];
                    int color = (int)(dotProd * 100);
                    if (color > 100)
                    {
                        color = 100;
                    }
                    base = "\033[38;2;" + to_string(color) + ";" + to_string(color) + ";" + to_string(color) + "m";
                    base += "█";
                }
                else
                {
                    base = " ";
                }
                render.append(base);
            }
            render.append("\n");
        }
        cout << "\033[2J\033[1;1H";
        cout << render;
        i++;
        usleep(1000);
    }

    return 0;
}
