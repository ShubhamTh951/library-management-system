#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// INHERITANCE & POLYMORPHISM
class Item {  // Base class (Abstract)
protected:
    std::string id;
    std::string title;
    bool isAvailable;
    
public:
    Item(std::string i, std::string t) : id(i), title(t), isAvailable(true) {}
    virtual ~Item() = default;  // Virtual destructor
    
    // Pure virtual functions (Polymorphism)
    virtual void displayInfo() const = 0;
    virtual std::string getType() const = 0;
    
    // Common methods
    std::string getId() const { return id; }
    std::string getTitle() const { return title; }
    bool getAvailability() const { return isAvailable; }
    void setAvailability(bool status) { isAvailable = status; }
};

// INHERITANCE
class Book : public Item {
private:
    std::string author;
    int pages;
    
public:
    Book(std::string i, std::string t, std::string a, int p) 
        : Item(i, t), author(a), pages(p) {}
    
    // Override virtual functions
    void displayInfo() const override {
        std::cout << "BOOK - ID: " << id << " | Title: " << title 
                  << " | Author: " << author << " | Pages: " << pages
                  << " | Status: " << (isAvailable ? "Available" : "Borrowed") << std::endl;
    }
    
    std::string getType() const override { return "Book"; }
    std::string getAuthor() const { return author; }
    int getPages() const { return pages; }
};

class Magazine : public Item {
private:
    int issueNumber;
    std::string month;
    
public:
    Magazine(std::string i, std::string t, int issue, std::string m)
        : Item(i, t), issueNumber(issue), month(m) {}
    
    void displayInfo() const override {
        std::cout << "MAGAZINE - ID: " << id << " | Title: " << title 
                  << " | Issue: " << issueNumber << " | Month: " << month
                  << " | Status: " << (isAvailable ? "Available" : "Borrowed") << std::endl;
    }
    
    std::string getType() const override { return "Magazine"; }
    int getIssue() const { return issueNumber; }
    std::string getMonth() const { return month; }
};

// CAPSULATION & COMPOSITION
class Member {
private:
    std::string memberId;
    std::string name;
    std::vector<std::string> borrowedItems;  // Composition
    int maxBorrowLimit;
    
public:
    Member(std::string id, std::string n, int limit = 3) 
        : memberId(id), name(n), maxBorrowLimit(limit) {}
    
    // Getters
    std::string getId() const { return memberId; }
    std::string getName() const { return name; }
    int getBorrowedCount() const { return borrowedItems.size(); }
    int getMaxLimit() const { return maxBorrowLimit; }
    
    // Check if can borrow more
    bool canBorrow() const {
        return borrowedItems.size() < maxBorrowLimit;
    }
    
    // Borrow item
    bool borrowItem(const std::string& itemId) {
        if (!canBorrow()) return false;
        borrowedItems.push_back(itemId);
        return true;
    }
    
    // Return item
    bool returnItem(const std::string& itemId) {
        auto it = std::find(borrowedItems.begin(), borrowedItems.end(), itemId);
        if (it != borrowedItems.end()) {
            borrowedItems.erase(it);
            return true;
        }
        return false;
    }
    
    // Display member info
    void displayInfo() const {
        std::cout << "👤 MEMBER - ID: " << memberId << " | Name: " << name 
                  << " | Borrowed: " << borrowedItems.size() << "/" << maxBorrowLimit << std::endl;
        if (!borrowedItems.empty()) {
            std::cout << "   Borrowed Items: ";
            for (const auto& item : borrowedItems) {
                std::cout << item << " ";
            }
            std::cout << std::endl;
        }
    }
};

// MAIN MANAGEMENT CLASS
class LibrarySystem {
private:
    std::vector<Item*> items;        // Polymorphism - store different item types
    std::vector<Member> members;
    
    // Helper functions (Encapsulation)
    Item* findItem(const std::string& id) {
        for (auto* item : items) {
            if (item->getId() == id) return item;
        }
        return nullptr;
    }
    
    Member* findMember(const std::string& id) {
        for (auto& member : members) {
            if (member.getId() == id) return &member;
        }
        return nullptr;
    }

