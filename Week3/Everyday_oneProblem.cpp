#include<iostream>

using namespace std; 

#include<vector>

// 34. 在排序数组中查找元素的第一个出现的位置和最后一个出现的位置
// ->1, 使用二分查找的方式
//2. 利用常规的二分法进行计算
class Solution {
public:
//1.Times 
    // 常规的二分查找
    int Find_F_position(vector<int>& nums, int target) {
        int n = nums.size(); 
        int left = 0; 
        int right = n -1; 
        while(left < right) {
            int mid = left + (right - left) /2; 
            if(nums[mid] <target)
                left = mid +1; 
            else if( nums[mid] == target)
                right = mid; 
            else 
                right = mid -1; 
        }
        if(nums[left] != target)
            return -1; 
        return left; 
    }
    int Find_R_position(vector<int>& nums, int target) {
        int n = nums.size();
        int left = 0;
        int right = n - 1;
        while (left < right) {
            int mid = left + (right - left + 1) / 2;
            if (nums[mid] > target) {
                right = mid - 1;
            } else if (nums[mid] == target){
                left = mid;
            } else {
                // nums[mid] < target
                left = mid + 1;
            }
        }
        if (nums[right] != target) {
            return -1;
        }
        return right;
    }
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size(); 
        if(n ==0)
            return {-1, -1};
        int first = Find_F_position(nums, target);
        if(first == -1) 
            return {-1, -1};
        int right = Find_R_position(nums, target);
        return {first,right};
    }
};

//-> 2
class Solution { 
public:
    int binarySearch(vector<int>& nums, int target, bool lower) {
        int left = 0, right = (int)nums.size() - 1, ans = (int)nums.size();
        while (left <= right) {
            int mid = (left + right) / 2;
            if (nums[mid] > target || (lower && nums[mid] >= target)) {
                right = mid - 1;
                ans = mid;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        int leftIdx = binarySearch(nums, target, true);
        int rightIdx = binarySearch(nums, target, false) - 1;
        if (leftIdx <= rightIdx && rightIdx < nums.size() && nums[leftIdx] == target && nums[rightIdx] == target) {
            return vector<int>{leftIdx, rightIdx};
        } 
        return vector<int>{-1, -1};
    }
}; 


//12.02 
// 321. (Hard) 拼接最大数
class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> result;
        int size1 = nums1.size();
        int size2 = nums2.size();
        for( int i = 0;i <= size1;i++ )//从第一个数组中取 i 个元素
        {
            if( i > k ) break;//最多取 k 个
            if(  size2 >= k -i )//第二个数组中能取够剩余元素
            {
                vector<int> vec1 = getMax(nums1,i);
                vector<int> vec2 = getMax(nums2,k-i);
                vector<int> res = meger2vec(vec1,vec2);
                result = max(result,res);
            }
        }
        return result;
    }
    //从数组中取 k 位数字，并保持相对顺序，使其构成的数字最大
    vector<int> getMax(vector<int>& nums1,int k)
    {
        //要使数字最大，就使从左到右每一位尽可能的最大，即单调递减

        vector<int> result;//返回结果
        int size = nums1.size();
        int remain = size -k;//允许丢弃的元素个数
        for( auto &num : nums1)
        {
            //如果下个元素值比当前位置的值大，则可以选择舍弃当前元素
            //但可舍弃的元素个数小于 1 时，表示不能再舍弃元素了，只能添加
            while( result.size() > 0 && remain > 0 && num > result.back() )
            {
                remain--;//允许舍弃的元素个数减一
                result.pop_back();//末尾删除元素
            }
            if( result.size() < k ) //未取够k个，添加到末尾
            {
                result.push_back(num) ;
            }
            else//已经取够了k个，直接丢弃
            {
                remain--;
            }    
        }
        return result;
    }
    //合并两个递减数组,使结果保存递减,并且构成的数字最大
     vector<int> meger2vec(vector<int>& nums1,vector<int>& nums2)
     {
         //当两个位置数值一样时，要接着比较下一位，以使下一位尽可能的大
         vector<int> result;
         int size1 = nums1.size();
         int size2 = nums2.size();
         int i = 0;
         int j = 0;
         while( i < size1 && j < size2)
         {
             //哪个大取哪个，当前位置相同就继续比较下一位
             //if( vector<int>(nums1.begin()+i,nums1.end()) > vector<int>(nums2.begin()+j,nums2.end()) )
             if( !lexicographical_compare(nums1.begin()+i,nums1.end(),nums2.begin()+j,nums2.end()) )
             {
                 result.push_back(nums1[i]);
                 i++;
             }
             else
             {
                 result.push_back(nums2[j]);
                 j++;
             }
         }
         //拷贝剩余元素到结果数组
         copy(nums1.begin()+i,nums1.end(),back_inserter(result));
         copy(nums2.begin()+j,nums2.end(),back_inserter(result));
         return result;
     }
};



//12.03
//204. 计数质数
//1.Times
/* 使用暴力的方法进行求解，时间复杂度为O(n^2) */ 
class Solution {
public:
// 1.Times
// 质数就是他的因数只有1和本身的数,直接使用暴力法
    // 先判断是不是质数，这里的时间复杂度就位O(n^2)，时间复杂度这里是分析错了，应该是O(n根号n）
    bool IsPrime(int x) {
        for(int i = 2; i *i <= x; ++i) {
            if(x % i ==0)
                return false; 
        }
        return true;
    }
    int countPrimes(int n) {
        int counts = 0; 
        for(int i = 2; i< n; ++i) {
            counts += IsPrime(i);
        }
        return counts; 
    }
};

// 使用埃氏筛， 时间复杂度就位O(nlognlogn)
class Solution {
public:

    int countPrimes(int n) {
        vector<int>IsPrime(n, 1); 
        int counts = 0; 
        for(int i = 2; i < n; ++i) {
            if(IsPrime[i]) {
                counts +=1; 
                if((long long)i *i < n) { //这里的类型需要转换，因为i*i的数可能是超过int的范围
                    for(int j = i *i; j < n; j +=i) {
                        IsPrime[j] = 0; 
                    }
                }
            }
        }
        return counts; 
    }
};


//12.04 
//659. 分割数组为连续的子序列









//12.05 
//621. 任务调度器











//12.06 
//118. 杨辉三角
class Solution {
public:
// 这里的时间复杂度就是为O(n^2)
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ret(numRows);
        for (int i = 0; i < numRows; ++i) {
            ret[i].resize(i + 1);
            ret[i][0] = ret[i][i] = 1;
            for (int j = 1; j < i; ++j) {
                ret[i][j] = ret[i - 1][j] + ret[i - 1][j - 1];
            }
        }
        return ret;
    }
};

























