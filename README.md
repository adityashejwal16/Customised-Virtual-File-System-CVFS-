📁 Customised Virtual File System (CVFS)
📌 Overview

Customised Virtual File System (CVFS) is a system-level project developed in C language that simulates the internal working of an Operating System’s file management system.

The project creates a virtual environment where files can be created, accessed, modified, and deleted using internally designed data structures similar to real operating systems such as Linux and Windows.

CVFS demonstrates core OS concepts including Inodes, File Descriptors, File Tables, Memory Buffers, and Permission Management.

🎯 Project Objectives

Understand internal architecture of file systems

Implement operating system concepts using data structures

Simulate real file handling operations

Learn low-level memory management in C

Strengthen system programming fundamentals

⚙️ Features

✅ Virtual File Creation
✅ File Deletion (Unlink Operation)
✅ Read & Write Operations
✅ Permission-Based Access Control
✅ Inode-Based File Management
✅ User File Descriptor Table (UFDT)
✅ Command Driven Interactive Shell
✅ Memory Management Simulation

🧠 Core Components
🔹 Boot Block

Stores boot information of the virtual file system.

🔹 Super Block

Maintains:

Total number of inodes

Free inode count

🔹 DILB (Disk Inode List Block)

Linked list containing all available inodes.

🔹 Inode

Stores file metadata:

File Name

File Size

Actual File Size

Permission

Reference Count

Data Buffer Address

🔹 File Table

Maintains runtime information:

Read Offset

Write Offset

Mode

🔹 UAREA

Represents process-level file descriptor table similar to an operating system.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

🖥️ Supported Commands
Command	Arguments	Description
creat	<filename> <permission>	Create a new file
write	<fd>	Write data into file
read	<fd> <size>	Read data from file
ls	—	Display list of all files
unlink	<filename>	Delete existing file
man	<command>	Display manual page
help	—	Show help menu
clear	—	Clear terminal
exit	—	Terminate CVFS

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

🔐 Permission Model
Value	Permission Type	Description
1	Read	File can only be read
2	Write	File can only be written
3	Read + Write	File supports both operations

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

🏗️ System Architecture
User Commands
      ↓
Command Interpreter (Shell)
      ↓
UFDT (File Descriptor Table)
      ↓
File Table
      ↓
Inode
      ↓
Memory Buffer (File Data)

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

🚀 Compilation & Execution
Linux / macOS
gcc cvfs.c -o cvfs
./cvfs
Windows (MinGW)
gcc cvfs.c -o cvfs.exe
cvfs.exe

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

📚 Concepts Used

Linked List Data Structure

File System Design

Memory Management

Pointer Handling

Operating System Concepts

System Programming in C

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

💡 Learning Outcomes

Understanding internal file system working

Role of inodes and file descriptors

Read/Write offset management

File permission implementation

Virtual file system abstraction

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

👨‍💻 Author

Aditya Dipak Shejwal

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

🔮 Future Enhancements

Close File Command

File Seek (lseek)

File Statistics (stat / fstat)

Directory Structure Support

Multi-process Simulation
