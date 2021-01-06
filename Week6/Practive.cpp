#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std; 

/*****************************  动态规划       *********************************/

//******************** 
// 120. 三角形的最小路径和

class Solution {
public:
// 1.Times
    // 动态规划问题, 将整个数组看成是一个直角三角形
    // 时间复杂度为O(n^2)，空间复杂度也是一样的了
    // Dp 
        // a. 重复性
        // b. 定义状态数组
        // c. DP 方程 dp[i][j]= min(dp[i-1][j -1], dp[i-1][j]) + triangle[i][j]; 
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size(); 
        vector<vector<int>>dp(n, vector<int>(n)); 
        dp[0][0] = triangle[0][0]; 
        for(int i = 1; i< n; ++ i) {
            dp[i][0] = dp[i- 1][0] + triangle[i][0]; 
            for(int j = 1; j < i; ++ j){
                dp[i][j]= min(dp[i-1][j -1], dp[i-1][j]) + triangle[i][j]; 
            }
            dp[i][i] = dp[i -1][i - 1] + triangle[i][i]; 
        }
        //最终的返回值就是哪一维度的最小值
        return *min_element(dp[n-1].begin(), dp[n -1].end()); 
    }
};


// 对上面的进行优化, 优化的既是空间复杂度，
class Solution {
public:
// 1.Times
    // 动态规划问题, 将整个数组看成是一个直角三角形
    // Dp 
        // a. 重复性
        // b. 定义状态数组
        // c. DP 方程 dp[i][j]= min(dp[i-1][j -1], dp[i-1][j]) + triangle[i][j]; 
    int minimumTotal(vector<vector<int>>& triangle) {
        int n = triangle.size(); 
        vector<int>dp(n); 
        dp[0]= triangle[0][0]; 
        for(int i = 1; i< n; ++i) {
            dp[i] = dp[i -1] + triangle[i][i]; 
            for(int j = i -1; j > 0; -- j) {
                dp[j] = min(dp[j -1], dp[j]) + triangle[i][j]; 
            }
            dp[0] += triangle[i][0]; 
        }
        return * min_element(dp.begin(), dp.end()); 
    }
};



// **************************************
// 53. 最大子序和
class Solution {
public:
// 2.Times
    // 时间复杂度问O(n)
    int maxSubArray(vector<int>& nums) {
        if(nums.empty())
            return 0; 
        int n = nums.size(); 
        if(n ==1)
            return nums[0];
        vector<int>dp(n+1, 0);
        dp[0]= nums[0];
        int max_value = dp[0];
        for(int i = 1; i <n; ++i){  // 这里的小于n, 是不能有等于的，因为在nums中是没有第n项的，只有第n-1项
            dp[i] = max(dp[i -1] + nums[i],nums[i]);
            max_value = max(dp[i], max_value);       //应该利用一个值将最大值个保存下来
        }
        return max_value;
    }
};



// ***********************************
// 152. Maximum Product Subarray 乘积最大子数组
// 这一道题还是和前面的题，还是有区别的
class Solution {
public:
// !. times
    // 动态规划，这里相当于考虑到负负得正的思想，所以和前面的额题，还是有不一样的
    int maxProduct(vector<int>& nums) {
        vector<int>max_f(nums), min_f(nums); 
        for(int i = 1 ; i< nums.size(); ++ i) {
            max_f[i] = max(max_f[i -1] * nums[i], max(nums[i], min_f[i -1] * nums[i])); 
            min_f[i] = min(min_f[i -1] * nums[i], min(nums[i], max_f[i -1] * nums[i])); 
        }
        return * max_element(max_f.begin(), max_f.end()); 
    }
};

class Solution {
public:
// 1. Times
    // 动态规划
    // 进行空间的优化
    int maxProduct(vector<int>& nums) {
        int max_f = nums[0]; 
        int min_f = nums[0]; 
        int ans = nums[0]; 
        for(int i = 1; i< nums.size(); ++ i) {
            int max_dp = max_f;
            int min_dp = min_f; 
            max_f = max(max_dp * nums[i], max(nums[i], min_dp * nums[i])); 
            min_f = min(min_dp * nums[i], min(nums[i], max_dp * nums[i])); 
            ans = max(max_f, ans); 
        }
        return ans; 
    }
};


// **************************************
// 322. coin change （零钱兑换）
// 动态规划
class Solution {
public:
// 2. Times 
    // 使用动态规划
    int coinChange(vector<int>& coins, int amount) {
        if(coins.empty())
            return -1; 
        vector<int>dp(amount +1, INT_MAX -1); // 这里的初始化数是可以为任意大小的数字
        dp[0] = 0; 
        for(int i = 1; i <= amount; ++ i) {
            for(int& c: coins) {
                if(c <= i)
                    dp[i] = min(dp[i], dp[i - c] + 1); 
            }     
        }
        return dp[amount] > amount? -1 : dp[amount]; 
    }
};




