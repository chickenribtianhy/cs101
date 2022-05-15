#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Letter
{
public:
    Letter()
    {
        m_heir_num = 0;
    }
    Letter(char letter)
    {
        m_letter = letter;
        m_heir_num = 0;
    }
    void append(Letter *heir)
    {
        m_heir.push_back(heir);
        m_heir_num += 1;
    }

    void dfs(Letter *root)
    {
        Letter *state = root;
        for (int i = 0; i < m_heir_num; ++i)
        {
            cout << state->m_letter;
            Letter *tmp = state;
            state = this->m_heir[i];
            dfs(state);
            state = tmp;
        }
        cout << endl;
    }

    char m_letter;
    vector<Letter *> m_heir;
    int m_heir_num;
};

int main()
{
    int n;
    cin >> n;
    Letter *root = nullptr;
    for (int i = 0; i < n; ++i)
    {
        string word;
        cin >> word;
        int j = 0;
        for (; j < word.length(); ++j)
        {
            cout << word[j];
        }
        cout << word;
        cout << "hi";
        Letter *state = root;
        // int j = 0;
        j = 0;
        bool is_found = true;
        // for (; j < word.length(); ++j)
        // {
        while (is_found)
        {
            is_found = false;
            for (int k = 0; k < root->m_heir_num; ++k)
            {
                if (word[j] == state->m_heir[k]->m_letter)
                {
                    state = state->m_heir[k];
                    is_found = true;
                    break;
                }
            }
        }
        // if (!is_found)
        // break;
        // }
        for (; j < word.length(); ++j)
        {
            state->append(new Letter(word[j]));
            state = state->m_heir[0];
        }
    }

    root->dfs(root);

    return 0;
}




int dfs(Letter *root, int height, int max_height, string words, string affix)
{
    if (root->m_heir_num == 0)
    {
        return 1;
    }
    Letter *state = root;
    for (int i = 0; i < root->m_heir_num; ++i)
    {
        Letter *tmp = state;
        if (state->m_heir_num >= 2)
        {
            max_height = height;
            affix = words;
            cout << affix << endl;
        }
        words += root->m_letter;
        state = root->m_heir[i];
        // cout << state->m_letter;
        // if(height>)
        // cout << max_height << endl;
        dfs(state, height + 1, max_height, words, affix);
        state = tmp;
        // affix[-1] = '\0';
    }

    // cout << endl;
}
