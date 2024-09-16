#include <iostream>
#include <queue>

using namespace std;

int R, C, K;
int fx, fy;
int golidx = 10;
int forest[71][71];
int exitarray[71][71];
int answer = 0;
int dr[] = {-1, 0, 1, 0};
int dc[] = {0, 1, 0, -1};

bool check_range(int x, int y){
    if(x < 0) return true;
    return x > -1 && x < R && y > -1 && y < C;
}

bool check_bound(int x, int y){
    return x < R - 1 && x > 0 && y < C - 1 && y > 0;
}

bool check_move_down(int x, int y){
    if(check_range(x + 1, y - 1)) { // 왼쪽 대각
        if(forest[x + 1][y - 1] != 0) return false;
    }else{
        return false;
    }

    if(check_range(x + 1, y + 1)){ // 오른쪽 대각
        if(forest[x + 1][y + 1] != 0) return false;
    }else {
        return false;
    }

    if(check_range(x + 2,y)){ // 아래
        if(forest[x + 2][y] != 0) return false;
    }else{
        return false;
    }

    return true;
}

bool check_move_left(int x, int y){
    if(check_range(x, y - 2)){
        if(forest[x][y - 2] != 0) return false;
    }else return false;
    
    if(check_range(x - 1, y - 1)){
        if(forest[x - 1][y - 1] != 0) return false;
    }else return false;
    if(check_range(x + 1, y - 1)){
        if(forest[x + 1][y - 1] != 0) return false;
    }else return false;

    if(check_range(x + 1, y - 2)){
        if(forest[x + 1][y - 2] != 0) return false;
    }else return false;
    if(check_range(x + 2, y - 1)){
        if(forest[x + 2][y - 1] != 0) return false;
    }else return false;
    
    return true;
}

bool check_move_right(int x, int y){
if(check_range(x, y + 2)){
        if(forest[x][y + 2] != 0) return false;
    }else return false;
    
    if(check_range(x - 1, y + 1)){
        if(forest[x - 1][y + 1] != 0) return false;
    }else return false;
    if(check_range(x + 1, y + 1)){
        if(forest[x + 1][y + 1] != 0) return false;
    }else return false;

    if(check_range(x + 1, y + 2)){
        if(forest[x + 1][y + 2] != 0) return false;
    }else return false;
    if(check_range(x + 2, y + 1)){
        if(forest[x + 2][y + 1] != 0) return false;
    }else return false;
    
    return true;
}

bool moveGolem(int r, int c, int exit){
    if(check_move_down(r, c)){
        return moveGolem(r + 1, c, exit);
    }else if(check_move_left(r, c)){
        return moveGolem(r + 1, c - 1, ((exit - 1) + 4) % 4);
    }else if(check_move_right(r, c)){
        return moveGolem(r + 1, c + 1, (exit + 1) % 4);
    }else{ // 이동할 수 없음
        if(!check_bound(r, c)){ // 현재 골렘이 바운더리 안에 없음
            return false;
        }else {
        forest[r][c] = golidx;
        for(int i = 0; i < 4; i++){
            forest[r + dr[i]][c + dc[i]] = golidx;
        }

        golidx++;

        exitarray[r + dr[exit]][c + dc[exit]] = 1;

        fx = r;
        fy = c;

        return true;
        }
    }
}

void moveFairy(int x, int y){
    bool visited[71][71];
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            visited[i][j] = false;
        }
    }

    queue<pair<int, int>> q;
    q.push({x, y});
    visited[x][y] = true;
    int value = 0;
    while(!q.empty()){
        int nowx = q.front().first;
        int nowy = q.front().second;
        q.pop();

        value = max(value, nowx);

        for(int i = 0; i < 4; i++){
            int nextx = nowx + dr[i];
            int nexty = nowy + dc[i];

            if(nextx < R && nextx > -1 && nexty < C && nexty > -1 && !visited[nextx][nexty] && forest[nextx][nexty] != 0){
                if(forest[nowx][nowy] != forest[nextx][nexty]){
                    if(exitarray[nowx][nowy] == 1) {
                        visited[nextx][nexty] = true;
                        q.push({nextx, nexty});
                    }
                }else{
                    visited[nextx][nexty] = true;
                    q.push({nextx, nexty});
                }
            }
        }
    }

    answer += value + 1;
}

void clearForest(){
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            forest[i][j] = 0;
            exitarray[i][j] = 0;
        }
    }
}

void printForest(){
    for(int i = 0; i < R; i++){
        for(int j = 0; j < C; j++){
            cout << forest[i][j] << ' ';
        }
        cout << endl;
    }
}

int main(){
    cin >> R >> C >> K;

    for(int i = 0; i < K; i++){
        int c, d; cin >> c >> d;

        if(!moveGolem(-2, c - 1, d)) {
            clearForest();
        }else{
            moveFairy(fx, fy);
        }

        // printForest();
        // cout << answer << endl;
    }

    cout << answer << '\n';
}