    // Check for duplicate IDs before adding new items or members
    bool itemIdExists(const std::string& id) {
        return findItem(id) != nullptr;
    }

    bool memberIdExists(const std::string& id) {
        return findMember(id) != nullptr;
    }
    
public:
    ~LibrarySystem() {  // Destructor for cleanup
        for (auto* item : items) {
            delete item;
        }
    }
    
    // Add items (Polymorphism in action)
    void addBook(std::string id, std::string title, std::string author, int pages) {
        if (itemIdExists(id)) {
            std::cout << "Book with ID " << id << " already exists!" << std::endl;
            return;
        }
        
        items.push_back(new Book(id, title, author, pages));
        std::cout << "Book added successfully!" << std::endl;
    }
    
    void addMagazine(std::string id, std::string title, int issue, std::string month) {
        if (itemIdExists(id)) {
            std::cout << "Magazine with ID " << id << " already exists!" << std::endl;
            return;
        }
        items.push_back(new Magazine(id, title, issue, month));
        std::cout << "Magazine added successfully!" << std::endl;
    }
    
    // Add member
    void addMember(std::string id, std::string name) {
        if (memberIdExists(id)) {
            std::cout << "Member with ID " << id << " already exists!" << std::endl;
            return;
        }
        members.emplace_back(id, name);
        std::cout << "Member " << name << " added successfully!" << std::endl;
    }
    
    // Borrow item
    void borrowItem(std::string memberId, std::string itemId) {
        Member* member = findMember(memberId);
        Item* item = findItem(itemId);
        
        if (!member) {
            std::cout << "Member not found!" << std::endl;
            return;
        }
        
        if (!item) {
            std::cout << "Item not found!" << std::endl;
            return;
        }
        
        if (!item->getAvailability()) {
            std::cout << "Item already borrowed!" << std::endl;
            return;
        }
        
        if (!member->canBorrow()) {
            std::cout << "Member has reached borrowing limit!" << std::endl;
            return;
        }
        
        // Process borrowing
        item->setAvailability(false);
        member->borrowItem(itemId);
        std::cout << member->getName() << " borrowed " << item->getTitle() << std::endl;
    }
    
    // Return item
    void returnItem(std::string memberId, std::string itemId) {
        Member* member = findMember(memberId);
        Item* item = findItem(itemId);
        
        if (!member || !item) {
            std::cout << "Member or Item not found!" << std::endl;
            return;
        }
        
        if (member->returnItem(itemId)) {
            item->setAvailability(true);
            std::cout << item->getTitle() << " returned successfully!" << std::endl;
        } else {
            std::cout << "This member didn't borrow this item!" << std::endl;
        }
    }
    
    // Display all items (Polymorphism in action)
    void displayAllItems() const {
        std::cout << "\n========== ALL LIBRARY ITEMS ==========" << std::endl;
        for (const auto* item : items) {
            item->displayInfo();  // Calls appropriate displayInfo() based on actual type
        }
    }
    
    // Display all members
    void displayAllMembers() const {
        std::cout << "\n========== ALL MEMBERS ==========" << std::endl;
        for (const auto& member : members) {
            member.displayInfo();
        }
    }
    
    // Search by title
    void searchByTitle(const std::string& title) const {
        std::cout << "\n========== SEARCH RESULTS ==========" << std::endl;
        bool found = false;
        for (const auto* item : items) {
            if (item->getTitle().find(title) != std::string::npos) {
                item->displayInfo();
                found = true;
            }
        }
        if (!found) {
            std::cout << "No items found with title containing: " << title << std::endl;
        }
    }
    
    // Statistics
    void showStatistics() const {
        int totalItems = items.size();
        int availableItems = 0;
        int totalBooks = 0, totalMagazines = 0;
        
        for (const auto* item : items) {
            if (item->getAvailability()) availableItems++;
            if (item->getType() == "Book") totalBooks++;
            else if (item->getType() == "Magazine") totalMagazines++;
        }
        
        std::cout << "\n========== LIBRARY STATISTICS ==========" << std::endl;
        std::cout << "Total Items: " << totalItems << std::endl;
        std::cout << "Available Items: " << availableItems << std::endl;
        std::cout << "Borrowed Items: " << (totalItems - availableItems) << std::endl;
        std::cout << "Total Books: " << totalBooks << std::endl;
        std::cout << "Total Magazines: " << totalMagazines << std::endl;
        std::cout << "Total Members: " << members.size() << std::endl;
    }
};

