///////////////////////////////////////////////////////////////
///////  ACCEPTED
////// https://leetcode.com/problems/query-kth-smallest-trimmed-number/
//////////////////////////////////////////////////////////////

#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Solution
{
public:
    vector<int> smallestTrimmedNumbers(vector<string> &nums, vector<vector<int>> &queries)
    {
        int maxDigit = nums[0].size();

        vector<vector<int>> sortedState(maxDigit + 1, vector<int>(nums.size()));

        for (int i = 0; i < nums.size(); i++)
            sortedState[0][i] = i;

        for (int step = 1; step <= maxDigit; step++)
        {
            int frequency[10] = {0};
            for (int i = 0; i < nums.size(); i++)
            {
                int digit = nums[sortedState[step - 1][i]][maxDigit - step] - '0';
                frequency[digit]++;
            }

            for (int i = 1; i < 10; i++)
                frequency[i] += frequency[i - 1];

            for (int i = nums.size() - 1; i >= 0; i--)
            {
                int digit = nums[sortedState[step - 1][i]][maxDigit - step] - '0';
                sortedState[step][--frequency[digit]] = sortedState[step - 1][i];
            }
        }
        vector<int> answer;
        for (auto q : queries)
        {
            int k = q[0], trimPos = q[1];
            k--; // given k is 1-indexed
            // string trimSubstr=nums[sortedState[trimPos][k]].substr(nums[sortedState[trimPos][k]].size()-trimPos,trimPos);
            answer.push_back(sortedState[trimPos][k]);
        }
        return answer;
    }
};

// int main()
// {
//     vector<string> nums{"102", "473", "251", "814"};
//     vector<vector<int>> q{{1, 1}, {2, 3}, {4, 2}, {1, 2}};
//     Solution s;
//     auto ret = s.smallestTrimmedNumbers(nums, q);
//     cout << endl;
//     for (int i = 0; i < ret.size(); i++)
//         cout << ret[i] << "  ";
// }