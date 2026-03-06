// Created by liasa on 03/03/2026.
// this is a max Li Chao tree
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define v vector
#define lp(i, s, e) for (ll i = s; i < e; ++i)

const ll inf = 1e18;
struct Line {
  ll m, b;
  ll f(ll x) { return (m * x + b); }
};

ll x_max = 1e6 + 5;

struct LiChao {
  v<Line> seg;
  ll sz = 1;

  LiChao(ll n) {
    for (; sz < x_max; sz *= 2)
      ;
    seg.resize(2 * sz, {0, -inf});
  }


  void insert(ll i, ll l, ll r, ll a, ll b, Line add) {
    if (l > b || r < a)
      return;
    ll mid = (l + r) / 2;

    if (l >= a && r <= b) {
      if (seg[i].f(mid) < add.f(mid)) {
        swap(seg[i], add);
      }
      
      if (l == r)
        return;
      
      if (seg[i].f(l) < add.f(l)) {
        insert(i * 2, l, mid, a, b, add);
      }
      
      if (seg[i].f(r) < add.f(r)) {
        insert(i * 2 + 1, mid + 1, r, a, b, add);
      }
      
      return;
    }
    
    insert(i * 2, l, mid, a, b, add);
    insert(i * 2 + 1, mid + 1, r, a, b, add);
  }
  void insert(Line add, ll a, ll b) { insert(1, 0, x_max - 1, a, b, add); }

  ll query(ll i, ll l, ll r, ll x) {
    ll res = seg[i].f(x);
    if (l == r)
      return res;
    
    ll mid = (l + r) / 2;
    
    if (x <= mid)
      return max(res, query(i << 1, l, mid, x));
    else
      return max(res, query(i << 1 | 1, mid + 1, r, x));
  }
};
