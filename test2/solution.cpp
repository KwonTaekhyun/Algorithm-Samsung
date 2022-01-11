#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>

using namespace std;

typedef pair<int, int> Edge;
typedef struct
{
    int sex;
    char name[20];
} Vertex;
// typedef pair<int, char[]> Vertex;

vector<Vertex> vertex_list;
vector<Edge> adjacent_list[201];
vector<int> dist_list(201);

int lastMemNum;

//	 The below commented functions are for your reference. If you want
//	 to use it, uncomment these functions.
int mstrcmp(const char a[], const char b[])
{
    int i;
    for (i = 0; a[i] != '\0'; ++i)
        if (a[i] != b[i])
            return a[i] - b[i];
    return a[i] - b[i];
}

void mstrcpy(char dest[], const char src[])
{
    int i = 0;
    while (src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = src[i];
}

int mstrlen(const char a[])
{
    int i;
    for (i = 0; a[i] != '\0'; ++i)
        ;
    return i;
}

void init(char initialMemberName[], int initialMemberSex)
{
    if (vertex_list.size() != 0)
        vertex_list.clear();

    for (int i = 0; i < 200; i++)
    {
        if (adjacent_list[i].size() != 0)
            adjacent_list[i].clear();
    }

    Vertex temp;
    temp.sex = initialMemberSex;
    mstrcpy(temp.name, initialMemberName);
    vertex_list.push_back(temp);
    lastMemNum = 0;
}

bool addMember(char newMemberName[], int newMemberSex, int relationship, char existingMemberName[])
{
    int existingMemNum;
    Vertex existingMem;
    for (int i = 0; i < 200; i++)
    {
        if (!mstrcmp(vertex_list[i].name, existingMemberName))
        {
            existingMemNum = i;
            existingMem = vertex_list[i];
            break;
        }
    }

    switch (relationship)
    {
    case 0:
    {
        // 배우자로 추가
        if (existingMem.sex != newMemberSex)
        {
            // 이성 배우자

            vector<Edge> *existingMemAdjList = &adjacent_list[existingMemNum];

            for (int i = 0; i < existingMemAdjList->size(); i++)
            {
                if (existingMemAdjList->at(i).second == 0)
                {
                    return false;
                }
            }

            // 배우자 존재 X
            // 멤버 추가
            Vertex temp;
            temp.sex = newMemberSex;
            mstrcpy(temp.name, newMemberName);
            vertex_list.push_back(temp);
            lastMemNum++;

            vector<Edge> *newMemAdjList = &adjacent_list[lastMemNum];

            // 1. 기존멤버와 배우자관계 추가
            existingMemAdjList->push_back(make_pair(lastMemNum, 0));
            newMemAdjList->push_back(make_pair(existingMemNum, 0));
            // 2. 기존멤버의 자식들과 부모관계 추가
            for (int i = 0; i < existingMemAdjList->size(); i++)
            {
                Edge adjMem = existingMemAdjList->at(i);
                if (adjMem.second == 2)
                {
                    newMemAdjList->push_back(make_pair(adjMem.first, 2));
                    adjacent_list[adjMem.first].push_back(make_pair(lastMemNum, 1));
                }
            }

            return true;
        }

        return false;
        break;
    }
    case 1:
    {
        // 부모로 추가

        vector<Edge> *existingMemAdjList = &adjacent_list[existingMemNum];
        bool marriage = false;
        int existingParNum = INT_MAX;

        for (int i = 0; i < existingMemAdjList->size(); i++)
        {
            Edge adjMem = existingMemAdjList->at(i);
            if (adjMem.second == 1)
            {
                Vertex existingPar = vertex_list[adjMem.first];
                // 부모 존재 && 자신과 성별 동일
                if (existingPar.sex == newMemberSex)
                {
                    return false;
                }
                // 자신과 성별이 다른 부모가 존재 -> 배우자관계로 추가
                marriage = true;
                existingParNum = adjMem.first;
            }
        }

        // 자신과 성별이 동일한 부모가 존재하지 않음 -> 자신과 기존멤버 사이 부모관계 추가
        if (marriage)
        {
            // 만약 기존멤버에 자신과 성별이 다른 부모가 존재할 경우 해당멤버와 배우자관계로 추가
            // 자동으로 기존멤버의 부모로 자신이 등록
            // 멤버 추가
            Vertex temp;
            temp.sex = newMemberSex;
            mstrcpy(temp.name, newMemberName);
            vertex_list.push_back(temp);
            lastMemNum++;

            vector<Edge> *newMemAdjList = &adjacent_list[lastMemNum];
            vector<Edge> *existingParAdjList = &adjacent_list[existingParNum];

            // 1. 기존멤버와 배우자관계 추가
            existingParAdjList->push_back(make_pair(lastMemNum, 0));
            newMemAdjList->push_back(make_pair(existingParNum, 0));
            // 2. 기존멤버의 자식들과 부모관계 추가
            for (int i = 0; i < existingParAdjList->size(); i++)
            {
                Edge adjMem = existingParAdjList->at(i);
                if (adjMem.second == 2)
                {
                    newMemAdjList->push_back(make_pair(adjMem.first, 2));
                    adjacent_list[adjMem.first].push_back(make_pair(lastMemNum, 1));
                }
            }
        }
        else
        {
            // 만약 기존멤버에 자신과 성별이 다른 부모가 존재하지 않는 경우 바로 자신을 부모로 등록
            // 멤버 추가
            Vertex temp;
            temp.sex = newMemberSex;
            mstrcpy(temp.name, newMemberName);
            vertex_list.push_back(temp);
            lastMemNum++;

            vector<Edge> *newMemAdjList = &adjacent_list[lastMemNum];

            newMemAdjList->push_back(make_pair(existingMemNum, 2));
            adjacent_list[existingMemNum].push_back(make_pair(lastMemNum, 1));
        }

        return true;
        break;
    }
    case 2:
    {
        // 자식으로 추가

        vector<Edge> *existingMemAdjList = &adjacent_list[existingMemNum];

        // 멤버 추가
        Vertex temp;
        temp.sex = newMemberSex;
        mstrcpy(temp.name, newMemberName);
        vertex_list.push_back(temp);
        lastMemNum++;

        vector<Edge> *newMemAdjList = &adjacent_list[lastMemNum];

        // 기존 멤버에 배우자가 존재할 경우 자신과 부모관계 추가
        for (int i = 0; i < existingMemAdjList->size(); i++)
        {
            Edge adjMem = existingMemAdjList->at(i);
            if (adjMem.second == 0)
            {
                newMemAdjList->push_back(make_pair(adjMem.first, 1));
                adjacent_list[adjMem.first].push_back(make_pair(lastMemNum, 2));

                break;
            }
        }

        // 기존 멤버와 자신 사이 부모관계 추가
        newMemAdjList->push_back(make_pair(existingMemNum, 1));
        adjacent_list[existingMemNum].push_back(make_pair(lastMemNum, 2));

        return true;
        break;
    }
    }

    return false;
}

void getDijkstra(char name[])
{
    // 기준 멤버로 부터 모든 멤버까지의 최단 경로 구하기

    // 기준 멤버 찾기
    int existingMemNum;
    for (int i = 0; i < 200; i++)
    {
        if (!mstrcmp(vertex_list[i].name, name))
        {
            existingMemNum = i;
            break;
        }
    }

    // 최단 경로 리스트 초기화
    for (int i = 0; i < 200; i++)
    {
        dist_list[i] = INT_MAX;
    }

    dist_list[existingMemNum] = 0;

    priority_queue<pair<int, int> > pq;
    pq.push(make_pair(0, existingMemNum));

    while (!pq.empty())
    {
        int distance = -pq.top().first;
        int currMemNum = pq.top().second;
        pq.pop();

        if (dist_list[currMemNum] < distance)
            continue;

        for (int i = 0; i < adjacent_list[currMemNum].size(); i++)
        {
            int destMemNum = adjacent_list[currMemNum][i].first;
            int tempDistance = adjacent_list[currMemNum][i].second == 0 ? distance : distance + 1;

            if (tempDistance < dist_list[destMemNum])
            {
                dist_list[destMemNum] = tempDistance;
                pq.push(make_pair(-tempDistance, destMemNum));
            }
        }
    }
}

int getDistance(char nameA[], char nameB[])
{
    getDijkstra(nameA);

    int destMemNum;
    for (int i = 0; i < 200; i++)
    {
        if (!mstrcmp(vertex_list[i].name, nameB))
        {
            destMemNum = i;
            break;
        }
    }

    return dist_list[destMemNum] != INT_MAX ? dist_list[destMemNum] : -1;
}

int countMember(char name[], int dist)
{
    getDijkstra(name);

    int srcMemNum;
    for (int i = 0; i < 200; i++)
    {
        if (!mstrcmp(vertex_list[i].name, name))
        {
            srcMemNum = i;
            break;
        }
    }

    int count = 0;
    for (int i = 0; i < 200; i++)
    {
        if (i == srcMemNum)
            continue;

        if (dist_list[i] == dist)
            count++;
    }

    return count;
}
