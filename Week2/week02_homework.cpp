#include<vector>
#include<iostream>

#include<queue>
#include<unordered_map>

using namespace std; 


//347. top k frequent elements -medium (前k个高频的元素)
// shiyong map + Heap(proorityqueue)
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int,int> map;         //统计频次
        for(auto i:nums) map[i]++;
        
        priority_queue<pair<int,int>> que;  
        for(auto m:map){
            que.push(make_pair(m.second, m.first));     //优先队列（堆）按照第一项进行排序
        }

        vector<int> vec;
        for(int i=0;i<k;i++){
            vec.push_back(que.top().second);
            que.pop();
        }
        return vec;
    }
};



//<剑指offer>49. 丑数 
//. 使用动态规划进行
class Solution {
public:
// 1.
    // 使用动态规划是可以做的
    int nthUglyNumber(int n) {
        vector<int>dp(n,0);
        dp[0] = 1; 
        int a_2 = 0; 
        int a_3 = 0; 
        int a_5 = 0; 
        for(int i = 1; i< n; ++i ){ 
            int t_2 = dp[a_2] *2; 
            int t_3 = dp[a_3] *3; 
            int t_5 = dp[a_5] *5; 
            dp[i] = min(min(t_2, t_3), t_5);
            if(dp[i] == t_2)
                a_2 ++; 
            if(dp[i] == t_3)
                a_3 ++; 
            if(dp[i] == t_5)
                a_5 ++; 
        }
        return dp[n-1];
    }
};
