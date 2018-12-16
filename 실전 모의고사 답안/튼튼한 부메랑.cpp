#include <iostream>
#include <algorithm>
#define MAX 11

using namespace std;

int n, m;
int a[MAX][MAX];
int v[MAX][MAX]; // Ư�� ��ġ���� �̹� �θ޶��� ������������� ����ϴ�. 

int dfs(int x, int y)
{
	// �Ʒ� ������ ���� �� ��� 0�� ��ȯ 
	if(x == n) return 0;
	// ������ ������ �̵��� ��� �Ʒ��� �� ĭ �������ϴ�. 
	if(y == m) return dfs(x + 1, 0); 
	int result = 0;
	// ��� 1 
	if(x + 1 < n && y + 1 < m && v[x][y] + v[x][y + 1] + v[x + 1][y] == 0)
	{
		v[x][y] = v[x][y + 1] = v[x + 1][y] = 1;
		result = max(result, dfs(x, y + 1) + (a[x][y] * 2 + a[x][y + 1] + a[x + 1][y]));
		v[x][y] = v[x][y + 1] = v[x + 1][y] = 0;
	}
	// ��� 2 
	if(x + 1 < n && y + 1 < m && v[x][y] + v[x + 1][y] + v[x + 1][y + 1] == 0)
	{
		v[x][y] = v[x + 1][y] = v[x + 1][y + 1] = 1;
		result = max(result, dfs(x, y + 1) + (a[x + 1][y] * 2 + a[x][y] + a[x + 1][y + 1]));
		v[x][y] = v[x + 1][y] = v[x + 1][y + 1] = 0; 
	}
	// ��� 3 
	if(x + 1 < n && y + 1 < m && v[x][y] + v[x][y + 1] + v[x + 1][y + 1] == 0)
	{ 
		v[x][y] = v[x][y + 1] = v[x + 1][y + 1] = 1;
		result = max(result, dfs(x, y + 1) + (a[x][y + 1] * 2 + a[x][y] + a[x + 1][y + 1]));
		v[x][y] = v[x][y + 1] = v[x + 1][y + 1] = 0; 
	}
	// ��� 4 
	if(x + 1 < n && y + 1 < m && v[x + 1][y] + v[x][y + 1] + v[x + 1][y + 1] == 0)
	{
		v[x + 1][y] = v[x][y + 1] = v[x + 1][y + 1] = 1; 
		result = max(result, dfs(x, y + 1) + (a[x + 1][y + 1] * 2 + a[x + 1][y] + a[x][y + 1]));
		v[x + 1][y] = v[x][y + 1] = v[x + 1][y + 1] = 0; 
	}
	// ���� ��ġ���� �θ޶��� �������� �ʴ� ��� 
	result = max(result, dfs(x, y + 1));
	return result;
	
}
// ��������� �� �Լ��� �����Ͽ� ����� ����� �� 6������ ����� ���� �ݺ������� �����Ͽ� ���� �� �� ����

int main(void)
{
	cin >> n >> m;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			cin >> a[i][j];
	cout << dfs(0, 0);
	return 0;
}