// ************************************
// 198. House Robber （打家劫舍） Easy
// 动态规划
// dp[i]表示前i间房子，能够偷到的最高的金额
            // 状态方程
            //    dp[i] = max( dp[i-2] + nums[i], dp[i-1])
            // 同时还需要注意的就是边界条件
class Solution {
public:
// 1 . times
    // 动态规划 
    // 这里的时间复杂度为O(n)，空间复杂度也为O(n)
    int rob(vector<int>& nums) {
        // int ans = 0; 
        if(nums.empty())
            return 0; 
        int n = nums.size(); 
        if(n == 1)
            return nums[0]; 
        // if(n == 2)
            // return max(nums[0], nums[1]); 
        vector<int>dp(n, 0);
        dp[0] = nums[0]; 
        dp[1] = max(nums[0], nums[1]);
        for(int i = 2; i< n;  ++ i)  {
            dp[i] = max(dp[i -2] + nums[i], dp[i -1]); 
        }
        return dp[n-1]; 
    }
};

// 针对上面的额情况，可以进行空间的优化
// 使其空间复杂度为O(1)
class Solution {
public:
// 1.times
    // 进行空间复杂度优化
    int rob(vector<int>& nums) {
        if(nums.empty())
            return 0;
        if(nums.size()== 1)
            return nums[0]; 
        int dp_0 = nums[0]; 
        int dp_1 = max(nums[0], nums[1]);
        if(nums.size() == 2)
            return dp_1; 
        int ans = 0; 
        for(int i = 2; i < nums.size(); ++i) {
            ans = max(dp_0 + nums[i], dp_1); 
            dp_0 = dp_1; 
            dp_1 = ans; 
        }
        return ans; 
    }
};



// *********************************************
// 213. House Robber -ii （打家劫舍-II） Medium
// 动态规划
// dp[i][0 or 1]表示前i间房子，能够偷到的最高的金额
            // 状态方程
            //    dp[i][1,0] = max( dp[i-2] + nums[i], dp[i-1])
            // 同时还需要注意的就是边界条件
class Solution {
public:
// 2. Times
    // 动态规划
    int rob(vector<int>& nums) {
        int n = nums.size(); 
        if(nums.empty())
            return 0; 
        if(n < 4)
            return (*max_element(nums.begin(), nums.end())); 
        vector<vector<int>>dp(n, vector<int>(2, 0));  // 这后面的表示的就是是否偷了第一家
        // int dp[n][2]; 
        // 下面就是分别表示不同的状态, 也就是边界的情况
        dp[0][0] = 0; 
        dp[0][1] = nums[0];   // 偷了第0家，偷到第0家的最大金额
        dp[1][1] = nums[0];   // 偷了第0家，偷到第1家是的最大金额
        dp[1][0] = nums[1];   // 没有偷第0家，到第1家的最大金额(也就是可以偷第1家了)
        for(int i = 2; i< n; ++ i) {
            if(i != n -1) {
                // 将最后一家分为两个状态，一个是偷第一家和不投第一家
                dp[i][0] = max(dp[i -1][0], dp[i -2][0] + nums[i]); 
                dp[i][1] = max(dp[i -1][1], dp[i -2][1] + nums[i]); 
            }
            else{
                // 投最后一家是，如果没有通过第0家，这可以直接投
                dp[i][0] = max(dp[i -1][0], dp[i -2][0] + nums[i]); 
                // 投了第0 家了，这指正选择不投了
                dp[i][1] = dp[i -1][1]; 
            }
        }
        return max(dp[n -1][0], dp[n-1][1]); 
    }
};

// 对上面的额结果进行优化
class Solution {
public:
// 1. times
    // 进行空间的优化
    int rob(vector<int>& nums) {
        if(nums.size() == 1)
            return nums[0]; 
            int n = nums.size(); 
            vector<int>dp_1(n +1), dp_2(n +1); 
            for(int i = 2; i<= n; ++ i) {
                dp_1[i] = max(dp_1[i -1], dp_1[i -2] + nums[i -2]); // 这里就是相当于是取了第0家
                dp_2[i] = max(dp_2[i -1], dp_2[i -2] + nums[i -1]); // 这里就是表示没有取第0家
            }
            return max(dp_2[n], dp_1[n]); 
    }
};





// *********************************************
// 337. House Robber -iii （打家劫舍-III） Medium
// 动态规划
// dp[i][0 or 1]表示前i间房子，能够偷到的最高的金额
            // 状态方程
            //    




// ***********************************************
// 279. Perfect Squares (完全平方数) - Medium
// 动态规划
class Solution {
public:
//1.TImes 
    // 使用动态规划，时间复杂度为O(n)
    int numSquares(int n) {
        vector<int>dp(n +1, INT_MAX);
        dp[0]= 0; 
        for(int i = 1; i <=n; ++i){
            for(int j = 1 ; j *j <= i; ++j){
                dp[i] = min(dp[i], dp[i - j*j]+ 1);
            }
        }
        return dp[n];
    }
};





