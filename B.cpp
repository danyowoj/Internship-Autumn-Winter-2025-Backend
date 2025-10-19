#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

struct Cell
{
    int time;
    int x;
    int y;

    bool operator>(const Cell &other) const
    {
        return time > other.time;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> height(n, vector<int>(m));
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));

    // Чтение высот
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cin >> height[i][j];
        }
    }

    priority_queue<Cell, vector<Cell>, greater<Cell>> pq;

    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    // Инициализация: все водные клетки имеют время 0
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (height[i][j] == 0)
            {
                dist[i][j] = 0;
                pq.push({0, i, j});
            }
        }
    }

    // Основной алгоритм - алгоритм Дейкстры
    while (!pq.empty())
    {
        Cell current = pq.top();
        pq.pop();

        int current_time = current.time;
        int x = current.x;
        int y = current.y;

        // Если извлеченное время больше текущего сохраненного, пропускаем
        if (current_time > dist[x][y])
        {
            continue;
        }

        // Проверяем всех соседей
        for (int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            // Проверка границ
            if (nx >= 0 && nx < n && ny >= 0 && ny < m)
            {
                // Время затопления соседа - максимум из текущего времени и высоты соседа
                int new_time = max(current_time, height[nx][ny]);

                // Если нашли лучшее время, обновляем
                if (new_time < dist[nx][ny])
                {
                    dist[nx][ny] = new_time;
                    pq.push({new_time, nx, ny});
                }
            }
        }
    }

    // Вывод результата
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << dist[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
