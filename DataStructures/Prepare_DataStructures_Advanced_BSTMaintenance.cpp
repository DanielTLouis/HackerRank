/*
Consider a binary search tree T which is initially empty. Also, consider the first N positive
integers {1, 2, 3, 4, 5, ....., N} and its permutation P {a1, a2, ..., aN}.
If we start adding these numbers to the binary search tree T, starting from a1, continuing
with a2, ... (and so on) ..., ending with aN. After every addition we ask you to output the
sum of distances between every pair of T's nodes.
Input Format
    The first line of the input consists of the single integer N, the size of the list.
    The second line of the input contains N single space separated numbers the permutation
    a1, a2, ..., aN itself.
Constraints
    1 ≤ N ≤ 250000
Output Format
    Output N lines.
    On the ith line output the sum of distances between every pair of nodes after adding the
    first i numbers from the permutation to the binary search tree T
Sample Input #00
    8
    4 7 3 1 8 2 6 5
Sample Output #00
    0
    1
    4
    10
    20
    35
    52
    76
Explanation #00
    After adding the first element, the distance is 0 as there is only 1 element
        4
    After adding the second element, the distance between 2 nodes is 1.
        4
         \
          7
    After adding the third element, the distance between every pair of elements is
    2+1+1=4
          4
         / \
        3   7
    After adding the fourth element, the distance between every pair of elements is
    3 + 2 + 1 + 2 + 1 + 1 = 10
            4
           / \
          3   7
         /
        1
    After adding the fifth element, the distance between every pair of elements is
    4 + 3 + 2 + 1 + 3 + 2 + 1 + 2 + 1 + 1 = 20
            4
           / \
          3   7
         /     \
        1       8
    After adding the sixth element, the distance between every pair of elements is
    5 + 4 + 3 + 2 + 1 + 4 + 3 + 2 + 1 + 3 + 2 + 1 + 2 + 1 + 1 = 35
            4
           / \
          3   7
         /     \
        1       8
         \
          2
    After adding the seventh element, the distance between every pair of elements is
    5+5+4+3+2+1+4+4+3+2+1+3+3+2+1+2+2+1+1+1+2=52
            4
           / \
          3   7
         /   / \
        1   6   8
         \
          2
    After adding the final element, the distance between every pair of elements is
    6+5+5+4+3+2+1+5+4+4+3+2+1+4+3+3+2+1+3+2+2+1+2+1+1+2+1+3=76
              4
            /   \
           3      7
         /      /   \
        1      6     8
         \    /
          2  5
*/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <memory.h>

using namespace std;

int p[250005];

// stupid solver

struct node {
  node(int _val) : val(_val), size(1), h(0), left(NULL), right(NULL), parent(NULL) {};
  int val, size, h;
  node* left;
  node* right;
  node* parent;
};

vector<vector<int> > g;

void addEdge(int a, int b) {
  g[a].push_back(b);
  g[b].push_back(a);
}

void buildGraph(node* root) {
  if (root == NULL) return;
  if (root->left != NULL) {
    addEdge(root->val, root->left->val);
  }
  if (root->right != NULL) {
    addEdge(root->val, root->right->val);
  }
  buildGraph(root->left);
  buildGraph(root->right);
}

int findAll(int v, int d = 0, int par = -1) {
  int ans = d;
  for (int i = 0; i < g[v].size(); ++i) {
    if (g[v][i] != par) {
      ans += findAll(g[v][i], d + 1, v);
    }
  }
  return ans;
}

int countForTree(int n, node* root) {
  g.clear(); g.resize(n);
  buildGraph(root);
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    ret += findAll(i);
  }
  return ret / 2;
}

vector<int> solveStupid(int n) {
  node* root = new node(p[0]);
  vector<int> ret(1, 0);
  for (int i = 1; i < n; ++i) {
    node* cur = root;
    while (true) {
      if (cur->val > p[i]) {
        if (cur->left == NULL) {
          cur->left = new node(p[i]);
          break;
        } else {
          cur = cur->left;
        }
      } else {
        if (cur->right == NULL) {
          cur->right = new node(p[i]);
          break;
        } else {
          cur = cur->right;
        }
      }
    }

    ret.push_back(countForTree(n, root));

  }
  return ret;
}

// tree structure

long long tree[1000005], H[250005];
int add[1000005];

long long getH(int l, int r) {
  return r - l + 1;
  return H[r] - (l > 0 ? H[l - 1] : 0);
}

void push(int v, int l, int r) {
  if (add[v]) {
    int m = (l + r) / 2;
    add[2 * v] += add[v];
    tree[2 * v] += 1LL * getH(l, m) * add[v];
    add[2 * v + 1] += add[v];
    tree[2 * v + 1] += 1LL * getH(m + 1, r) * add[v];
    add[v] = 0;
  }
}

void update(int i, int l, int r, int L, int R, int val) {
  if (l == L && r == R) {
    tree[i] += 1LL * getH(l, r) * val;
    add[i] += val;
    return;
  }
  push(i, l, r);
  int m = (l + r) >> 1;
  if (R <= m) update(2 * i, l, m, L, R, val);
  else if (L > m) update(2 * i + 1, m + 1, r, L, R, val);
  else {
    update(2 * i, l, m, L, m, val);
    update(2 * i + 1, m + 1, r, m + 1, R, val);
  }
  tree[i] = tree[2 * i] + tree[2 * i + 1];
}

