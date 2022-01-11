#define MISS 0
#define CARRIER 1
#define BATTLESHIP 2
#define CRUISER 3
#define SUBMARINE 4
#define DESTROYER 5
#define UNCHECKED -1

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

extern int fire(int r, int c);

vector<vector<int> > Board(10, vector<int>(10, UNCHECKED));
int Rest[6] = {0, 5, 4, 3, 3, 2};

int Odd[5] = {1, 3, 5, 7, 9};
int Even[5] = {0, 2, 4, 6, 8};
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};

typedef struct
{
    int type;
    int row;
    int col;
} Chessman;

bool checkFinish()
{
    return (Rest[1] == 0) && (Rest[2] == 0) && (Rest[3] == 0) && (Rest[4] == 0) && (Rest[5] == 0);
}

void init(int limit)
{
}

void play()
{
    // 초기화
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            Board[i][j] = UNCHECKED;
        }
    }
    Rest[1] = 5;
    Rest[2] = 4;
    Rest[3] = 3;
    Rest[4] = 3;
    Rest[5] = 2;

    bool isOdd = false;

    // 게임 시작
    for (int row = 0; row < 10; row++)
    {
        for (int colCnt = 0; colCnt < 5; colCnt++)
        {
            int col = isOdd ? Odd[colCnt] : Even[colCnt];

            if (Board[row][col] != UNCHECKED)
            {
                // 이미 추격한 block
                continue;
            }
            else
            {
                // 추격
                int result = fire(row, col);
                Board[row][col] = result;

                if (result == MISS)
                {
                    // MISS
                    continue;
                }
                else
                {
                    // HIT
                    queue<Chessman> Queue;
                    int direction = 0;
                    int tempRow = row;
                    int tempCol = col;
                    int pivotRow = row;
                    int pivotCol = col;

                    Rest[result]--;
                    while (Rest[result] || !Queue.empty())
                    {
                        if ((Rest[result] == 0) && !Queue.empty())
                        {
                            Chessman temp = Queue.front();
                            Queue.pop();

                            if (Rest[temp.type] == 0)
                            {
                                direction = 0;
                                continue;
                            }

                            result = temp.type;
                            tempRow = temp.row;
                            tempCol = temp.col;
                            pivotRow = temp.row;
                            pivotCol = temp.col;
                            direction = 0;

                            continue;
                        }

                        if ((tempRow + dy[direction] > 9) || (tempRow + dy[direction] < 0) || (tempCol + dx[direction] > 9) || (tempCol + dx[direction] < 0))
                        {
                            if ((tempRow == pivotRow) && (tempCol == pivotCol))
                            {
                                // 처음 주위 탐색의 경우 방향을 1만 바꾼다
                                direction++;
                                continue;
                            }
                            else
                            {
                                direction += 2;
                                tempRow = pivotRow;
                                tempCol = pivotCol;
                                continue;
                            }
                        }

                        int subResult = fire(tempRow + dy[direction], tempCol + dx[direction]);
                        Board[tempRow + dy[direction]][tempCol + dx[direction]] = subResult;

                        if (subResult == MISS)
                        {
                            // MISS
                            if ((tempRow == pivotRow) && (tempCol == pivotCol))
                            {
                                // 처음 주위 탐색의 경우 방향을 1만 바꾼다
                                direction++;
                                continue;
                            }
                            else
                            {
                                direction += 2;
                                tempRow = pivotRow;
                                tempCol = pivotCol;
                                continue;
                            }
                        }
                        else if (subResult == result)
                        {
                            // HIT (현재 추격중인 block)
                            Rest[result]--;
                            tempRow += dy[direction];
                            tempCol += dx[direction];
                            continue;
                        }
                        else
                        {
                            // HIT (다른 type의 block)
                            Rest[subResult]--;
                            Chessman temp;
                            temp.type = subResult;
                            temp.row = tempRow + dy[direction];
                            temp.col = tempCol + dx[direction];
                            Queue.push(temp);

                            if ((tempRow == pivotRow) && (tempCol == pivotCol))
                            {
                                // 처음 주위 탐색의 경우 방향을 1만 바꾼다
                                direction++;
                                continue;
                            }
                            else
                            {
                                direction += 2;
                                tempRow = pivotRow;
                                tempCol = pivotCol;
                                continue;
                            }
                        }
                    }
                }
            }

            if (checkFinish())
                return;
        }

        isOdd = !isOdd;
    }
}