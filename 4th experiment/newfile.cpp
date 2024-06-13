#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cmath>
using namespace std;
double cal_entropy(double yesc, double noc)
{
    double totalc = yesc + noc;

    double entropy = 0.0;
    if (totalc > 0)
    {
        double yesprob = yesc / totalc;
        double noprob = noc / totalc;

        if (yesprob > 0)
        {
            entropy -= yesprob * log2(yesprob);
        }
        if (noprob > 0)
        {
            entropy -= noprob * log2(noprob);
        }
    }
    return entropy;
}

double calculate_info_gain(map<string, int> &parentCounts, map<string, map<string, int>> &childCounts)
{
    double yesc = parentCounts["yes"];
    double noc = parentCounts["no"];
    double totalp = yesc + noc;

    double parentEntropy = cal_entropy(yesc, noc);
    cout << "parent entropy is:" << parentEntropy << endl;

    double childEntropy = 0.0;
    for (auto it = childCounts.begin(); it != childCounts.end(); ++it)
    {
        string childName = it->first;
        double yesc = it->second["yes"];
        double noc = it->second["no"];
        double totalchild = yesc + noc;

        double childEpart = cal_entropy(yesc, noc);

        childEntropy += (totalchild / totalp) * childEpart;
    }

    cout << "weighted child entrpy:" << childEntropy << endl;

    double infogain = parentEntropy - childEntropy;
    cout << "Information gain :" << infogain << endl;

    return infogain;
}

int main()
{

    ifstream file("input.csv");

    string line, outlook, temprature, humidity, value;
    map<string, int> parentcount;
    map<string, map<string, int>> childcount;

    if (!file.is_open())
    {
        cerr << "Error while opening file" << endl;
        return -1;
    }

    int i = 0;
    string childn;
    int ch = 0;

    while (getline(file, line))
    {
        stringstream str(line);
        getline(str, outlook, ',');
        getline(str, temprature, ',');
        getline(str, humidity, ',');
        getline(str, value, ',');

        if (i == 0)
        {
            i++;
            cout << "Child column names are:" << endl;
            cout << "1.Day  2.Level 3. Routine  4.Value" << endl;
            cout << "Enter child column number for which you want to calculate info gain" << endl;
            cin >> ch;

            continue;
        }

        switch (ch)
        {
        case 1:
            childn = outlook;
            break;

        case 2:
            childn = temprature;
            break;

        case 3:
            childn = humidity;
            break;

        case 4:
            childn = value;
            break;

        default:
            childn = outlook;
            break;
        }

        parentcount[value]++;
        childcount[childn][value]++;
    }

    double info_gain_res = calculate_info_gain(parentcount, childcount);

    cout << "Information gain for selected attribute is:" << info_gain_res << endl;

    return 0;
}