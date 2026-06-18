/**
 * ParkingLot_Sort.cpp - 停车场排序算法实现
 * 停车场管理系统
 */

#include "ParkingLot.h"
#include <iostream>
#include <algorithm>

using namespace std;

// 功能6：直接插入排序或折半插入排序（按车牌号）
void ParkingLot::insertionSort() {
    if (size <= 1) {
        cout << "车辆数量不足，无需排序。" << endl;
        return;
    }

    cout << "选择排序方式：" << endl;
    cout << "1. 直接插入排序" << endl;
    cout << "2. 折半插入排序" << endl;
    cout << "请选择: ";
    
    int choice;
    cin >> choice;

    if (choice == 1) {
        // 直接插入排序
        for (int i = 1; i < size; i++) {
            Vehicle temp = vehicles[i];
            int j = i - 1;
            while (j >= 0 && vehicles[j].plateNumber > temp.plateNumber) {
                vehicles[j + 1] = vehicles[j];
                j--;
            }
            vehicles[j + 1] = temp;
        }
        cout << "直接插入排序完成！" << endl;
    } else if (choice == 2) {
        // 折半插入排序
        for (int i = 1; i < size; i++) {
            Vehicle temp = vehicles[i];
            int low = 0, high = i - 1;
            
            // 折半查找插入位置
            while (low <= high) {
                int mid = (low + high) / 2;
                if (vehicles[mid].plateNumber > temp.plateNumber) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            }
            
            // 后移元素
            for (int j = i - 1; j >= low; j--) {
                vehicles[j + 1] = vehicles[j];
            }
            vehicles[low] = temp;
        }
        cout << "折半插入排序完成！" << endl;
    } else {
        cout << "无效选择！" << endl;
        return;
    }

    displayAll();
}

// 功能7：快速排序（按车牌号）
void ParkingLot::quickSort() {
    if (size <= 1) {
        cout << "车辆数量不足，无需排序。" << endl;
        return;
    }

    quickSortHelper(0, size - 1);
    cout << "快速排序完成！" << endl;
    displayAll();
}

// 快速排序辅助函数（递归）
void ParkingLot::quickSortHelper(int low, int high) {
    if (low < high) {
        int pivot = partition(low, high);
        quickSortHelper(low, pivot - 1);
        quickSortHelper(pivot + 1, high);
    }
}

// 分区函数
int ParkingLot::partition(int low, int high) {
    Vehicle pivot = vehicles[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (vehicles[j].plateNumber <= pivot.plateNumber) {
            i++;
            swap(vehicles[i], vehicles[j]);
        }
    }
    swap(vehicles[i + 1], vehicles[high]);
    return i + 1;
}
