# 📚 Advanced Library Management System

A robust **Console-Based Library Management System** developed in **C++** that demonstrates the practical implementation of **Object-Oriented Programming (OOP)** principles, including **Encapsulation, Inheritance, Polymorphism, Abstraction, and Composition**.

The system enables efficient management of library resources such as books, magazines, and members while providing borrowing, returning, searching, and statistical reporting functionalities through an interactive menu-driven interface.

---

## ✨ Key Features

### 📖 Item Management

* Add and manage books
* Add and manage magazines
* Unique ID validation for all library items
* View complete item catalog with availability status

### 👤 Member Management

* Register library members
* Prevent duplicate member registrations
* Track borrowed items for each member
* Enforce borrowing limits

### 🔄 Borrowing Operations

* Borrow library items
* Return borrowed items
* Availability tracking
* Validation for invalid operations

### 🔍 Search & Reporting

* Search items by title
* Display all registered members
* Display all library items
* Generate library statistics and usage reports

---

## 🏗️ Object-Oriented Design

This project was designed to showcase industry-standard OOP concepts.

### Encapsulation

* Private data members protect internal object state.
* Public member functions provide controlled access to data.

### Inheritance

* `Book` and `Magazine` inherit from the abstract `Item` base class.

### Polymorphism

* Runtime polymorphism implemented using virtual functions.
* Library items are managed through base-class pointers.

### Abstraction

* The `Item` class defines a common interface for all library resources.
* Implementation details are hidden from users of the class.

### Composition

* Members maintain collections of borrowed items.
* The library system manages collections of items and members.

---

## 📂 Class Architecture

```text
                    Item (Abstract Class)
                           │
            ┌──────────────┴──────────────┐
            │                             │
          Book                       Magazine


                    LibrarySystem
                    │          │
                    │          │
                 Items      Members
                                │
                                │
                        Borrowed Items
```

---

## 🛠️ Technologies Used

* C++
* Standard Template Library (STL)

  * vector
  * string
  * algorithm
* Object-Oriented Programming (OOP)

---

## 📊 Functional Overview

| Feature                 | Status |
| ----------------------- | ------ |
| Book Management         | ✅      |
| Magazine Management     | ✅      |
| Member Management       | ✅      |
| Borrowing System        | ✅      |
| Return System           | ✅      |
| Search Functionality    | ✅      |
| Statistics Dashboard    | ✅      |
| Duplicate ID Validation | ✅      |
| Menu-Driven Interface   | ✅      |

---

## ▶️ Getting Started

### Clone Repository

```bash
git clone git@github.com:ShubhamTh951/library-management-system.git
cd library-management-system
```

### Compile

```bash
g++ main.cpp -o library
```

### Run

```bash
./library
```

---

## 📈 Future Enhancements

* File-based persistent storage
* Reservation and waitlist system
* Borrowing and due-date tracking
* Late fee calculation
* Fine management system
* Smart pointers (`std::unique_ptr`)
* Database integration
* Graphical User Interface (GUI)

---

## 🎯 Learning Outcomes

This project helped strengthen understanding of:

* Object-Oriented Design
* Class Relationships
* Runtime Polymorphism
* Dynamic Memory Management
* STL Containers
* Software Architecture Principles
* Input Validation and Error Handling

---

## 👨‍💻 Author

**Shubham Thakur**
B.Tech – Computer Science Engineering

---

⭐ If you found this project interesting, consider giving it a star.
