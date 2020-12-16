#include<iostream>



using namespace std; 



/*************         深度优先遍历和广度优先遍历                *********************/


#include<unordered_set>
#include<unordered_map>
#include<queue> 


// 127. Word ladder (单词接龙) - Medium       ( 这题还是比较难的，还是需要更多的练习吧)
// 针对这类的复杂类型的题，还是不够快速，得利用多点时间吧，
// 1. 利用广度优先搜索BFS
class Solution {
public:
// 1.Times
    // 直接使用BFS
    // 利用的就是一个单词之间只是差了一个字母，然后进行一次又一次的进行替换就好，这里就是关键
    // 只是需要利用好这个条件，然后就可以利用广度优先搜索就好了，利用队列实现BFS。
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        // 将word放在set中进行快速的查找
        unordered_set<string>wordSet(wordList.begin(), wordList.end()); 
        if(wordSet.find(endWord) == wordSet.end())
            return 0; // 表示灭有出现最后一个单词
        // 判断word是否已经出现过了
        // map.second 记录的就是这个word出现的长度
        unordered_map<string, int>Vis_map;
        queue<string>que; 
        // 将首单词放入到队列，中
        que.push(beginWord); 
        // 初始化map
        Vis_map.insert(pair<string,int>( beginWord, 1)); 
        while( ! que.empty()) {
            string word = que.front(); 
            que.pop(); 
            int path = Vis_map[word]; 
            // 这里就是对每一个单词，进行每一个字母进行查找相似
            for(int i = 0; i< word.size(); ++i) {
                string newword = word; 
                // 进行字母的替换
                for( int j = 0; j < 26; ++j) {
                    // 这里就是替换，替换一个字母，看是否是有这样的单词在Set中间，
                    newword[i] = j +'a'; 
                    if(newword == endWord)
                        return path +1; 
                    // 这个单词存在set中，不存在map中就是说明这个单词是可行的，并且还没有访问过
                    if(wordSet.find(newword) != wordSet.end() && 
                         Vis_map.find(newword) == Vis_map.end()) { 
                             // 添加访问信息，也就是在路径上增加一个信息，，
                            //  也就是这个单词已经访问过了，后面的就不能在访问了
                             Vis_map.insert(pair<string, int> (newword,path +1));
                             // 这里就是将所有的具有一个不同字母的单词全部都放在了同一层的队列中
                             // 因为这里就是利用的广度优先搜索，所以最先找到的答案就是最佳的答案
                             que.push(newword); 
                         } 
                }
            }
        }
        return 0; 
    }
};
/////////////////////////////////   整体思考下来，还是挺清晰的，挺清晰了。


//126. word ladder -II





//200. number of islands
class Solution {
public:
// 1.Times
    // 使用DFS
    void Dfs(vector<vector<char> >& grid, int i , int j) {
        if(Edge(i, j, grid.size(), grid[0].size()) && grid[i][j]=='1') {
            // 将遍历过得全标记为**
            grid[i][j] = '*'; 
            // 进行遍历访问了
            Dfs(grid, i, j +1); 
            Dfs(grid, i , j-1); 
            Dfs(grid, i +1, j); 
            Dfs(grid, i -1, j); 
        }
    }
    //这里就是条件判断,
    bool Edge(int i, int j, int row, int col){
        return (0 <= i) && (i < row) && (j >=0) && (j < col); 
    }
    int numIslands(vector<vector<char>>& grid) {
        int counts_island = 0; 
        for(int i = 0; i< grid.size(); ++ i) {
            for(int j =0; j <grid[0].size(); ++j) {
                // 是否是为1
                if(grid[i][j]== '1'){
                    counts_island ++; 
                    Dfs(grid, i, j); 
                }
            }
        }
        return counts_island;  
    }
};




/// 529 。 扫雷游戏


