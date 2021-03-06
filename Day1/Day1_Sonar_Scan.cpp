#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Function to get input from txt file
void get_input(ifstream& inputfile, vector<int>& input)
{

    inputfile.open("input.txt");
    if(inputfile.fail())
        cout << "Failed to open input" << endl;
    else
    {
        cout << "Input file opened successfully" << endl;
        int input_num;
        while(!inputfile.eof())
        {
            inputfile >> input_num;
            input.push_back(input_num);
        }
    }

    inputfile.close();
}

//Function compares current number with next number, if current number is smaller than next number then increase count
int compare (vector<int>& inputnumber)
{
    int count = 0;
    for(int index = 0; index < inputnumber.size() - 2; index++)
        if(inputnumber[index] < inputnumber[index+1])
            count++;
    return count;
}

//Function adds 3 numbers at a time, store results in a vector
//for example we have vector [1,2,3,4,5] then this function adds: 1,2,3 stores result in sum, then adds 2,3,4 stores result in sum, adds 3,4,5 stores results in sum
void three_sums(vector<int>& inputnumber, vector<int>& sum)
{
    for(int index = 0; index < inputnumber.size() - 2; index++)
    {
        int summation = 0;
        summation = inputnumber[index] + inputnumber[index+1] + inputnumber[index+2];
        sum.push_back(summation);
    }
}

int main()
{
    vector<int> input;
    vector<int> sum;
    ifstream inputfile;
    get_input(inputfile,input);
    three_sums(input,sum);
    cout << compare(sum) << endl;
}