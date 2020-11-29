#include<iostream>
#include<vector>
#include<algorithm>



using namespace std;

                     /*****************     Array       ****************/
//11. container with most water 盛最多水的容器
class Solution {
public:
    // 使用左右夹逼的方法(类似双指针的方式)
    // 此时的时间复杂度为O(n)
    int maxArea(vector<int>& height) {
        int max_Area = 0; 
        if(height.empty())
            return max_Area; 
        int n = height.size() ; 
        int j = n -1; 
        int i = 0; 
        while(i < j) {
            int min_h = height[i] < height[j] ? height[i++] : height[j--];
            max_Area = max(max_Area, min_h * (j -i +1));  // 这里是需要对i或者j进行加一的操作，因为前面对i进行了++，后面对j进行了--
        }
        return max_Area; 
    }
};


//70. climbing stairs 爬梯子
class Solution {
public:
    // 1. 使用递归函数进行求解
    // 此时是超出时间的限制
    int climbStairs(int n) {
        if(n ==1)
            return 1; 
        else if(n == 2)
            return 2; 
        else 
            return climbStairs(n -1) + climbStairs(n - 2); 
    }
};
/* 对上面的进行优化，不使用递归函数
直接使用中间变量，保存钱两个变量 */
class Solution {
public:
// 时间复读为O(n)
    int climbStairs(int n) {
        if(n <= 0)
            return 0; 
        if(n ==1)
            return 1; 
        if(n ==2)
            return 2; 
        int a = 1, b = 2; 
        int c = 0; 
        for(int i = 3; i <=n; ++i) {
            c = a + b; 
            a = b; 
            b = c; 
        }
        return c; 
    }
};


//15. 3sum 3数之和
/* 最开始的思路，没有考虑都重复性，同时也灭有考虑都双指针的意思，导致没有输出，因为这里只是应用了一个指针的移动 */
// 不正确的解法
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        // 使用排序+ 双指针的方式：
        vector<vector<int>>ans; 
        if(nums.empty())    
             return ans; 
        int n = nums.size(); 
        //int k= 0; 
        int j = n -1, i = 1; 
        // 对数组进行排序
        sort(nums.begin(), nums.end());
        for(int k = 0; k < n-2; ++ k) {
            while(i < j) {
                int sum_2 = nums[j] + nums[i];
                if(nums[k] + sum_2 ==0)
                    ans.push_back({nums[k], nums[i], nums[j]});
                else if( nums[k] +sum_2 < 0)
                    ++ i; 
                else 
                    -- j; 
            }
        }
        return ans; 
    }
};

// 修正后的答案
class Solution {
public:
    // 这里的时间复杂度为O(n^2)
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans; 
        if(nums.empty())
            return ans; 
        sort(nums.begin(), nums.end()); 
        int n = nums.size(); 
        for(int k =0; k < n-2; ++k) {
            int i = k +1; 
            int j = n -1; 
            // 去重
            if(nums[k] >0)
                return ans; 
            if( k >0 && nums[k] == nums[k -1])
                continue; 
            while(i < j) {
                
                if( nums[k] + nums[i] + nums[j] < 0 )
                    ++ i; 
                else if (nums[k] + nums[i] + nums[j] > 0)
                    -- j; 
                else {
                    ans.push_back({nums[k], nums[i], nums[j]});
                    // 这里就是去重的
                    while(i < j && nums[i] == nums[i +1])
                        ++ i ; 
                    while( i < j && nums[j] == nums[j-1])
                        -- j; 
                    // 当没有重复的时候u，就是需要对i，j进行同时的收缩
                    ++ i; 
                    -- j; 
                } 
            }
        }
       return ans; 
    }
};


//26. remove duplicates from sorted array 删除排序数组中的重复项、
class Solution {
public:
// 时间为O(n)，双指针（快慢），也就是最后是截取的数组的前面没有重复的部分
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty())
            return 0; 
        int j = 0; 
        for(int i = 0; i < nums.size()-1; ++i) {
            if(nums[i] != nums[i +1]) {
                nums[++ j] = nums[i +1];
            }
        }
        return j +1; 
    }
};


