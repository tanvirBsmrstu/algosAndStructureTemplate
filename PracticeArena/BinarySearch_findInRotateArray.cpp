
#include <iostream>
#include <functional>
#include <vector>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
///             ACCEPTED
///     https://leetcode.com/problems/search-in-rotated-sorted-array/
///
///////////////////////////////////////////////////////////////////////////////

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
                        int mid = low + ((high - low) >> 1);
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
                        int mid = low + ((high - low) >> 1);
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

class Solution
{
public:
        int search(vector<int> &nums, int target)
        {
                int k = 0;
                for (int i = 1; i < nums.size(); i++)
                {
                        if (nums[i - 1] > nums[i])
                        {
                                k = i;
                                break;
                        }
                }
                BinarySearch bs;
                // clang-format off
                int ans = bs.firstOccurance(0, k - 1, [&target, &nums](int mid) -> BinarySearch::Comp {
                                if(nums[mid] == target ) return BinarySearch::Comp::EQUAL;
                                else if (nums[mid]< target) return BinarySearch::Comp::RIGHT;
                                else return BinarySearch::Comp::LEFT; 
                });

                if (ans == -1)
                        ans = bs.firstOccurance(k, nums.size() - 1, [&target, &nums](int mid) -> BinarySearch::Comp {
                                if(nums[mid] == target ) return BinarySearch::Comp::EQUAL;
                                else if (nums[mid]< target) return BinarySearch::Comp::RIGHT;
                                else return BinarySearch::Comp::LEFT; 
                        });
                // clang-format on
                return ans;
        }
};