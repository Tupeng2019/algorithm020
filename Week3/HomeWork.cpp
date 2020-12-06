#include<iostream>

using namespace std; 



/// 236. 
// lowest common ancestor of a binary tree (Medium) 二叉树的最近父节点

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
    // 利用深度优先遍历，时间复杂度为O(n)
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root == nullptr)
            return nullptr; 
        if(root ==p || root ==q) // 这里既是更节点就是这辆个节点的其中之一
            return root; 
        TreeNode* left = lowestCommonAncestor(root ->left, p, q);
        TreeNode* right = lowestCommonAncestor(root -> right, p, q);
        if(! left )
            return right; 
        if(! right)
            return  left; 
        if(left && left) // 如果p,q就是分布在此时的根节点的两侧
            return root; 
        return root; 
    }
};

// 这两种做法都是一样的，只是代码的简洁性不一样而已
class Solution {
public:
// 1.Times

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(!root || root== p || root == q)
            return root; 
        TreeNode* left = lowestCommonAncestor(root -> left, p, q); 
        TreeNode* right = lowestCommonAncestor(root ->right, p, q); 
        if(left && right)
            return root; 
        return left? left:right;         
    }
};


#include<vector>
/// 105. 
// construct binary tree from preorder ans inorder traversal (Medium从前序与中序遍历序列构造二叉树)
class Solution {
public:
//1.Times 
    // 使用递归的思路,显然时间复杂度为O(n)，需要对所以的节点进行遍历,但是这里的空间复杂度就不好计算了，
    // 利用前序遍历的特点，也就是更节点总是在最前面，而中序遍历就是根节点的左边就是左子树，右边就是柚子树
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size(); 
        if(!n )
            return nullptr; 
        // 前序遍历的第一个数字，就是二叉树的根节点
        TreeNode* root = new TreeNode(preorder[0]);
        vector<int>p_left, i_left, p_right, i_right; 
        // 在中序遍历中找到根节点，然后划分左右子树
        int i= 0;  // 因为需要划分左右子树，所以讲i设置为全局变量
        for( ; i< n; ++i) {
            if(inorder[i] == preorder[0])
                break; 
            // 这里就是构建左子树   
            i_left.push_back(inorder[i]);
        }
        for(i = i+1; i < n; ++i) {
            i_right.push_back(inorder[i]);
        }
        //需要构建左右子树的前序遍历
        for(int j = 1; j <n; ++j) {
            if(j <= i_left.size())
                p_left.push_back(preorder[j]); 
            else 
                p_right.push_back(preorder[j]); 
        }
        // 进行递归
        root ->left = buildTree(p_left, i_left); 
        root ->right = buildTree(p_right, i_right); 
        return root; 
    }
};

#include<unordered_map>
// 根据官方的题解对上面的整体思路，进行代码的优化
// 利用map快速的进行根节点的定位
class Solution {
// 1.Times
// 使用哈希，进行优化，时间复杂度为O(n)，空间复杂福也是O(n)
    unordered_map<int, int>map_index; 
public:
    TreeNode* BuildTree(const vector<int>& preorder, const vector<int>& inorder, int  p_left, int p_right, int i_left, int i_right) {
        if(p_left > p_right)
            return nullptr; 
        int p_root = p_left; 
        //在中序遍历中定位根节点
        int i_root = map_index[preorder[p_root]]; 
        // 现将整个根节点给设置出来
        TreeNode* root = new TreeNode(preorder[p_root]); 
        int size_left = i_root - i_left; 
        // 使用递归构造左子树
        root ->left = BuildTree(preorder, inorder, p_left +1,p_left+ size_left, i_left, i_root - 1 ); 
        // 使用递归构建柚子树
        root -> right = BuildTree(preorder, inorder, p_left+ size_left+1, p_right, i_root +1, i_right); 
        return root; 
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size(); 
        for(int i = 0; i < n; ++i) {// 这里是至关重要的，因为是以中序遍历进行左右子树的划分的
            map_index[inorder[i]] = i; 
        }
        return BuildTree(preorder, inorder, 0, n-1, 0, n-1);
    }
};


/// 77. combinations (组合)  ---Medium

class Solution {
public:
//1.Times 
    // 直接使用递归，深度有效搜索,+ 回溯法
    vector<int>cur_vec; 
    vector<vector<int>>ans; 
    void DFS(int cur, int n, int k ){
        if(cur_vec.size() + n-cur +1 < k)
            return ; 
        // 记录正确的答案
        if(cur_vec.size() == k){
            ans.push_back(cur_vec); 
            return ; 
        }
        // 选择当前的位置，
        cur_vec.push_back(cur); 
        DFS( cur +1, n, k); 
        // 不选择当前的位置
        cur_vec.pop_back(); 
        DFS(cur +1, n, k); 
    }
    vector<vector<int>> combine(int n, int k) {
        DFS(1, n, k); 
        return ans; 
    }
};


///46
// permutations-I(全排序)  --Medium
class Solution {
public:
// 1 .Times
    //使用回溯法,时间复杂度为O(n * n!),空间度咋读为O（n）
    // 在这里的思想，和数学常用的方式是一样的，先固定一个位置，然后在下一个位置时，用所有的数字都去做一遍
    void backtrack(vector<vector<int>>& ans, vector<int>& nums, int first, int end) {
        if(first == end) {
            ans.push_back(nums); 
            return ; 
        }
        for(int i = first; i< end; ++i) {
            swap(nums[i], nums[first]); 
            backtrack(ans, nums, first+ 1, end); 
            swap(nums[i], nums[first]); 
        }
    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans; 
        backtrack(ans, nums, 0, nums.size()); 
        return ans;    
    }
};


#include<algorithm>
/// 47. 
// permutations- II (Medium)
// 这个题和上面的哪一题，可以用同样的方法进行做，只是要去除一些重复的数字就行了
class Solution {
public:
//1.Times
    vector<int>vec; 
    void Backtrack(vector<int>& nums, vector<vector<int>>& ans, int index, vector<int>& cur) {
        if(index == nums.size()) {
            ans.push_back(cur); 
            return; 
        }
        for(int i = 0; i< nums.size(); ++ i) {
            if(vec[i] || (i >0 && nums[i] == nums[i-1] && ! vec[i-1]))
                continue; 
            cur.push_back(nums[i]); 
            vec[i] = 1; 
            Backtrack(nums, ans, index +1, cur); 
            vec[i] = 0; 
            cur.pop_back(); 
        }
    }
    vector<vector<int>> permuteUnique(vector<int>& nums) {
       vector<vector<int>> ans; 
       vector<int>cur; 
       vec.resize(nums.size()); 
       sort(nums.begin(), nums.end()); 
       Backtrack(nums, ans, 0, cur); 
       return ans; 
    }
};














