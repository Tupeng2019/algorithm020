
#include<iostream>
#include<vector>
#include<algorithm>



using namespace std;

//283. move zeros --easy 移动0
class solution {
    void mocveZeroes(vector<int>& nums) {
        if(nums.empty())
            return ; 
        int j = 0; 
        for(int i = 0; i < nums.size(); i++) {
            if(nums[i] != 0)
                swap(nums[j ++], nums[i]);
        }
    }
};


//189. rotate array 旋转数组(medium)
// 1. 使用最简单的暴力法, 直接将最后一个数字向前交换位置就可以了
// O(n^2) 显示超出时间限制了

class Solution {
public: 
    void rotate(vector<int>& nums, int k ) {
        for (int i = 0; i < k % nums.size(); ++i) {
            for(int j = nums.size() - 1; j >0;--j ) {
                swap(nums[j], nums[j-1]);
            }
        }
    }
};

// 使用reverse(),函数进三次反转就可以了，使用了库函数，法当然也是可以自己编写函数的
class Solution {
public: 
    // 直接使用三次旋转就行了
    void rotate(vector<int>& nums, int k ) {
        if(nums.empty())
            return ; 
        if( k > nums.size())
            k = k % nums.size(); 
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin()+k);
        reverse(nums.begin() + k , nums.end());
    }
};
////////******** 这就是自己写的reverse函数，和前面的时间复杂度是差不多的
class Solution {
public: 
    // 直接使用三次旋转就行了
    void reverse(vector<int>& nums, int i , int j) {
        while(i < j) {
            swap( nums[i],  nums[j]);
            ++ i; 
            -- j; 
        }
    }

    void rotate(vector<int>& nums, int k ) {
        if(nums.empty())
            return ; 
        if( k > nums.size())
            k = k % nums.size(); 
        reverse(nums, 0 , nums.size()-1);
        reverse(nums, 0, k-1);
        reverse(nums, k, nums.size()-1);
    }
};




//88. merge sorted array(Easy) 合并两个有序的数组
// 直接合并然后排序， 时间复杂度O((n+m)log(n+m))
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        if(nums1.empty() && nums2.empty())
            return ; 
        for(int i = 0; i < n; ++i) {
            nums1[m +i ] = nums2[i];
        }
        sort(nums1.begin(), nums1.end());
        //return nums1; 
    }
};
 
// 可以降低时间复杂度为O(m+n)的做法，就是采用双指针
class Solution {
public:
    // 采用双指针就是从后面向前面进行操作
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int pos = n + m -1; 
        int i = m -1; 
        int j = n -1; 
        while( j >=0 && i >=0) 
            nums1[pos--] = nums1[i] >=nums2[j] ? nums1[i--]: nums2[j--];
        // 在考虑还有剩下的nums2
        while(j >=0) 
            nums1[pos--] = nums2[j --];
    } 
};


//1.two sum -easy(两数之和)
class Solution {
public:
// 暴力法 时间复杂度为O(n^2)
    vector<int> twoSum(vector<int>& nums, int target) {
        //vector<int>ans; 
        if(nums.empty())
            return {}; 
        for(int i= 0; i < nums.size()-1; ++i) {
            for(int j = i +1; j < nums.size(); ++j) {
                if(nums[i] + nums[j] == target)
                    return {i, j};
                }
            }
        return {}; 
    }
};


#include<map>
// 对上面的进行优化，使用map，时间复杂度为O(n)
class Solution {
public:
    vector<int> twoSum(vector<int>&nums, int target) {
        map<int, int>map_num; 
        for(int i = 0; i < nums.size(); ++i){
            auto it = map_num.find(target - nums[i]);
            if(it != map_num.end())
                return {it->second, i};
            map_num[nums[i]] = i; 
        }
        return  {};
    }
};


//66. plus one -easy 加一
// 时间复杂度为O(n)，空间复杂度为O(n)
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size(); 
        int i = n-1; 
        while(i >=0) {
            if(digits[i] != 9) {
                digits[i] +=1; 
                return digits;  
            }
            else {
                digits[i] = 0; 
                -- i; 
            }
        }
        vector<int>ans(n+1, 0);
        ans[0] = 1; 
        return ans;    
    }
};

// 使用STL函数，进行翻转, 时间复杂度还是为O(n)， reverse（）的时间复杂度为O(n)
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int n = digits.size(); 
        reverse(digits.begin(), digits.end()); 
        int i = 0; 
        digits[0]++; 
        while(digits[i] ==10) {
            digits[i] = 0; 
            ++ i; 
            if( i ==n) 
                digits.push_back(1);
            else 
                digits[i] += 1; 
        }
        reverse(digits.begin(), digits.end());
        return digits; 
    }
};


/***********************       队列                     ****************************/
//641. design circular daque - medium (设计循环双端队列)
class MyCircularDeque {
private:
    vector<int> arr;
    int front;
    int rear;
    int capacity;
public:
    MyCircularDeque(int k) {
        capacity = k + 1;
        arr.assign(capacity, 0);
        front = 0;
        rear = 0;
    }
    bool insertFront(int value) {
        if (isFull()) {
            return false;
        }
        front = (front - 1 + capacity) % capacity;
        arr[front] = value;
        return true;
    }
    bool insertLast(int value) {
        if (isFull()) {
            return false;
        }
        arr[rear] = value;
        rear = (rear + 1) % capacity;
        return true;
    }
    bool deleteFront() {
        if (isEmpty()) {
            return false;
        }
        // front 被设计在数组的开头，所以是 +1
        front = (front + 1) % capacity;
        return true;
    }
    //删除最后一个元素
    bool deleteLast() {
        if (isEmpty()) {
            return false;
        }
        // rear 被设计在数组的末尾，所以是 -1
        rear = (rear - 1 + capacity) % capacity;
        return true;
    }
    //从双端队列中获取前项
    int getFront() {
        if (isEmpty()) {
            return -1;
        }
        return arr[front];
    }
    //从双端队列中获取最后一个元素
    int getRear() {
        if (isEmpty()) {
            return -1;
        }
        // 当 rear 为 0 时防止数组越界
        return arr[(rear - 1 + capacity) % capacity];
    }
    //检查圆形双端队列是否为空。
    bool isEmpty() {
        return front == rear;
    }
    //检查圆形双端队列是否已满。
    bool isFull() {
        // 注意：这个设计是非常经典的做法
        return (rear + 1) % capacity == front;
    }
};


#include<stack>

//42. trappping rain water -Hard(接雨水)
// 利用栈
class Solution {
public:
    int trap(vector<int>& height) {
        int ans = 0, current = 0;
        stack<int>st;
        // 这里就是相当于维护一个单调减的栈，然后由此确定两个边界，进行中间的求解，就可以了
        while (current < height.size()) {
            while (!st.empty() && height[current] > height[st.top()]) {
                int top = st.top();
                st.pop();
                if (st.empty())
                    break;
                int distance = current - st.top() - 1;
                int bounded_height = min(height[current], height[st.top()]) - height[top];
                ans += distance * bounded_height;
            }
            st.push(current++);
        }
        return ans;
    }
};







