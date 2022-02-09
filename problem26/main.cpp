#include <iostream>
#include <map>
#include <queue>
#include <string>

using namespace std;

int N;

char alphabet[101];
map<int, pair<int, int>> binaryTree;
queue<int> inOrderQueue;

void in_order(int node) {
  if (binaryTree[node].first != 0) in_order(binaryTree[node].first);
  inOrderQueue.push(node);
  if (binaryTree[node].second != 0) in_order(binaryTree[node].second);
}

int main(int argc, char** argv) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int test_case;
  int T;

  freopen("input.txt", "r", stdin);
  //   cin >> T;

  for (test_case = 1; test_case <= 10; ++test_case) {
    cin >> N;

    int depth = 0;
    while (N > ((1 << (depth + 1)) - 1)) depth++;

    if (!binaryTree.empty()) binaryTree.clear();
    while (!inOrderQueue.empty()) inOrderQueue.pop();

    int tempN = N;
    char c;
    int p, l, r;
    for (int curr = 0; curr <= depth - 2; curr++) {
      int itrNum = (1 << curr);
      for (int itr = 0; itr < itrNum; itr++) {
        cin >> p >> c >> l >> r;

        alphabet[p] = c;
        binaryTree[p] = make_pair(l, r);

        tempN--;
      }
    }
    int itrNum = tempN - (1 << (depth - 1));
    for (int itr = 0; itr < (itrNum / 2); itr++) {
      cin >> p >> c >> l >> r;

      alphabet[p] = c;
      binaryTree[p] = make_pair(l, r);

      tempN--;
    }
    for (int itr = 0; itr < (itrNum % 2); itr++) {
      cin >> p >> c >> l;

      alphabet[p] = c;
      binaryTree[p] = make_pair(l, 0);

      tempN--;
    }
    for (int itr = 0; itr < tempN; itr++) {
      cin >> p >> c;

      alphabet[p] = c;
      binaryTree[p] = make_pair(0, 0);
    }

    in_order(1);

    string ret;
    while (!inOrderQueue.empty()) {
      ret.push_back(alphabet[inOrderQueue.front()]);
      inOrderQueue.pop();
    }

    cout << '#' << test_case << ' ' << ret << '\n';
  }
  return 0;  //정상종료시 반드시 0을 리턴해야합니다.
}