
#include <iostream>
#include <math.h>

using namespace std;

/////////////////////////////////////////////////////////////////////////////
///             ACCEPTED
///     https://www.spoj.com/problems/THRBL/
///
///     from each index i calculate the answer for the bucket size of 2^j
///     if the starting index L and R-L+1 = K
///     answer lying in [L][2^(k-1)], [L+2^(k-1)][k-1]
///////////////////////////////////////////////////////////////////////////////

const int N = 1 + 1e5;
const int LOG = 17; /// for standard problem, LOG=17 is enough
int spTable[LOG][N];

int f(int a, int b)
{
        return max(a, b);
}

void build_SpTable(size_t n) /// assuming spTable[0][...] contains the original array
{
        for (int j = 1; j <= LOG; j++)
        {
                for (int i = 0; i + (1 << j) <= n; i++)
                {
                        spTable[j][i] = f(spTable[j - 1][i], spTable[j - 1][i + (1 << (j - 1))]);
                }
        }
}

int query(int low, int high) /// inclusive range, 0-based index
{
        int len = high - low + 1;
        int answer = 1 << 31;
        for (int i = LOG; i >= 0; i--)
        {
                if (len & (1 << i))
                {
                        answer = f(answer, spTable[i][low]);
                        low += (1 << i);
                }
        }
        return answer;
}

int main()
{

        int n, q, l, r;
        cin >> n >> q;
        for (int i = 0; i < n; i++)
        {
                cin >> spTable[0][i];
        }

        build_SpTable(n);

        int answer = 0;
        while (q--)
        {

                cin >> l >> r;
                if (l > r)
                        swap(l, r);
                l--, r--; // make 0-based index
                l++, r--; // not [A,B] , problem says between means (A,B)
                answer += r < l ? 1 : (query(l, r) <= spTable[0][l - 1]);
        }
        cout << answer << endl;
        return 0;
}