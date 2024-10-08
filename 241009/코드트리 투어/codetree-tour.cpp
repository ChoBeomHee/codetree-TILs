#include <iostream>
#include <queue>
#include <cstring>
#define MAX 2001

using namespace std;
int n, m;
vector<pair<int, int>> graph[MAX];
priority_queue<pair<pair<int, int>, int>> contents;
int dist[MAX];
int destination[30001];
bool isDelete[30001];

int start = 0;

void dijk()
{
    priority_queue<pair<int, int>> pq;

    memset(dist, 10101001, sizeof dist);
    pq.push({0, start});
    dist[start] = 0;

    while (!pq.empty())
    {
        int nowNode = pq.top().second;
        pq.pop();
        for (int i = 0; i < graph[nowNode].size(); i++)
        {
            int nextNode = graph[nowNode][i].first;
            int cost = graph[nowNode][i].second;

            if (dist[nextNode] > dist[nowNode] + cost)
            {
                dist[nextNode] = dist[nowNode] + cost;
                pq.push({-dist[nextNode], nextNode});
            }
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int Q;
    cin >> Q;

    for (int i = 0; i < Q; i++)
    {
        int commend;
        cin >> commend;

        if (commend == 100)
        {
            cin >> n >> m;

            for (int i = 0; i < m; i++)
            {
                int a, b, c;
                cin >> a >> b >> c;

                graph[a].push_back({b, c});
                graph[b].push_back({a, c});
            }

            dijk();
        }
        else if (commend == 200)
        {
            int id, rev, dest;
            cin >> id >> rev >> dest;

            isDelete[id] = false;
            int value = rev - dist[dest];
            contents.push({{value, -id}, rev});
            destination[id] = dest;
        }
        else if (commend == 300)
        {
            int idx;
            cin >> idx;

            isDelete[idx] = true;
        }
        else if (commend == 400){
            bool flag = false;

            priority_queue<pair<pair<int, int>, int>> tmp = contents;
            
            while (!tmp.empty())
            {
                pair<pair<int, int>, int> t = tmp.top();
                int cost = t.first.first;
                int idx = - t.first.second;
                tmp.pop();

                if(isDelete[idx]){ // 삭제 됐으면
                    contents.pop();
                }else{ // 삭제 안됨
                    flag = true;
                    if(cost < 0){
                        cout << -1 << '\n';
                    }else{
                        isDelete[idx] = true;
                        cout << idx << '\n';
                    }
                    break;
                }
            }

            if(!flag) cout << -1 << '\n';
        }
        else if (commend == 500)
        {
            int newStart;
            cin >> newStart;

            start = newStart;

            dijk();

            priority_queue<pair<pair<int, int>, int>> tmp_pq;

            while (!contents.empty()){
                pair<pair<int, int>, int> current = contents.top();

                int idx = current.first.second;
                int cost = current.second;
                int value = cost - dist[destination[-idx]];
                contents.pop();

                if (!isDelete[-idx]) {
                    tmp_pq.push(current);
                }
            }

            while(!tmp_pq.empty()){
                pair<pair<int, int>, int> current = tmp_pq.top();

                int idx = current.first.second;
                int cost = current.second;
                int value = cost - dist[destination[-idx]];

                tmp_pq.pop();
                contents.push({{value, idx}, cost});
            }

        }
    }
}