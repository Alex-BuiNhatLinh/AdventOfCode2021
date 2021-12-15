#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Function gets input from txt file. Gets direction first then steps. Store results in 2 vectors directions and stepsnum.
void get_input(vector<string>& directions, vector<int>& stepsnum, ifstream& inputfile)
{
    inputfile.open("input.txt");
    string dir;
    int steps;
    if (inputfile.fail())
        cout << "Failed to open input file" << endl;
    else
    {
        cout << "Inputfile opened successfully" << endl;
        while(!inputfile.eof())
        {
            inputfile >> dir >> steps;
            directions.push_back(dir);
            stepsnum.push_back(steps);
        }
    }
}

//Calculates the horizontal and depth and aim according to the directions.
//down x increases aim by x
//up x decreases aim by x
//forward x increase horizontal by x
//forward x increase depth by aim multiplied by x
//Returns horizontal*depth
int mult(vector<string>& direction, vector<int>& steps)
{
    int horizontal = 0;
    int depth = 0;
    int aim = 0;
    for(int i = 0; i < direction.size(); i++)
    {
        if(direction[i] == "forward")
        {
            horizontal += steps[i];
            depth += aim*steps[i];
        }
        if(direction[i] == "down")
            aim += steps[i];
        if (direction[i] == "up")
            aim -= steps[i];
    }

    return horizontal*depth;

}

int main()
{
    vector<string> direction;
    vector<int> steps;
    ifstream inputfile;
    get_input(direction,steps,inputfile);
    cout << mult(direction,steps) << endl;    
}