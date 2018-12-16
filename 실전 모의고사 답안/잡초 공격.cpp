#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#define MAX 8

using namespace std;

int n, m;
int a[MAX][MAX];
int temp[MAX][MAX];
int result = INT_MAX;

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

void show() {
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			cout << a[i][j] << ' ';
		}
		cout << '\n';
	}
}

int getScore() {
	queue<pair<int, int> > q;
	// 초기 상태의 잡초를 큐에 담습니다.
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(a[i][j] == 2) q.push(make_pair(i, j));
			// 임시 배열을 이용해 상태를 저장합니다. 
			temp[i][j] = a[i][j];
		}
	}
	int day = 0; // 총 지난 날의 개수 
	int round = q.size(); // 하루 하루의 잡초 개수
	while(!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		temp[x][y] = 2;
		if(round-- == 0) {
			day++;
			// 아직 더 번식을 한 게 있는 경우 
			round = q.size();
		}
		for(int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if(nx >= 0 && nx < n && ny >= 0 && ny < m && temp[nx][ny] == 0) {
				temp[nx][ny] = 2;
				q.push(make_pair(nx, ny));
			}
		}
	}
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			// 하나라도 잡초가 없는 공간이 남아있다면 INT_MAX를 반환합니다. 
			if(temp[i][j] == 0) {
				return INT_MAX;
			}
		}
	}
	// 잡초가 모든 영역을 차지한 경우 최소 일자를 출력합니다. 
	return day;
}

// 안 되면 -1

// 조합이므로 순서를 지키면서 DFS()를 수행합니다. 
void dfs(int x, int y, int count) {
	if(count == 4) {
		result = min(result, getScore());
		return;
	}
	// 오른쪽 끝에 닿은 경우 아랫줄로 내려갑니다. 
	if(y == m) {
		dfs(x + 1, 0, count);
		return;
	}
	// 아래쪽 끝에 닿은 경우 함수를 종료합니다. 
	if(x == n) return;
	// 현재 위치에 초기 잡초를 심는 경우 
	if(a[x][y] == 0) {
		a[x][y] = 2;
		dfs(x, y + 1, count + 1);
		a[x][y] = 0;
	}
	dfs(x, y + 1, count);
}

int main(void)
{
	cin >> n >> m;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			cin >> a[i][j];
	dfs(0, 0, 0);
	if(result == INT_MAX) cout << -1;
	else cout << result;
	return 0;
}

