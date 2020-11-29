
#include<iostream> 
#include<string>
#include<vector>


using namespace std; 

/******************   哈希表 映射、集合----> 第二周       ***************************/

#include<map>
// 242. valid Anagram  --easy(有效的字母异位)
class Solution {
public:
// 时间复杂度为O(n)。空间复杂度为O(n)
    bool isAnagram(string s, string t) {
        if(s.empty() && t.empty()) 
            return true; 
        if(s.size()!= t.size())
            return false; 
        map<char, int>map_s; 
        map<char, int>map_t; 
        for(int i = 0; i < s.size(); ++i) {
            map_s[s[i]]++; 
            map_t[t[i]]++; 
        }
        return map_s == map_t; 
    }
};

#include<algorithm>
// 直接使用排序的方式进行比较
// 时间复杂度为O(nlogn)
class Solution {
public:
    bool isAnagram(string s, string t) {
        if(s.size() != t.size())
            return false; 
        sort(t.begin(), t.end());
        sort(s.begin(), s.end());
        return s==t; 
    }
};

// 直接维护一个数组的数组的方式，会让效率更加高，但是时间复杂度任然是为O(n)，空间复杂度为O(n)
class Solution {
public:
    bool isAnagram(string s, string t) {
        vector<char> counter(26);
        if(s.size() != t.size()) return false;
        for(int i = 0; i < s.size(); ++i){
            counter[s[i]-'a']++;
            counter[t[i]-'a']--;
        }
        for(auto& it:counter){
            if(it<0){
                return false;
            }
        }
        return true;
    }
};

#include<unordered_map>
///49. Group Anagram  -- medium (字母异位次分组)
class Solution {
public:
    // 利用hash加上排序
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> ans; 
        if(strs.empty())
            return ans; 
        unordered_map<string ,vector<string>>s_map; 
        for(string & w: strs) {
            string t = w; 
            sort(t.begin(), t.end());
            // 根据单词的顺序进行排序 
            s_map[t].push_back(w);
        }
        for(auto &c: s_map) {
            ans.push_back(c.second); 
        }
        return ans; 
    }
};

// 时间复杂度为O(nm) 
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> ans; 
        if(strs.empty())
            return ans; 
        unordered_map<unsigned int, vector<string>>s_map; 
        unsigned int x, y; 
        for(string& w: strs) {
            x = 1; 
            y = 0; 
            for(char& c: w) {
                // 计算字母的ASCII码的乘积和字母的ASCIIASCII之和
                // 最初是想利用c-'a'然后这样的，但是这样就会有特殊情况，这样是不合理的
                //x = c- 'a'+1;
                //y +=x; 
                x *= c; 
                y += c; 
            }
            s_map[y+x].push_back(w);
        }
        for(auto& ww: s_map)
            ans.push_back(ww.second);
        return ans; 
    }
};


/// 1. two sum -easy (两数之和) -->利用hash做
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



/**************************    树、二叉树、二叉搜索树      ************************/

///94. binary tree inorder traversal -Medium (二叉树的中序遍历)



 // Definition for a binary tree node.
 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 

//1- 使用递归法，进行求解
class Solution {
public:

    //显示进行二叉树的中序遍历
    void Traversal(TreeNode* root, vector<int>& vec) {
        if(!root )
            return; 
        Traversal(root ->left, vec);
        vec.push_back(root ->val);
        Traversal(root ->right, vec);
        
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int>ans; 
        Traversal(root,ans );
        return ans; 
    }
};

#include<stack>
//2--> 使用迭代的方法
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> st;
        TreeNode* cur = root;
        while (cur || !st.empty()) {
            if (cur ) { // 指针来访问节点，访问到最底层
                st.push(cur); // 将访问的节点放进栈
                cur = cur->left;                // 左
            } else {
                cur = st.top(); // 从栈里弹出的数据，就是要处理的数据（放进result数组里的数据）
                st.pop();
                result.push_back(cur->val);     // 中
                cur = cur->right;               // 右
            }
        }
        return result;
    }
};




