
#include <iostream>
#include <functional>
#include <vector>
using namespace std;

/////////////////////////////////////////////////////////////////////////////
///             InProgress
///     https://leetcode.com/problems/median-of-two-sorted-arrays/
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
        int lowerBound(int low, int high, function<Comp(int)> comparetor)
        {
                int ans = -1, mid;
                while (low <= high)
                {
                        mid = low + ((high - low) >> 1);
                        Comp action = comparetor(mid);
                        if (action == Comp::LEFT)
                        {
                                ans = mid;
                                low = mid + 1;
                        }
                        else
                        {
                                high = mid - 1;
                        }
                }
                return ans;
        }
        // int upperBound()//stricly less than 
        int countLessThan(int low, int high, function<Comp(int)> comparetor){
              return  lowerBound(low, high, comparetor) - low + 1;
        }
        
};

class Solution
{
public:
        double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
        {
                int totalSize = nums1.size() + nums2.size(), centerL, centerR,median = 0;
                centerL = totalSize >> 1;
                centerR = centerL;
                if (!(totalSize & 1))
                        centerL--;
                int low = 0, high = nums1.size() - 1, mid;
                while(low<=high){
                        mid = low + (high - low) / 2;
                        int l = 0, r = nums2.size() - 1, mid2;
                        int numberOfElementsLessThan = 0;
                        
                        while(l<=r){
                                mid2 = l + (r - l) / 2;
                                if(nums2[mid2]<nums1[mid]){
                                        numberOfElementsLessThan = mid2 + 1;
                                        l = mid2 + 1;
                                }else{
                                        r = mid2 - 1;
                                }
                        }
                        cout << "less than " << nums1[mid] << " is " << numberOfElementsLessThan << endl;

                        l = 0, r = nums2.size() - 1, mid2;
                        int numberOfElementsLessOrEqual = 0;
                        while(l<=r){
                                mid2 = l + (r - l) / 2;
                                if(nums2[mid2]<=nums1[mid]){
                                        numberOfElementsLessOrEqual = mid2 + 1;
                                        l = mid2 + 1;
                                }else{
                                        r = mid2 - 1;
                                }
                        }
                        cout << "less Equal " << nums1[mid] << " is " << numberOfElementsLessOrEqual << endl;
                        int numberOfEqual = nums2.size() - numberOfElementsLessOrEqual;
                        cout << "grater " << nums1[mid] << " is " << nums2.size()-numberOfEqual << endl;
                        int sortedStartPos = mid + numberOfElementsLessThan;
                        int sortedEndPos = mid + numberOfElementsLessOrEqual;
                        if(sortedStartPos>=centerL && sortedEndPos<= centerR)
                                median += nums1[mid];
                        if(sortedStartPos <centerL) {
                                low = mid + 1;
                        }else if(sortedEndPos > centerL){
                                high = mid - 1;
                        }
                }
                return median;
        }
};

int main()
{
        vector<int> num1 = {0, 0};
        vector<int> nums2 = {0, 0};
        Solution s;
        // printf("%0.5f\n", s.findMedianSortedArrays(num1, nums2));
        cout << s.findMedianSortedArrays(num1, nums2) << endl;
        return 0;
}