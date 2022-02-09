#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
  int s, e, c;
};

struct DisjointSet {
  vector<int> parent, rank;

  DisjointSet(int N) : parent(N + 1), rank(N + 1, 1) {
    for (int i = 1; i <= N; i++) {
      parent[i] = i;
    }
  }

  int find(int u) {
    if (u == parent[u]) return u;
    return parent[u] = find(parent[u]);
  }

  void merge(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return;

    if (rank[u] > rank[v]) swap(u, v);
    parent[u] = v;
    if (rank[u] == rank[v]) ++rank[v];
  }
};

bool cmpEdge(const Edge& a, const Edge& b) { return a.c < b.c; }

int N, M;
Edge edgeList[200000];

int main(int argc, char** argv) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int test_case;
  int T;

  freopen("input.txt", "r", stdin);
  cin >> T;

  for (test_case = 1; test_case <= T; ++test_case) {
    cin >> N >> M;

    for (int i = 0; i < M; i++) {
      int s, e, c;
      Edge& edge = edgeList[i];
      cin >> edge.s >> edge.e >> edge.c;
    }

    // Kruskal 알고리즘
    long long int totalCost = 0;
    DisjointSet DS(N);
    sort(edgeList, edgeList + M, cmpEdge);

    for (int i = 0; i < M; i++) {
      Edge& curr = edgeList[i];

      if (DS.find(curr.s) == DS.find(curr.e)) continue;

      DS.merge(curr.s, curr.e);
      totalCost += curr.c;
    }

    cout << '#' << test_case << ' ' << totalCost << '\n';
  }
  return 0;  //정상종료시 반드시 0을 리턴해야합니다.
}