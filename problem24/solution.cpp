int adjList[100][5];
int insertPos[100];
bool visited[100];
bool ended;
int currKing;

void dfs_init(int N, int path[100][2]) {
  for (int i = 1; i < 100; i++) {
    insertPos[i] = 0;
  }

  for (int i = 0; i < 100; i++) {
    if (path[i][0] == 0) break;

    adjList[path[i][0]][insertPos[path[i][0]]] = path[i][1];
    insertPos[path[i][0]]++;
  }
}

void dfs_exe(int here) {
  visited[here] = true;
  for (int i = 0; (i < insertPos[here]) && (!ended); i++) {
    int there = adjList[here][i];

    if (there > currKing) {
      currKing = there;
      ended = true;
      return;
    }

    if (!visited[there]) {
      dfs_exe(there);
    }
  }
}

int dfs(int n) {
  ended = false;
  currKing = n;

  for (int i = 1; i < 100; i++) {
    visited[i] = false;
  }

  dfs_exe(n);

  if (currKing > n)
    return currKing;
  else
    return -1;
}
