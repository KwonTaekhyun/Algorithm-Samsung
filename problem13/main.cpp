/////////////////////////////////////////////////////////////////////////////////////////////
// 기본 제공코드는 임의 수정해도 관계 없습니다. 단, 입출력 포맷 주의
// 아래 표준 입출력 예제 필요시 참고하세요.
// 표준 입력 예제
// int a;
// float b, c;
// double d, e, f;
// char g;
// char var[256];
// long long AB;
// cin >> a;                            // int 변수 1개 입력받는 예제
// cin >> b >> c;                       // float 변수 2개 입력받는 예제
// cin >> d >> e >> f;                  // double 변수 3개 입력받는 예제
// cin >> g;                            // char 변수 1개 입력받는 예제
// cin >> var;                          // 문자열 1개 입력받는 예제
// cin >> AB;                           // long long 변수 1개 입력받는 예제
/////////////////////////////////////////////////////////////////////////////////////////////
// 표준 출력 예제
// int a = 0;
// float b = 1.0, c = 2.0;
// double d = 3.0, e = 0.0; f = 1.0;
// char g = 'b';
// char var[256] = "ABCDEFG";
// long long AB = 12345678901234567L;
// cout << a;                           // int 변수 1개 출력하는 예제
// cout << b << " " << c;               // float 변수 2개 출력하는 예제
// cout << d << " " << e << " " << f;   // double 변수 3개 출력하는 예제
// cout << g;                           // char 변수 1개 출력하는 예제
// cout << var;                         // 문자열 1개 출력하는 예제
// cout << AB;                          // long long 변수 1개 출력하는 예제
/////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> A, B;
int aLength, bLength;
int maxSnacks[3][100][101];

int main(int argc, char** argv) {
  int test_case;
  int T;
  /*
     아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
     앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의
     코드입니다.
     //여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을
     저장한 후, freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신
     파일로부터 입력을 받아올 수 있습니다. 따라서 테스트를 수행할 때에는 아래
     주석을 지우고 이 함수를 사용하셔도 좋습니다. freopen 함수를 사용하기
     위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다. 단,
     채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리
     하셔야 합니다.
  */
  freopen("input.txt", "r", stdin);
  cin >> T;
  /*
     여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
  */
  for (test_case = 1; test_case <= T; ++test_case) {
    if (!A.empty()) A.clear();
    if (!B.empty()) B.clear();

    cin >> aLength;
    for (int i = 0; i < aLength; i++) {
      int temp;
      cin >> temp;
      A.push_back(temp);
    }
    cin >> bLength;
    for (int i = 0; i < bLength; i++) {
      int temp;
      cin >> temp;
      B.push_back(temp);
    }

    // exception case: B가 존재하지 않는 경우
    if (bLength == 0) {
      int quantity[3000] = {};

      for (int k = aLength - 1; k >= 0; k--) {
        if (k == aLength - 1) {
          quantity[k] = A[k];
          continue;
        }

        if (k == aLength - 2) {
          quantity[k] = max(A[k], quantity[k + 1]);
        } else {
          quantity[k] = max(quantity[k + 2] + A[k], quantity[k + 1]);
        }
      }

      cout << '#' << test_case << ' ' << quantity[0] << endl;

      continue;
    }

    if (!B.empty()) {
      sort(B.begin(), B.end());
    }

    // base case: A를 다 소진한 케이스
    for (int l = 0; l < bLength; l++) {
      for (int r = 0; r <= (l + 1); r++) {
        if (r == 0) {
          maxSnacks[aLength % 3][l][r] = 0;
          continue;
        } else if (r == 1) {
          maxSnacks[aLength % 3][l][r] = B[l];
          continue;
        } else {
          maxSnacks[aLength % 3][l][r] =
              max(maxSnacks[aLength % 3][l - 1][r - 2] + B[l],
                  maxSnacks[aLength % 3][l][r - 1]);
          continue;
        }
      }
    }

    for (int k = aLength - 1; k >= 0; k--) {
      for (int l = 0; l < bLength; l++) {
        for (int r = 0; r <= (l + 1); r++) {
          int& quantity = maxSnacks[k % 3][l][r] = 0;

          // 1. Ao
          // 1-1. Ao 종료
          if ((r == 0) && (k == aLength - 1)) {
            quantity = max(quantity, maxSnacks[(k + 1) % 3][l][r] + A[k]);
          } else {
            // 1-2. Ao Ax
            if (k <= aLength - 2) {
              quantity = max(quantity, maxSnacks[(k + 2) % 3][l][r] + A[k]);
            }
            // 1-3. Ao Bx
            if (r > 0) {
              quantity = max(quantity, maxSnacks[(k + 1) % 3][l][r - 1] + A[k]);
            }
          }

          // 2. Ax
          quantity = max(quantity, maxSnacks[(k + 1) % 3][l][r]);

          // 3. Bo
          // 3-1. Bo Ax
          if (r > 0) {
            if (l == 0) {
              quantity = max(quantity, maxSnacks[(k + 1) % 3][l][r - 1] + B[l]);
            } else {
              quantity =
                  max(quantity, maxSnacks[(k + 1) % 3][l - 1][r - 1] + B[l]);
            }
          }
          // 3-2. Bo Bx
          if (r >= 2) {
            quantity = max(quantity, maxSnacks[k % 3][l - 1][r - 2] + B[l]);
          }

          // 4. Bx
          if (r > 0) {
            quantity = max(quantity, maxSnacks[k % 3][l][r - 1]);
          }
        }
      }
    }
    cout << '#' << test_case << ' ' << maxSnacks[0][bLength - 1][bLength]
         << endl;
  }
  return 0;  //정상종료시 반드시 0을 리턴해야합니다.
}