long long find(int i, int l, int r, int L, int R) {
  if (l == L && r == R)
    return tree[i];
  push(i, l, r);
  int m = (l + r) >> 1;
  if (R <= m) return find(2 * i, l, m, L, R);
  else if (L > m) return find(2 * i + 1, m + 1, r, L, R);
  return find(2 * i, l, m, L, m) + find(2 * i + 1, m + 1, r, m + 1, R);
}

// cool solution

node* whatNode[250005];
set<int> f;

node* createNode(int val) {
  node* ret = new node(val);
  f.insert(val);
  whatNode[val] = ret;
  return ret;
}

node* buildFullTree(int n) {
  node* root = createNode(p[0]);
  set<int>::iterator it;
  for (int i = 1; i < n; ++i) {
    it = f.upper_bound(p[i]);
    if (it != f.end() && whatNode[*it]->left == NULL) {
      whatNode[*it]->left = createNode(p[i]);
      whatNode[*it]->left->parent = whatNode[*it];
      whatNode[*it]->left->h = whatNode[*it]->h + 1;
    } else {
      --it;
      whatNode[*it]->right = createNode(p[i]);
      whatNode[*it]->right->parent = whatNode[*it];
      whatNode[*it]->right->h = whatNode[*it]->h + 1;
    }

    // // test-code
    // g.clear(); g.resize(n);
    // buildGraph(root);
    // int sum = 0;
    // for (int i = 0; i < n; ++i) {
    //   sum += findAll(i);
    // }
    // cout << sum / 2 << endl;
  }
  return root;
}

int fillSize(node* root) {
  if (root->left != NULL) {
    root->size += fillSize(root->left);
  }
  if (root->right != NULL) {
    root->size += fillSize(root->right);
  }
  return root->size;
}

vector<int> order;
int L[250005], where[250005];

void dfs(node* root, int left) {
  H[order.size()] = root->h;
  order.push_back(root->val);
  where[root->val] = order.size() - 1;
  L[root->val] = left;
  if (root->left != NULL && root->right != NULL) {
    if (root->left->size >= root->right->size) {
      dfs(root->left, left);
      dfs(root->right, order.size());
    } else {
      dfs(root->right, left);
      dfs(root->left, order.size());
    }
  } else if (root->left != NULL) {
    dfs(root->left, left);
  } else if (root->right != NULL) {
    dfs(root->right, left);
  }
}

long long findOnPath(int n, int v) {
  long long ret = 0, hSum = 0;
  int left = L[v];
  while (true) {
    // cout << "Fnd: " << left << "  " << where[v] << endl;
    ret += find(1, 0, n - 1, left, where[v]);
    if (left == 0) break;
    v = whatNode[order[left]]->parent->val;
    // cout << "V: " << v << endl;
    left = L[v];
  }
  return ret;
}

void updateOnPath(int n, int v) {
  int left = L[v];
  while (true) {
    // cout << "Upd: " << left << "  " << where[v] << endl;
    if (left == 0) {
      if (1 <= where[v])
        update(1, 0, n - 1, 1, where[v], 1);
      break;
    } else {
      update(1, 0, n - 1, left, where[v], 1);
    }
    v = whatNode[order[left]]->parent->val;
    left = L[v];
  }
}

vector<long long> solve(int n) {
  vector<long long> ret(1, 0);
  node* root = buildFullTree(n);
  fillSize(root);
  dfs(root, 0);
  for (int i = 1; i < n; ++i) {
    H[i] += H[i - 1];
    // cout << H[i] << " ";
  }
  // cout << endl;
  // for (int i = 0; i < n; ++i)
  //   cout << order[i] + 1 << " ";
  // cout << endl;
  // for (int i = 0; i < n; ++i)
  //   cout << L[i] << " ";
  // cout << endl;
  long long hSum = 0, ans = 0;
  for (int i = 1; i < n; ++i) {
    ans += hSum;
    hSum += whatNode[p[i]]->h;
    ans += 1LL * i * whatNode[p[i]]->h;
    ans -= 2 * findOnPath(n, whatNode[p[i]]->parent->val);
    // long long K = findOnPath(n, whatNode[p[i]]->parent->val);
    // cout << whatNode[p[i]]->parent->val + 1 << "  " << K << endl;
    updateOnPath(n, p[i]);
    ret.push_back(ans);
  }
  return ret;
}

void checker() {
  for (int it = 0; it < 100; ++it) {
    int n = rand() % 100 + 1;
    for (int i = 0; i < n; ++i) {
      p[i] = i;
      int ind = rand() % i + 1;
      swap(p[i], p[ind]);
    }

    vector<int> real = solveStupid(n);
    vector<long long> my = solve(n);
    for (int i = 0; i < my.size(); ++i) {
      if (real[i] != my[i])
        puts("fuck");
    }
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &p[i]); --p[i];
  }

  vector<long long> my = solve(n);
  for (int i = 0; i < my.size(); ++i) {
    printf("%lld\n", my[i]);
  }

  // checker();
  return 0;
}
