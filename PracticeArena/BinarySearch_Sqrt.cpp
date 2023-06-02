
#include <iostream>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
///             ACCEPTED
///     https://leetcode.com/problems/sqrtx/
///
///////////////////////////////////////////////////////////////////////////////

class Solution
{
public:
        int mySqrt(int x)
        {
                int l = 0, r = x, ans = -1;
                while (l <= r)
                {
                        long long mid = l + (r - l) / 2;
                        if (mid * mid <= x)
                        {
                                ans = mid;
                                l = mid + 1;
                        }
                        else
                        {
                                r = mid - 1;
                        }
                }
                return ans;
        }
};

// int main()
// {
//         Solution s;
//         int res = s.mySqrt(8);
//         cout << res << endl;
// }