/***********************           Linked list 链表         ******************************************/

//Definition for singly-linked list.
struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};


//206. reverse linked list -easy 翻转链表
// 时间复杂度就为O(n)
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* cur = NULL, *pre = head;
        while (pre != NULL) {
            ListNode* t = pre->next;
            pre->next = cur;
            cur = pre;
            pre = t;
        }
        return cur;
    }
};


//24. swap nodes in pairs - medium -两两交换链表中的节点
// 使用递归的方式进行,此时的时间复杂度为O(n)， 需要对每一个节点进行遍历
// 空间复杂度也为O(n)，
class Solution {
public:
    ListNode* swapPairs( ListNode* head) {
        if(head == nullptr || head-> next == nullptr) {
            return head; 
        }
        ListNode* newhead = head->next; 
        head ->next = swapPairs(newhead -> next);
        newhead ->next = head; 
        return newhead; 
    }
};

// 使用迭代的方式时间复杂度为O(n)， 空间复杂度为O(1)
class Solution {
public:
    ListNode* swapPairs( ListNode* head) {
        ListNode* dummyHead = new ListNode(0);
        dummyHead ->next = head; 
        ListNode* temp = dummyHead; 
        while(temp ->next && temp ->next -> next) {
            ListNode* node1 = temp ->next; 
            ListNode* node2 = temp ->next ->next; 
            temp ->next = node2; 
            node1 -> next = node2 ->next; 
            node2 ->next = node1; 
            temp = node1;
        }
        return dummyHead ->next; 
    }
};


//141. linked list cycle - easy(环形链表)
// 直接使用双指针， 时间复杂度O(n)， 空间复杂度为O(1)
class Solution {
public:
    bool hasCycle(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return false;
        }
        ListNode* slow = head;
        ListNode* fast = head->next;
        while (slow != fast) {
            if (fast == nullptr || fast->next == nullptr) {
                return false;
            }
            slow = slow->next;
            fast = fast->next->next;
        }
        return true;
    }
};

#include<unordered_set>

// 使用哈希表也可以进行求解时间复杂度为O(n)， 空间复杂度也为O(n)
class Solution {
public:
    bool hasCycle(ListNode *head) {
        unordered_set<ListNode*> seen;
        while (head != nullptr) {
            if (seen.count(head)) {
                return true;
            }
            seen.insert(head);
            head = head->next;
        }
        return false;
    }
};



//142. linked list cycle 2 - medium(环形链表2)
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast != nullptr) {
            slow = slow->next;
            if (fast->next == nullptr) {
                return nullptr;
            }
            fast = fast->next->next;
            if (fast == slow) {
                ListNode *ptr = head;
                while (ptr != slow) {
                    ptr = ptr->next;
                    slow = slow->next;
                }
                return ptr;
            }
        }
        return nullptr;
    }
};


//25. reverse nodes in k group ---hard (k个一组进行翻转链表)
// 时间复杂度为O(n)
// 这种接法就是将每次都已k为基准进行简单的交换就性了
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(! head)
            return head; 
        ListNode* pre = new  ListNode(0);
        pre ->next = head; 
        ListNode* cur= pre, * p1 = pre; 
        int count = 0; 
        while(cur) {
            ++ count; // 这就是向前进行几个节点，也就是是否是达到翻转点
            cur = cur ->next; 
            if(count == k && cur ) {
                ListNode* p2 = p1 ->next; 
                while(-- count) { // 这里就是将要进行翻转
                    // 每次将p1->next插入到cur->next，且p1->next指向p1->next->next
                    // 这里就是相当于应用过的插入法
                    ListNode* p3 = p1 ->next; 
                    p1 ->next = p3 ->next; 
                    p2 ->next = cur ->next; 
                    cur ->next = p3; 
                }
                p1 = cur = p2; 
            }
        }
        return pre->next; 

    }
};


//21. merge two sorted lists - easy (合并两个有序的链表)
// 使用递归，时间复杂度问O(n+m)
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) {
            return l2;
        } else if (l2 == nullptr) {
            return l1;
        } else if (l1->val < l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        } else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
};


