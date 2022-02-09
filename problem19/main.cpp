#include <algorithm>
#include <climits>
#include <iostream>

using namespace std;

typedef struct {
  int y, x;
} Point;

Point core[12];
int Board[12][12];

int dy[4] = {-1, 0, +1, 0};
int dx[4] = {0, 1, 0, -1};

int N, C, maxCoreNum, maxTotalLength;

bool isConnected(Point& p) {
  if (p.y == 0 || p.y == N - 1 || p.x == 0 || p.x == N - 1)
    return true;
  else
    return false;
}

bool isPromissing(int coreIdx, int coreNum) {
  if ((C - (coreIdx + 1) + coreNum) >= maxCoreNum)
    return true;
  else
    return false;
}

void BT_DFS(int coreIdx, int coreNum, int totalLength) {
  if (coreIdx == C) {
    if (coreNum > maxCoreNum) {
      maxCoreNum = coreNum;
      maxTotalLength = totalLength;
    } else if (coreNum == maxCoreNum) {
      maxTotalLength = min(maxTotalLength, totalLength);
    }
    return;
  }

  Point& curr = core[coreIdx];
  if (isConnected(curr)) {
    if (isPromissing(coreIdx, coreNum + 1)) {
      BT_DFS(coreIdx + 1, coreNum + 1, totalLength);
    }
    return;
  }

  for (int i = 0; i < 4; i++) {
    Point point = {curr.y + dy[i], curr.x + dx[i]};
    int length = 1;

    while ((Board[point.y][point.x] == 0) && (!isConnected(point))) {
      point.y += dy[i];
      point.x += dx[i];
      length++;
    }

    if ((Board[point.y][point.x] == 0) && (isConnected(point))) {
      if (isPromissing(coreIdx, coreNum + 1)) {
        for (int l = 1; l <= length; l++) {
          Board[curr.y + dy[i] * l][curr.x + dx[i] * l] = 1;
        }
        BT_DFS(coreIdx + 1, coreNum + 1, totalLength + length);
        for (int l = 1; l <= length; l++) {
          Board[curr.y + dy[i] * l][curr.x + dx[i] * l] = 0;
        }
      }
    } else {
      if (isPromissing(coreIdx, coreNum)) {
        BT_DFS(coreIdx + 1, coreNum, totalLength);
      }
    }
  }
}

int main(int argc, char** argv) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int test_case;
  int T;

  freopen("input.txt", "r", stdin);
  cin >> T;

  for (test_case = 1; test_case <= T; ++test_case) {
    maxCoreNum = INT_MIN;
    maxTotalLength = INT_MAX;

    cin >> N;
    C = 0;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cin >> Board[i][j];

        if (Board[i][j] == 1) {
          Point& corePoint = core[C++];
          corePoint.y = i;
          corePoint.x = j;
        }
      }
    }

    BT_DFS(0, 0, 0);

    cout << '#' << test_case << ' ' << maxTotalLength << '\n';
  }
  return 0;  //정상종료시 반드시 0을 리턴해야합니다.
}