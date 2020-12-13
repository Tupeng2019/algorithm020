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






















