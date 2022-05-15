#include <iostream>
#include <string.h>
using namespace std;

class Letter
{
public:
    Letter()
    {
        m_heir_num = 0;
        m_degree = 0;
        m_father = nullptr;
        m_all_word_num = 1;
        // affix = "";
    }
    Letter(char letter)
    {
        m_letter = letter;
        m_heir_num = 0;
        m_degree = 0;
        m_father = nullptr;
        m_all_word_num = 1;
        // affix = "";
    }

    void append(Letter *heir)
    {
        heir->m_degree = this->m_degree + 1; // degree is the lenth of an affix
        heir->m_father = this;
        m_heir[m_heir_num] = heir;
        m_heir_num += 1;

        Letter *state = heir;
        if (this->m_heir_num == 1)
            return;
        rev_affix = "";
        while (state->m_father != nullptr)
        {
            state = state->m_father;
            rev_affix += state->m_letter;
            state->m_all_word_num += 1; // times that the affix appears
        }
    }
    // void get_aff()
    // {
    //     int x = rev_affix.length() - 2;
    //     for (int i = x; i >= 0; --i)
    //     {
    //         affix += rev_affix[i];
    //     }
    //     affix += '\0'; // affix itself
    // }

    char m_letter;
    Letter *m_heir[27];
    int m_heir_num;
    int m_degree;
    Letter *m_father;
    int m_all_word_num;
    // string affix;
    string rev_affix;
};

class Node // only for bfs, as a replacement of queue
{
public:
    Node()
    {
        next = nullptr;
    }
    Node(Letter *l)
    {
        lr = l;
        next = nullptr;
    }
    Letter *lr;
    Node *next;
};

class List
{
public:
    List(Node *a)
    {
        head = a;
        tail = a;
        count = 1;
    }
    Node *pop()
    {
        Node *tmp;
        tmp = head;
        if (head->next == nullptr)
        {
            head = tail = nullptr;
            --count;
            return tmp;
        }
        head = head->next;
        --count;
        return tmp;
    }
    void push(Node *nod)
    {
        if (tail == nullptr)
        {
            head = nod;
            tail = nod;
            ++count;
        }
        else
        {
            tail->next = nod;
            tail = tail->next;
            ++count;
        }
    }
    Node *head;
    Node *tail;
    int count;
};

Letter *bfs(List *list)
{
    Letter *max_l = list->head->lr;
    while (list->count != 0)
    {
        Letter *x = list->pop()->lr;
        // x->get_aff();
        if (x->m_all_word_num >= 2 && x->m_degree > max_l->m_degree)
        {
            max_l = x;
        }
        else if (x->m_all_word_num >= 2 && x->m_degree == max_l->m_degree && x->m_all_word_num > max_l->m_all_word_num)
        {
            max_l = x;
        }
        else if (x->m_all_word_num >= 2 && x->m_degree == max_l->m_degree && x->m_all_word_num == max_l->m_all_word_num) //&& x->affix < max_l->affix
        {
            int k = max_l->rev_affix.length() - 2;
            bool is = true;
            while (k >= 0)
            {
                if (x->rev_affix[k] > max_l->rev_affix[k])
                {
                    is = false;
                    break;
                }
                else if (x->rev_affix[k] < max_l->rev_affix[k])
                {
                    break;
                }
                --k;
            }
            if (is)
                max_l = x;
        }
        for (int j = 0; j < x->m_heir_num; ++j)
        {
            list->push(new Node(x->m_heir[j]));
        }
    }
    return max_l;
}

Letter *bfs2(List *list)
{
    Letter *max_l = list->head->lr;
    while (list->count != 0)
    {
        Letter *x = list->pop()->lr;
        if (x->m_all_word_num >= 2 && x->m_degree > max_l->m_degree)
        {
            max_l = x;
        }
        else if (x->m_all_word_num >= 2 && x->m_degree == max_l->m_degree && x->m_all_word_num > max_l->m_all_word_num)
        {
            max_l = x;
        }
        else if (x->m_all_word_num >= 2 && x->m_degree == max_l->m_degree && x->m_all_word_num == max_l->m_all_word_num && x->rev_affix < max_l->rev_affix)
        {
            max_l = x;
        }
        for (int j = 0; j < x->m_heir_num; ++j)
        {
            list->push(new Node(x->m_heir[j]));
        }
    }
    return max_l;
}

void free_l(List *list)
{
    Letter *max_l = list->head->lr;
    while (list->count != 0)
    {
        Letter *x = list->pop()->lr;

        for (int j = 0; j < x->m_heir_num; ++j)
        {
            list->push(new Node(x->m_heir[j]));
        }
        delete x;
    }
}

int main()
{
    int n;
    cin >> n;
    string words[50001];
    for (int i = 0; i < n; ++i)
    {
        cin >> words[i];
    }

    Letter *root = new Letter();
    for (int i = 0; i < n; ++i)
    {
        string word;
        word = words[i] + ' ';
        Letter *state = root;
        int j = 0;
        bool is_found = true;
        for (; j < word.length(); ++j)
        {
            is_found = false;
            for (int k = 0; k < state->m_heir_num; ++k)
            {
                if (word[j] == state->m_heir[k]->m_letter)
                {
                    state = state->m_heir[k];
                    is_found = true;
                    break;
                }
            }
            if (!is_found)
                break;
        }
        for (; j < word.length(); ++j)
        {
            state->append(new Letter(word[j]));
            state = state->m_heir[state->m_heir_num - 1];
        }
    }

    Node *a0 = new Node(root);
    List *list = new List(a0);
    Letter *ans1 = bfs(list);
    int j = ans1->rev_affix.length() - 2;
    // cout << ans1->rev_affix.length() << endl;
    for (int i = j; i >= 0; --i)
    {
        cout << ans1->rev_affix[i];
    }
    cout << " " << ans1->m_all_word_num << endl;
    delete a0;
    delete list;

    //======================suffix following===============================

    for (int i = 0; i < n; ++i)
    {
        string str = "";
        int k = words[i].length() - 1;
        while (k >= 0)
        {
            str += words[i][k];
            --k;
        }
        words[i] = str;
    }
    root = new Letter();
    for (int i = 0; i < n; ++i)
    {
        string word;
        word = words[i] + ' ';
        // cin >> word;
        Letter *state = root;
        int j = 0;
        bool is_found = true;
        for (; j < word.length(); ++j)
        {
            is_found = false;
            for (int k = 0; k < state->m_heir_num; ++k)
            {
                if (word[j] == state->m_heir[k]->m_letter)
                {
                    state = state->m_heir[k];
                    is_found = true;
                    break;
                }
            }

            if (!is_found)
                break;
        }
        for (; j < word.length(); ++j)
        {
            state->append(new Letter(word[j]));
            state = state->m_heir[state->m_heir_num - 1];
        }
    }

    a0 = new Node(root);
    list = new List(a0);
    Letter *ans2 = bfs2(list);
    j = ans2->rev_affix.length() - 2;
    for (int i = 0; i <= j; ++i)
    {
        cout << ans2->rev_affix[i];
    }
    cout << " " << ans2->m_all_word_num << endl;
    a0 = new Node(root);
    list = new List(a0);
    free_l(list);
    delete a0;
    delete list;

    return 0;
}