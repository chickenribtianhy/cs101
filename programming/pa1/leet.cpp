#include <iostream>
#include <string.h>
struct TrieNode
{
    TrieNode *next[26];
    char c;
    bool isWord; //用于保存当前字符是否是单词结尾

    TrieNode(char _c) : c(_c), isWord(false)
    {
        memset(next, 0, sizeof(TrieNode *) * 26);
    }
};

//实现Trie前缀树
class Trie
{
public:
    TrieNode *root;
    /** Initialize your data structure here. */
    Trie()
    {
        root = new TrieNode(' ');
    }

    /** Inserts a word into the trie. */
    void insert(string word)
    { //向前缀树中插入单词word
        int n = word.size();
        TrieNode *currentNode = root;
        for (int i = 0; i < n; i++)
        {
            if (!currentNode->next[word[i] - 'a'])
            {
                currentNode->next[word[i] - 'a'] = new TrieNode(word[i]);
            }

            currentNode = currentNode->next[word[i] - 'a'];
        }
        currentNode->isWord = true;
    }

    /** Returns if the word is in the trie. */
    bool search(string word)
    { //搜索树中是否存在单词word
        int n = word.size();
        TrieNode *currentNode = root;
        for (int i = 0; i < n; i++)
        {
            int index = word[i] - 'a';

            if (currentNode->next[index])
            {
                currentNode = currentNode->next[index];
            }
            else
            {
                return false;
            }
        }
        return currentNode->isWord;
    }

    string startsWith(string word, int nWord)
    {
        TrieNode *currentNode = root;
        string result;
        for (int i = 0; i < word.size(); i++)
        {
            int count = 0;
            //统计每个节点下有多少个有效节点
            for (int j = 0; j < 26; ++j)
            {
                if (currentNode->next[j])
                {
                    count++;
                }
            }

            if (count == 1)
            {
                result = word.substr(0, i + 1);
            }
            else
            {
                break;
            }

            if (currentNode->next[word[i] - 'a']->isWord) //当前缀树某一节点是单词的标志时即停止查找
            {
                break;
            }

            currentNode = currentNode->next[word[i] - 'a'];
        }
        return result;
    }

    //14最长公共前缀

    string longestCommonPrefix(vector<string> &strs)
    {
        int n = strs.size();
        if (n == 0)
        {
            return ""; //当输入数组为空时，返回空字符串
        }

        for (int i = 0; i < n; i++)
        {
            if (strs[i].size() == 0) //数组中某一字符串为空时，则返回空字符串
                return "";
            insert(strs[i]); //前缀树的特点：在查询前先插入字符串
        }

        string result = startsWith(strs[0], n); //查询过程
        return result;
    }
};
