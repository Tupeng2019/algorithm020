#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std; 

/*****************************  动态规划       *********************************/






//******************** 
/// 32. Longest valid parentheses(最长有效括号)

///动态规划
class Solution {
public:
    int longestValidParentheses(string s) {
        int maxans = 0, n = s.length();
        vector<int> dp(n, 0);
        for (int i = 1; i < n; i++) {
            if (s[i] == ')') {
                if (s[i - 1] == '(') {
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                } else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(') {
                    dp[i] = dp[i - 1] + ((i - dp[i - 1]) >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;
                }
                maxans = max(maxans, dp[i]);
            }
        }
        return maxans;
    }
};





// **************************************
/// 64 . minimum path sum (最小路径和)- Medium
class Solution {
public:
// 2.times
    // 使用动态规划，
    // 分为三种情况，在左边界，上边界和中间的所有部分数字情况。
    int minPathSum(vector<vector<int>>& grid) {
        //int ans = 0; 
        if(grid.empty() || grid[0].empty())
            return 0; 
        int m = grid.size(); 
        int n = grid[0].size(); 
        vector<vector<int>>dp(m, vector<int>(n)); 
        dp[0][0] = grid[0][0]; 
        for(int i = 1; i< m; ++ i) 
            dp[i][0] = dp[i -1][0] + grid[i][0]; 
        for(int i = 1; i <n; ++i)
            dp[0][i] = dp[0][i -1] + grid[0][i]; 
        for(int i = 1; i< m; ++i) {
            for(int j = 1; j < n; ++j) {
                dp[i][j] = min(dp[i -1][j], dp[i][j -1]) + grid[i][j]; 
            }
        }
        return dp[m-1][n-1]; 
    }
};


// ****************************************
/// 72. edit distance (编辑距离) - Hard
// 
class Solution {
public:
// 2. Times 
    // 动态规划
    // 时复杂度为O(nm)， 空间复杂度也为O(nm)
    int minDistance(string word1, string word2) {
        int n = word1.length(); 
        int m = word2.length(); 
        if(n *m == 0)
            return n +m; // 有一个为空，这返回不为空的
        vector<vector<int>>dp(n +1, vector<int>(m +1)); 
        // 确定两个边界的问题
        dp[0][0]= 0;
        for(int i = 1; i <=n; ++ i) {
            dp[i][0] = i; 
        }
        for(int j = 1; j <=m; ++ j) {
            dp[0][j] = j; 
        }
        // 计算非边界的问题
        for(int i = 1; i<= n; ++ i) {
            for(int j = 1; j <= m; ++ j) {
                int left = dp[i -1][j] +1; 
                int down = dp[i][j -1] +1;
                int left_down = dp[i -1][j -1] ; 
                if(word1[i -1] != word2[j -1])
                    left_down += 1; 
                dp[i][j] = min(left, min(down, left_down));  
            }
        }
        return dp[n][m]; 
    }
};





// ***********************************
/// 91. Decode ways (解码方法)  -- Medium

class Solution {
public:
// 1. Times 
    // 使用动态规划
    int numDecodings(string s) {
        int n = s.length(); 
        if(s.empty() || n == 0|| s[0] == '0')
            return 0; 
        if(n ==1)
            return 1; 
        //  先确定首数字对应的字符
        int pre = s[0] - '0'; 
        vector<int>dp(n +1, 1);
        for(int i = 2; i <= n; ++ i) {
            int cur = s[i-1] - '0'; // 表示当前的最后一个数字
            if((pre== 0 || pre > 2) && cur ==0 )
                return 0; 
            if((pre >0 && pre < 2) || pre == 2 && cur < 7) {
                if(cur )
                    dp[i] = dp[i -2] + dp[i -1];
                else 
                    dp[i] = dp[i -2]; 
            }
            else {
                dp[i] = dp[ i-1]; 
            }
            pre = cur; 
        }
        return dp[n]; 
    }
};



// **************************************
/// 221. maximal square(最大正方形) ——Medium
// 动态规划
class Solution {
public:
// 1.Times
    // 动态规划
    int maximalSquare(vector<vector<char>>& matrix) {
        if(matrix.empty() || matrix[0].empty())
            return 0; 
        int m = matrix.size(); 
        int n = matrix[0].size(); 
        int max_side = 0; 
        vector<vector<int>>dp(m+1, vector<int>(n+1, 0));
        // dp[i][j]就是表示以第i行和第j列，为右下角的正方形的最大边长
        for(int i = 1; i <= m; ++i){
            for(int j = 1; j <= n; ++j){
                if(matrix[i-1][j-1] == '1'){
                    // 如果其余的三个角都是大于0 的数字，则可以表示当前的数字可以组成正方形的
                    dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1])) +1; 
                }
                max_side= max(dp[i][j], max_side);
            }
        }
        return max_side*max_side; 
    }
};



