//
// Created by liasa on 04/03/2026.
//
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define v vector
#define lp(i, s, e) for (ll i = s; i < e; ++i)
#define pll pair<ll, ll>

const ll inf = 4e18;

struct Line {
  ll m, b;

  ll f(ll x) { return m * x + b; }
};

struct Seg {
  Seg *left = nullptr, *right = nullptr;
  int l, r, mid;
  ll shift = 0;
  Line L = {0, -inf};

  ll x_l = 0, x_r = 0, x_mid = 0;

  Seg(int l, int r) : l(l), r(r), mid((l + r) / 2) {}

  void ensure() {
    if (l == r)
      return;

    if (left == nullptr) {
      left = new Seg(l, mid);
      right = new Seg(mid + 1, r);
    }
  }

  void apply_shift(ll add) {
    shift += add;
    x_l += add, x_r += add, x_mid += add;
    L.b -= L.m * add;
  }

  void push() {
    if (shift == 0 || l == r)
      return;

    ensure();
    left->apply_shift(shift), right->apply_shift(shift);
    shift = 0;
  }

  void push_line() {
    if (l == r)
      return;

    ensure();

    left->add(L), right->add(L);
    L = {0, -inf};
  }

  void update_x() {
    if (l == r)
      return;
    x_l = left->x_l;
    x_r = right->x_r;
    x_mid = left->x_r;
  }

  void add(Line V) {
    push();

    Line lo = L, hi = V;
    if (lo.f(x_mid) < hi.f(x_mid))
      swap(lo, hi);

    L = lo;

    if (l == r)
      return;

    ensure();
    if (lo.f(x_l) < hi.f(x_l)) {
      left->add(hi);
    } else if (lo.f(x_r) < hi.f(x_r)) {
      right->add(hi);
    }
  }

  void add_line(int a, int b, Line V) {
    if (a > r || b < l)
      return;
    if (a <= l && r <= b) {
      add(V);
      return;
    }

    push();

    left->add_line(a, b, V);
    right->add_line(a, b, V);
  }

  void add_shift(int a, int b, ll delta) {
    if (a > r || b < l)
      return;
    if (a <= l && r <= b) {
      apply_shift(delta);
      return;
    }
    push();
    push_line();

    left->add_shift(a, b, delta);
    right->add_shift(a, b, delta);
    update_x();
  }

  ll q_func(int x, ll &true_x) {
    push();
    if (l == r) {
      true_x = x_l;
      return L.f(true_x);
    }
    ensure();
    ll ans = -inf;
    if (x <= mid)
      ans = left->q_func(x, true_x);
    else
      ans = right->q_func(x, true_x);

    ans = max(ans, L.f(true_x));
    return ans;
  }

  ll q(int x) {
    ll true_x = 0;
    return q_func(x, true_x);
  }
};
