
#include <iostream>

using namespace std;

const int LOG = 17;
const int N = 3 + 2e5;
pair<int, int> spTable[LOG][N];

pair<int, int> f(pair<int, int> &a, pair<int, int> &b)
{
        return make_pair(min(a.first, b.first), max(a.second, b.second));
}
int logb2[N];
void buildSpTable(int n)
{
        for (int j = 1; j <= logb2[n]; j++)
        {
                for (int i = 0; i + (1 << j) <= n; i++)
                {
                        spTable[j][i] = f(spTable[j - 1][i], spTable[j - 1][i + (1 << (j - 1))]);
                }
        }
}

pair<int, int> query(int low, int high)
{
        int len = high - low + 1;
        int k = logb2[len];
        return f(spTable[k][low], spTable[k][high - (1 << k) + 1]);
}

int main()
{
        int n;
        int testCases;
        logb2[1] = 0;
        for (int i = 2; i < N; i++)
        {
                logb2[i] = logb2[i >> 1] + 1;
        }
        cin >> testCases;
        while (testCases--)
        {
                cin >> n;
                for (int i = 0; i < n; i++)
                {
                        cin >> spTable[0][i].first;
                        spTable[0][i].second = spTable[0][i].first;
                }
                buildSpTable(n);
                int left = 0, right = n - 1;
                while (left < right)
                {
                        int p1 = query(0, left).second;
                        int p3 = query(right, n - 1).second;
                        // cout << "left " << left << " right " << right << "p1 " << p1 << " p3 " << p3 << endl;
                        if (p1 < p3)
                                left++;
                        else if (p1 > p3)
                                right--;
                        else
                        {
                                int p2 = query(left + 1, right - 1).first;
                                if (p2 == p1)
                                {
                                        left++, right++;
                                        break;
                                }
                                int notChanged = true;

                                while (left + 1 < right && spTable[0][left + 1].first < p1)
                                        left++, notChanged = false;

                                while (right - 1 > left && spTable[0][right - 1].first < p1)
                                        right--, notChanged = false;
                                if (notChanged)
                                        left++;
                                // cout << "left " << left << " right " << right << " p1 " << p1 << " p2 " << p2 << " p3 " << p3 << endl;
                        }
                }
                if (right <= left + 1)
                {
                        // no answer
                        cout << "NO\n";
                }
                else
                {
                        // x=left,y=right-left+1,z=n-right+1
                        cout << "YES\n"
                             << left << " " << right - left - 1 << " " << n - right + 1 << endl;
                }
        }
        return 0;
}