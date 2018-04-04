#include <iostream>
#include <vector>
#include <utility>
#include <queue>
using namespace std;

vector<vector<int>> picture{{1,1,1,0},{1,2,2,0},{1,0,0,1},{0,0,0,1},{0,0,0,3},{0,0,0,3}};

vector<int> solution(int m, int n, vector<vector<int>> picture) {
    for (int i = 0;i < m; ++i) {
        for (int j = 0;j < n; ++j) {
            picture[i][j] = -picture[i][j]; // picture의 색깔을 나타내는 숫자를 모두 음수로
        }
    }
    //색칠되어 있는 비트의 갯수
    int cnt = 0;
    
    //오른쪽, 왼쪽, 위, 아래 탐색을 위한 x좌표배열,y좌표배열
    int dx[] = {0,0,1,-1};
    int dy[] = {1,-1,0,0};
    
    for(int i = 0;i < m; ++i) {
        for(int j = 0;j < n; ++j) {
            if (picture[i][j] < 0) {
                cnt++; // 색칠되어 있는 비트 카운트
                int num = picture[i][j]; // 좌표의 색깔정보 저장.
                
                queue<pair<int, int>> q; //
                q.push(make_pair(i, j)); // 색칠되어 있는 영역의 x,y좌표를 pair로 만들어서 queue에 삽입
                while(!q.empty()) { // queue가 비어있지 않으면
                    
                    //queue의 맨앞에 있는 pair에 저장된 x,y좌표 가져오고 큐에서 pop
                    int cx = q.front().first;
                    int cy = q.front().second;
                    q.pop();
                    
                    for(int k = 0; k < 4; ++k) {
                        //받아온 x,y좌표를 기준으로 오른쪽,왼쪽,위,아래 차례로 탐색
                        int nx = cx + dx[k];
                        int ny = cy + dy[k];
                    
                        if (nx >= 0 && nx < m && ny >= 0 && ny < n && picture[nx][ny] == num) { // 그림의 범위를 벗어나지 않고, 상하좌우의 비트가 기준좌표의 비트색깔과 같으면
                            picture[nx][ny] = cnt;  // cnt를 숫자정보로 저장
                            q.push(make_pair(nx, ny)); // 상하좌우의 비트를 pair로 만들어 queue에 푸쉬, while의 조건에 의해 반복
                        }
                    }
                }
            }
        }
    }
    int cnt_chk[10001] = {0};
    for(int i = 0; i < m; ++i) {
        for(int j = 0; j < n; ++j) {
            cnt_chk[picture[i][j]]++; // 영역의 넓이를 카운트.
        }
    }
    int ans=0;
    for (int i = 1; i < 10001; ++i) {
        ans = max(cnt_chk[i],ans); // 영역의 넓이를 비교하여 가장 넓은 영역의 크기 구하기
    }
    
    return vector<int>{cnt,ans};
}

int main(int argc, const char * argv[]) {
    vector<int> arrr = solution(6, 4, picture);
    cout << arrr[0] << "\n" << arrr[1] << "\n";
    return 0;
}