///-- 144. binary tree preorder traversal -medium (前序遍历)
// 1、采用递归的方式进行传递
class Solution {
public:
    //使用递归的方法进行
    void Traversal(TreeNode* root, vector<int>& ans) { // 这里对对于vector的传入方式应该是选择以引用的方式进行参数传递
        if(!root)
            return; 
        ans.push_back(root ->val); 
        Traversal(root ->left, ans);
        Traversal(root ->right, ans);

    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int>ans; 
        Traversal(root, ans);
        return ans; 
    }
};

// 2、采用栈迭代的方进行
class Solution {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        stack<TreeNode*> st;
        vector<int> result;
        if (root == NULL) return result;
        st.push(root);
        while (!st.empty()) {
            TreeNode* node = st.top();                       // 中
            st.pop();
            result.push_back(node->val);
            if (node->right) 
                st.push(node->right);           // 右（空节点不入栈）
            if (node->left) 
                st.push(node->left);             // 左（空节点不入栈）
        }
        return result;
    }
};



//每日一练
// Day6: 299. Bulls and Cows  -medium (猜数字游戏) - 公牛or奶牛、

/********** 这里是自己写的代码，总是有不对的地方，留着以后俩思考     ****************/
class Solution {
public:
    // 使用map, 
    string getHint(string secret, string guess) {
        string ans = ""; 
        int counts_Bulls = 0; 
        int counts_Cols = 0; 
        int all = 0; 
        map<char, int>map_char;
        for(int i = 0; i< secret.size(); ++i) {
            map_char[secret[i]] ++ ;
            if(secret[i] == guess[i])
                ++ counts_Bulls; 
        }
        for(int i = 0; i < guess.size(); ++i) {
           if(map_char.find(guess[i]) != map_char.end() ) {
               if( map_char[guess[i] >= 0]) {
                ++ all ; 
                map_char[guess[i]]--; 
               }
           }
        }
        counts_Cols = all -counts_Bulls; 
        ans += to_string(counts_Bulls) + "A" + to_string(counts_Cols) + "B";
        return ans; 
    }
};

// 后面通过改进的代码 时间繁杂度为O(n)，空间复杂度也为O(n)
class Solution {
public:
    string getHint(string secret, string guess) {
        int counts_Bulls = 0; 
        int counts_Cols = 0; 
        int counts = 0; 
        unordered_map<char, int>map_num; 
        for(int i = 0; i < secret.size(); ++i ) {
            map_num[secret[i]] ++; 
            counts_Bulls += (secret[i] == guess[i]);
        }
        for(auto& c: guess) {
            counts += (map_num[c]-- > 0);
        }
        counts_Cols = counts - counts_Bulls; 
        return to_string(counts_Bulls) + "A" + to_string(counts_Cols) + "B" ;
    }
};

// 通过优化
class Solution {
public:
    string getHint(string secret, string guess) {
        int counts_Bulls = 0; 
        int counts_Cols = 0; 
        int m[256] = {0};
        for (int i = 0; i < secret.size(); ++i) {
            if(secret[i] == guess[i])
                ++ counts_Bulls; 
            else {
                if(m[secret[i]]++ < 0) // 小于0，就是表示在guess中出现过
                    ++ counts_Cols; 
                if(m[guess[i]]-- > 0) // 大于0，就是表示在secret中出现过
                    ++ counts_Cols; 
            }
        }
        return to_string(counts_Bulls) + "A" + to_string(counts_Cols) + "B";
    }
};


//145. Binary tree postorder traversal -medium(二叉树的后序遍历)
//-->1、直接使用递归法
class Solution {
public:
    void PosTraversal(TreeNode* root, vector<int>& ans) {
        if(! root)
            return ; 
        if(root ->left) 
            PosTraversal(root ->left, ans);
        if(root ->right) 
            PosTraversal(root ->right, ans);
        ans.push_back(root ->val);
    }
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int>ans;
        if(!root)
            return ans; 
        PosTraversal(root, ans);
        return ans; 
    }
};

