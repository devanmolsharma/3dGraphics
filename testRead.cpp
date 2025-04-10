#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
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
        buffer = c;
    }

    if (buffer.length())
    {
        splitted.push_back(buffer);
    }

    return splitted;
}

int main(int argc, char const *argv[])
{
    string fileName = "./mesh.obj";
    // Create a text string, which is used to output the text file

    string myText;
    vector triangles = vector<vector<int>>({});
    vector vertices = vector<vector<float>>({});

    // Read from the text file
    ifstream MyReadFile(fileName);
    // Use a while loop together with the getline() function to read the file line by line
    while (getline(MyReadFile, myText))
    {
        // Output the text from the file
        // cout << myText << endl;
        if (myText.length() > 0 && myText.at(0) == 'f')
        {

            size_t ind1 = myText.find('/');
            int size = ind1 - 2;
            int f1 = atoi(myText.substr(2, size).c_str());
            size_t spaceInd = myText.find(' ', 2);
            size_t slashInd = myText.find('/', spaceInd);
            int f2 = atoi(myText.substr(spaceInd + 1, slashInd - spaceInd - 1).c_str());
            size_t spaceInd2 = myText.find(' ', spaceInd + 1);
            size_t slashInd2 = myText.find('/', spaceInd2);
            int f3 = atoi(myText.substr(spaceInd2 + 1, slashInd2 - spaceInd2 - 1).c_str());
            triangles.push_back(vector<int>({f1, f2, f3}));
        }
        else if (myText.length() > 0 && myText.at(0) == 'v' && myText.at(1) == ' ')
        {
            auto splitted = split(myText, ' ');
            float p1 = atof(splitted[1].c_str());
            float p2 = atof(splitted[2].c_str());
            float p3 = atof(splitted[3].c_str());
            vertices.push_back(vector<float>({p1, p2, p3}));
        }
    }
    cout << triangles.size() << endl;
    cout << vertices.size() << endl;

    // Close the file
    MyReadFile.close();
    return 0;
}