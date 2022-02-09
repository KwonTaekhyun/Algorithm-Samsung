#include <float.h>

#include <cmath>
#include <iostream>

using namespace std;

struct node {
  int x;
  int y;
};

node nodeList[1000];
long double adjMatrix[1000][1000];
bool added[1000];
long double minWeight[1000];

int N;
long double E;

int main(int argc, char** argv) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int test_case;
  int T;

  freopen("input.txt", "r", stdin);
  cin >> T;

  for (test_case = 1; test_case <= T; ++test_case) {
    cin >> N;
    for (int i = 0; i < N; i++) {
      cin >> nodeList[i].x;
    }
    for (int i = 0; i < N; i++) {
      cin >> nodeList[i].y;
    }
    cin >> E;
    for (int i = 0; i < N; i++) {
      for (int j = i; j < N; j++) {
        if (i == j) {
          adjMatrix[i][j] = 0;
          continue;
        }

        long double dx = abs(nodeList[i].x - nodeList[j].x);
        long double dy = abs(nodeList[i].y - nodeList[j].y);
        long double weight = (dx * dx + dy * dy) * E;
        adjMatrix[i][j] = weight;
        adjMatrix[j][i] = weight;
      }
    }

    // 초기화
    long double totalDistance = 0;
    for (int i = 0; i < N; i++) {
      added[i] = false;
      minWeight[i] = DBL_MAX;
    }

    // Prim 알고리즘
    minWeight[0] = 0;
    for (int itr = 0; itr < N; itr++) {
      // 다음으로 추가될 노드 찾기
      int next = -1;
      for (int nodeIdx = 0; nodeIdx < N; nodeIdx++) {
        if (!added[nodeIdx] &&
            (next == -1 || minWeight[nodeIdx] < minWeight[next]))
          next = nodeIdx;
      }

      // 추가
      totalDistance += minWeight[next];
      added[next] = true;

      // 인접한 노드의 minWeight 갱신
      for (int adj = 0; adj < N; adj++) {
        if (!added[adj] && (adjMatrix[next][adj] < minWeight[adj]))
          minWeight[adj] = adjMatrix[next][adj];
      }
    }

    long long int ret = round(totalDistance);

    cout << '#' << test_case << ' ' << ret << '\n';
  }
  return 0;  //정상종료시 반드시 0을 리턴해야합니다.
}