class Solution {
public:
// 1.Times 
    // 使用DFSDFS
    // 因为一个方块的周围有八个方块，所以这里将方向定在8
    int dir_x[8] = {0, 1, 0, -1, 1, 1, -1, -1}; 
    int dir_y[8] = {1, 0, -1, 0, 1, -1, 1, -1}; 
    void dfs(vector<vector<char>>& board, int x, int y) {
        int counts = 0; 
        // 这一个循环就是记录，在选定的一个方块的八个方向上，有几个地雷
        for(int i = 0; i< 8; ++i) {
            int tx = x + dir_x[i]; 
            int ty = y + dir_y[i]; 
            if(tx < 0 || ty < 0 || tx >= board.size() || ty >= board[0].size()) 
                continue; 
                //记录有几个炸弹
            counts += board[tx][ty] == 'M'; 
        }
        if(counts >0)
        // 表示相邻的地雷的数量也
        // 即是规则3
            board[x][y] = counts + '0'; 
        else {
            // 也就是当这一块没有地雷时，将其定为B
        // 规则2
            board[x][y] = 'B'; 
            for(int i = 0; i <8; ++i) {
                int tx = x + dir_x[i]; 
                int ty = y + dir_y[i]; 
                if(tx < 0 || tx >= board.size() || ty < 0 || ty >= board[0].size() || board[tx][ty] != 'E')
                    continue; 
                // 这里就是进行搜索的关键一步了，就是选择下一个位置进行迭代
                dfs(board, tx, ty); 
            }
        }
    }
    vector<vector<char>> updateBoard(vector<vector<char>>& board, vector<int>& click) {
        int x = click[0], y = click[1]; 
        if(board[x][y] == 'M') {
            // 进行规则1
            board[x][y] = 'X'; 
        }
        else 
            dfs(board, x, y); 
        
        return board; 
    }
};



// 860.柃檬水找零
class Solution {
public:
// 3。Times
    // 直接使用贪心算法就可以了
    bool lemonadeChange(vector<int>& bills) {
        int five = 0, ten = 0;
        for(int i = 0; i < bills.size(); ++i) {
            if(bills[i] == 5) {
                ++five;
            } else if(bills[i] == 10 && five) {
                ten++;
                five--;
            } else {
                if(ten && five) {
                    five--;
                    ten--;
                }else if(five >= 3) {
                    five -= 3;
                }else {
                    return false;
                }
            }
        }
        return true;
    } 
};

// 122. 买卖股票的最佳时机-II
class Solution {
public:
// 2.Times 
    // 使用贪心算法
    int maxProfit(vector<int>& prices) {
        int ans = 0; 
        int n = prices.size(); 
        for( int i = 1; i< n; ++i) {
            ans += max(0, prices[i] - prices[i -1]);
        }    
        return ans; 
    }
};



class Solution {
public:
// 2.Times
     // 使用动态规划，时间复杂度为O(n)， 空间复杂度为o(n)
    int maxProfit(vector<int>& prices) {
        int n = prices.size(); 
        // 这里的dp就是两个状态，为0表示为这里不取上，为1就是表示将这个值取上
        vector<vector<int>>dp(n, vector<int>(2,0)); 
        dp[0][1] = - prices[0]; 
        for(int i = 1; i < n; ++i) {
            dp[i][0] = max(dp[i -1][0], dp[i -1][1] + prices[i]); 
            dp[i][1] = max(dp[i -1][1], dp[i -1][0] - prices[i]); 
        }
        return max(dp[n-1][0], dp[n-1][1]); 
    }
};




/// 455. 分发饼干
// 时间复杂度：O(nlogn)
// 空间复杂度：O(1)
class Solution {
public:
// 1.Times 
    // 使用贪心算法，将大饼干分给胃口大的孩子O(nlogn)
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end()); 
        sort(s.begin(), s.end()); 
        int index = s.size() -1; 
        int ans = 0; 
        for(int i = g.size() -1; i >= 0; -- i) {
            if(index >=0 && s[index] >= g[i]) {
                ++ ans; 
                index --; 
            }
        }
        return ans; 
    }
};


class Solution {
public:
//1.times 
    // 使用贪心，和上面的过程就是相反的理解，从小的开始依次进行分发
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(),g.end());
        sort(s.begin(),s.end());
        int res = 0;
        int index = 0;
        for(int i = 0;i < s.size();++i){
            if(index < g.size() && g[index] <= s[i]){
                index++;
                res++;
            }
        }
        return res;
    }
};


#include<set>
// 874. 模拟行走的机器人
/// 

class Solution {
public:
//1.Times
    // 直接进行模拟，
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        int x = 0, y = 0, di = 0;

        set<vector<int>> obstacleSet;
        for (auto& obstacle: obstacles)
            obstacleSet.insert(obstacle);

        int ans = 0;
        for (int cmd: commands) {
            if (cmd == -2)
                di = (di + 3) % 4;
            else if (cmd == -1)
                di = (di + 1) % 4;
            else {
                for (int k = 0; k < cmd; ++k) {
                    int nx = x + dx[di];
                    int ny = y + dy[di];
                    if (obstacleSet.find({nx, ny}) == obstacleSet.end()) {
                        x = nx;
                        y = ny;
                        ans = max(ans, x*x + y*y);
                    }
                }
            }
        }

        return ans;
    }
};