// ***********************************************
// 72. Edit distance (编辑距离) Hard
// D[i][j] 表示A的前i个字母和B的前j的字母之间的编辑距离
class Solution {
public:
// 1. Times 
    // 动态规划，这是经典的例题
    int minDistance(string word1, string word2) {
        int n = word1.size(); 
        int m = word2.size(); 
        // 判断是否有空字符串
        if(n * m == 0)
            return n + m; 
        // 定义状态数组
        vector<vector<int>>dp(n+1, vector<int>(m+1, 0)); 
        // 定义边界情况
        for(int i =0; i<= n; ++ i)
            dp[i][0] = i; 
        for(int j = 0; j <=m; ++ j)
            dp[0][j] = j; 
        for(int i = 1; i <= n; ++ i) {
            for(int j = 1; j <= m; ++ j) {
                int left = dp[i-1][j] + 1; 
                int down = dp[i][j -1] + 1; 
                int left_down = dp[i -1][j -1]; 
                if(word1[i -1] != word2[j -1])
                    left_down += 1; 
                dp[i][j] = min(left, min(down, left_down)); 
            }
        }
        return dp[n][m]; 
    }
};


// 稍稍进行优化
class Solution {
public:
// 1. Times
    // 动态规划
    int minDistance(string word1, string word2) {
        int m = word1.length();
        int n = word2.length(); 
        vector<vector<int>>dp(m +1, vector<int>(n+1, 0));
        for(int i = 0; i<= m; ++i){
            for(int j = 0; j <=n; ++j){
                if(i == 0)
                    dp[i][j] =j;
                else if(j ==0){
                    dp[i][j] =i;
                }
                else{
                     dp[i][j] = min(dp[i-1][j-1]+ ((word1[i-1]== word2[j-1])?0: 1),min(dp[i-1][j]+1, dp[i][j-1]+1));
                }
            }
        }
        return dp[m][n];
    }
};

// ************************************
// 55 跳跃游戏
// 1. 直接使用贪心算法
class Solution {
public:
    // 2.Times 
    // 直接跳
    bool canJump(vector<int>& nums) {
        int most_dir = 0; 
        for(int i = 0; i<nums.size() ; ++i) {
            if(i > most_dir)
                return false; 
            most_dir = max(most_dir, i + nums[i]); 
        
        }
        return true; 
    }
};


// 2.动态规划
class Solution {
public:
// 2. Times 
    // 动态规划
    bool canJump(vector<int>& nums) {
        int n = nums.size(); 
        // dp[i] = 0表示可以到达的，为0表示不可以到达的
        vector<int>dp(n, 0); 
        dp[0] = 1; 
        for(int i = 1; i< n; ++ i) {
            for(int j = i -1; j >=0; -- j) {
                if(dp[j]&& (nums[j] >= i -j)){   // 这里和前面的贪心算法其实都是差不多的解法
                    dp[i] =1; 
                    break; 
                }
            }
        }
        return dp[n -1]; 
    }
};




// ***************************************
// 45.jump games- ii (跳跃游戏-II)  Hard
class Solution {
public:
// 2. Times
    // 利用贪心，维护每一步多能够到达的最远距离
    int jump(vector<int>& nums) {
        int Etime_most_dir = 0; 
        int ans = 0; 
        int most_dir = 0; 
        for(int i = 0; i< nums.size()-1; ++i ) { // nums.size()-1，因为是不需要遍历最后一个位置的
            if(most_dir >= i) {
                most_dir = max(most_dir, i +nums[i]); 
                if(Etime_most_dir == i) { // 表示到达了当前位置可能到达的最大的位置
                    Etime_most_dir = most_dir; 
                    ++ ans; 
                }
            }   
        }
        return ans; 
    }
};


// 
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> f(m, vector<int>(n));
        for (int i = 0; i < m; ++i) {
            f[i][0] = 1;
        }
        for (int j = 0; j < n; ++j) {
            f[0][j] = 1;
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                f[i][j] = f[i - 1][j] + f[i][j - 1];
            }
        }
        return f[m - 1][n - 1];
    }
};

class Solution {
public:
//2.Times 
    // 动态规划，这里是对前面的二维做法进行空间优化
    //这里的优化，可以结果实际的格子图，进行理解
    // dp[i][j]= dp[i-1][j] + d[i][j-1];这种形式实际上也就是下面的先进行列的累加，然后进行
    // 行的累加就行了
    int uniquePaths(int m, int n) {
        vector<int>dp(n,1); 
        //for(int i =0; i <n; ++i ){
            //dp[i]= 1; 
        //}
        // 进行行的迭代
        for(int i = 1; i< m; ++i) {
            for(int j = 1; j < n; ++j) {
                dp[j] += dp[j-1]; 
            }
        }
        return dp[n-1]; 
    }
};

