#include<set>

// ****************************************
/// 363. max sum of rectangle no larger than k (矩形区域不超过k的最大数值和) -- Hard 
// 
class Solution {
public:
// 1.Times 
    // 这道题还是有一些，没有看懂，还是需要下来，更加的用工夫吧
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
        int row=matrix.size();
        if (row==0)
            return 0;
        int column=matrix.at(0).size();
        int ans=INT_MIN;
        for (int left=0;left<column;++left) {
            vector<int> row_sum(row,0);
            for (int right =left;right <column; ++right) {
                //直接在构建row_sum时嵌入求最大子序和
                int max_sub_sum=0;
                int max_sum=INT_MIN;
                for (int i=0;i<row;++i) {
                    row_sum.at(i)+=matrix.at(i).at(right);
                    max_sub_sum+=row_sum.at(i);
                    if (max_sub_sum<=k && ans<max_sub_sum)
                        ans=max_sub_sum;
                    if (max_sub_sum<0)
                        max_sub_sum=0;
                    max_sum=max(max_sum,max_sub_sum);
                }
                if (ans==k)
                    return k;
                if (max_sum<=k)
                    continue;
                set<int> helper_set;
                helper_set.insert(0);
                int prefix_row_sum=0;
                for (int i=0;i<row;++i)
                {
                    prefix_row_sum+=row_sum.at(i);
                    auto p=helper_set.lower_bound(prefix_row_sum-k);
                    helper_set.insert(prefix_row_sum);
                    if (p==helper_set.end())
                        continue;
                    else {
                        int temp=prefix_row_sum-(*p);
                        if (temp>ans)
                            ans=temp;
                    }
                }
                if (ans==k)
                    return k;
            }
        }        
        return ans;
    }
};



#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<functional>


//*****************************************
/// 403 . Frog jump -- Hard (青蛙过河)
//  这几到题都是比较有难度的，还是比较难的
class Solution {
public:
// 1.Times 
    //记忆话搜索
    bool canCross(vector<int>& stones) {
        unordered_set<int> h;
        for(auto x:stones) h.insert(x);
        unordered_map<long long, bool> memo;
        function<bool(int,int)> dfs = [&] (int x, int y) {
            if(y<=0 || !h.count(x)) return false;
            if(x==1&&y==1) return true;
            
            long long t = (long long)x<<32|y;
            if(memo.count(t)) return memo[t];
            
            if(dfs(x-y,y)||dfs(x-y,y-1)||dfs(x-y,y+1))
                return memo[t] = true;
            return memo[t] = false;
        };
        
        for(int i = 1 ; i <= 1001 ; i ++)
            if(dfs(stones.back(),i))
                return true;
        return false;
    }
};


//*************************************************
/// 410.Split array largest sum- 分割数组的最大值- Hard
//
// dp[i][j] 可以表示为将数组的前i个数，分割为j段，所得到的最大连续子数组和的最大值
class Solution {
public:
// 1.Times
// dp[i][j] 可以表示为将数组的前i个数，分割为j段，所得到的最大连续子数组和的最大值
    int splitArray(vector<int>& nums, int m) {
        int n = nums.size(); 
        vector<vector<long long>>dp(n +1, vector<long long>(m +1, LLONG_MAX));
        vector<long long>sub(n +1, 0); 
        for(int i = 0; i <n; ++ i) {
            sub[i+1] = sub[i] + nums[i]; 
        }
        dp[0][0]= 0; 
        for(int i = 1; i<= n; ++ i) {
            for(int j = 1; j <= min(i, m); ++j) {
                for(int  k= 0; k <i; k ++) {
                    dp[i][j] = min(dp[i][j], max(dp[k][j -1],sub[i]- sub[k]));
                }
            }
        }
        return (int)dp[n][m]; 
    }
};


//*****************************************************
///552. student attendance record-II (学生的出勤记录-II)--- Hard
// 
class Solution {
public:
// 1. Times
    // 动态规划
    // 先计算。P,L的数量，然后在去套用A
    //#define mod ((int) le9+7)
    int  mod = 1000000007;
    int checkRecord(int n) {
        if(n == 1)
            return 3; 
        if(n ==2)
            return 8; 
        // dp[i][0] 表示这个位置为p时的数量
        // dp[i][1] 表示这个位置为L时的数量
        vector<vector<long long>>dp(n, vector<long long>(2, 0)); 
        dp[0][0] = 1; 
        dp[0][1] = 1; 
        dp[1][0] = 2; 
        dp[1][1] = 2; 
        for(int i = 2; i < n; ++i) {
            dp[i][0] = (dp[i -1][0] + dp[i -1][1]) % mod; 
            dp[i][1] = (dp[i -1][0] + dp[i -2][0]) % mod; 
        }
        long long ans = (( dp[n -2][0] + dp[n -2][1])*2 % mod + dp[n -1][0] + dp[n -1][1]) % mod; 
        //这里就是表示在里面插入A
        for(int i = 1; i < n -1; ++i) {
            ans += (dp[i -1][0] + dp[i -1][1]) * (dp[n - i -2][0] + dp[n - i -2][1]); 
            ans %= mod; 
        }
        return ans; 
    }
};



