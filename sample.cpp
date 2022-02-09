#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int test_case;
  int T;

  freopen("input.txt", "r", stdin);
  cin >> T;

  for (test_case = 1; test_case <= T; ++test_case) {
    cout << '#' << test_case << ' ' << '\n';
  }
  return 0;  //정상종료시 반드시 0을 리턴해야합니다.
}