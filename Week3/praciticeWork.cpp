#include<iostream>
#include<vector>

using namespace std; 

/*****************************   递归方面的题  ********************/

//22. Generate parentheses (括号的生成)
//直接使用暴力法，先生成所有的可能情况，然后在检查每一个就好了
class Solution {
public:
// 1. Times
// 直接使用暴力法，进行求解
    bool Valid(const string& str) {
        // 次函数就是进行判断是否生成合法的括号
        int balance = 0; 
        for(char c: str) {
            if(c =='(')
                ++ balance; 
            else 
                -- balance; 
            if(balance < 0)
                return false; 
        }
        return balance ==0; // 最后返回的是0，则表示就是合法的了
    }
    // 生成所有的括号的情况了
    void generate_all(string& cur, int n, vector<string>&vec) {
        if(n == cur.size()) {
            if(Valid(cur))
                vec.push_back(cur); 
            return ; 
        }
        cur +='('; 
        generate_all(cur, n, vec); 
        cur.pop_back(); 
        cur += ')'; 
        generate_all(cur, n, vec); 
        cur.pop_back(); 
    }
    vector<string> generateParenthesis(int n) {
        vector<string>ans; 
        string current; 
        generate_all(current, n *2, ans); 
        return ans; 
    }
};
// 使用回溯法，进行

//2- 使用回溯法
class Solution {
public:
//1.Times 
    //使用回溯法，lc, rc 可以理解为左右括号的个数
    // 同时这了采用的深度优先搜索的方式进行的。
    void dfs( vector<string>& res, string path, int n, int lc, int rc) {
        if(rc >lc || lc > n || rc > n)
            return ; 
        if(lc == rc && lc ==n) {
            res.push_back(path); 
            return ; 
        }
        // 这里就是进行深度优先搜索的关键顺序
        dfs(res, path +'(', n, lc +1, rc); 
        dfs(res, path +')', n, lc, rc +1); 
    }
    vector<string> generateParenthesis(int n) {
        vector<string>ans; 
        int lc = 0; 
        int rc = 0; 
        dfs(ans, "", n, lc, rc); 
        return ans; 
    }
};





//226. invert binary tree (翻转二叉树)
// Definition for a binary tree node.
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

// 使用递归，时间复杂度为O(n)
// 1.Times
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if(! root)
            return nullptr; 
        // 这里的思路就是：先提取左右的子节点，然后在进行交换即可。
        TreeNode* left = invertTree(root -> left);
        TreeNode* right = invertTree(root -> right); 
        root ->left = right; 
        root ->right = left; 
        return root; 
    }
};


class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == NULL) return root;
        swap(root->left, root->right);  // 中
        invertTree(root->left);         // 左
        invertTree(root->right);        // 右
        return root;
    }
};

#include<stack>
// using stack to do 
//dfs
class Solution {
public:
//1.Times
    // 使用dfs
    TreeNode* invertTree(TreeNode* root) {
        if(!root)
            return nullptr; 
        stack<TreeNode*>s_tree; 
        s_tree.push(root); 
        while(!s_tree.empty()) {
            TreeNode* cur = s_tree.top(); 
            s_tree.pop(); 
            swap(cur ->left, cur ->right); 
            if(cur ->left)
                s_tree.push(cur ->left);
            if(cur -> right)
                s_tree.push(cur ->right); 
        }
        return root; 
    }
};

#include<queue>
// 广度优先搜索
// 就是利用队列类模拟
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        queue<TreeNode*> que;
        if (root != NULL) que.push(root);
        while (!que.empty()) {
            int size = que.size();
            for (int i = 0; i < size; i++) {
                TreeNode* node = que.front();
                que.pop();
                swap(node->left, node->right); // 节点处理
                if (node->left) que.push(node->left);
                if (node->right) que.push(node->right);
            }
        }
        return root;
    }
};



// 98.validate binary search tree 验证二叉树，（Medium）
// 1.Times
// 直接使用中序遍历，然后对最后的数组进行是否是递增的判断，就可以了，
// 此时间复杂度为O(n)，空间复杂度为O(n)

//Definition for a binary tree node.
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
//1.Times
    // 使用中序遍历，中序遍历的数组是按递增的方式排列的，
    void inorder(TreeNode* root, vector<int>& ans) {
        if(!root)
            return ; 
        if(root -> left)
            inorder(root ->left, ans); 
        ans.push_back(root ->val); 
        if(root -> right)
            inorder(root ->right, ans); 
    }
    bool isValidBST(TreeNode* root) {
        vector<int>ans; 
        if(! root)
            return false; 
        inorder(root, ans); 
        for(int i = 1; i< ans.size(); ++i) {
            if(ans[i]<= ans[i-1])
                return false; 
        }
        return true; 
    }
};