// --> 2、 使用栈模拟法
// 可以直接对前面的谦虚遍历进行一些是适当的修改，然后在对整个数组进行翻转就可以了
class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int>ans; 
        if(!root)
            return ans; 
        stack<TreeNode*>s_tree; 
        s_tree.push(root);
        while( !s_tree.empty()) {
            TreeNode* cur = s_tree.top(); 
            s_tree.pop(); 
            ans.push_back(cur ->val); 
            if(cur ->left)      // 相比于谦虚遍历改动的就是这里了，先入栈是左节点，然后在入栈是右 节点了
                s_tree.push(cur ->left);
            if(cur ->right)
                s_tree.push(cur ->right);
        }
        reverse(ans.begin(), ans.end());
        return ans;   
    }
};


/********************** n-叉树的遍历    **************************/
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;
    Node() {}
    Node(int _val) {
        val = _val;
    }
    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};

//590. Bianry tree Postorder traversal - easy(n叉树的后序遍历)
//1、使用递归法
class Solution {
public:
    void Traversal(Node* root, vector<int>&ans) {
        if(! root)
            return ; 
        for(int i = 0; i< root->children.size(); ++i) {
            Traversal(root ->children[i], ans);
        }
        ans.push_back(root ->val);
    }
    vector<int> postorder(Node* root) {
        vector<int>ans; 
        if(! root)
            return ans; 
        Traversal(root, ans);
        return ans; 

    }
};
//2、使用迭代法，同样也是用栈进行模拟的
class Solution {
public:
    vector<int> postorder(Node* root) {
        vector<int>ans; 
        if(!root) 
            return ans; 
        stack<Node*>s_tree; 
        s_tree.push(root);
        while(! s_tree.empty()) {
            Node* top = s_tree.top(); 
            s_tree.pop();
            ans.push_back(top ->val); 
            for(int i = 0; i< top ->children.size(); ++i ) {
                if(top ->children[i])
                    s_tree.push(top ->children[i]);
            }
        }
        reverse(ans.begin(), ans.end()); 
        return ans; 
    }
};



//589. N-ary tree preorder traversal -easy(n叉树的前序遍历)
//前序遍历
class Solution {
public:
    void Traversal(Node* root, vector<int>&ans) {
        if(!root)
            return ; 
        ans.push_back(root ->val); 
        for (int i = 0; i < root ->children.size(); ++ i) {
            Traversal(root ->children[i], ans);
        }
    }
    vector<int> preorder(Node* root) {
        vector<int>ans; 
        if(! root)   
            return ans; 
        Traversal(root, ans); 
        return ans; 
    }
};


//迭代法
class Solution {
public:
    vector<int> preorder(Node* root) {
        vector<int>ans; 
        if(!root) 
            return ans; 
        stack<Node*>s_tree; 
        s_tree.push(root);
        while(! s_tree.empty()) {
            Node* top = s_tree.top(); 
            s_tree.pop();
            ans.push_back(top ->val); 
            for(int i = top ->children.size()-1;i >=0; --i ) {
                if(top ->children[i])
                    s_tree.push(top ->children[i]);
            }
        }
        //reverse(ans.begin(), ans.end()); 
        return ans; 
    }
};



/*************************  Heap And  Binary-Heap                *********************/

//《剑指offer》40. 最小的k个数
// 1、直接利用sort排序进行操作。
class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int>ans; 
        if(arr.empty())
            return ans; 
        sort(arr.begin(), arr.end());
        for(int i =0; i< k; i++) {
            ans.push_back(arr[i]);
        }     
        return ans; 
    }
};

#include<queue>
class Solution {
public:
// 使用堆的思路，也就是优先队列
// 在C++中，优先队列模拟的大顶堆，所以，直接取k个数来组成大顶堆，而Python则是相反的
// 遇到比大顶堆堆顶大的pass， 比堆顶小的push。
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        vector<int>ans; 
        if(arr.empty() || k ==0) 
            return ans; 
        priority_queue<int>Q_heap; 
        for(int i = 0; i< k; ++i)
            Q_heap.push(arr[i]);
        for(int i = k; i < arr.size(); ++i) {
            if(Q_heap.top() > arr[i]) {
                Q_heap.pop(); 
                Q_heap.push(arr[i]);
            }
        }
        for(int i =0; i< k; ++i) {
            ans.push_back(Q_heap.top());
            Q_heap.pop(); 
        }
        return ans; 
    }
};
     

