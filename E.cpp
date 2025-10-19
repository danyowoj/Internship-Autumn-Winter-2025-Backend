#include <iostream>
#include <vector>
#include <set>
#include <functional>
#include <algorithm>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;

    // Построение графа
    vector<vector<int>> graph(n);
    for (int i = 0; i < k; i++)
    {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    // Поиск мостов с помощью DFS
    set<pair<int, int>> bridges;
    vector<int> tin(n, -1), low(n, -1);
    int timer = 0;

    function<void(int, int)> dfs_bridges = [&](int u, int p)
    {
        tin[u] = low[u] = timer++;
        for (int v : graph[u])
        {
            if (v == p)
                continue;
            if (tin[v] != -1)
            {
                low[u] = min(low[u], tin[v]);
            }
            else
            {
                dfs_bridges(v, u);
                low[u] = min(low[u], low[v]);
                if (low[v] > tin[u])
                {
                    bridges.insert({min(u, v), max(u, v)});
                }
            }
        }
    };

    for (int i = 0; i < n; i++)
    {
        if (tin[i] == -1)
        {
            dfs_bridges(i, -1);
        }
    }

    // Разметка компонент двусвязности
    vector<int> comp_id(n, -1);
    int comp_count = 0;
    function<void(int)> dfs_comp = [&](int u)
    {
        comp_id[u] = comp_count;
        for (int v : graph[u])
        {
            if (comp_id[v] != -1)
                continue;
            if (bridges.find({min(u, v), max(u, v)}) != bridges.end())
                continue;
            dfs_comp(v);
        }
    };

    for (int i = 0; i < n; i++)
    {
        if (comp_id[i] == -1)
        {
            dfs_comp(i);
            comp_count++;
        }
    }

    // Построение дерева мостов
    vector<vector<int>> tree(comp_count);
    for (auto &bridge : bridges)
    {
        int u = bridge.first, v = bridge.second;
        int c1 = comp_id[u], c2 = comp_id[v];
        tree[c1].push_back(c2);
        tree[c2].push_back(c1);
    }

    // Выбор представителей для каждой компоненты
    vector<int> comp_rep(comp_count, -1);
    for (int i = 0; i < n; i++)
    {
        if (comp_rep[comp_id[i]] == -1)
        {
            comp_rep[comp_id[i]] = i;
        }
    }

    // Сбор листьев дерева мостов
    vector<int> leaves;
    for (int i = 0; i < comp_count; i++)
    {
        if (tree[i].size() == 1)
        {
            leaves.push_back(comp_rep[i]);
        }
    }

    // Вывод результата
    int L = leaves.size();
    int m = (L + 1) / 2;
    cout << m << endl;
    for (int i = 0; i < m; i++)
    {
        // Соединяем листья попарно
        cout << leaves[i] + 1 << " " << leaves[i + L / 2] + 1 << endl;
    }

    return 0;
}
