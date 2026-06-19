/**
 * main.cpp - 停车场管理系统主程序
 * 基于顺序表实现的车辆信息管理
 * 支持 Windows / Linux / macOS 跨平台编译
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <iomanip>
#include "ParkingLot.h"

using namespace std;

struct AppConfig {
    int capacity;
    double feePerHour;
};

static AppConfig loadConfig() {
    AppConfig cfg;
    cfg.capacity = 100;
    cfg.feePerHour = 5.0;

    const char* envCapacity = getenv("PARKING_CAPACITY");
    if (envCapacity != nullptr) {
        int val = atoi(envCapacity);
        if (val > 0) {
            cfg.capacity = val;
        }
    }

    const char* envFee = getenv("PARKING_FEE_PER_HOUR");
    if (envFee != nullptr) {
        double val = atof(envFee);
        if (val > 0) {
            cfg.feePerHour = val;
        }
    }

    return cfg;
}

// 跨平台清屏
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// 跨平台暂停
void pauseScreen() {
    cout << "\n按回车键继续...";
    cin.ignore();
    cin.get();
}

// 显示菜单
void showMenu() {
    cout << "\n============================================" << endl;
    cout << "          停 车 场 管 理 系 统              " << endl;
    cout << "============================================" << endl;
    cout << "  1. 批量输入车辆信息" << endl;
    cout << "  2. 显示所有车辆信息" << endl;
    cout << "  3. 在指定位置插入车辆" << endl;
    cout << "  4. 删除指定位置的车辆" << endl;
    cout << "  5. 统计车辆数量" << endl;
    cout << "  6. 插入排序（直接/折半）" << endl;
    cout << "  7. 快速排序" << endl;
    cout << "  8. 折半查找（递归）" << endl;
    cout << "  9. 折半查找（非递归）" << endl;
    cout << "  0. 添加测试数据" << endl;
    cout << "  q. 退出系统" << endl;
    cout << "============================================" << endl;
    cout << "请选择操作: ";
}

int main() {
    AppConfig cfg = loadConfig();
    cout << "=== 停车场管理系统 ===" << endl;
    cout << "配置信息：车位容量 " << cfg.capacity << " 个，每小时费率 " << fixed << setprecision(2) << cfg.feePerHour << " 元" << endl;
    cout << "（可通过环境变量 PARKING_CAPACITY 和 PARKING_FEE_PER_HOUR 调整）" << endl;
    cout << endl;

    ParkingLot parkingLot(cfg.capacity, cfg.feePerHour);
    char choice;

    while (true) {
        showMenu();
        cin >> choice;

        switch (choice) {
            case '1':
                parkingLot.inputVehicles();
                break;
            case '2':
                parkingLot.displayAll();
                break;
            case '3':
                parkingLot.insertAt();
                break;
            case '4':
                parkingLot.deleteAt();
                break;
            case '5':
                parkingLot.countVehicles();
                break;
            case '6':
                parkingLot.insertionSort();
                break;
            case '7':
                parkingLot.quickSort();
                break;
            case '8':
                parkingLot.binarySearchRecursive();
                break;
            case '9':
                parkingLot.binarySearchIterative();
                break;
            case '0':
                parkingLot.addTestData();
                break;
            case 'q':
            case 'Q':
                cout << "感谢使用停车场管理系统，再见！" << endl;
                return 0;
            default:
                cout << "无效选择，请重新输入！" << endl;
        }

        pauseScreen();
        clearScreen();
    }

    return 0;
}
