//
// Created by liasa on 06/03/2026.
//
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define v vector
#define lp(i, s, e) for (ll i = s; i < e; ++i)

const ll inf = 4e18;

struct Line {
  ll m, b;

  ll f(ll x) {
    return m * x + b;
  }
};

struct Seg {

  Seg *left = nullptr, *right = nullptr;
  int l, r, mid;
  Line sum = {0, -inf};

  Seg(int l, int r) : l(l), r(r), mid((l + r) / 2) {}

  void ensure() {
    if (l == r)
      return;
    if (left == nullptr) {
      left = new Seg(l, mid);
      right = new Seg(mid + 1, r);
    }
  }

  ll q(int x) {
    ll ans = sum.f(x);
    if (l == r)
      return ans;

    ensure();
    if (x <= mid)
      return max(ans, left->q(x));
    return max(ans, right->q(x));
  }

  void add(Line V) {
    ll lef = l, rig = r, md = mid;

    Line lo = sum, hi = V;

    if (lo.f(md) < hi.f(md))
      swap(lo, hi);

    sum = lo;

    if (l == r)
      return;

    ensure();

    if (lo.f(lef) < hi.f(lef)) {
      left->add(hi);
    } else if (lo.f(rig) < hi.f(rig)) {
      right->add(hi);
    }
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int x_left = 0, x_right = 1000000;
  Seg st(x_left, x_right);

  st.add({2, 3});     // y = 2x + 3
  st.add({-1, 10});   // y = -x + 10

  cout << st.q(0) << '\n';
  cout << st.q(2) << '\n';
  cout << st.q(5) << '\n';

  return 0;
}
