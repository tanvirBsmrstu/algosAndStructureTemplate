
#include <iostream>
#include <vector>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
///             ACCEPTED
///     https://leetcode.com/problems/search-insert-position/
///
///////////////////////////////////////////////////////////////////////////////

class Solution
{
public:
        int searchInsert(vector<int> &nums, int target)
        {
                int l = 0, r = nums.size() - 1, ans = nums.size();
                while (l <= r)
                {
                        int mid = l + ((r - l) >> 1);
                        if (nums[mid] >= target)
                        {
                                ans = mid;
                                r = mid - 1;
                                if (nums[mid] == target)
                                        return mid;
                        }
                        else
                        {
                                l = mid + 1;
                        }
                }
                return ans;
        }
};
