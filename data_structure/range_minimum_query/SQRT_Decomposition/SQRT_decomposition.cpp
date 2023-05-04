#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

///////////////////////////////////////////////////////////////
///////  ACCEPTED   [307. Range Sum Query - Mutable]
////// https://leetcode.com/problems/range-sum-query-mutable/
//////////////////////////////////////////////////////////////

class NumArray
{
public:
    int maxSegment;
    vector<vector<int>> blocks;
    vector<int> arr;
    NumArray(vector<int> &nums)
    {
        arr = nums;
        maxSegment = sqrt(nums.size()) + 1;

        blocks = vector<vector<int>>(maxSegment);
        sqrt_decompose();
    }
    void sqrt_decompose()
    {
        for (int i = 0; i < arr.size(); i += maxSegment)
        {
            for (int j = 0, sum = 0; j < maxSegment && i + j < arr.size(); j++)
            {
                sum += arr[i + j];
                blocks[(i + j) / maxSegment].emplace_back(sum);
            }
        }
    }

    void update(int index, int val)
    {
        int segment = index / maxSegment, oldVal = arr[index];
        arr[index] = val;
        index %= maxSegment;

        while (index < blocks[segment].size())
            blocks[segment][index++] += val - oldVal;
    }

    int sumRange(int left, int right)
    {
        int leftSegment = left / maxSegment, rightSegment = right / maxSegment;
        left %= maxSegment, right %= maxSegment;

        if (leftSegment == rightSegment)
        {
            return blocks[leftSegment][right] - (left > 0 ? blocks[leftSegment][left - 1] : 0);
        }
        else
        {
            int sum = 0;
            sum += blocks[leftSegment][blocks[leftSegment].size() - 1] - (left > 0 ? blocks[leftSegment][left - 1] : 0);
            sum += blocks[rightSegment][right];

            while (++leftSegment < rightSegment)
                sum += blocks[leftSegment][blocks[leftSegment].size() - 1];

            return sum;
        }
    }
};

int main()
{
    vector<int> nums{1, 3, 5};
    NumArray *obj = new NumArray(nums);
    int param_2 = obj->sumRange(0, 2);
    cout << param_2 << endl;
    obj->update(1, 2);
    param_2 = obj->sumRange(0, 2);
    cout << param_2 << endl;
    return 0;
}

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */