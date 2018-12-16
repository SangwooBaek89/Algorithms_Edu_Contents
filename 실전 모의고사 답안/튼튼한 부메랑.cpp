#include <iostream>
#include <algorithm>
#define MAX 11

using namespace std;

int n, m;
int a[MAX][MAX];
int v[MAX][MAX]; // 특정 위치에서 이미 부메랑이 만들어졌는지를 담습니다. 

int dfs(int x, int y)
{
	// 아래 끝까지 내려 온 경우 0을 반환 
	if(x == n) return 0;
	// 오른쪽 끝까지 이동한 경우 아래로 한 칸 내려갑니다. 
	if(y == m) return dfs(x + 1, 0); 
	int result = 0;
	// 모양 1 
	if(x + 1 < n && y + 1 < m && v[x][y] + v[x][y + 1] + v[x + 1][y] == 0)
	{
		v[x][y] = v[x][y + 1] = v[x + 1][y] = 1;
		result = max(result, dfs(x, y + 1) + (a[x][y] * 2 + a[x][y + 1] + a[x + 1][y]));
		v[x][y] = v[x][y + 1] = v[x + 1][y] = 0;
	}
	// 모양 2 
	if(x + 1 < n && y + 1 < m && v[x][y] + v[x + 1][y] + v[x + 1][y + 1] == 0)
	{
		v[x][y] = v[x + 1][y] = v[x + 1][y + 1] = 1;
		result = max(result, dfs(x, y + 1) + (a[x + 1][y] * 2 + a[x][y] + a[x + 1][y + 1]));
		v[x][y] = v[x + 1][y] = v[x + 1][y + 1] = 0; 
	}
	// 모양 3 
	if(x + 1 < n && y + 1 < m && v[x][y] + v[x][y + 1] + v[x + 1][y + 1] == 0)
	{ 
		v[x][y] = v[x][y + 1] = v[x + 1][y + 1] = 1;
		result = max(result, dfs(x, y + 1) + (a[x][y + 1] * 2 + a[x][y] + a[x + 1][y + 1]));
		v[x][y] = v[x][y + 1] = v[x + 1][y + 1] = 0; 
	}
	// 모양 4 
	if(x + 1 < n && y + 1 < m && v[x + 1][y] + v[x][y + 1] + v[x + 1][y + 1] == 0)
	{
		v[x + 1][y] = v[x][y + 1] = v[x + 1][y + 1] = 1; 
		result = max(result, dfs(x, y + 1) + (a[x + 1][y + 1] * 2 + a[x + 1][y] + a[x][y + 1]));
		v[x + 1][y] = v[x][y + 1] = v[x + 1][y + 1] = 0; 
	}
	// 현재 위치에서 부메랑을 선택하지 않는 경우 
	result = max(result, dfs(x, y + 1));
	return result;
	
}
// 결과적으로 위 함수를 실행하여 ①부터 ⑥까지 총 6가지의 경우의 수를 반복적으로 실행하여 답을 얻어낼 수 있음

int main(void)
{
	cin >> n >> m;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			cin >> a[i][j];
	cout << dfs(0, 0);
	return 0;
}