///55. jump game (跳跃游戏 Medium)
class Solution {
public:
    // 1.times
    // 利用贪心算方式，每次只是需要进行当前所能够达到的最大位置，如果最后所能到达的位置是覆盖最后一个位置。
    // 那么就返回true
    // 时间复杂度为O(n）， 
    bool canJump(vector<int>& nums) {
        int n  = nums.size(); 
        // 表示最后能够覆盖的最大的距离
        int most_dir = 0; 
        for(int i = 0; i< n; ++i) {
            if(i <= most_dir) { // 表示从当下的位置到最大距离的位置之间的都是可以道到达的位置
                // 这里利用i + nums[i] ,就是表示能够到达的这个位置，和该位置的最大距离
                most_dir = max( most_dir, i + nums[i]); 
                if(most_dir >= n -1)
                    return true; 
            }
        }
        return false; 
    }
};

// 基于上面的进行思路的简化，模拟跳法
// 基本方式还是一样的，乜有什么变化，只是代码的方式变换一点点而已了
bool canJump(vector<int>& nums) 
{
	int k = 0;
	for (int i = 0; i < nums.size(); i++)
	{
		if (i > k) return false;
		k = max(k, i + nums[i]);
	}
	return true;
}


//*****************************************
/// 45. jump game-II (跳跃游戏-2)  --- Hard
// 利用贪心算法，每一次都是维护能够到达的最远的位置，那么最后得到的就是最少的跳跃次数
class Solution {
public:
// 1 Times
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


/****************************     二分查找              *************************/


// **********************************
/// 33. 搜索旋转排序数组 -Medium 
class Solution {
public:
//1.Times
    // 直接二分查找
    // 这个题的特殊性，就是是围绕一个点进行旋转了，所以按照二分法，进行肯定是有一部分是按照升序进行排序的
    int search(vector<int>& nums, int target) {
        if(nums.empty())
            return -1; 
        if(nums.size() ==1)
            return target == nums[0] ? 0: -1; 
        int left = 0; 
        int right = nums.size()-1; 
        int n = nums.size(); 
        //sort(nums.begin(), nums.end()); 
        while(left <= right) {
            int mid = left + (right - left)/2; 
            if(nums[mid] == target)
                return mid; 
            if(nums[0] <= nums[mid]) {  // 这里就是表示左边的可能就是升序排列的
                if(nums[0] <= target && target < nums[mid]) {
                    right = mid -1; 
                }
                else 
                    left = mid +1; 
            }
            else {
                if(nums[mid] < target && target <= nums[n -1]) {
                    left = mid +1; 
                }
                else 
                    right = mid -1; 
            }
        }
        return -1; 
    }
};


// *********************************
/// 74. 搜索二维矩阵，
// 直接暴力法
class Solution {
public:
// 1.times 
    // 直接暴力法
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty())
            return false; 
        for(int i = 0; i< matrix.size(); ++i) {
            for(int j = 0; j < matrix[0].size(); ++j) {
                if(matrix[i][j] == target)
                    return true; 
            }
        }
        return false; 
    }
};


// 使用二分找
class Solution {
public:
// 1.Times 
    // 使用二分查找法
    // 这里就是应用的整体二分法，将所有的序号，相当于就是排成一行
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        if(!m)
            return false; 
        int n = matrix[0].size(); 

        int left = 0, right = m*n -1; 
        int mid, mid_element; 
        while(left <= right) {
            mid = (left + right)/2; 
            mid_element = matrix[mid /n][mid %n]; 
            if(target == mid_element)
                return true; 
            else {
                if(target < mid_element) 
                    right = mid -1; 
                else    
                    left = mid +1; 
            }
        }
        return false; 
    }
};


//*************************************
/// 153. 寻找旋转排序数组中的最小值
// 这个题还是挺简单的了
class Solution {
public:
// 1.Times 
    // 直接暴力法
    int findMin(vector<int>& nums) {
        if(nums.empty())
            return -1; 
        int ans = INT_MAX; 
        for(int i = 0; i< nums.size(); ++ i) {
            ans = min(ans, nums[i]); 
        }
        return ans;     
    }
};


// 使用二分法
class Solution {
public:
// 1.Tiems
    // 二分法
    int findMin(vector<int>& nums) {
        int left = 0; 
        int right = nums.size() -1; 
        if(nums[0] < nums[right]) // 就是表示是有序的
            return nums[left]; 
        while(left < right) {
            int mid = left + (right -left) /2; 
            if(nums[0] > nums[mid])
                right = mid; 
            else 
                left = mid +1; 
        }
        return nums[left]; 
    }
};































