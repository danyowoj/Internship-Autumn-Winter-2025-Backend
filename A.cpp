#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, m; // количество островов и туннелей
    cin >> n >> m;

    vector<int> v(n); // ценность сокровищ
    for (int i = 0; i < n; i++)
        cin >> v[i];

    // матрица смежности графа
    vector<vector<bool>> graph(n, vector<bool>(n, false));
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        // переход к 0-индексации
        a--;
        b--;
        graph[a][b] = true;
        graph[b][a] = true;
    }

    // инициализация DP: dp[mask][last] = максимальная сумма
    vector<vector<int>> dp(1 << n, vector<int>(n, -1));
    dp[1 << 0][0] = v[0]; // начальная позиция на острове 1

    // перебор всех масок
    for (int mask = 0; mask < (1 << n); mask++)
    {
        for (int last = 0; last < n; last++)
        {
            // пропускаем недостижимые состояния
            if (dp[mask][last] == -1)
                continue;

            // пытаемся перейти на следующий остров
            for (int next = 0; next < n; next++)
            {
                // веряем, что остров еще не посещен и есть туннель
                if (!(mask & (1 << next)) && graph[last][next])
                {
                    int new_mask = mask | (1 << next);
                    int new_value = dp[mask][last] + v[next];
                    // обновляем значение, если нашли лучше
                    if (new_value > dp[new_mask][next])
                    {
                        dp[new_mask][next] = new_value;
                    }
                }
            }
        }
    }

    // поиск максимальной суммы среди всех состояний
    int ans = 0;
    for (int mask = 0; mask < (1 << n); mask++)
    {
        for (int i = 0; i < n; i++)
        {
            ans = max(ans, dp[mask][i]);
        }
    }

    cout << ans << endl;

    return 0;
}
