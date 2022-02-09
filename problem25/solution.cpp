typedef struct {
  int y, x;
} Point;

int adjMap[11][11];
int distance[11][11];
int N;
Point queue[10000];
int qPos;
int qNum;

int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, +1, 0};

void bfs_init(int map_size, int map[10][10]) {
  N = map_size;
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      adjMap[i][j] = map[i - 1][j - 1];
    }
  }
}
int bfs(int x1, int y1, int x2, int y2) {
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++) {
      distance[i][j] = -1;
    }
  }

  qPos = 0;
  qNum = 0;

  Point start = {y1, x1};
  queue[qPos] = start;
  qPos++;
  qNum++;
  distance[y1][x1] = 0;

  while (qNum != 0) {
    Point here = queue[qPos - qNum];
    qNum--;

    for (int i = 0; i < 4; i++) {
      Point there = {here.y + dy[i], here.x + dx[i]};
      if (there.x < 1 || there.x > N || there.y < 1 || there.y > N) {
        continue;
      }
      if (adjMap[there.y][there.x]) {
        continue;
      }

      if (distance[there.y][there.x] == -1) {
        queue[qPos] = there;
        qPos++;
        qNum++;
        distance[there.y][there.x] = distance[here.y][here.x] + 1;
      }
    }
  }

  return distance[y2][x2];
}