// 使用哨兵节点的方式时间复杂度为O(n+m)， 空间复杂度为O(1)
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* preHead = new ListNode(-1);

        ListNode* prev = preHead;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val < l2->val) {
                prev->next = l1;
                l1 = l1->next;
            } else {
                prev->next = l2;
                l2 = l2->next;
            }
            prev = prev->next;
        }

        // 合并后 l1 和 l2 最多只有一个还未被合并完，我们直接将链表末尾指向未合并完的链表即可
        prev->next = l1 == nullptr ? l2 : l1;

        return preHead->next;
    }
};



/*************************       栈，队列，双端队列、优先队列         *****************/

#include<stack>

//20. valid pareutheses -easy (有效的括号)
// 直接使用stack，时间复杂度为O(n)，空间复杂度为O(1)
class Solution {
public:
    bool isValid(string s) {
        if(s.empty())
            return false; 
        stack<char>stk; 
        for(char c :s) {
            if(!stk.empty()) {
                char ch= stk.top(); 
                if(ch == ')' || ch =='}' || ch ==']')
                    return false; 
                if(c ==')' && ch == '(') {
                    stk.pop(); 
                    continue; 
                }
                if(c ==']' && ch == '[') {
                    stk.pop(); 
                    continue; 
                }
                if(c == '}' && ch == '{') {
                    stk.pop(); 
                    continue; 
                }
            }
            stk.push(c);
        }
        return stk.empty(); 
    }
};


//155. min stack -easy (最小栈)
class MinStack {
public:
    /** initialize your data structure here. */
    stack<int>stk; 
    stack<int>s_min; 
    MinStack() {  }
    
    void push(int x) {
        stk.push(x);
        if(s_min.empty())
            s_min.push(x);
        else {
            s_min.push(min(s_min.top(), x));
        }
        
    }
    void pop() {
        stk.pop(); 
        s_min.pop(); 
    }
    
    int top() {
       return stk.top(); 
    }
    
    int getMin() {
        int min_s = s_min.top(); 
        return min_s; 
    }
};



//84. largest rectangle in histogram -hard (柱状图中最大的矩形)

// 超出时间限制，时间复杂度为O(n^2)
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        int ans = 0;
        // 枚举左边界
        for (int left = 0; left < n; ++left) {
            int minHeight = INT_MAX;
            // 枚举右边界
            for (int right = left; right < n; ++right) {
                // 确定高度
                minHeight = min(minHeight, heights[right]);
                // 计算面积
                ans = max(ans, (right - left + 1) * minHeight);
            }
        }
        return ans;
    }
};

// 使用栈（单调栈）
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> st;
        if(heights.size() == 0)
            return 0;
        int maxArea = heights[0];
        heights.push_back(0);   //设置末尾边界
        for(int i = 0; i < heights.size(); i++){
            while(!st.empty() && heights[i] < heights[st.top()]){
                int top_index = st.top();
                //右边第一个比heights[st.top()]小的元素
                int right = i;
                st.pop();
                //左边第一个比heights[st.top()]小的元素
                int left = st.empty() ? -1 : st.top();	//注意无左边界的情况
                maxArea = max(maxArea, heights[top_index] * (right - left - 1));
            }
            st.push(i);
        }
        return maxArea;
    }
};


//239. sliding window maximum - hard (滑动窗口的最大值)
// 使用队列(双端队列)
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        if(k == 0)
             return res;
        deque<int> window;   //双端队列，从队头到队尾 依次存 窗口内最大元素的index ~ 最小元素的index
        int right = 0;
        while(right < nums.size()){   
            //后续，窗口每右移一次，都会产生一个最大值[队列头位置的元素]
            if(!window.empty() && window.front() <= right - k){   
                //队头不在窗口范围内
                window.pop_front();
            }
            while(!window.empty() && nums[right] > nums[window.back()]){   
                //待入队元素比队尾元素大
                window.pop_back();
            }
            window.push_back(right);
            right++;
            if(right >= k) 
                res.push_back(nums[window.front()]);
        }
        return res;
    }

