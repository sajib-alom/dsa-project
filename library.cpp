#include <iostream>
#include <string>
#include <vector>

class Book {
private:
    int id;
    std::string title;
    std::string author;
    bool available;

public:
    Book(int id, const std::string& title, const std::string& author)
        : id(id), title(title), author(author), available(true) {
    }

    int getID() const {
        return id;
    }

    std::string getTitle() const {
        return title;
    }

    std::string getAuthor() const {
        return author;
    }

    bool isAvailable() const {
        return available;
    }

    void setAvailable(bool status) {
        available = status;
    }
};

class Library {
private:
    std::vector<Book> books;

public:
    void addNewBook(const Book& book) {
        books.push_back(book);
    }

    Book* searchBookById(int id) {
        for (auto& book : books) {
            if (book.getID() == id) {
                return &book;
            }
        }
        return nullptr;
    }

    Book* searchBookByTitle(const std::string& title) {
        for (auto& book : books) {
            if (book.getTitle() == title) {
                return &book;
            }
        }
        return nullptr;
    }

    void issueBook(int bookId, int memberId) {
        Book* book = searchBookById(bookId);
        if (book != nullptr && book->isAvailable()) {
            std::cout << "Book details:" << std::endl;
            std::cout << "ID: " << book->getID() << ", Title: " << book->getTitle() << ", Author: " << book->getAuthor() << std::endl;
            book->setAvailable(false);
            std::cout << "Book with ID " << bookId << " issued to member with ID " << memberId << "." << std::endl;
        } else {
            std::cout << "Book with ID " << bookId << " not found or already issued." << std::endl;
        }
    }

    void returnBook(int bookId) {
        Book* book = searchBookById(bookId);
        if (book != nullptr && !book->isAvailable()) {
            book->setAvailable(true);
            std::cout << "Book with ID " << bookId << " returned." << std::endl;
        } else {
            std::cout << "Book with ID " << bookId << " not found or already available." << std::endl;
        }
    }

    void listAllBooks() {
        if (books.empty()) {
            std::cout << "No books available in the library." << std::endl;
        } else {
            for (const auto& book : books) {
                std::cout << "ID: " << book.getID() << ", Title: " << book.getTitle() << ", Author: " << book.getAuthor();
                if (book.isAvailable()) {
                    std::cout << ", Status: Available" << std::endl;
                } else {
                    std::cout << ", Status: Issued" << std::endl;
                }
            }
        }
    }

    void deleteBook(int bookId) {
        for (auto it = books.begin(); it != books.end(); ++it) {
            if (it->getID() == bookId) {
                books.erase(it);
                std::cout << "Book with ID " << bookId << " deleted." << std::endl;
                return;
            }
        }
        std::cout << "Book with ID " << bookId << " not found." << std::endl;
    }
};

int main() {
    Library library;

    // Adding new books
    library.addNewBook(Book(1, "The Great Gatsby", "F. Scott Fitzgerald"));
    library.addNewBook(Book(2, "To Kill a Mockingbird", "Harper Lee"));
    library.addNewBook(Book(3, "The Lord of the Rings", "J. R. R. Tolkien"));
    library.addNewBook(Book(4, "War and Peace", "Leo Tolstoy"));
    

    int choice;
    do {
        std::cout << "\nLibrary Management System Menu:" << std::endl;
        std::cout << "1. Add a New Book" << std::endl;
        std::cout << "2. Issue a Book" << std::endl;
        std::cout << "3. Return a Book" << std::endl;
        std::cout << "4. Search for a Book" << std::endl;
        std::cout << "5. List All Books" << std::endl;
        std::cout << "6. Delete a Book" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int id;
                std::string title, author;
                std::cout << "Enter the ID of the book: ";
                std::cin >> id;
                std::cout << "Enter the title of the book: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                std::cout << "Enter the author of the book: ";
                std::getline(std::cin, author);
                library.addNewBook(Book(id, title, author));
                std::cout << "Book added successfully." << std::endl;
                break;
            }
            case 2: {
                int bookId, memberId;
                std::cout << "Enter the ID of the book to issue: ";
                std::cin >> bookId;
                std::cout << "Enter the ID of the member: ";
                std::cin >> memberId;
                library.issueBook(bookId, memberId);
                break;
            }
            case 3: {
                int bookId;
                std::cout << "Enter the ID of the book to return: ";
                std::cin >> bookId;
                library.returnBook(bookId);
                break;
            }
            case 4: {
                int searchChoice;
                std::cout << "Search by:" << std::endl;
                std::cout << "1. Title" << std::endl;
                std::cout << "2. ID" << std::endl;
                std::cout << "Enter your choice: ";
                std::cin >> searchChoice;

                if (searchChoice == 1) {
                    std::string title;
                    std::cout << "Enter the title of the book to search: ";
                    std::cin.ignore();
                    std::getline(std::cin, title);
                    Book* book = library.searchBookByTitle(title);
                    if (book != nullptr) {
                        std::cout << "Book found. Title: " << book->getTitle() << ", Author: " << book->getAuthor() << std::endl;
                    } else {
                        std::cout << "Book not found." << std::endl;
                    }
                } else if (searchChoice == 2) {
                    int id;
                    std::cout << "Enter the ID of the book to search: ";
                    std::cin >> id;
                    Book* book = library.searchBookById(id);
                    if (book != nullptr) {
                        std::cout << "Book found. Title: " << book->getTitle() << ", Author: " << book->getAuthor() << std::endl;
                    } else {
                        std::cout << "Book not found." << std::endl;
                    }
                } else {
                    std::cout << "Invalid choice." << std::endl;
                }
                break;
            }
            case 5:
                library.listAllBooks();
                break;
            case 6: {
                int id;
                std::cout << "Enter the ID of the book to delete: ";
                std::cin >> id;
                library.deleteBook(id);
                break;
            }
            case 0:
                std::cout << "Exiting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 0);

    return 0;
}
