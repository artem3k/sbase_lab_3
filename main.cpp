#include <deque>
#include <iostream>
#include <string>
#include <random>
#include <list>
#include <chrono>

using namespace std;

void setupLang(){
    //Русификация
#ifdef _WIN32
    system("CHCP 65001"); // UTF-8
#else
    setlocale(LC_ALL,"RUS");
#endif
}

void setStart(int* N,int* M,int* K,int* L,int* S){
    cout << "Введите сколько СИДЕЛО СЕРЫХ мышей (N) -> " << endl;
    cin >> *N;
    cout << "Введите сколько СИДЕЛО БЕЛЫХ мышей (M) -> " << endl;
    cin >> *M;
    cout << "Какую S-мышку есть кот? -> " << std::endl;
    cin >> *S;
    cout << "Введите сколько ОСТАЛОС CЕРЫХ мышей (K) -> " << endl;
    cin >> *K;
    cout << "Введите сколько ОСТАЛОСЬ БЕЛЫХ мышей (L) -> " << endl;
    cin >> *L;
}

void validation(int N,int M,int K,int L,int S){
    if(N + M < K + L || N < K || M < L || S <= 0){
        cout << "Неверные входные данные, решения нет!" << std::endl;
        exit(0);
    }
    cout << "Предполагается что при N = " << N << " M = " << M << " S = " << S << " K = " << K << " L = " << L << " есть решение." <<std::endl;
}

void alg_array(int N, int M, int K, int L, int S) {
    vector<string> mice;
    random_device rd;
    default_random_engine generator(rd());
    uniform_int_distribution<int> distribution(0, 1);

    // Инициализация массива мышей
    for (int i = 0; i < N; i++) {
        if (K > 0 && (distribution(generator) == 0 || i >= K))
            mice.insert(mice.begin(), "G");
        else {
            mice.push_back("G");
            K--;
        }
    }
    for (int i = 0; i < M; i++) {
        if (L > 0 && (distribution(generator) == 0 || i >= L))
            mice.insert(mice.begin(), "W");
        else {
            mice.push_back("W");
            L--;
        }
    }

    // Перемешиваем S-мышку
    for (int i = 0; i < S; i++) {
        int randomIndex = distribution(generator) % (N + M - i);
        swap(mice[randomIndex], mice[N + M - i - 1]);
    }

    for (const auto& mouse : mice) {
        cout << mouse << ' ';
    }
    cout << '\n';
}

void alg_list(int N, int M, int K, int L, int S) {
    list<string> mice;
    random_device rd;
    default_random_engine generator(rd());
    uniform_int_distribution<int> distribution(0, 1);

    // Инициализация списка мышей
    for (int i = 0; i < N; i++) {
        if (distribution(generator) == 0 || K == 0)
            mice.push_front("G");
        else {
            mice.push_back("G");
            K--;
        }
    }
    for (int i = 0; i < M; i++) {
        if (distribution(generator) == 0 || L == 0)
            mice.push_front("W");
        else {
            mice.push_back("W");
            L--;
        }
    }

    // Перемешиваем S-мышку
    auto it = mice.begin();
    for (int i = 0; i < S; i++) {
        advance(it, distribution(generator) % (N + M - i));
        if (it == mice.end()) it = mice.begin();
        string mouse = *it;
        mice.erase(it);
        mice.push_back(mouse);
        it = mice.begin();
    }

    for (const auto& mouse : mice) {
        cout << mouse << ' ';
    }
    cout << '\n';
}



void algSTL(int N, int M, int K, int L, int S) {
    deque<string> mice;
    random_device rd;
    default_random_engine generator(rd());
    uniform_int_distribution<int> distribution(0, 1);

    // Случайно вставляем мышей
    for (int i = 0; i < N; i++) {
        if (distribution(generator) == 0 || K == 0)
            mice.push_front("G");
        else {
            mice.push_back("G");
            K--;
        }
    }
    for (int i = 0; i < M; i++) {
        if (distribution(generator) == 0 || L == 0)
            mice.push_front("W");
        else {
            mice.push_back("W");
            L--;
        }
    }

    // Перемешиваем S-мышку
    for (int i = 0; i < S; i++) {
        int randomIndex = distribution(generator) % (N + M - i);
        swap(mice[randomIndex], mice[N + M - i - 1]);
    }

    for (const auto& mouse : mice) {
        cout << mouse << ' ';
    }
    cout << '\n';
}

int main() {
    setupLang();
    std::cout << "Лабораторная работа номер №3 Круглый Артём Васильевич ФИТУ АИСа-о22" << std::endl;

    int N; //Было серых
    int M; //Было белых
    int K; //Осталось серых
    int L; //Осталось Белых
    int S; //Кушает каждую

    setStart(&N,&M,&K,&L,&S);

    auto start = chrono::high_resolution_clock::now();
    alg_array(N, M, K, L, S);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Время выполнения для ArrayQueue: " << duration << " мс" << endl;

    start = chrono::high_resolution_clock::now();
    alg_list(N, M, K, L, S);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Время выполнения для LinkedListQueue: " << duration << " мс" << endl;

    start = chrono::high_resolution_clock::now();
    algSTL(N, M, K, L, S);
    end = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
    cout << "Время выполнения для STL Queue: " << duration << " мс" << endl;

    return 0;
}

