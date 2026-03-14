#  Secure Password Manager
### C++ Project | Case Study 99 | BTech CSE — First Year

A simple command-line password manager built in C++.  
It lets you store, view, update and delete passwords — all saved in **encrypted form**.

---

## 📋 Features

-  Master login with username & password
-  Account locks after 3 wrong attempts
-  Add new credentials (website, username, password)
-  View saved passwords (decrypted on request)
-  Update existing passwords
-  Delete saved entries
-  Activity log with timestamps
-  Report showing total accounts & last login time

---


##  Default Login

| Field    | Value  |
|----------|--------|
| Username | `Saad` |
| Password | `1234` |

---

## Files Created at Runtime

| File             | Purpose                        |
|------------------|--------------------------------|
| `passwords.txt`  | Stores all encrypted passwords |
| `log.txt`        | Activity log with timestamps   |
| `lastlogin.txt`  | Records last successful login  |

---

## Encryption

Uses a simple **Caesar Cipher** — every character is shifted by **+3** while saving and **-3** while reading.

Example:
```
Original  →  hello
Encrypted →  khoor
```

Passwords are **never stored as plain text.**

---

##  Classes Used

| Class                   | What it does                          |
|-------------------------|---------------------------------------|
| `EncryptionManager`     | Encrypts and decrypts passwords       |
| `Credential`            | Stores one website entry              |
| `User`                  | Holds master login details            |
| `StorageManager`        | Reads and writes all files            |
| `PasswordManagerSystem` | Controls the menu and overall flow    |

---

##  Concepts Covered

- Object Oriented Programming (Classes, Objects, Constructors, Encapsulation)
- File Handling (ifstream, ofstream)
- Functions
- Vectors (dynamic data storage)
- Loops and Conditionals

---

## Project Structure

```
  password-manager
 ┣ 📄 password_manager.cpp   ← main source code
 ┣ 📄 passwords.txt          ← auto created when you add a password
 ┣ 📄 log.txt                ← auto created on first login
 ┣ 📄 lastlogin.txt          ← auto created on first login

```

---
