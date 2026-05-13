#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <future>

using namespace std;

void sortPart(vector<double>& arr, int start, int end, string name) {
    for (int i = start; i < end - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < end; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }

    for (int i = start; i < end; i++) {
        cout << name << " " << arr[i] << endl;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

int main() {
    setlocale(0, "");

    const int size = 10;
    vector<double> arr(size);

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(1.0, 100.0);

    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }

    cout << "Исходный массив: ";
    for (double x : arr) cout << x << " ";
    cout << endl << endl;

    int half = size / 2;

    auto f1 = async(launch::async, sortPart, ref(arr), 0, half, "thread1");
    auto f2 = async(launch::async, sortPart, ref(arr), half, size, "thread2");

    f1.wait();
    f2.wait();

    auto f3 = async(launch::async, sortPart, ref(arr), 0, size, "thread3");
    f3.wait();

    cout << endl << "Главный поток: все потоки завершили работу" << endl;

    return 0;
}