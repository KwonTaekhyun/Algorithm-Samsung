#include <algorithm>
#include <climits>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int N, height;
vector<int> childList[100001];
int parentList[100001][21];
int depth[100001];

int LCA_find(int x, int y) {
  if (depth[x] > depth[y]) swap(x, y);

  for (int j = 20; j >= 0; j--) {
    if ((depth[y] - depth[x]) >= (1 << j)) {
      y = parentList[y][j];
    }
  }

  if (x == y) return x;

  for (int j = 20; j >= 0; j--) {
    if (parentList[x][j] != parentList[y][j]) {
      x = parentList[x][j];
      y = parentList[y][j];
    }
  }

  return parentList[x][0];
}

int main(int argc, char** argv) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int test_case;
  int T;

  freopen("input.txt", "r", stdin);
  cin >> T;

  for (test_case = 1; test_case <= T; ++test_case) {
    cin >> N;
    for (int i = 1; i <= N; i++) {
      if (!childList[i].empty()) childList[i].clear();
    }
    for (int i = 1; i <= N; i++) {
      for (int j = 0; j <= 20; j++) {
        parentList[i][j] = 0;
      }
    }

    for (int i = 2; i <= N; i++) {
      int parent;
      cin >> parent;
      childList[parent].push_back(i);
      parentList[i][0] = parent;
    }

    queue<int> BFSList;
    queue<int> q;
    q.push(1);
    BFSList.push(1);
    depth[1] = 0;

    while (!q.empty()) {
      int parent = q.front();
      q.pop();
      for (int i = 0; i < childList[parent].size(); i++) {
        int child = childList[parent][i];
        q.push(child);
        BFSList.push(child);
        depth[child] = depth[parent] + 1;
      }
    }

    for (int j = 1; j <= 20; j++) {
      for (int i = 1; i <= N; i++) {
        parentList[i][j] = parentList[parentList[i][j - 1]][j - 1];
      }
    }

    long long int totalLength = 0;
    int prev = BFSList.front();
    BFSList.pop();

    while (!BFSList.empty()) {
      int curr = BFSList.front();
      BFSList.pop();

      int LCA = LCA_find(prev, curr);

      totalLength += (depth[prev] + depth[curr] - depth[LCA] * 2);

      prev = curr;
    }

    cout << '#' << test_case << ' ' << totalLength << '\n';
  }
  return 0;  //정상종료시 반드시 0을 리턴해야합니다.
}