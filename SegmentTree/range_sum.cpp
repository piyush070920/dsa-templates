#include <bits/stdc++.h>
using namespace std;

// YOU NEED TO [0 | 1 BASED INDEXING, LOW , HIGH] TO THE CONSTRUCTOR
// THEN YOU CAN PLAY WITH THAT INDEXING
class SegmentTree
{
    // IT WILL ALWAYS PLAY WITH 0 based INDEXING
    // IT WILL CONVERT 1 based INTO 0 based
private:
    long long MAXN = 1e5;
    vector<long long> seg;
    int indexing, low, high;

    void build(vector<int> &a, int ind, int low, int high)
    {
        if (low == high)
        {
            seg[ind] = a[low];
        }
        else
        {
            int mid = (low + high) / 2;
            build(a, ind * 2 + 1, low, mid);
            build(a, ind * 2 + 2, mid + 1, high);
            seg[ind] = seg[ind * 2 + 1] + seg[ind * 2 + 2];
        }
    }
    long long sum(int ind, int low, int high, int l, int r)
    {
        if (l > r)
            return 0;
        if (l == low && r == high)
        {
            return seg[ind];
        }
        int mid = (low + high) / 2;
        return sum(ind * 2 + 1, low, mid, l, min(r, mid)) + sum(ind * 2 + 2, mid + 1, high, max(l, mid + 1), r);
    }
    void update(int ind, int low, int high, int pos, int new_val)
    {
        if (low == high)
        {
            seg[ind] = new_val;
        }
        else
        {
            int mid = (low + high) / 2;
            if (pos <= mid)
                update(ind * 2 + 1, low, mid, pos, new_val);
            else
                update(ind * 2 + 2, mid + 1, high, pos, new_val);
            seg[ind] = seg[ind * 2 + 1] + seg[ind * 2 + 2];
        }
    }
    void Print(int low, int high)
    {
        printf("seg: ");
        for (int i = low; i <= high; i++)
        {
            printf("%d,", seg[i]);
        }
        cout << endl;
    }

public:
    SegmentTree(int indexing, int low, int high)
    {
        this->indexing = indexing;
        this->low = low - (indexing == 1);
        this->high = high - (indexing == 1);
        seg.resize(4 * MAXN, 0);
    }
    void build(vector<int> &a)
    {
        // builds segment tree
        build(a, 0, low, high);
    }
    long long sum(int l, int r)
    {
        // return sum of [l, r] range inclusive
        l = l - indexing;
        r = r - indexing;
        return sum(0, low, high, l, r);
    }
    void update(int idx, int new_val)
    {
        // updates new_val to idx position in array
        idx = idx - indexing;

        update(0, low, high, idx, new_val);
    }
    void PrintTree()
    {
        // prints segment Tree
        Print(low, 2 * high + 2);
    }
};

int main()
{
    SegmentTree sgt(0, 0, 4);
    vector<int> a = {2, 1, 4, 3, 1};
    sgt.build(a);
    sgt.PrintTree();
    // sgt.update(1, 2);
    // sgt.PrintTree();
    cout << sgt.sum(1, 4);
    cout << sgt.sum(1, 3);
    cout << sgt.sum(4, 4);

    return 0;
}
