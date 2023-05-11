
#include <iostream>
#include <string>
#include <memory>
#include <vector>

using namespace std;

constexpr const size_t mod = 10000007;

struct TreapNode
{
    shared_ptr<TreapNode> leftChild, rightChild;

    int key;
    size_t priority, size;

    TreapNode(int key, shared_ptr<TreapNode> left = nullptr, shared_ptr<TreapNode> right = nullptr, size_t priority = rand() % mod)
    {
        this->priority = priority;
        this->key = key;
        leftChild = left;
        rightChild = right;
        size = 1;
    }

    size_t recalculateSize()
    {
        int s = 1;
        if (leftChild)
            s += leftChild->size;
        if (rightChild)
            s += rightChild->size;
        return size = s;
    }

    string toString()
    {
        return "Value : " + to_string(key) + "  priority : " + to_string(priority) + "   size " + to_string(size);
    }
};

class Treap
{
    shared_ptr<TreapNode> root;

    void cleanup(shared_ptr<TreapNode> node)
    {
        if (!node)
            return;
        cleanup(node->leftChild);
        cleanup(node->rightChild);
        node.~shared_ptr();
    }

public:
    Treap()
    {
    }
    shared_ptr<TreapNode> getRoot()
    {
        return root;
    }
    void insert(int val, int pos)
    {
        shared_ptr<TreapNode> newNode = make_shared<TreapNode>(pos, nullptr, nullptr, val);

        shared_ptr<TreapNode> left = nullptr, right = nullptr;
        cout << "++++++++++++++++++++++++++++++++++++++++++++++" << endl;

        split(val, root, left, right);
        if (left)
        {
            cout << "left tree ================" << endl;
            print(left);
            cout << " left end tree ************" << endl;
        }
        if (right)
        {
            cout << " right tree ================" << endl;
            print(right);
            cout << " right tree end************" << endl;
        }
        // if (left)
        // {
        //     cout << val << "       left : " << left->toString() << endl;
        //     print(left);
        //     cout << "***" << endl;
        // }
        // if (right)
        //     cout << val << "       right : " << right->toString() << endl;
        // if (root)
        //     cout << val << "       one root : " << root->toString() << endl;
        // cout << "________" << endl;
        // // shared_ptr<TreapNode> dd = merge(left, newNode);
        // // cout << val << "       merge : " << dd->toString() << endl;
        // // print(dd);
        // // cout << "________" << endl;

        root = merge(merge(left, newNode), right);
        // root->recalculateSize();
        cout << " root tree ================" << endl;
        print(root);
        cout << " root tree end************" << endl;
    }

    size_t getSubTreeSize(shared_ptr<TreapNode> node)
    {
        return node ? node->size : 0;
    }

    void split(int key, shared_ptr<TreapNode> node, shared_ptr<TreapNode> &left, shared_ptr<TreapNode> &right)
    {
        if (!node)
        {
            left = right = nullptr;
            return;
        }

        int currentIndex = getSubTreeSize(node->leftChild);
        if (key < currentIndex)
        { /// search left subtree according to BST
            right = node;
            split(key, node->leftChild, left, node->leftChild);
        }
        else
        {
            left = node;
            split(key - currentIndex, node->rightChild, node->rightChild, right);
        }
        if (left)
            left->recalculateSize();
        if (right)
            right->recalculateSize();
    }

    shared_ptr<TreapNode> merge(shared_ptr<TreapNode> left, shared_ptr<TreapNode> right)
    {
        if (!left)
            return right;
        if (!right)
            return left;

        if (left->priority > right->priority)
        {                                                      // min priority will be the parent
            left->rightChild = merge(left->rightChild, right); // Right rotation
            left->recalculateSize();
            return left;
        }
        else
        {
            right->leftChild = merge(left, right->leftChild); // Left rotation
            right->recalculateSize();
            return right;
        }
    }

    void print(shared_ptr<TreapNode> node, int rootIndex = 1)
    {
        if (!node)
            return;
        print(node->leftChild, rootIndex << 1);
        cout << "index : " << rootIndex << " Tree : " << node->toString() << endl;
        print(node->rightChild, (rootIndex << 1) + 1);
    }

    int find_kth_minimum_number_interval(int low, int high, int k)
    {
        shared_ptr<TreapNode> left, right, intervalTree;
        split(low, root, left, right);
        cout << "left tree ================" << endl;
        print(left);
        cout << " left end tree ************" << endl;

        split(high - low + 1, right, intervalTree, right);
        cout << " Interval tree ================" << endl;
        print(intervalTree);
        cout << " Interval tree ************" << endl;
        cout << " right tree ================" << endl;
        print(right);
        cout << " right tree end************" << endl;
        int answer = find_kth_minimum_number(intervalTree, k);
        root = merge(left, merge(intervalTree, right));
        return answer;
    }

    int find_kth_minimum_number(shared_ptr<TreapNode> node, int k)
    {
        if (!node)
            return 0;
        // if (node->size < k)
        //     return 0;
        if (k == 1)
            return node->priority;
        int currentIndex = getSubTreeSize(node->leftChild) + 1;
        if (currentIndex > k)
        {
            return find_kth_minimum_number(node->leftChild, k);
        }
        else
        {
            return find_kth_minimum_number(node->rightChild, k - currentIndex);
        }
    }

    void build(vector<int> &array)
    {
        for (int i = 0; i < array.size(); i++)
        {
            insert(array[i], i);
        }
        cout << "########################" << endl;
        print(root);
        cout << "________" << endl;
    }

    ~Treap()
    {
        cleanup(root);
    }
};

int main()
{
    vector<int> input{10, 20, 5, 7, 11, 3, 1};

    Treap cartesianTree;
    cartesianTree.build(input);

    // int kthMin = cartesianTree.find_kth_minimum_number_interval(2, 5, 2);

    // cout << "answer : " << kthMin << endl;

    return 0;
}

/// ///////////////////////////
///
///     http://e-maxx.ru/algo/treap
///     https://habr.com/en/articles/102364/
///