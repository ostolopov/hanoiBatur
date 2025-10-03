#include <iostream>
#include <vector>
#include <string>
#include <chrono>

#include "utils.h"

class Solution {
public:
    void solveHanoi(int disks) {
        n = disks;
        counter = 0;
        std::cout << "Решение для " << n << " дисков:" << std::endl;
        initTowers(disks);
        printTowers();
        func(n, 0, 2, 1);
        std::cout << "Всего ходов: " << counter << std::endl;
    }

    long long countMovesExact(int disks) {
        long long cnt = 0;
        countFunc(disks, 0, 2, 1, cnt);
        return cnt;
    }

private:
    int n;
    long long counter = 0;
    std::string pole1 = "A";
    std::string pole2 = "B";
    std::string pole3 = "C";
    std::vector<std::vector<int>> towers;

    void initTowers(int disks) {
        towers.clear();
        towers.resize(3);
        for (int i = disks; i >= 1; --i)
            towers[0].push_back(i);
    }

    std::string drawDisk(int size, int maxSize) {
        if (size == 0)
            return std::string(maxSize, ' ') + "|" + std::string(maxSize, ' ');
        int width = 2 * size - 1;
        int padding = maxSize - size;
        return std::string(padding, ' ') + std::string(width, '#') + std::string(padding, ' ');
    }

    void printTowers() {
        std::cout << "\nТекущее состояние башен:\n";
        for (int level = n - 1; level >= 0; --level) {
            for (int t = 0; t < 3; ++t) {
                int diskSize = (level < (int)towers[t].size()) ? towers[t][level] : 0;
                std::cout << drawDisk(diskSize, n) << "   ";
            }
            std::cout << "\n";
        }
        std::cout << std::string(n, '=') << "A" << std::string(n, '=') << "   ";
        std::cout << std::string(n, '=') << "B" << std::string(n, '=') << "   ";
        std::cout << std::string(n, '=') << "C" << std::string(n, '=') << "\n\n";
    }

    void moveDisk(int from, int to) {
        int disk = towers[from].back();
        towers[from].pop_back();
        towers[to].push_back(disk);
        counter++;
        std::cout << "Ход " << counter << ": ";
        std::cout << "Переместить диск " << disk << " со стержня "
                  << (from == 0 ? pole1 : from == 1 ? pole2 : pole3)
                  << " на стержень "
                  << (to == 0 ? pole1 : to == 1 ? pole2 : pole3) << std::endl;
        printTowers();
    }

    void func(int n, int from, int to, int aux) {
        if (n <= 0) return;
        if (n == 1) {
            moveDisk(from, to);
        } else {
            func(n - 1, from, aux, to);
            moveDisk(from, to);
            func(n - 1, aux, to, from);
        }
    }

    void countFunc(int n, int from, int to, int aux, long long &cnt) {
        if (n <= 0) return;
        if (n == 1) {
            cnt++;
        } else {
            countFunc(n - 1, from, aux, to, cnt);
            cnt++;
            countFunc(n - 1, aux, to, from, cnt);
        }
    }
};

int main() {
    Solution solv;
    int n;
    std::cout << "Введите количество дисков для решения задачи: " << std::endl;
    getInt(n, 1, INT_MAX);

    //раскоментить если нужна визуализация

    // auto start_vis = std::chrono::high_resolution_clock::now();
    // solv.solveHanoi(n);
    // auto end_vis = std::chrono::high_resolution_clock::now();
    // std::chrono::duration<double> duration_vis =
    //     std::chrono::duration_cast<std::chrono::milliseconds>(end_vis - start_vis);
    // std::cout << "Время выполнения с визуализацией: " << duration_vis.count() << " миллисекунд" << std::endl;

    // без визуализации

    auto start_no_vis = std::chrono::high_resolution_clock::now();
    long long moves = solv.countMovesExact(n);
    auto end_no_vis = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_no_vis =
        std::chrono::duration_cast<std::chrono::milliseconds>(end_no_vis - start_no_vis);
    std::cout << "Подсчет без визуализации: " << moves << " ходов" << std::endl;
    std::cout << "Время выполнения без визуализации: " << duration_no_vis.count() << " миллисекунд" << std::endl;

    return 0;
}

