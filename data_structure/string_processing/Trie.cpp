#include <iostream>
#include <unordered_map>

#include <array>
#include <vector>

using namespace std;

///////////////////////////////////////////////////////////////
///////  ACCEPTED
////// https://www.hackerrank.com/challenges/sparse-arrays/problem
//////////////////////////////////////////////////////////////

struct TrieNode
{
    unordered_map<char, TrieNode *> nextRoute;
    int endCounter;
    TrieNode()
    {
        endCounter = 0;
    }
    bool hasNextNodeUsing(char ch)
    {
        return nextRoute.find(ch) != nextRoute.cend();
    }
    TrieNode *getNextNodeUsing(char ch)
    {
        return nextRoute[ch];
    }
    void setNextNode(char ch, TrieNode *nextNode)
    {
        nextRoute[ch] = nextNode;
    }
};

class Trie
{
private:
    TrieNode *root = nullptr;

public:
    Trie()
    {
        root = new TrieNode();
    }

    void insert(string s)
    {
        TrieNode *node = root;
        for (int i = 0; i < s.size(); i++)
        {
            if (node->hasNextNodeUsing(s[i]) == false)
            {
                node->setNextNode(s[i], new TrieNode());
            }
            node = node->getNextNodeUsing(s[i]);
        }
        node->endCounter++;
    }

    int getFrequency(string s)
    {
        TrieNode *node = root;
        for (int i = 0; i < s.size(); i++)
        {
            if (node->hasNextNodeUsing(s[i]))
                node = node->getNextNodeUsing(s[i]);
            else
                return 0;
        }
        return node->endCounter;
    }

    int deleteString(string s)
    {
        TrieNode *node = root;
        for (int i = 0; i < s.size(); i++)
        {
            if (node->hasNextNodeUsing(s[i]))
                node = node->getNextNodeUsing(s[i]);
            else
                return 0;
        }
        node->endCounter--;
        return true;
    }
};

int main()
{
    array<string, 3> stringList = {"ab", "abc", "ab"};
    array<string, 3> queries = {"ab", "abc", "ab"};
    Trie trie;
    for (auto s : stringList)
    {
        trie.insert(s);
    }
    vector<int> answer;
    for (auto s : queries)
    {
        answer.emplace_back(trie.getFrequency(s));
        cout<<answer[answer.size()-1]<<endl;
    }

    return 0;
}
