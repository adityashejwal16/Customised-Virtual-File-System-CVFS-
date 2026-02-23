📁 Customised Virtual File System (CVFS)
📌 Overview

The Customised Virtual File System (CVFS) is a system-level project written in C language that simulates the internal working of an Operating System’s file management system.

This project creates a virtual environment where files can be created, accessed, modified, and deleted using internally designed data structures similar to real operating systems like Linux.

CVFS demonstrates how operating systems manage files using concepts such as inodes, file descriptors, memory buffers, and permission handling.

🎯 Objectives

Understand internal architecture of file systems

Implement OS concepts using data structures

Simulate file handling operations

Learn low-level memory management in C

Build strong Operating System fundamentals

⚙️ Features

✅ Virtual File Creation
✅ File Deletion (Unlink)
✅ Read & Write Operations
✅ Permission Management
✅ Inode Based File Structure
✅ User File Descriptor Table (UFDT)
✅ Command Driven Shell Interface

🧠 Core Components
🔹 Boot Block

Stores boot information of the virtual file system.

🔹 Super Block

Maintains:

Total number of inodes

Free inode count

🔹 DILB (Disk Inode List Block)

Linked list containing all inodes available in the system.

🔹 Inode

Stores metadata of each file:

File Name

File Size

Actual Size

Permission

Reference Count

Buffer Address

🔹 File Table

Maintains runtime file information:

Read Offset

Write Offset

Mode

🔹 UAREA

Represents process file descriptor table similar to OS process structure.

🖥️ Supported Commands
Command	Description
creat <filename> <permission>	Create new file
write <fd>	Write data into file
read <fd> <size>	Read data from file
ls	List all files
Unlink <filename>	Delete file
man <command>	Display manual page
help	Show help menu
clear	Clear terminal
exit	Terminate CVFS
🔐 Permission Model
Value	Permission
1	Read
2	Write
3	Read + Write
🏗️ Architecture
User Commands
      ↓
Command Interpreter
      ↓
UFDT (File Descriptor Table)
      ↓
File Table
      ↓
Inode
      ↓
Memory Buffer
🚀 Compilation & Execution
Linux / macOS
gcc cvfs.c -o cvfs
./cvfs
Windows (MinGW)
gcc cvfs.c -o cvfs.exe
cvfs.exe
📚 Concepts Used

Linked List Data Structure

File System Design

Memory Management

Pointers in C

Operating System Concepts

System Programming

👨‍💻 Author

Aditya Dipak Shejwal

📄 License

This project is created for educational and learning purposes.
