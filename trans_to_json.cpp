#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <windows.h>
#include <ctime>
using namespace std;
struct Node
{
    string name;
    int lrk, hrk, score;
    bool operator<(const Node oth) const
    {
        if (score == oth.score)
        {
            return name < oth.name;
        }
        return score > oth.score;
    }
};
Node ns[100005];
int main()
{
    int MX = 0, utime = time(0);
    double wgt = 0;
    cout << "Print the num of players : ";
    cin >> MX;
    string id;
    cout << "Print the ID of contest : ";
    cin >> id;
    cout << "Print the weight of contest : ";
    cin >> wgt;
    // name, score
    // csv文件需要按照上述顺序提供数据
    freopen("result.csv", "r", stdin);
    freopen("xxx.json", "w", stdout);
    string s;
    cin >> s;
    for (int i = 1; i <= MX; i++)
    {
        cin >> s;
        int pos = 0, last = 0;
        while (s[pos] != ',')
        {
            pos++;
        }
        ns[i].name = s.substr(last, pos - last);
        stringstream ss;
        ss << s.substr(pos + 1);
        ss >> ns[i].score;
    }
    sort(ns + 1, ns + 1 + MX);
    int pos = 0, ok = 0;
    for (int i = 1; i <= MX; i++)
    {
        if (ns[i].score == ns[i - 1].score)
        {
            if (ok == 0)
            {
                pos = i - 1, ok = 1;
            }
        }
        else
        {
            if (ok == 1)
            {
                for (int j = pos; j < i; j++)
                {
                    ns[j].lrk = pos, ns[j].hrk = i - 1;
                }
                ok = 0;
            }
            ns[i].lrk = ns[i].hrk = i;
        }
        if (i == MX && ok == 1)
        {
            for (int j = pos; j <= i; j++)
            {
                ns[j].lrk = pos, ns[j].hrk = i;
            }
        }
    }
    cout << "{\n";
    cout << "\t\"name\": \"" << id << "\",\n";
    cout << "\t\"time_seconds\": " << utime << ",\n";
    cout << "\t\"weight\": " << wgt << ",\n";
    cout << "\t\"standings\": [\n";
    for (int i = 1; i <= MX; i++)
    {
        cout << "\t\t[\n";
        cout << "\t\t\t\"" << ns[i].name << "\",\n";
        cout << "\t\t\t" << ns[i].lrk << ",\n";
        cout << "\t\t\t" << ns[i].hrk << "\n";
        if (i != MX)
        {
            cout << "\t\t],\n";
        }
        else
        {
            cout << "\t\t]\n";
        }
    }
    cout << "\t]\n";
    cout << "}\n";
    return 0;
}