#include <climits>
#include <iostream>
#include <queue>

using namespace std;

int N;
int Board[300][300];
int minClickNum;

int dy[8] = {1, 1, 0, -1, -1, -1, 0, 1};
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};

typedef pair<int, int> Point;

bool isOF(Point p) {
  if (p.first == -1 || p.first == N || p.second == -1 || p.second == N)
    return true;
  else
    return false;
}

void BFS(Point s) {
  queue<Point> q;

  Board[s.first][s.second] = INT_MAX;
  q.push(s);
  while (!q.empty()) {
    Point here = q.front();
    q.pop();

    for (int k = 0; k < 8; k++) {
      Point there = make_pair(here.first + dy[k], here.second + dx[k]);
      if (isOF(there)) continue;
      if (Board[here.first + dy[k]][here.second + dx[k]] == 0) q.push(there);
      Board[here.first + dy[k]][here.second + dx[k]] = INT_MAX;
    }
  }
}

int main(int argc, char** argv) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int test_case;
  int T;

  //   freopen("input.txt", "r", stdin);
  cin >> T;

  for (test_case = 1; test_case <= T; ++test_case) {
    minClickNum = 0;
    cin >> N;

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        char temp;
        cin >> temp;
        if (temp == '*')
          Board[i][j] = INT_MAX;
        else
          Board[i][j] = INT_MIN;
      }
    }

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (Board[i][j] == INT_MIN) {
          int bombNum = 0;
          for (int k = 0; k < 8; k++) {
            if (isOF(make_pair(i + dy[k], j + dx[k]))) continue;
            if (Board[i + dy[k]][j + dx[k]] == INT_MAX) bombNum++;
          }
          Board[i][j] = bombNum;
        }
      }
    }

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (Board[i][j] == 0) {
          minClickNum++;
          BFS(make_pair(i, j));
        }
      }
    }

    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (Board[i][j] != INT_MAX) {
          minClickNum++;
        }
      }
    }

    cout << '#' << test_case << ' ' << minClickNum << '\n';
  }
  return 0;  //정상종료시 반드시 0을 리턴해야합니다.
}