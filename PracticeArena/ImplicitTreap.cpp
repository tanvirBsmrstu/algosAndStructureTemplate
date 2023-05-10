
#include <iostream>
#include <string>
#include <memory>

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
    void insert(int val)
    {
        shared_ptr<TreapNode> newNode = make_shared<TreapNode>(val);

        shared_ptr<TreapNode> left, right;

        cout << "########################" << endl;

        split(val, root, left, right);
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
        cout << "       root : " << root->toString() << endl;
        print(root);
        cout << "________" << endl;
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

        int currentIndex = getSubTreeSize(node->leftChild) + 1;
        if (key < currentIndex)
        { /// search left subtree according to BST
            split(key, node->leftChild, node->leftChild, right);
            right = node;
        }
        else
        {
            split(key - currentIndex, node->rightChild, left, node->rightChild);
            left = node;
        }
        if (left)
            left->recalculateSize();
        if (right)
            right->recalculateSize();
        if (node)
            node->recalculateSize();
    }

    shared_ptr<TreapNode> merge(shared_ptr<TreapNode> left, shared_ptr<TreapNode> right)
    {
        if (!left)
            return right;
        if (!right)
            return left;

        if (left->priority < right->priority)
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

    void print(shared_ptr<TreapNode> node)
    {
        if (!node)
            return;
        print(node->leftChild);
        cout << node->toString() << endl;
        print(node->rightChild);
    }
    
    int find_kth_minimum_number(shared_ptr<TreapNode> node, int k)
    {
        if (!node)
            return 0;
        if (node->size < k)
            return 0;
        if (k == 0)
            return node->priority;
        if (getSubTreeSize(node->leftChild) > k)
        {
            return find_kth_minimum_number(node->leftChild, k);
        }
        else
        {
            return find_kth_minimum_number(node->rightChild, k - getSubTreeSize(node->leftChild));
        }
    }

    ~Treap()
    {
        cleanup(root);
    }
};

int main()
{
    Treap cartesianTree;
    cartesianTree.insert(45);
    cartesianTree.print(cartesianTree.getRoot());
    cout << endl;
    cartesianTree.insert(40);
    cartesianTree.print(cartesianTree.getRoot());
    cout << endl;
    cartesianTree.insert(50);
    cartesianTree.print(cartesianTree.getRoot());
    cout << endl;

    return 0;
}

/// ///////////////////////////
///
///     http://e-maxx.ru/algo/treap
///     https://habr.com/en/articles/102364/
///