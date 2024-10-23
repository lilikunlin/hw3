#include <iostream>
#include <list>
#include <forward_list>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>

using namespace std;

// 定義圖書結構
struct Book {
    string title;  // 書名
    string author; // 作者
    string id;     // 圖書編號
};

// 定義借閱者結構
struct Borrower {
    string name;                // 借閱者姓名
    vector<string> borrowedBooks; // 借閱的圖書編號列表
};

// 使用雙向鏈結串列管理圖書
list<Book> books;

// 使用單向鏈結串列管理借閱者
forward_list<Borrower> borrowers;

// 檢查圖書編號是否符合格式要求
bool isValidBookId(const string& id) {
    regex pattern("^[A-Z][0-9]{4}$"); // 圖書編號格式：首字母+4位數字
    return regex_match(id, pattern);
}

// 添加新圖書
void addBook() {
    Book book;
    cout << "輸入書名: ";
    cin >> book.title;
    cout << "輸入作者: ";
    cin >> book.author;
    do {
        cout << "輸入圖書編號: ";
        cin >> book.id;
        if (!isValidBookId(book.id)) {
            cout << "圖書編號格式錯誤，請重新輸入。" << endl;
        }
    } while (!isValidBookId(book.id)); // 直到輸入有效的圖書編號
    books.push_back(book); // 添加到圖書列表
}

// 刪除指定圖書編號的圖書
void deleteBook() {
    string id;
    cout << "輸入要刪除的圖書編號: ";
    cin >> id;
    books.remove_if([&id](const Book& book) { return book.id == id; }); // 刪除符合條件的圖書
}

// 搜索指定圖書編號的圖書
void searchBook() {
    string id;
    cout << "輸入要搜索的圖書編號: ";
    cin >> id;
    for (const auto& book : books) {
        if (book.id == id) {
            cout << "書名: " << book.title << ", 作者: " << book.author << ", 圖書編號: " << book.id << endl;
            return;
        }
    }
    cout << "未找到圖書。" << endl;
}

// 依照圖書編號排序列出所有圖書
void listBooks() {
    books.sort([](const Book& a, const Book& b) { return a.id < b.id; }); // 按圖書編號排序
    for (const auto& book : books) {
        cout << "書名: " << book.title << ", 作者: " << book.author << ", 圖書編號: " << book.id << endl;
    }
}

// 添加新借閱者
void addBorrower() {
    Borrower borrower;
    cout << "輸入借閱者姓名: ";
    cin >> borrower.name;
    int numBooks;
    cout << "輸入借閱的圖書數量: ";
    cin >> numBooks;
    for (int i = 0; i < numBooks; ++i) {
        string bookId;
        cout << "輸入借閱的圖書編號: ";
        cin >> bookId;
        borrower.borrowedBooks.push_back(bookId); // 添加借閱的圖書編號
    }
    borrowers.push_front(borrower); // 添加到借閱者列表
}

// 刪除指定姓名的借閱者
void deleteBorrower() {
    string name;
    cout << "輸入要刪除的借閱者姓名: ";
    cin >> name;
    borrowers.remove_if([&name](const Borrower& borrower) { return borrower.name == name; }); // 刪除符合條件的借閱者
}

// 搜索指定姓名的借閱者
void searchBorrower() {
    string name;
    cout << "輸入要搜索的借閱者姓名: ";
    cin >> name;
    for (const auto& borrower : borrowers) {
        if (borrower.name == name) {
            cout << "姓名: " << borrower.name << ", 借閱的圖書編號: ";
            for (const auto& bookId : borrower.borrowedBooks) {
                cout << bookId << " ";
            }
            cout << endl;
            return;
        }
    }
    cout << "未找到借閱者。" << endl;
}

// 列出所有借閱者及其借閱的圖書
void listBorrowers() {
    for (const auto& borrower : borrowers) {
        cout << "姓名: " << borrower.name << ", 借閱的圖書編號: ";
        for (const auto& bookId : borrower.borrowedBooks) {
            cout << bookId << " ";
        }
        cout << endl;
    }
}

int main() {
    // 測試資料
    books = {
        {"紅樓夢", "曹雪芹", "A1234"},
        {"西遊記", "吳承恩", "B2345"},
        {"水滸傳", "施耐庵", "B3456"},
        {"三國演義", "羅貫中", "C4567"},
        {"金瓶梅", "蘭陵笑笑生", "C5678"},
        {"聊齋志異", "蒲松齡", "D6789"},
        {"儒林外史", "吳敬梓", "D7890"},
        {"封神演義", "許仲琳", "E8901"},
        {"鏡花緣", "李汝珍", "E9012"},
        {"老殘遊記", "劉鶚", "F0123"}
    };

    borrowers = {
        {"小明", {"A1234", "B2345"}},
        {"小華", {"C4567"}},
        {"小美", {"D6789", "E8901"}},
        {"小強", {"F0123"}},
        {"小麗", {"B3456", "C5678"}}
    };

    int choice;
    do {
        // 顯示選單
        cout << "1. 添加新圖書\n2. 刪除圖書\n3. 搜索圖書\n4. 列出所有圖書\n";
        cout << "5. 添加新借閱者\n6. 刪除借閱者\n7. 搜索借閱者\n8. 列出所有借閱者\n9. 退出\n";
        cout << "選擇操作: ";
        cin >> choice;
        switch (choice) {
            case 1: addBook(); break;
            case 2: deleteBook(); break;
            case 3: searchBook(); break;
            case 4: listBooks(); break;
            case 5: addBorrower(); break;
            case 6: deleteBorrower(); break;
            case 7: searchBorrower(); break;
            case 8: listBorrowers(); break;
            case 9: break;
            default: cout << "無效的選擇。" << endl; break;
        }
    } while (choice != 9); // 直到選擇退出

    return 0;
}