//104.maximum depth of bianry tree(二叉树的最大深度)  -Easy

// Definition for a binary tree node.
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Solution {
public:
//2.Times
    // 使用广度优先遍历，遍历的最大层数就是二叉树的最大深度。.
    int maxDepth(TreeNode* root) {
        int counts = 0; 
        if(! root)
            return counts; 
        queue<TreeNode*>Q_tree; 
        Q_tree.push(root); 
        while(! Q_tree.empty()) {
            int size_Q = Q_tree.size(); 
            while(size_Q >0) {
                TreeNode* cur = Q_tree.front(); 
                Q_tree.pop(); 
                if(cur ->left)
                    Q_tree.push(cur ->left); 
                if(cur ->right)
                    Q_tree.push(cur ->right); 
                -- size_Q; 
            }
            ++ counts; 
        }
        return counts; 
    }
};

// 直接使用递归的方式，时间复杂度O(n)
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};




/// 111. minimum depth of binary tree(二叉树的最小深度) - Easy
//1.Times 
    // 使用递归的方式，
class Solution {
    int minDepth(TreeNode* root) {
        if(! root)
            return 0; 
        int min_1 = minDepth(root ->left); 
        int min_2 = minDepth(root ->right); 
        //如果左右孩子都为空的情况下，直接返回层数加一
        // 如果都不为空，咋直接返回较小的深度加一
        return root ->left && root -> right ?min(min_1,min_2) +1: min_1 +min_2 +1; 
    }
};

// 利用深度优先
// 
class Solution {
public:
//1.Times 
    // dfs
    int minDepth(TreeNode* root) {
        if(!root)
            return 0; 
        if(!root ->left && !root ->right)
            return 1; 
        int min_d= INT_MAX; //因为每次去的小，所以这里就是必须用int的最大值来表示
        if( root ->left)
            min_d = min(min_d, minDepth(root ->left)); 
        if( root ->right)
            min_d = min(min_d, minDepth(root ->right));
        return min_d +1; 
    }
};

//利用Bfs（广度优先搜索）
class Solution {
public:
    int minDepth(TreeNode *root) {
        if (!root ) 
            return 0;
        queue<pair<TreeNode *, int> > que;
        que.emplace(root, 1);
        while (!que.empty()) {
            TreeNode *node = que.front().first;
            int depth = que.front().second;
            que.pop();
            if (node->left == nullptr && node->right == nullptr) {
                return depth;
            }
            if (node->left != nullptr) {
                que.emplace(node->left, depth + 1);
            }
            if (node->right != nullptr) {
                que.emplace(node->right, depth + 1);
            }
        }

        return 0;
    }
};



///297. serialize ans deserialize binary tree (Hard) (二叉树的序列化与反序列化)
// 这道题还是需要好好理解的，还是比较难的
#include<sstream>
// Definition for a binary tree node.
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

class Codec {
public:
    void serialize(TreeNode* root,ostringstream& out){
        if(root){
            out<<root->val<<' ';
            serialize(root->left,out);
            serialize(root->right,out);
        }else{
            out<<"# ";
        }
    }
    TreeNode* deserialize(istringstream& in){
        string val;
        in>>val;
        if(val=="#"){
            return nullptr;
        }
        TreeNode* root=new TreeNode(stoi(val));
        root->left=deserialize(in);
        root->right=deserialize(in);
        return root;
    }
    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        ostringstream out;
        serialize(root,out);
        return out.str();
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        istringstream in(data);
        return deserialize(in);
    }
};
// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));


// 这里就是leetcode上面的最优的解，还需要好好的看看
class Codec {
public:

    char* serialize(TreeNode *root) {    
        vector<int> vals;
        this->PreOrder(root, vals);
        
        int size = vals.size();
        int *res = new int[size];
        for (int i=0;i<size;i++) res[i] = vals[i];
        return (char*)res;
    }
    
    void PreOrder(TreeNode *root, vector<int>&vals) {
        if (root!=NULL) {
            vals.push_back(root->val);
            this->PreOrder(root->left, vals);
            this->PreOrder(root->right, vals);
        } else {
            vals.push_back(INT_MAX);   // -1
        }
    }
    
    TreeNode* BuildTree(int *&p) {
        if (*p==INT_MAX) {
            ++p;
            return NULL;
        }
        
        TreeNode *T = new TreeNode(*p);
        ++p;
        T->left = this->BuildTree(p);
        T->right = this->BuildTree(p);
        
        return T;
    }
    TreeNode* deserialize(char *str) {
        int *p = (int *)str;
        return this->BuildTree(p);
    }
};








