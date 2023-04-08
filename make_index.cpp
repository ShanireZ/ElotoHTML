#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <windows.h>
using namespace std;
struct Node
{
    string name;
    int rating, m_rating, c_contests, l_change, rank;
};
Node ns[100005];
int score[20] = {3000, 2500, 2000, 1700, 1400, 1200, 1000, -9999};
string sname[20] = {"王者", "大师", "钻石", "铂金", "黄金", "白银", "青铜", "黑铁"};
string GBK_2_UTF8(string gbkStr)
{
    string outUtf8 = "";
    int n = MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, NULL, 0);
    WCHAR *str1 = new WCHAR[n];
    MultiByteToWideChar(CP_ACP, 0, gbkStr.c_str(), -1, str1, n);
    n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
    char *str2 = new char[n];
    WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
    outUtf8 = str2;
    delete[] str1;
    str1 = NULL;
    delete[] str2;
    str2 = NULL;
    return outUtf8;
}
string UTF8_2_GBK(string utf8Str)
{
    string outGBK = "";
    int n = MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, NULL, 0);
    WCHAR *str1 = new WCHAR[n];
    MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), -1, str1, n);
    n = WideCharToMultiByte(CP_ACP, 0, str1, -1, NULL, 0, NULL, NULL);
    char *str2 = new char[n];
    WideCharToMultiByte(CP_ACP, 0, str1, -1, str2, n, NULL, NULL);
    outGBK = str2;
    delete[] str1;
    str1 = NULL;
    delete[] str2;
    str2 = NULL;
    return outGBK;
}
void find_pos(string str, int &pos)
{
    while (str[pos] != ',') // 当前积分读取
    {
        pos++;
    }
}
void print_cls(string str, string cls)
{
    if (cls == GBK_2_UTF8("王者"))
    {
        cout << "\t\t\t<td>";
        cout << " <span class=\"" << GBK_2_UTF8("王者") << "\">" << str.substr(0, 3) << "</span>";
        cout << "<span class=\"" << GBK_2_UTF8("大师") << "\">" << str.substr(3) << "</span>";
        cout << " </td>\n";
    }
    else
    {
        cout << "\t\t\t<td class=\"" << cls << "\">" << str << "</td>\n";
    }
}
int main()
{
    int MX = 0;
    cout << "Print the num of players : ";
    cin >> MX;
    freopen("index.html", "w", stdout);
    // 直接提供算法生成的all_players.csv原文件即可,无需调整
    freopen("all_players.csv", "r", stdin);
    stringstream ss;
    string s;
    cin >> s; // 跳过csv表头
    for (int i = 1; i <= MX; i++)
    {
        cin >> s;
        int pos = 0, last = 0;
        // 当前排位读取
        find_pos(s, pos);
        ss << s.substr(last, pos - last);
        ss >> ns[i].rank;
        ss.clear(), last = ++pos;
        // 当前积分读取
        find_pos(s, pos);
        ss << s.substr(last, pos - last);
        ss >> ns[i].rating;
        ss.clear(), last = ++pos;
        // 最高积分读取
        find_pos(s, pos);
        ss << s.substr(last, pos - last);
        ss >> ns[i].m_rating;
        ss.clear(), last = ++pos;
        // 跳过
        find_pos(s, pos), last = ++pos;
        find_pos(s, pos), last = ++pos;
        // 参赛数量读取
        find_pos(s, pos);
        ss << s.substr(last, pos - last);
        ss >> ns[i].c_contests;
        ss.clear(), last = ++pos;
        // 跳过
        find_pos(s, pos), last = ++pos;
        find_pos(s, pos), last = ++pos;
        find_pos(s, pos), last = ++pos;
        // 积分变动读取
        find_pos(s, pos);
        ss << s.substr(last, pos - last);
        ss >> ns[i].l_change;
        ss.clear(), last = ++pos;
        // 学员姓名读取
        ns[i].name = s.substr(last);
        if (ns[i].rating == ns[i - 1].rating && i > 1)
        {
            ns[i].rank = ns[i - 1].rank;
        }
    }
    // 输出网页头部
    freopen("pre.txt", "r", stdin), cin.clear();
    while (getline(cin, s))
    {
        cout << s << "\n";
    }
    // 输出学员信息
    for (int i = 1; i <= MX; i++)
    {
        string cls, m_cls, lc = GBK_2_UTF8(ns[i].l_change >= 0 ? "上分" : "掉分");
        for (int j = 0; j < 8; j++)
        {
            if (m_cls.empty() && ns[i].m_rating >= score[j])
            {
                m_cls = GBK_2_UTF8(sname[j]);
            }
            if (ns[i].rating >= score[j])
            {
                cls = GBK_2_UTF8(sname[j]);
                break;
            }
        }
        cout << "\t\t<tr align=\"center\">\n";
        cout << "\t\t\t<td>" << ns[i].rank << "</td>\n";
        print_cls(ns[i].name, cls);
        print_cls(cls, cls);
        cout << "\t\t\t<td>" << ns[i].rating << "</td>\n";
        cout << "\t\t\t<td class=\"" << lc << "\">" << ns[i].l_change << "</td>\n";
        cout << "\t\t\t<td>" << ns[i].c_contests << "</td>\n";
        cout << "\t\t\t<td>" << ns[i].m_rating << "</td>\n";
        print_cls(m_cls, m_cls);
        cout << "\t\t</tr>\n";
    }
    // 输出网页尾部
    freopen("suf.txt", "r", stdin), cin.clear();
    while (getline(cin, s))
    {
        cout << s << "\n";
    }
    return 0;
}