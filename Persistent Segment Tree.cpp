//
// Created by liasa on 09/03/2026.
//
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define v vector
#define lp(i, s, e) for (ll i = s; i < e; ++i)
#define pll pair<ll, ll>
#define tpl tuple<ll, ll, ll>

const ll inf = 1e18;
struct Seg {
  Seg *left = nullptr, *right = nullptr;
  int l, r, mid;
  ll mn = inf;
  Seg(int l, int r) : l(l), r(r), mid((l + r) / 2) {}

  Seg(Seg *copy) {
    left = copy->left, right = copy->right, mid = copy->mid, l = copy->l,
    r = copy->r, mn = copy->mn;
  }

  void ensure() {
    if (l == r)
      return;
    if (left == nullptr) {
      left = new Seg(l, mid);
      right = new Seg(mid + 1, r);
    }
  }

  ll q(int a, int b) {
    if (l > b || r < a)
      return inf;
    if (l >= a && r <= b)
      return mn;

    ensure();
    return min(left->q(a, b), right->q(a, b));
  }

  Seg *update(Seg *node, int pos, ll new_val) {
    Seg *cur = new Seg(node);

    if (cur->l == cur->r) { // the leaf node
      cur->mn = min(cur->mn, new_val);
      return cur;
    }

    cur->ensure();
    if (pos <= cur->mid)
      cur->left = update(cur->left, pos, new_val);
    else
      cur->right = update(cur->right, pos, new_val);

    cur->mn = min(cur->left->mn, cur->right->mn);
    return cur;
  }
};

Seg *build(int l, int r) {
  Seg *node = new Seg(l, r);
  if (l != r) {
    node->left = build(l, node->mid);
    node->right = build(node->mid + 1, r);
  }
  return node;
}
