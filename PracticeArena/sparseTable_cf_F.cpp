
#include <iostream>
#include <functional>

using namespace std;

/////////////////////////////////////////////////////////////////////////////
///             ACCEPTED
///     https://codeforces.com/contest/1454/problem/F
///
///     from each index i calculate the answer for the bucket size of 2^j
///     if the starting index L and R-L+1 = K
///     answer lying in [L][2^(k-1)], [L+2^(k-1)][k-1]
///////////////////////////////////////////////////////////////////////////////

const int N = 3 + 2e5;

template <typename T>
class SparseTable
{

        vector<vector<T>> spTable;
        vector<int> logb2;
        void preCalculateLogBase2(size_t maxLen)
        {
                logb2.resize(maxLen);
                logb2[1] = 0;
                for (int i = 2; i < maxLen; i++)
                {
                        logb2[i] = logb2[i >> 1] + 1;
                }
        }

        T f(T &a, T &b)
        {
                return make_pair(min(a.first, b.first), max(a.second, b.second));
        }

public:
        SparseTable(size_t maxLen)
        { /// len of the array
                preCalculateLogBase2(maxLen + 5);
                spTable.resize(logb2[maxLen] + 2, vector<T>(maxLen));
        }

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

        T query_impodent(int low, int high) // f(a)= x, then f(f(a))=x :: impodent function
        {
                int len = high - low + 1;
                if (low > high)
                        make_pair(-1, -1);
                int k = logb2[len];
                return f(spTable[k][low], spTable[k][high - (1 << k) + 1]);
        }

        T directAccess(int from, size_t powLength)
        {
                return spTable[powLength][from];
        }

        void directRawInput(size_t len)
        {
                for (int i = 0; i < len; i++)
                {
                        cin >> spTable[0][i].first;
                        spTable[0][i].second = spTable[0][i].first;
                }
        }
        T directRawAccess(int at_index)
        {
                return spTable[0][at_index];
        }
};

class BinarySearch
{
public:
        enum Comp
        {
                LEFT = -1,
                EQUAL = 0,
                RIGHT = 1
        };
        int lastOccurance(int low, int high, function<Comp(int)> comparetor)
        {
                int answer = -1;
                int left = low, right = high;
                while (low <= high)
                {
                        int mid = (low + high) >> 1;
                        int comp_val = comparetor(mid);
                        if (comp_val == EQUAL)
                        {
                                answer = mid;
                                low = mid + 1; // go right
                        }
                        else if (comp_val == LEFT) // go left
                        {
                                high = mid - 1;
                        }
                        else
                        {
                                low = mid + 1;
                        }
                }
                return answer;
        }
        int firstOccurance(int low, int high, function<Comp(int)> comparetor)
        {
                int answer = -1;
                int left = low, right = high;
                while (low <= high)
                {
                        int mid = (low + high) >> 1;
                        int comp_val = comparetor(mid);
                        if (comp_val == EQUAL)
                        {
                                answer = mid;
                                high = mid - 1; // go left
                        }
                        else if (comp_val == LEFT) // go left
                        {
                                high = mid - 1;
                        }
                        else
                        {
                                low = mid + 1;
                        }
                }
                return answer;
        }
};

int main()
{
        int n;
        int testCases;
        SparseTable<pair<int, int>> table(N);
        BinarySearch bSearch;
        cin >> testCases;
        while (testCases--)
        {
                cin >> n;
                int found = false;

                table.directRawInput(n);

                table.buildSpTable(n);

                int left = 0, right = n - 1;
                if (n == 3 && table.directRawAccess(0) == table.directRawAccess(1) && table.directRawAccess(0) == table.directRawAccess(2))
                {
                        found = true;
                        cout << "YES\n1 1 1\n";
                        continue;
                }
                for (int i = 0; i < n - 2; i++)
                {
                        left = i;
                        int p1 = table.query_impodent(0, i).second;

                        int R = bSearch.lastOccurance(i + 1, n - 2,
                                                      [&table, &i, &p1](int mid) -> BinarySearch::Comp
                                                      {
                                                              int p = table.query_impodent(i + 1, mid).first;
                                                              if (p == p1)
                                                                      return BinarySearch::Comp::EQUAL;
                                                              else if (p < p1)
                                                                      return BinarySearch::Comp::LEFT; // min is in decreasing order
                                                              else
                                                                      return BinarySearch::Comp::RIGHT;
                                                      });
                        int L = bSearch.firstOccurance(i + 1, n - 2,
                                                       [&table, &i, &p1](int mid) -> BinarySearch::Comp
                                                       {
                                                               int p = table.query_impodent(i + 1, mid).first;
                                                               if (p == p1)
                                                                       return BinarySearch::Comp::EQUAL;
                                                               else if (p < p1)
                                                                       return BinarySearch::Comp::LEFT; // min is in decreasing order
                                                               else
                                                                       return BinarySearch::Comp::RIGHT;
                                                       });

                        if (R == -1 || L == -1)
                                continue;

                        L = min(L + 1, n - 1);
                        R = min(R + 1, n - 1);

                        int answer = bSearch.firstOccurance(L, R,
                                                            [&table, &n, &p1](int mid) -> BinarySearch::Comp
                                                            {
                                                                    int p = table.query_impodent(mid, n - 1).second;
                                                                    if (p == p1)
                                                                            return BinarySearch::Comp::EQUAL;
                                                                    else if (p < p1)
                                                                            return BinarySearch::Comp::LEFT; // max is in increasing order
                                                                    else
                                                                            return BinarySearch::Comp::RIGHT;
                                                            });

                        if (answer == -1)
                                continue;

                        int p2 = table.query_impodent(i + 1, answer - 1).first;
                        int p3 = table.query_impodent(answer, n - 1).second;

                        if (p3 == p1 && p2 == p1)
                        {
                                found = true;
                                cout << "YES\n"
                                     << i + 1 << " " << answer - i - 1 << " " << n - answer << endl;
                                break;
                        }
                }

                if (!found)
                {
                        // no answer
                        cout << "NO\n";
                }
        }
        return 0;
}