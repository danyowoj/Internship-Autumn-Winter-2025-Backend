#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <string>

using namespace std;

// Структура для системы непересекающихся множеств (DSU)
class DSU
{
private:
    vector<int> parent;
    vector<int> rank;

public:
    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y)
    {
        x = find(x);
        y = find(y);
        if (x == y)
            return;
        if (rank[x] < rank[y])
        {
            parent[x] = y;
        }
        else if (rank[x] > rank[y])
        {
            parent[y] = x;
        }
        else
        {
            parent[y] = x;
            rank[x]++;
        }
    }
};

int main()
{
    int n;
    cin >> n;

    // Чтение запросов
    vector<set<string>> queries(n);
    for (int i = 0; i < n; i++)
    {
        int mi;
        cin >> mi;
        for (int j = 0; j < mi; j++)
        {
            string word;
            cin >> word;
            queries[i].insert(word);
        }
    }

    // Инициализация DSU
    DSU dsu(n);

    // Создание отображения слово -> индексы запросов
    unordered_map<string, vector<int>> word_map;
    for (int i = 0; i < n; i++)
    {
        for (const string &word : queries[i])
        {
            word_map[word].push_back(i);
        }
    }

    // Объединение запросов, имеющих общие слова
    for (auto &entry : word_map)
    {
        vector<int> &indices = entry.second;
        if (indices.size() > 1)
        {
            int first = indices[0];
            for (size_t k = 1; k < indices.size(); k++)
            {
                dsu.unite(first, indices[k]);
            }
        }
    }

    // Группировка запросов по компонентам связности
    unordered_map<int, set<string>> component_words;
    for (int i = 0; i < n; i++)
    {
        int root = dsu.find(i);
        // Добавляем все слова из запроса i в множество компоненты root
        component_words[root].insert(queries[i].begin(), queries[i].end());
    }

    // Нахождение максимального размера компоненты
    int max_size = 0;
    for (auto &comp : component_words)
    {
        if (comp.second.size() > max_size)
        {
            max_size = comp.second.size();
        }
    }

    // Вывод результата
    cout << component_words.size() << " " << max_size << endl;

    return 0;
}
