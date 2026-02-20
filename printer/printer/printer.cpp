// printer.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
    setlocale(0, "rus");
    HANDLE hMutex = CreateMutex(NULL, FALSE, L"Mutx");
    if (hMutex == NULL)
    {
        cout << "Мьютекс не создан" << endl;
        return GetLastError();
    }

    cout << "Запущен" << endl;
    DWORD start = GetTickCount();
    const DWORD TIME_TEN = 600* 1000;

    while (true)
    {
        if (GetTickCount() - start > TIME_TEN)
        {
            cout << "\n10 минут не было клтентов" << endl;
            break;
        }
        DWORD res = WaitForSingleObject(hMutex, 20);

        if (res == WAIT_OBJECT_0)
        {
            ReleaseMutex(hMutex);
        }
        else if (res == WAIT_TIMEOUT)
        {
            start = GetTickCount(); // Сброс таймера
            WaitForSingleObject(hMutex, INFINITE);
            cout << "Печать" << endl;
            int sec = 5 + rand() % 11;
            cout << "Время печати:" << sec << endl;
            Sleep(sec * 1000);
            if (sec > 10)
                cout << "ошибка печати" << endl;
            else
            cout << "завершена печать" << endl;
            ReleaseMutex(hMutex);
        }
        else
        {
            cout << "Ошибка: " << GetLastError() << endl;
            break;
        }
    }
    CloseHandle(hMutex);
    return 0;
}