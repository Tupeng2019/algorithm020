#include<iostream>

using namespace std; 


/**********************************  DFS && BFS  **********************************/

#include<vector>
#include<queue>
/// 102 . Binary tree level order traversal (二叉树的层序遍历)-Medium

// BFS ,使用广度优先搜索, 
// 现在做着道题还是挺简单的了
// Definition for a binary tree node.
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Solution {
public:
//1.Times 
    // 使用queue来模拟广度优先搜索
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>>ans; 
        if(!root)
            return ans; 
        queue<TreeNode*>que; 
        que.push(root); 
        while(!que.empty()) {
            int size = que.size(); 
            vector<int>vec; 
            for(int i = 0; i< size; ++i) {
                TreeNode* cur = que.front(); 
                que.pop(); 
                vec.emplace_back(cur ->val); 
                if(cur -> left)
                    que.push(cur ->left); 
                if(cur -> right)
                    que.push(cur ->right); 
            }
            ans.emplace_back(vec); 
        }
        return ans; 
    }
};

// 这里使用DFS，因为是向下进行递归的，所以要记住每一层递归的，然后将相应的层所对应点额数字，填在对应的vector
class Solution {
public:
//1.Times
    // DFS
    void DFS(TreeNode* root, vector<vector<int>>&ans, int level) {
        if(! root) 
            return; 
        if(level >= ans.size()) {
            vector<int>vec; 
            ans.emplace_back(vec); 
        }
        ans[level].push_back(root ->val); 
        DFS(root ->left, ans, level+1);
        DFS(root ->right, ans, level +1); 
    }
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans; 
        DFS(root, ans, 0); 
        return ans; 
    }
};



/// 433. minimum genetic mutation (最小基因变化) - Medium
// 使用广度优先搜索
class Solution {
public:
    //解法1：单向bfs
    int minMutation(string start, string end, vector<string>& bank) {
        //1:判读极端情况
        if(start.empty()||end.empty()||bank.empty())return -1;
        if(find(bank.begin(),bank.end(),end)==bank.end())return -1;//目标基因不在基因库中
        //2:bfs的初始化工作
        vector<int> visit(bank.size(),0);
        int step=0;
        queue<string> q;
        q.push(start);
        //3:进行bfs
        while(!q.empty()){
            step++;
            int n=q.size();//确定每次bfs的宽度
            for(int i=0;i<n;++i){
                string &temp=q.front();q.pop();//获得队头元素
                for(int j=0;j<bank.size();++j){//遍历整个基因库,访问未标记的基因；找到某个字符变异的基因添加标记，并进入队列即可
                    if(visit[j]==0){
                        int diff=0;
                        for(int k=0;k<temp.size();++k){
                            if(temp[k]!=bank[j][k])diff++;
                        }
                        if(diff==1){//找到某个字符编译的基因
                            if(bank[j]==end)return step;//若该下标j代表的基因为目标基因，则直接返回步长
                            visit[j]=1;//标记下标为j的基因已访问
                            q.push(bank[j]);
                        }
                    }
                }
            }
        }
        return -1;
    }
};



// 双向BFS
#include<unordered_map>
class Solution {
public:
    //解法2：双向bfs
    int minMutation(string start, string end, vector<string>& bank) {
        //1:建立hashmap表，顺便去掉重复元素
        unordered_map<string,int> mp;
        for(const auto& b:bank)mp[b]=0;
        
        //2:排除极端情况，end不在基因库中
        if(mp.count(end)==0)return -1;
        
        //3:bfs的初始化工作
        queue<string> q1({start}),q2({end});//前向队列，后向队列
        int step=0;
        const char table[4]={'A','C','G','T'};//基因的字符
        //或1表示前向队列由前往后遍历，或2表示后向队列由后向前遍历，每次我们选用较小的队列进行遍历
        for(mp[start]|=1,mp[end]|=2;q1.size()&&q2.size();++step)//每遍历完一次，步长+1
        {
            bool first=q1.size()<q2.size();
            queue<string> &q=first?q1:q2;//选择较小的队列进行遍历节约时间
            int flag=first?1:2;//此次遍历的方式
            
            for(int n=q.size();n--;q.pop()){
                string& temp=q.front();
                if(mp[temp]==3)return step;//两个队列碰头，返回步长
                for(int i=0;i<temp.size();++i){
                    for(int j=0;j<4;++j){
                        string s=temp;
                        if(s[i]==table[j])continue;//重复字符，跳出循环，寻找下一个字符
                        s[i]=table[j];
                        if(mp.count(s)==0||mp[s]&flag)continue;//该单词不在map中或该单词已经被遍历过了，跳出循环，寻找下一个单词
                        mp[s]|=flag;//标记该单词已经被遍历过了
                        q.push(s);
                    }
                }
            }
        }
        return -1;
    }
};

