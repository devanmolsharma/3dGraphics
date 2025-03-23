#include <iostream>
#include "./helpers/model.cpp"
#include <unistd.h>

using namespace std;
int main(int argc, char const *argv[])
{
    auto model = Model();
    int i = 0;
    while (true)
    {
        string render = "";
        int angle = i % 360;
        vector<vector<DrawnPoint>> result = vector<vector<DrawnPoint>>(100, vector<DrawnPoint>(100, {" ", -INFINITY}));
        model.render2d(&result, 20, 0, 0, angle, 20, 0);
        model.render2d(&result, 20, 0, -30, 20, angle, 0);
        model.render2d(&result, 20, 0, 30, 20, 20, angle);

        for (auto x : result)
        {
            for (auto y : x)
            {

                render.append(y.color);
            }
            render.append("\n");
        }
        cout << "\033[2J\033[1;1H";
        cout << render;
        i++;
        usleep(10000);
    }

    return 0;
}
