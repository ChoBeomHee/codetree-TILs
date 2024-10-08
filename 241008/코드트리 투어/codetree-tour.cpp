#include <iostream>
    #include <queue>
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

        for (int i = 0; i <= n; i++)
        {
            dist[i] = 10101010;
        }
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
                    pq.push({-cost, nextNode});
                }
            }
        }
    }

    int main()
    {
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
            else if (commend == 400)
            {
                bool flag = false;

                priority_queue<pair<pair<int, int>, int>> tmp_pq = contents;
                priority_queue<pair<pair<int, int>, int>> after_pq;
                while (!tmp_pq.empty())
                {
                    int cost = tmp_pq.top().first.first;
                    int idx = -tmp_pq.top().first.second;

                    if (cost < 0){
                        after_pq.push(tmp_pq.top());
                        tmp_pq.pop();
                        continue;
                    }

                    if (isDelete[idx]){
                        tmp_pq.pop();
                        continue;
                    }

                    tmp_pq.pop();
                    
                    flag = true;
                    cout << idx << '\n';
                    
                    isDelete[idx] = true;
                    
                    break;
                }

                while(!tmp_pq.empty()){
                    after_pq.push(tmp_pq.top());
                    tmp_pq.pop();
                }

                contents = after_pq;

                if (!flag)
                    cout << -1 << '\n';
            }
            else if (commend == 500)
            {
                int newStart;
                cin >> newStart;

                start = newStart;

                dijk();

                priority_queue<pair<pair<int, int>, int>> tmp_pq = contents;

                while (!contents.empty())
                {
                    int idx = contents.top().first.second;
                    int value = contents.top().second - dist[destination[-idx]];
                    int origin = contents.top().second;
                    contents.pop();
                    if (!isDelete[-idx]){
                        tmp_pq.push({{value, idx}, origin});
                    }
                }

                contents = tmp_pq;
            }
        }
    }