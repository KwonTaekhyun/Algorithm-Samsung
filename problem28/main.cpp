#include <climits>
#include <cmath>
#include <iostream>
#include <string>

using namespace std;

int N;

string value[1001];
pair<int, int> BT[1001];

long double operation(long double l, long double r, string op) {
  switch (op[0]) {
    case '+':
      return l + r;
    case '-':
      return l - r;
    case '*':
      return l * r;
    case '/':
      return l / r;
    default:
      return INT_MIN;
  }
}

bool is_operator(string c) {
  if (c == "+" || c == "-" || c == "*" || c == "/")
    return true;
  else
    return false;
}

long double post_oreder(int node) {
  long double L = 0, R = 0;

  if (BT[node].first == 0 && BT[node].second == 0) {
    return stod(value[node]);
  }

  if (BT[node].first != 0) {
    L = post_oreder(BT[node].first);
  }
  if (BT[node].second != 0) {
    R = post_oreder(BT[node].second);
  }

  return operation(L, R, value[node]);
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

    for (int i = 1; i <= N; i++) {
      value[i].clear();
    }

    int tempN = N;
    string c;
    int p, l, r;

    for (int itr = 0; itr < N; itr++) {
      if (!c.empty()) c.clear();
      cin >> p >> c;
      value[p] = c;

      if (is_operator(c)) {
        cin >> l >> r;
        BT[p].first = l;
        BT[p].second = r;
      } else {
        BT[p].first = 0;
        BT[p].second = 0;
      }
    }

    cout << '#' << test_case << ' ' << floor(post_oreder(1)) << '\n';
  }
  return 0;  //정상종료시 반드시 0을 리턴해야합니다.
}