///////////////////////////////////////////////////////////////
///////  ACCEPTED
////// https://leetcode.com/problems/sort-an-array/
//////////////////////////////////////////////////////////////

#include <vector>
#include <iostream>

using namespace std;

class Solution
{
public:
    vector<int> sortArray(vector<int> &nums)
    {
        int maxValue = -(1 << 30), minValue = (1 << 30), maxDigit = 0;

        for (int num : nums)
            minValue = min(minValue, num);

        for (int i = 0; i < nums.size(); i++) // making all numbers positive where minValue is negative, since indexing using negative numbers is not possible
            nums[i] -= minValue;

        for (int num : nums)
            maxValue = max(maxValue, num);

        while (maxValue > 0)
            maxDigit++, maxValue /= 10;

        for (int step = 1, exp = 1; step <= maxDigit; exp *= 10, step++)
        {
            int frequency[10] = {0};
            for (int i = 0; i < nums.size(); i++)
            {
                int digit = (nums[i] / exp) % 10;
                frequency[digit]++;
            }

            for (int i = 1; i < 10; i++)
                frequency[i] += frequency[i - 1];

            vector<int> auxArray(nums.size());
            for (int i = nums.size() - 1; i >= 0; i--)
            {
                int digit = (nums[i] / exp) % 10;
                auxArray[--frequency[digit]] = nums[i];
            }
            nums = auxArray;
        }

        for (int i = 0; i < nums.size(); i++) // retrieving original number
            nums[i] += minValue;

        return nums;
    }
};
/*
int main()
{
    vector<int> nums{5, 7, -9, 11, 69, 121, 25, 79};
    Solution s;
    auto ret = s.sortArray(nums);
    cout << endl;
    for (int i = 0; i < ret.size(); i++)
        cout << ret[i] << "  ";
}
*/