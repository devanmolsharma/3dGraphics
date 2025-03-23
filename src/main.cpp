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
        system("clear");
        int angle = i % 180;
        auto rendered = model.render2d(100, 100, 25, 0, 0, angle, angle, angle);
        string colors[] = {"\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m", "\033[37m"};

        for (auto x : rendered)
        {
            for (auto y : x)
            {
                if (y > 0)
                {
                    cout << colors[y % 7] << "██";
                }
                else
                {
                    cout << " ";
                }
            }
            printf("\n");
        }
        i++;
        usleep(100000);
    }

    return 0;
}
