#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main()
{
    int n;
    cin >> n;
    vector<int> h(n);
    for (int i = 0; i < n; i++)
    {
        cin >> h[i];
    }

    // Разделяем платформы на четные и нечетные индексы
    vector<int> even, odd;
    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
            even.push_back(h[i]);
        }
        else
        {
            odd.push_back(h[i]);
        }
    }

    // Функция для поиска следующего большего элемента в массиве
    auto findNextGreater = [](const vector<int> &arr) -> vector<int>
    {
        int m = arr.size();
        vector<int> nextGreater(m, -1);
        stack<int> st; // стек для хранения индексов

        // Проходим справа налево
        for (int i = m - 1; i >= 0; i--)
        {
            // Удаляем из стека все элементы, которые меньше или равны текущему
            while (!st.empty() && arr[st.top()] <= arr[i])
            {
                st.pop();
            }
            // Если стек не пуст, следующий больший элемент найден
            if (!st.empty())
            {
                nextGreater[i] = st.top();
            }
            // Добавляем текущий индекс в стек
            st.push(i);
        }
        return nextGreater;
    };

    // Находим следующие большие элементы для четных и нечетных массивов
    vector<int> nextEven = findNextGreater(even);
    vector<int> nextOdd = findNextGreater(odd);

    // Формируем результат для всех платформ
    vector<int> res(n);
    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
        {
            int k = i / 2; // индекс в массиве even
            if (nextEven[k] != -1)
            {
                res[i] = 2 * (nextEven[k] - k);
            }
            else
            {
                res[i] = -1;
            }
        }
        else
        {
            int k = i / 2; // индекс в массиве odd (для i=1 k=0, i=3 k=1 и т.д.)
            if (nextOdd[k] != -1)
            {
                res[i] = 2 * (nextOdd[k] - k);
            }
            else
            {
                res[i] = -1;
            }
        }
    }

    // Выводим результат
    for (int i = 0; i < n; i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;

    return 0;
}
