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
	// �ʱ� ������ ���ʸ� ť�� ����ϴ�.
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(a[i][j] == 2) q.push(make_pair(i, j));
			// �ӽ� �迭�� �̿��� ���¸� �����մϴ�. 
			temp[i][j] = a[i][j];
		}
	}
	int day = 0; // �� ���� ���� ���� 
	int round = q.size(); // �Ϸ� �Ϸ��� ���� ����
	while(!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();
		temp[x][y] = 2;
		if(round-- == 0) {
			day++;
			// ���� �� ������ �� �� �ִ� ��� 
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
			// �ϳ��� ���ʰ� ���� ������ �����ִٸ� INT_MAX�� ��ȯ�մϴ�. 
			if(temp[i][j] == 0) {
				return INT_MAX;
			}
		}
	}
	// ���ʰ� ��� ������ ������ ��� �ּ� ���ڸ� ����մϴ�. 
	return day;
}

// �� �Ǹ� -1

// �����̹Ƿ� ������ ��Ű�鼭 DFS()�� �����մϴ�. 
void dfs(int x, int y, int count) {
	if(count == 4) {
		result = min(result, getScore());
		return;
	}
	// ������ ���� ���� ��� �Ʒ��ٷ� �������ϴ�. 
	if(y == m) {
		dfs(x + 1, 0, count);
		return;
	}
	// �Ʒ��� ���� ���� ��� �Լ��� �����մϴ�. 
	if(x == n) return;
	// ���� ��ġ�� �ʱ� ���ʸ� �ɴ� ��� 
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

