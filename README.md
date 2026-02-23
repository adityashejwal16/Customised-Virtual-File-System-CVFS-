# 🚀 Customised Virtual File System (CVFS)

> 💻 A System Programming project in C language that simulates the internal working of an Operating System File System.

---

## 📌 Overview

Customised Virtual File System (CVFS) is a system-level project developed in C language that replicates how an operating system manages files internally.

The project creates a virtual environment where files can be created, accessed, modified, and deleted using custom-designed data structures similar to real operating systems.

CVFS demonstrates important OS concepts such as Inodes, File Descriptors, File Tables, Memory Buffers, and Permission Management.

---

## 🎯 Project Objectives

- Understand file system architecture
- Implement OS concepts using data structures
- Simulate real file handling operations
- Learn low-level memory management
- Strengthen system programming fundamentals

---

## ⚙️ Features

- 📁 Virtual File Creation
- ❌ File Deletion (Unlink)
- ✍️ Read and Write Operations
- 🔐 Permission-Based Access Control
- 🧩 Inode-Based File Management
- 📊 User File Descriptor Table (UFDT)
- 🖥️ Command Driven Interactive Shell
- 💾 Memory Management Simulation

---

## 🧠 Core Components

### 🔹 Boot Block
Stores boot information of the virtual file system.

### 🔹 Super Block
Maintains total inode count and free inode count.

### 🔹 DILB (Disk Inode List Block)
Linked list containing available inodes.

### 🔹 Inode
Stores file metadata:
- File Name
- File Size
- Actual File Size
- Permission
- Reference Count
- Data Buffer Address

### 🔹 File Table
Maintains:
- Read Offset
- Write Offset
- Mode

### 🔹 UAREA
Represents process-level file descriptor table.

---

## 🖥️ Supported Commands

| Command | Arguments | Description |
|---------|-----------|-------------|
| creat | <filename> <permission> | Create new file |
| write | <fd> | Write data into file |
| read | <fd> <size> | Read data from file |
| ls | - | List all files |
| unlink | <filename> | Delete file |
| man | <command> | Show manual |
| help | - | Display help menu |
| clear | - | Clear terminal |
| exit | - | Exit CVFS |

---

## 🔐 Permission Model

| Value | Permission | Description |
|-------|------------|-------------|
| 1 | Read | Only read allowed |
| 2 | Write | Only write allowed |
| 3 | Read + Write | Both operations allowed |

---

## 🏗️ System Architecture
<br>
User Commands
<br>
↓
<br>
Command Interpreter
<br>
↓
<br>
UFDT
<br>
↓
<br>
File Table
<br>
↓
<br>
Inode
<br>
↓
<br>
Memory Buffer


---

## 🚀 Compilation & Execution

### Linux / macOS

gcc cvfs.c -o cvfs
./cvfs


### Windows (MinGW)

gcc cvfs.c -o cvfs.exe
cvfs.exe


---

## 📚 Concepts Used

- Linked List
- File System Design
- Memory Management
- Pointer Handling
- Operating System Concepts
- System Programming in C

---

## 💡 Learning Outcomes

- Understanding file system internals
- Role of inodes and file descriptors
- Offset management
- Permission implementation
- Virtual file abstraction

---

## 👨‍💻 Author

Aditya Dipak Shejwal

---

## 🔮 Future Enhancements

- Close File Command
- File Seek (lseek)
- File Statistics (stat / fstat)
- Directory Structure Support
- Multi-process Simulation

---

## 📄 License

This project is developed for educational purposes.
