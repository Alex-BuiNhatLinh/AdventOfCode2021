#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Gets input from txt file as strings, stores in vector binary
void get_input(ifstream& inputfile, vector<string>& binary)
{
    string bin;
    inputfile.open("input.txt");
    if (inputfile.fail())
        cout << "Failed to open inputfile" << endl;
    else
    {
        cout << "File opened successfully" << endl;
        while(!inputfile.eof())
        {
            inputfile >> bin;
            binary.push_back(bin);
        }
    }

    inputfile.close();
}

//Calculates the power consumption
//Gamma and epsilon is calculated by counting 1s and 0s vertically
//If 1s is more than 0s, append 1 to gamma and 0 to epsilon, if 0s is more than 1s then append 0 to gamma and 1 to epsilon
int power_consumption (vector<string>& binary)
{
    int count_1 = 0;
    int count_0 = 0;
    string gamma;
    string epsilon;
    for (int column = 0; column < binary[0].length(); column++)
    {
        for(int row = 0; row < binary.size(); row++)
        {
            if (binary[row][column] == '1')
                count_1++;

            if (binary[row][column] == '0')
                count_0++;
        }

        if (count_1 < count_0)
        {
            gamma += "0";
            epsilon += "1";
        }
        else
        {
            gamma += "1";
            epsilon += "0";
        }
        count_1 = 0;
        count_0 = 0;
    }
    return stoi(gamma,0,2)*stoi(epsilon,0,2);
}

//Calculates oxygen rating recursively by updating vector binary and column
//Counts 1s and 0s vertically. 
//If 1s occurs more than 0s in that column, then delete the elements in binary that has 0 in that column.
//If 0s occurs more than 1s in that column, then delete the elements in binary that has 1 in that column.
//If occurence of 0s and 1s are the same in that column, then only keep the elements that have 1 in that column
//Repeat this until there is only 1 element left inside binary vector.
int oxygen_rating(vector<string>& binary, int column)
{
    int count_1 = 0;
    int count_0 = 0;
    
    if (binary.size() == 1)
        return stoi(binary[0],0,2);
    if (column == binary[0].length())
        return 0;
    else
    {
        for(int row = 0; row < binary.size(); row++)
        {
            if (binary[row][column] == '1')
                count_1++;
            else
                count_0++;
        }

        if (count_0 <= count_1)
        {
            for(int i = binary.size() - 1; i >= 0; i--)
            {
                if(binary[i][column] == '0')
                {
                    binary.erase(binary.begin()+i);                
                }
            }
        }
        else
        {
            for(int x = binary.size() - 1; x >= 0; x--)
            {
                if(binary[x][column] == '1')
                    binary.erase(binary.begin()+x);
            }
        }
        return oxygen_rating(binary, column + 1);
    }
}

//Does the same as oxygen_rating but the other way round.
int co2_rating(vector<string>& binary, int column)
{
    int count_1 = 0;
    int count_0 = 0;
    
    if (binary.size() == 1)
        return stoi(binary[0],0,2);
    if (column == binary[0].length())
        return 0;
    else
    {
        for(int row = 0; row < binary.size(); row++)
        {
            if (binary[row][column] == '1')
                count_1++;
            else
                count_0++;
        }

        if (count_0 <= count_1)
        {
            for(int i = binary.size() - 1; i >= 0; i--)
            {
                if(binary[i][column] == '1')
                {
                    binary.erase(binary.begin()+i);                
                }
            }
        }
        else
        {
            for(int x = binary.size() - 1; x >= 0; x--)
            {
                if(binary[x][column] == '0')
                    binary.erase(binary.begin()+x);
            }
        }
        return co2_rating(binary, column + 1);
    }
}

int main()
{
    vector<string> binary;
    vector<string> binary1;
    ifstream inputfile;
    get_input(inputfile, binary);
    binary1 = binary;
    cout << oxygen_rating(binary,0)*co2_rating(binary1,0) << endl;
}