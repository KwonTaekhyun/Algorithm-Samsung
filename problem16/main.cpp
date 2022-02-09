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

using namespace std;

typedef struct {
  int s;
  int e;
} Ad;

Ad peakAdList[100000];
int peakAdSum[100001];

int main(int argc, char** argv) {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);

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
    int N, L;
    cin >> L;
    cin >> N;
    int maxOverlappingTime = 0;

    //초기화
    for (int i = 0; i < N; i++) {
      int s, e;
      cin >> s >> e;
      peakAdList[i].s = s;
      peakAdList[i].e = e;
    }
    int adTime = 0;
    for (int i = 0; i <= N; i++) {
      peakAdSum[i] = adTime;
      if (i != N) {
        adTime += peakAdList[i].e - peakAdList[i].s;
      }
    }

    // 이분탐색을 통해 시작 광고에 대해 cover가 불가능한 첫 광고를 찾고
    // (upperBound) upperBound-1 광고까지의 최대 광고 overlapping time을 찾는다
    for (int i = 0; i < N; i++) {
      int pivot = i;
      int start = i + 1;
      int end = N - 1;
      int upperBound = N;

      // upperBound 찾기
      while (start <= end) {
        int mid = (start + end) / 2;

        if (peakAdList[mid].s + 1 >= peakAdList[pivot].s + L) {
          // mid가 cover 불가능한 원소이다
          end = mid - 1;
          upperBound = mid;
        } else {
          start = mid + 1;
        }
      }

      // overlappingTime 찾기
      // pivot.start ~ upperBound-1까지의 overlappingTime
      int overlappingTime;
      if (pivot == (N - 1))
        overlappingTime =
            ((min(peakAdList[upperBound - 1].e, peakAdList[pivot].s + L) -
              peakAdList[upperBound - 1].s));
      else
        overlappingTime =
            (peakAdSum[upperBound - 1] - peakAdSum[pivot]) +
            ((min(peakAdList[upperBound - 1].e, peakAdList[pivot].s + L) -
              peakAdList[upperBound - 1].s));

      maxOverlappingTime = max(maxOverlappingTime, overlappingTime);
    }

    cout << "#" << test_case << ' ' << maxOverlappingTime << '\n';
  }
  return 0;  //정상종료시 반드시 0을 리턴해야합니다.
}