// MENU SYSTEM 
void showMenu() {
    std::cout << "\n========== LIBRARY MANAGEMENT SYSTEM ==========";
    std::cout << "\n1. Add Book";
    std::cout << "\n2. Add Magazine"; 
    std::cout << "\n3. Add Member";
    std::cout << "\n4. Borrow Item";
    std::cout << "\n5. Return Item";
    std::cout << "\n6. Display All Items";
    std::cout << "\n7. Display All Members";
    std::cout << "\n8. Search by Title";
    std::cout << "\n9. Show Statistics";
    std::cout << "\n0. Exit";
    std::cout << "\nChoose option: ";
}

int main() {
    LibrarySystem library;
    int choice;
    
    std::cout << "Welcome to Library Management System!" << std::endl;
    std::cout << "Loading sample data with ID validation..." << std::endl;
    
    // Sample data - notice how IDs are properly managed
    library.addBook("B001", "C++ Programming", "Bjarne Stroustrup", 1300);
    library.addBook("B002", "Clean Code", "Robert Martin", 464);
    library.addMagazine("M001", "Tech Today", 45, "January 2025");
    library.addMember("MEM001", "Alice Johnson");
    library.addMember("MEM002", "Bob Smith");
    
    // This will demonstrate ID validation - try to add duplicate
    std::cout << "\n--- Testing Duplicate ID Prevention ---" << std::endl;
    library.addBook("B001", "Duplicate Book", "Test Author", 100);  // Should fail!
    library.addMember("MEM001", "Duplicate Member");                // Should fail!
    
    do {
        showMenu();
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                std::string id, title, author;
                int pages;
                std::cout << "Enter Book ID: "; std::cin >> id;
                std::cout << "Enter Title: "; std::cin.ignore(); std::getline(std::cin, title);
                std::cout << "Enter Author: "; std::getline(std::cin, author);
                std::cout << "Enter Pages: "; std::cin >> pages;
                library.addBook(id, title, author, pages);
                break;
            }
            case 2: {
                std::string id, title, month;
                int issue;
                std::cout << "Enter Magazine ID: "; std::cin >> id;
                std::cout << "Enter Title: "; std::cin.ignore(); std::getline(std::cin, title);
                std::cout << "Enter Issue Number: "; std::cin >> issue;
                std::cout << "Enter Month: "; std::cin.ignore(); std::getline(std::cin, month);
                library.addMagazine(id, title, issue, month);
                break;
            }
            case 3: {
                std::string id, name;
                std::cout << "Enter Member ID: "; std::cin >> id;
                std::cout << "Enter Name: "; std::cin.ignore(); std::getline(std::cin, name);
                library.addMember(id, name);
                break;
            }
            case 4: {
                std::string memberId, itemId;
                std::cout << "Enter Member ID: "; std::cin >> memberId;
                std::cout << "Enter Item ID: "; std::cin >> itemId;
                library.borrowItem(memberId, itemId);
                break;
            }
            case 5: {
                std::string memberId, itemId;
                std::cout << "Enter Member ID: "; std::cin >> memberId;
                std::cout << "Enter Item ID: "; std::cin >> itemId;
                library.returnItem(memberId, itemId);
                break;
            }
            case 6: library.displayAllItems(); break;
            case 7: library.displayAllMembers(); break;
            case 8: {
                std::string title;
                std::cout << "Enter title to search: ";
                std::cin.ignore(); std::getline(std::cin, title);
                library.searchByTitle(title);
                break;
            }
            case 9: library.showStatistics(); break;
            case 0: std::cout << "Thank you for using Library System!" << std::endl; break;
            default: std::cout << "Invalid choice!" << std::endl;
        }
        
        if (choice != 0) {
            std::cout << "\nPress Enter to continue...";
            std::cin.ignore(); std::cin.get();
        }
        
    } while (choice != 0);
    
    return 0;
}
