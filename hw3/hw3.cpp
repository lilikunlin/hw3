#include <iostream>
#include <list>
#include <forward_list>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>

using namespace std;

struct Book {
    string title;
    string author;
    string id;
};

struct Borrower {
    string name;
    vector<string> borrowedBooks;
};

list<Book> books;
forward_list<Borrower> borrowers;

bool isValidBookId(const string& id) {
    regex pattern("^[A-Z][0-9]{4}$");
    return regex_match(id, pattern);
}

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
    } while (!isValidBookId(book.id));
    books.push_back(book);
}

void deleteBook() {
    string id;
    cout << "輸入要刪除的圖書編號: ";
    cin >> id;
    books.remove_if([&id](const Book& book) { return book.id == id; });
}

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

void listBooks() {
    books.sort([](const Book& a, const Book& b) { return a.id < b.id; });
    for (const auto& book : books) {
        cout << "書名: " << book.title << ", 作者: " << book.author << ", 圖書編號: " << book.id << endl;
    }
}

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
        borrower.borrowedBooks.push_back(bookId);
    }
    borrowers.push_front(borrower);
}

void deleteBorrower() {
    string name;
    cout << "輸入要刪除的借閱者姓名: ";
    cin >> name;
    borrowers.remove_if([&name](const Borrower& borrower) { return borrower.name == name; });
}

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
    } while (choice != 9);

    return 0;
}
