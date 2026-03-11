struct Flow {
    struct Node {
        ll to, idx, cost, cap;
    };

    ll n;
    ll flow = 0, costi = 0;
    v<v<Node> > g;
    v<ll> par, pe;

    Flow(ll n) : n(n) {
        g.resize(n);
    }

    void add_edge(ll u, ll v, ll cap, ll cost) {
        g[u].push_back({v, (ll)g[v].size(), cost, cap});
        g[v].push_back({u, (ll)g[u].size() - 1, -cost, 0});
    }

    ll dij() {
        priority_queue<pair<ll, ll>, v<pair<ll, ll> >, greater<pair<ll, ll> > > pq;
        pq.push({0, 0});
        v<ll> dist(n, 1e18);
        par.assign(n, -1);
        pe.assign(n, -1);
        dist[0] = 0;
        
        while (!pq.empty()) {
            auto [dis, node] = pq.top();
            pq.pop();
            for (ll ei = 0; ei < g[node].size(); ei++) {
                auto [to, idx, cost, cap] = g[node][ei];
                if (cap <= 0) continue;
                if (dist[to] > dis + cost) {
                    dist[to] = dis + cost;
                    par[to] = node;
                    pe[to] = ei;
                    pq.push({dist[to], to});
                }
            }
        }
        return dist[n - 1];
    }

    void solve(ll k) {
        const ll inf = 1e18;
        while (flow < k) {
            ll d = dij();
            if (d >= inf) break;
            ll add = k - flow;
            for (ll x = n - 1; x != 0; x = par[x]) {
                ll p = par[x];
                if (p == -1) {
                    add = 0;
                    break;
                }
                add = min(add, g[p][pe[x]].cap);
            }
            if (add == 0) break;

            for (ll x = n - 1; x != 0; x = par[x]) {
                ll p = par[x];
                Node &a = g[p][pe[x]];
                Node &b = g[a.to][a.idx];
                a.cap -= add;
                b.cap += add;
            }
            flow += add;
            costi += add * d;
        }
    }
};
