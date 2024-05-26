#include <windows.h>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddControls(HWND);
void displayData(HWND);
void searchData(HWND);
void updateData(HWND);
void deleteData(HWND);

HWND hName, hRollNo, hCourse, hClass, hContact;
HWND hAddButton, hShowButton, hSearchButton, hUpdateButton, hDeleteButton;
HWND hDisplay;

struct Student {
    wstring name;
    wstring rollNo;
    wstring course;
    wstring class_;
    wstring contact;
};

vector<Student> students;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {
    WNDCLASSW wc = {0};
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hInstance = hInst;
    wc.lpszClassName = L"myWindowClass";
    wc.lpfnWndProc = WindowProcedure;

    if (!RegisterClassW(&wc))
        return -1;

    CreateWindowW(L"myWindowClass", L"Student Management System", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 500, 600, NULL, NULL, NULL, NULL);

    MSG msg = {0};

    while (GetMessage(&msg, NULL, NULL, NULL)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_COMMAND:
            switch (wp) {
                case 1:
                    {
                        wchar_t name[30], rollNo[30], course[30], class_[30], contact[30];
                        GetWindowTextW(hName, name, 30);
                        GetWindowTextW(hRollNo, rollNo, 30);
                        GetWindowTextW(hCourse, course, 30);
                        GetWindowTextW(hClass, class_, 30);
                        GetWindowTextW(hContact, contact, 30);

                        Student s = {name, rollNo, course, class_, contact};
                        students.push_back(s);

                        SetWindowTextW(hName, L"");
                        SetWindowTextW(hRollNo, L"");
                        SetWindowTextW(hCourse, L"");
                        SetWindowTextW(hClass, L"");
                        SetWindowTextW(hContact, L"");

                        MessageBoxW(NULL, L"Student added successfully!", L"Info", MB_OK);
                    }
                    break;
                case 2:
                    displayData(hWnd);
                    break;
                case 3:
                    searchData(hWnd);
                    break;
                case 4:
                    updateData(hWnd);
                    break;
                case 5:
                    deleteData(hWnd);
                    break;
            }
            break;
        case WM_CREATE:
            AddControls(hWnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProcW(hWnd, msg, wp, lp);
    }
}

void AddControls(HWND hWnd) {
    CreateWindowW(L"static", L"Name:", WS_VISIBLE | WS_CHILD, 50, 50, 100, 40, hWnd, NULL, NULL, NULL);
    hName = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 50, 200, 40, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"static", L"Roll No:", WS_VISIBLE | WS_CHILD, 50, 100, 100, 40, hWnd, NULL, NULL, NULL);
    hRollNo = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 100, 200, 40, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"static", L"Course:", WS_VISIBLE | WS_CHILD, 50, 150, 100, 40, hWnd, NULL, NULL, NULL);
    hCourse = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 150, 200, 40, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"static", L"Class:", WS_VISIBLE | WS_CHILD, 50, 200, 100, 40, hWnd, NULL, NULL, NULL);
    hClass = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 200, 200, 40, hWnd, NULL, NULL, NULL);

    CreateWindowW(L"static", L"Contact:", WS_VISIBLE | WS_CHILD, 50, 250, 100, 40, hWnd, NULL, NULL, NULL);
    hContact = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 150, 250, 200, 40, hWnd, NULL, NULL, NULL);

    hAddButton = CreateWindowW(L"button", L"Add Student", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 300, 100, 50, hWnd, (HMENU)1, NULL, NULL);
    hShowButton = CreateWindowW(L"button", L"Show Students", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 300, 100, 50, hWnd, (HMENU)2, NULL, NULL);
    hSearchButton = CreateWindowW(L"button", L"Search Student", WS_VISIBLE | WS_CHILD | WS_BORDER, 50, 360, 100, 50, hWnd, (HMENU)3, NULL, NULL);
    hUpdateButton = CreateWindowW(L"button", L"Update Student", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 360, 100, 50, hWnd, (HMENU)4, NULL, NULL);
    hDeleteButton = CreateWindowW(L"button", L"Delete Student", WS_VISIBLE | WS_CHILD | WS_BORDER, 125, 420, 100, 50, hWnd, (HMENU)5, NULL, NULL);

    hDisplay = CreateWindowW(L"edit", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 50, 480, 350, 50, hWnd, NULL, NULL, NULL);
}

void displayData(HWND hWnd) {
    wstringstream ss;
    for (size_t i = 0; i < students.size(); ++i) {
        ss << L"Student " << i + 1 << L"\n";
        ss << L"Name: " << students[i].name << L"\n";
        ss << L"Roll No: " << students[i].rollNo << L"\n";
        ss << L"Course: " << students[i].course << L"\n";
        ss << L"Class: " << students[i].class_ << L"\n";
        ss << L"Contact: " << students[i].contact << L"\n\n";
    }
    wstring data = ss.str();
    SetWindowTextW(hDisplay, data.c_str());
}

void searchData(HWND hWnd) {
    wchar_t rollNo[30];
    GetWindowTextW(hRollNo, rollNo, 30);
    for (const auto &student : students) {
        if (student.rollNo == rollNo) {
            wstringstream ss;
            ss << L"Name: " << student.name << L"\n";
            ss << L"Roll No: " << student.rollNo << L"\n";
            ss << L"Course: " << student.course << L"\n";
            ss << L"Class: " << student.class_ << L"\n";
            ss << L"Contact: " << student.contact;
            wstring data = ss.str();
            SetWindowTextW(hDisplay, data.c_str());
            return;
        }
    }
    MessageBoxW(NULL, L"Student not found", L"Error", MB_OK);
}

void updateData(HWND hWnd) {
    wchar_t rollNo[30];
    GetWindowTextW(hRollNo, rollNo, 30);

    for (auto &student : students) {
        if (student.rollNo == rollNo) {
            wchar_t name[30], course[30], class_[30], contact[30];

            GetWindowTextW(hName, name, 30);
            GetWindowTextW(hCourse, course, 30);
            GetWindowTextW(hClass, class_, 30);
            GetWindowTextW(hContact, contact, 30);

            student.name = name;
            student.course = course;
            student.class_ = class_;
            student.contact = contact;

            MessageBoxW(NULL, L"Student updated successfully!", L"Info", MB_OK);
            return;
        }
    }

    MessageBoxW(NULL, L"Student not found", L"Error", MB_OK);
}

void deleteData(HWND hWnd) {
    wchar_t rollNo[30];
    GetWindowTextW(hRollNo, rollNo, 30);

    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->rollNo == rollNo) {
            students.erase(it);
            MessageBoxW(NULL, L"Student deleted successfully!", L"Info", MB_OK);
            return;
        }
    }

    MessageBoxW(NULL, L"Student not found", L"Error", MB_OK);
}