// **********************************
///621. Task schedular(任务调度器)  -- Hard
class Solution {
public:
// 1.Times 
    // 桶思想， 时间复杂度为O(nlogn)， 空间复杂度为O(1)
    // 这里的n就是表示两个相同的任务之间所需要的间隔时间
    int leastInterval(vector<char>& tasks, int n) {
        int len=tasks.size();
        vector<int> vec(26);
        for(char c:tasks) 
            ++ vec[c-'A'];
        // 将任务的种类，按照数量从大到小进行排列
        sort(vec.begin(),vec.end(),[](int& x,int&y){return x>y;});

        int ans=1;
        // 这里就是判断是否有相同数量的任务一直不通数量的任务就可以了
        while(ans <vec.size() && vec[ans] ==vec[0])
             ans ++;
        return max(len, ans +(n+1) *(vec[0]-1) );
        

    }
};




// ************************************
/// 647. Palindromic substings(回文子串) 
/// ---1
class Solution {
public:
// 1.Times 
    // 直接法----中心拓展
    /*
    既是：枚举出所有的回文子串，分为两种枚举的方式：
        1.枚举所有的子串，然后进行判断。
        2.枚举每一个可能的回文中心，然后用两个指针分别向左右拓展，
          当两个指针指向的元素相同的时候就进行拓展，否则就是停止拓展。
    **/
    int countSubstrings(string s) {
        int n = s.size(); 
        int ans= 0; 
        for(int i = 0; i < 2 *n -1; ++ i) {
            int left = i /2; 
            int right = i /2 + i % 2; 
            while(left >= 0 && right < n && s[left] == s[right]) {
                -- left; 
                ++ right; 
                ++ ans; 
            }
        }
        return ans; 
    }
};

// ----2
class Solution {
public:
// 1.Times
    // Manacher 算法
    /* 
        Manacher 算法是在线性时间内求解最长回文子串的算法，
        其主要思想：依旧是枚举s的灭一个位置，假设其是回文中心，但是他利用计算
        已经计算出来的状态来更新当前的状态，而不是像中心拓展那样盲目的扩展，
    */
    int countSubstrings(string s) {
        int n = s.size(); 
        string t = "$#"; 
        //这里就是为了解决奇偶性不一样的问题，向其中添加一些字符
        for(const char& c:s) {
            t += c; 
            t += '#'; 
        }
        // 需要更新现在的长度
        n = t.size(); 
        t += '!';
        vector<int>f(n); 
        int L_max = 0; 
        int R_max = 0; 
        int ans = 0; 
        for(int i = 1; i < n; ++i) {
            // 初始化f[i]
            f[i] = (i <= R_max) ? min(R_max - i +1, f[2 *L_max -i]) :1; 
            // 中心拓展
            while(t[i+ f[i]] == t[i - f[i]] )
                ++ f[i] ; 
            // 动态维护
            if(i + f[i] - 1 > R_max) {
                L_max = i; 
                R_max = i + f[i] - 1; 
            }
            // 统计答案，当前贡献值为(f[i] -1) /2 上取整
            ans += (f[i] / 2); 
        }
        return ans; 
    }
};


//**********************************************
///76. minimum window substring (最小覆盖子串) --- Hard
class Solution {
public:
//1Times
    // 滑动窗口

    unordered_map<char, int>origin, cur; 
    // 判断是否是正确的
    bool check() {
        for(const auto& p : origin) {
            // 如果该子串值真确的，则在这两个hash中，键值是一样的，否则就是不对的
            if(cur[p.first] < p.second)
                return false; 
        }
        return true; 
    }

    string minWindow(string s, string t) {
        // 进行hash
        for(const auto& c: t) 
            ++ origin[c]; 

        int left = 0, right = -1; 
        int len = INT_MAX, ansL = -1, ansR = -1; 

        int n = s.size(); 
        while(right < n ) {
            if(origin.find(s[++ right]) != origin.end())
                // 表示找到一当前与t中有相同的字母
                ++ cur[s[right]]; 
            while( check() && left <= right) {
                if(right - left + 1 < len) {
                    len = right - left + 1; 
                    ansL = left; 
                }
                if(origin.find(s[left]) != origin.end())
                    -- cur[s[left]]; 
                ++ left; 
            }
        }
        return ansL == -1 ? string(): s.substr(ansL, len); 
    }
};




