// Day 09:    1021-删除最层的括号
// 时间复杂度为O(n)
// 这里就是相当于每一次都是出去最外层的括号，开始进行遍历的。
class Solution {
public:
    string removeOuterParentheses(string S) {
        string ans = ""; 
        if(S.empty())
            return ans; 
        int left_bracket= 1; 
        int right_bracket = 0; 
        for(int i = 0; i< S.size(); ++i) {
            if(S[i] == '(') 
                ++ left_bracket; 
            else 
                ++ right_bracket; 
            if(left_bracket != right_bracket)
                ans.push_back(S[i]); 
            else {
                i ++; 
                left_bracket = 1; 
                right_bracket = 0; 
            }
        }
        return ans; 
    }
};

//429. n-ary tree levelc traversal -Medium （n叉树的层序遍历）

// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
// 这里就是利用对队列来模拟的，时间复杂度为O(n)
class Solution {
public:
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> ans; 
        if(! root)
            return ans; 
        queue<Node*>q_tree; 
        q_tree.push(root);
        while(!q_tree.empty()) {
            vector<int> cur_ver; 
            int size_q = q_tree.size(); 
            for(int i = 0; i< size_q; ++ i) {
                Node* cur = q_tree.front(); 
                q_tree.pop(); 
                cur_ver.push_back(cur ->val); 
                for(int j = 0; j < cur ->children.size(); ++j ) {
                    if(cur ->children[j])
                        q_tree.push(cur ->children[j]);
                }
            }
            ans.push_back(cur_ver);
        }
        return  ans; 
    }
};

// 使用递归来做， 也就是dfs

class Solution {
public:
    void dfs(Node* root, vector<vector<int>>& ans, int levels) {
        if(!root)
            return ; 
        if(ans.size() == levels)
            ans.push_back(vector<int>());
        ans[levels].push_back(root->val); 
        for(auto &c: root ->children)
            dfs(c, ans, levels+1); 
    }
    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>>ans; 
        if(! root)
            return ans; 
        dfs(root, ans, 0); 
        return ans; 
    }
};


//239。Sliding window maximum -Hard (滑动窗口最大值)

class Solution {
public:
        // 第二遍
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int>ans; 
        if(nums.empty() )
            return ans; 
        deque<int>window; 
        // 这里就是在第一个窗口总放入一个最大的值
        for(int i =0; i< k; ++i) {
            while( ! window.empty() && nums[i] >nums[window.back()])
                window.pop_back();
            window.push_back(i); 
        }
        // 这里就是维护一个单调递减的双端队列，然后想队列中，添加的是元素在数组中的下标而不是具体的数据
        ans.push_back(nums[window.front()]); 
        for(int i = k; i< nums.size(); ++i) {
            if(! window.empty() && window.front() <= i -k) 
                window.pop_front(); 
            while( !window.empty() && nums[i] > nums[window.back()]) 
                window.pop_back(); 
            window.push_back(i); 
            ans.push_back(nums[window.front()]); 
        }
        return ans; 
    }
};

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        if (n == 0) return vector<int>();
        vector<int>p(n,0);
        int kaka = k - 1;
        vector<int> res(n, 0);
        int hh = 0, tt = -1;
        for (int i = 0; i < n; i ++){
            if (hh <= tt && i - k + 1 > q[hh]) hh ++;
            while (hh <= tt && nums[q[tt]] <= nums[i]) tt --;

            q[++ tt] = i;
            if (i >= k - 1) res[i - k + 1] = nums[q[hh]];
        }

        while (kaka --) res.pop_back();
        return res;
    }
};


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


