#include<iostream>
#include<vector>
#include<cstring>
#include <queue>
using namespace std;

int K, M;
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};
int letter_idx = 0;
vector<vector<int>> historicsite(5, vector<int>(5));
vector<int> letter;
void print(vector<vector<int>> vec){
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            cout << vec[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}   
vector<vector<int>> lotation_maps(int x, int y, int rad){ // 회전해서 리턴
    vector<vector<int>> result = historicsite;

    for(int i = 0; i < rad; i++){
        int tmp = result[x - 1][y - 1];
        result[x - 1][y - 1] = result[x + 1][y - 1];
        result[x + 1][y - 1] = result[x + 1][y + 1];
        result[x + 1][y + 1] = result[x - 1][y + 1];
        result[x - 1][y + 1] = tmp;

        tmp = result[x - 1][y];
        result[x - 1][y] = result[x][y - 1];
        result[x][y - 1] = result[x + 1][y];
        result[x + 1][y] = result[x][y + 1];
        result[x][y + 1] = tmp;
    }

    return result;
}

bool range(int x, int y) {
    return x < 5 && x > -1 && y < 5 && y > -1;
}

int Count_ruins(vector<vector<int>> maps){ // 유적의 개수를 새서 리턴
    bool check[5][5];
    int result = 0;
    memset(check, false, sizeof check);

    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            int value = maps[i][j];
            int cnt = 1;

            if(!check[i][j]){
                queue<pair<int, int>> q;

                q.push({i, j});
                check[i][j] = true;

                while(!q.empty()){
                    int x = q.front().first;
                    int y = q.front().second;
                    q.pop();

                    for(int idx = 0; idx < 4; idx++){
                        int nx = x + dx[idx];
                        int ny = y + dy[idx];

                        if(range(nx, ny) && !check[nx][ny] && maps[nx][ny] == value){
                            check[nx][ny] = true;
                            cnt++;
                            q.push({nx, ny});
                        }
                    }
                }
            }
            if(cnt > 2) result += cnt;
        }
    }

    return result;
}

int recusion(vector<vector<int>> maps){
    bool check[5][5];
    int result = 0;

    memset(check, false, sizeof check);
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            if(!check[i][j]){
                vector<pair<int, int>> points;

                points.push_back({i, j});
                int value = maps[i][j];

                queue<pair<int, int>> q;

                q.push({i, j});
                check[i][j] = true;

                while(!q.empty()){
                    int x = q.front().first;
                    int y = q.front().second;
                    q.pop();

                    for(int idx = 0; idx < 4; idx++){
                        int nx = x + dx[idx];
                        int ny = y + dy[idx];

                        if(range(nx, ny) && !check[nx][ny] && maps[nx][ny] == value){
                            check[nx][ny] = true;
                            points.push_back({nx, ny});
                            q.push({nx, ny});
                        }
                    }
                }
            
                if(points.size() > 2){
                    for(pair<int, int> p : points){
                        maps[p.first][p.second] = -1;
                    }

                    result += points.size();
                
                }                 
            }
        }
    }

    // -1 인 부분 유적 채우기
    int pre = letter_idx;
    for(int j = 0; j < 5; j++){
        for(int i = 4; i > -1; i--){
            if(maps[i][j] == -1){
                maps[i][j] = letter[letter_idx];
                letter_idx++;
            }
        }
    }

    int after = letter_idx;

    if(pre == after) {
        historicsite = maps;
        return 0;
    }
    else return result + recusion(maps);
}



bool turn(){
    int row = 6, col = 6, rad = 4, maxCnt = 0;
    vector<vector<int>> next_map;

    for(int i = 1; i < 4; i++){
        for(int j = 1; j < 4; j++){
            for(int k = 1; k < 4; k++){
                vector<vector<int>> tmp_maps = lotation_maps(i, j, k);
                int cnt = Count_ruins(tmp_maps);

                if(maxCnt < cnt){
                    row = i, col = j, rad = k, maxCnt = cnt, next_map = tmp_maps;
                }else if(maxCnt == cnt){
                    if(rad > k){
                        row = i, col = j, rad = k, maxCnt = cnt, next_map = tmp_maps;
                    }else if(rad == k){
                        if(row > i){
                            row = i, col = j, rad = k, maxCnt = cnt, next_map = tmp_maps;
                        }else if(col > j){
                            row = i, col = j, rad = k, maxCnt = cnt, next_map = tmp_maps;
                        }
                    }
                }
                // if(i == 2 && j == 2){
                //     cout << Count_ruins(tmp_maps) << endl;
                // }
            }
        }
    }

    if(maxCnt > 2){
        cout << recusion(next_map) << ' ';

        return true;
    }

    return false;
}

int main(){
    cin >> K >> M;

    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++)
            cin >> historicsite[i][j];
    for(int i = 0; i < M; i++){
        int tmp; cin >> tmp;
        letter.push_back(tmp);
    }

    for(int i = 0; i < K; i++){
        if(turn()) break;
    }
}