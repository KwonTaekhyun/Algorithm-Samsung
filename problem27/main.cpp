#include <climits>
#include <iostream>
#include <map>

using namespace std;

int N;

char value[201];
map<int, pair<int, int>> binaryTree;

bool is_operator(char c) {
  if (c == '+' || c == '-' || c == '*' || c == '/')
    return true;
  else
    return false;
}

int post_oreder(int node) {
  int L = 0, R = 0;

  if (binaryTree[node].first == 0 && binaryTree[node].second == 0) {
    if (!is_operator(value[node]))
      return 1;
    else
      return 0;
  }

  if (binaryTree[node].first != 0) {
    L = post_oreder(binaryTree[node].first);
  }
  if (binaryTree[node].second != 0) {
    R = post_oreder(binaryTree[node].first);
  }

  if (is_operator(value[node]) && ((L != 0) && (R != 0))) {
    return 1;
  } else
    return 0;
}

int main(int argc, char** argv) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int test_case;
  int T;

  // freopen("input.txt", "r", stdin);
  //    cin >> T;

  for (test_case = 1; test_case <= 10; ++test_case) {
    cin >> N;

    int ret = 1;

    int depth = 0;
    while (N > ((1 << (depth + 1)) - 1)) depth++;

    if (!binaryTree.empty()) binaryTree.clear();

    int tempN = N;
    char c;
    int p, l, r;
    for (int curr = 0; curr <= depth - 2; curr++) {
      int itrNum = (1 << curr);
      for (int itr = 0; itr < itrNum; itr++) {
        cin >> p >> c >> l >> r;

        value[p] = c;
        binaryTree[p] = make_pair(l, r);

        if (!is_operator(c)) {
          ret = 0;
        }

        tempN--;
      }
    }
    int itrNum = tempN - (1 << (depth - 1));
    for (int itr = 0; itr < (itrNum / 2); itr++) {
      cin >> p >> c >> l >> r;

      value[p] = c;
      binaryTree[p] = make_pair(l, r);

      if (!is_operator(c)) {
        ret = 0;
      }

      tempN--;
    }
    for (int itr = 0; itr < (itrNum % 2); itr++) {
      cin >> p >> c >> l;

      value[p] = c;
      binaryTree[p] = make_pair(l, 0);

      ret = 0;

      tempN--;
    }
    for (int itr = 0; itr < tempN; itr++) {
      cin >> p >> c;

      value[p] = c;
      binaryTree[p] = make_pair(0, 0);

      if (is_operator(c)) {
        ret = 0;
      }
    }

    cout << '#' << test_case << ' ' << ret << '\n';
  }
  return 0;  //정상종료시 반드시 0을 리턴해야합니다.
}