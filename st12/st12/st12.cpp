// st12.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <Windows.h>
#include <iostream>
#include <conio.h>
using namespace std;


int main()
{
    setlocale(0, "rus");
    cout << "\nВыберите приоритет потока: 1,2,3" << endl;
    char choice = _getch();
    int priority;
    switch (choice) {
    case '1':
        priority = THREAD_PRIORITY_IDLE;
        break;
    case '2':
        priority = THREAD_PRIORITY_NORMAL;
        break;
    case '3':priority = THREAD_PRIORITY_HIGHEST;
        break;
    default:
        priority = THREAD_PRIORITY_NORMAL;
        break;
    }
    if (SetThreadPriority(GetCurrentThread(), priority)) {
        cout << "Приоритет установлен-";
        switch (priority) {
        case THREAD_PRIORITY_IDLE:
            cout << "IDLE"; break;
        case THREAD_PRIORITY_NORMAL:
            cout << "NORMAL"; break;
        case THREAD_PRIORITY_HIGHEST:
            cout << "HIGHEST"; break;
        }
    }
	HANDLE hMutex;
	hMutex = OpenMutex(SYNCHRONIZE, FALSE, L"Mutx");
	if (hMutex == NULL)
	{
		cout << "Мьютекс не создан-принтер не запущен" << endl;
		return GetLastError();
	}
    while (true)
    {
        cout << "Чтобы начать печать нажмите любую клавишу- выход 0" << endl;
        char key = _getch();
        if (key == '0') break;
        DWORD res = WaitForSingleObject(hMutex, 1000);

        if (res == WAIT_OBJECT_0)
        {
            cout << "\nОтправлено на печать" << endl;
            Sleep(50);
            ReleaseMutex(hMutex);//передать принтеру
            WaitForSingleObject(hMutex, INFINITE);//ждем когда принтер вернет
            cout <<"Печать завершена" << endl;
            ReleaseMutex(hMutex);//освободить
        }
        else if (res == WAIT_TIMEOUT)
        {
           cout << "Мьютекс занят" << endl;
        }
        else
        {
            cout << "\nПринтер не отвечает" << endl;
        }
    }
    CloseHandle(hMutex);
    return 0;
}