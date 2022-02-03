// PINGPONG.cpp : Определяет точку входа для приложения.
//

#include "framework.h"
#include "PINGPONG.h"
#include "pong.h"
#include <thread>
#include <mutex>
#define MAX_LOADSTRING 100
#define THREADS_NUMBER 2
// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING] = L"PING-PONG";                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING] = L"PING-PONG";            // имя класса главного окна

Pong* pong;
Gamer* gamer1 = new Gamer();
Gamer* gamer2 = new Gamer();


TCHAR* pStr = (TCHAR*)L"Работал поток 1";
TCHAR* pStr2 = (TCHAR*)L"Работал поток 2";

LPDWORD threadId11;
LPDWORD threadId12;
string threadId1;
string threadId2;

HANDLE hThread1;
HANDLE hThread2;
// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


DWORD WINAPI ThreadFunc1(CONST LPVOID lpParam)
{

    switch ((WPARAM)lpParam) {
    case 0x57: {  /* Обрабатывает клавишу Shift - левый. */
        if (gamer1[0].getposY() > 0)
            gamer1[0].setposY(gamer1[0].getposY() - 10);
        //pStr = (TCHAR*)lpParam;
        break;
    }
    case 0x53: {/* Обрабатывает клавишу Ctrl - левый. */
        if (gamer1[0].getposY() > 0)
            gamer1[0].setposY(gamer1[0].getposY() + 10);
        //pStr = (TCHAR*)lpParam;
        break;
    }
    case VK_SPACE: {
    
        if (pong[0].getBolPosX() == 712
            && pong[0].getBolPosY() == 350) {
            if (rand() % 10 < 5)
                pong[0].setDirectX(-5);
            else
                pong[0].setDirectX(5);

            if (rand() & 10 < 5)
                pong[0].setDirectY(-5);
            else
                pong[0].setDirectY(5);
        } 
        break;
    }
    default:
        break; /* Обрабатывает другие не символьные нажатия клавиш.*/
    }
    ExitThread(0);

}
DWORD WINAPI ThreadFunc2(CONST LPVOID lpParam)
{
    switch ((WPARAM)lpParam) {
    case VK_UP: {/* Обрабатывает клавишу UP ARROW (Стрелка вверх). */
        if (gamer2[0].getposY() > 0)
            gamer2[0].setposY(gamer2[0].getposY() - 10);
        //pStr2 = (TCHAR*)wParam;
        break;
    }
    case VK_DOWN: {/* Обрабатывает клавишу DOWN ARROW (Стрелка вниз). */
        if (gamer2[0].getposY() > 0)
            gamer2[0].setposY(gamer2[0].getposY() + 10);
        //pStr2 = (TCHAR*)wParam;
        break;
    }
    case VK_SPACE: {
        if (pong[0].getBolPosX() == 712
            && pong[0].getBolPosY() == 350) {
            if (rand() % 10 < 5)
                pong[0].setDirectX(-5);
            else
                pong[0].setDirectX(5);

            if (rand() & 10 < 5)
                pong[0].setDirectY(-5);
            else
                pong[0].setDirectY(5);
        }
        break;
    }
    default:
        break; /* Обрабатывает другие не символьные нажатия клавиш.*/
    }
    
    ExitThread(0);
}



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    
    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PINGPONG, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PINGPONG));

    MSG msg;
    
    // Цикл основного сообщения:
    
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            if (msg.message != 273) {
               
                pong->setTime(GetTickCount64());
                while (GetTickCount64() - pong->getTime() < 5);
                pong->moverBol(gamer1, gamer2);
                
                
            }
        }
        
    }
    
    return (int) msg.wParam;
}



ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PINGPONG));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_PINGPONG);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_CREATE:
    {
        pong = new Pong(hWnd);
        pong[0].setup(gamer1, gamer2, hWnd);
        HMENU MainMenu = CreateMenu();
        HMENU PopupMenu = CreatePopupMenu();
    
        AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)PopupMenu, L"&Файл");
        {
            AppendMenu(PopupMenu, MF_STRING, IDM_EXIT, L"Выход");
        }
        AppendMenu(MainMenu, MF_STRING, IDM_ABOUT, L"&О программе");
        SetMenu(hWnd, MainMenu);
        SetFocus(hWnd);
       
       
    }break;
    case WM_KEYDOWN: {
        //thread th(MyThread11, wParam);
       // thread th2(MyThread12, wParam);
        hThread1 = CreateThread(
            NULL,         // атрибуты безопасности по умолчанию
            0,            // размер стека используется по умолчанию
            &ThreadFunc1,   // функция потока
            (LPVOID)wParam, // аргумент функции потока
            0,            // флажки создания используются по умолчанию
            threadId11); // возвращает идентификатор потока
        hThread2 = CreateThread(
            NULL,         // атрибуты безопасности по умолчанию
            0,            // размер стека используется по умолчанию
            &ThreadFunc2,   // функция потока
            (LPVOID)wParam, // аргумент функции потока
            0,            // флажки создания используются по умолчанию
            threadId12); // возвращает идентификатор потока
        if (hThread1 == NULL)
        {
            pStr = (TCHAR*)L"Error creating Thread1";
            break;
        }
        if (hThread2 == NULL)
        {
            pStr2 = (TCHAR*)L"Error creating Thread2";
            break;
        }
        DWORD exitCode1;
        DWORD exitCode2;
        if (GetExitCodeThread(hThread1, &exitCode1) != 0)
        {
            //ExitThread(exitCode1);
            pStr = (TCHAR*)L"Thread1 closed";

            if (CloseHandle(hThread1))
            {
                pStr = (TCHAR*)L"Handle closed 1";
            }
        }
        if (GetExitCodeThread(hThread2, &exitCode2) != 0)
        {
            //ExitThread(exitCode2);
            pStr2 = (TCHAR*)L"Thread2 closed";

            if (CloseHandle(hThread2))
            {
                pStr2 = (TCHAR*)L"Handle closed 2";
            }
        }
        break;
    }
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        RECT rect;
        GetClientRect(hWnd, &rect);
        
        

        SelectObject(hdc, pong[0].getRed()); // отрисовка разделительной линии
        MoveToEx(hdc, rect.right / 2, 0, NULL);
        LineTo(hdc, rect.right/ 2, rect.bottom);

        SelectObject(hdc, pong[0].getBlack()); 
        SelectObject(hdc, pong[0].getWhite());
        Ellipse(hdc, pong[0].getBolPosX() - 9, pong[0].getBolPosY() - 9,
            pong[0].getBolPosX() + 9, pong[0].getBolPosY() + 9);

        SelectObject(hdc, pong[0].getHBlack());
        SelectObject(hdc, pong[0].getBlack());
        Rectangle(hdc, gamer1[0].getposX() - 5, gamer1[0].getposY() - 30,
            gamer1[0].getposX() + 5, gamer1[0].getposY() + 30);

        SelectObject(hdc, pong[0].getHBlack());
        SelectObject(hdc, pong[0].getBlack());
        Rectangle(hdc, gamer2[0].getposX() - 5, gamer2[0].getposY() - 30,
            gamer2[0].getposX() + 5, gamer2[0].getposY() + 30);

        SetBkMode(hdc, TRANSPARENT);
        SelectObject(hdc, pong[0].getScoreFont());

        TextOutW(hdc, rect.right / 2 - 50, 10, LPCWSTR(gamer1->getScoreString().c_str()), gamer1->getScoreString().length());
        TextOut(hdc, 0, 0, pStr, _tcslen(pStr));
        TextOut(hdc, 0, 20, pStr2, _tcslen(pStr2));
        TextOut(hdc, 200, 0, (LPCWSTR)threadId11, char32_t(threadId11));
        TextOut(hdc, 200, 20, (LPCWSTR)threadId12, char32_t(threadId12));
        TextOutW(hdc, rect.right / 2 + 50, 10, LPCWSTR(gamer2->getScoreString().c_str()), gamer2->getScoreString().length());
        InvalidateRect(hWnd, NULL, true);
        EndPaint(hWnd, &ps);
        
    }break;
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Разобрать выбор в меню:
        switch (wmId)
        {
        case IDM_EXIT: {
            
            delete[] gamer1;
            delete[] gamer2;
            delete pong;
            DestroyWindow(hWnd);
            break;
        }
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }break;

    default:
        
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    
    return 0;
}


 