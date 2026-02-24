///////////////////////////////////////////////////////////////
//
//          Header File Inclusion
//
///////////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<string.h>

///////////////////////////////////////////////////////////////
//
//          User Defined Macros
//
///////////////////////////////////////////////////////////////

// Mximum File Size That we Allow in The Project
#define MAXFILESIZE 50

#define MAXOPENFILES 20

#define  MAXINODE 5

#define READ 1
#define WRITE 2
#define EXECUTE 4

#define START 0
#define CURRENT 1
#define END 2

#define EXECUTE_SUCCESS 0

#define REGULARFILE 1
#define SPECIALFILE 2

///////////////////////////////////////////////////////////////
//
//          User Defined Macros For Error Handling
//
///////////////////////////////////////////////////////////////

#define ERR_INVALID_PARAMETER -1

#define ERR_NO_INODES -2

#define ERR_FILE_ALREADY_EXIST -3
#define ERR_FILE_NOT_EXIST -4

#define ERR_PERMISSION_DENIED -5

#define ERR_INSUFFICIENT_SPACE -6
#define ERR_INSUFFICIENT_DATA -7

#define ERR_MAX_FILES_OPEN    -8

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                User Defined Structures
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
//
//      Structure Name : BootBlock 
//      Description  :   Holds the information to boot the os
//
///////////////////////////////////////////////////////////////

struct BootBlock
{
    char Information[100];
};

///////////////////////////////////////////////////////////////
//
//      Structure Name : SuperBlock 
//      Description  :   Holds the information about the file system
//
///////////////////////////////////////////////////////////////

struct SuperBlock
{
    int TotalInodes;
    int FreeInodes;
};

///////////////////////////////////////////////////////////////
//
//      Structure Name : Inode 
//      Description  :   Holds the information abut file
//
///////////////////////////////////////////////////////////////

#pragma pack(1)
struct Inode
{
    char FileName[20];
    int InodeNumber;
    int FileSize;
    int ActualFileSize;
    int FileType;
    int ReferenceCount;
    int Permission;
    char *Buffer;
    struct Inode *next;
};

typedef struct Inode INODE;
typedef struct Inode * PINODE;
typedef struct Inode ** PPINODE;

///////////////////////////////////////////////////////////////
//
//      Structure Name : FileTable 
//      Description  :   Holds the information abut Open file
//
///////////////////////////////////////////////////////////////

struct FileTable
{
    int ReadOffset;
    int WriteOffset;
    int Mode;
    PINODE ptrinode;
};

typedef FileTable FILETABLE;
typedef FileTable * PFILETABLE;

///////////////////////////////////////////////////////////////
//
//      Structure Name : UAREA
//      Description  :   Holds the information abut process file
//
///////////////////////////////////////////////////////////////

struct UAREA
{
    char ProcessName[20];
    PFILETABLE UFDT[MAXOPENFILES];
};


///////////////////////////////////////////////////////////////
//
//     Global Variable Or Object used in the project
//
///////////////////////////////////////////////////////////////

BootBlock bootobj;
SuperBlock superobj;
UAREA uareaobj;

PINODE head = NULL;

///////////////////////////////////////////////////////////
//
//    Function Name : InitialiseUAREA
//    Description :  it is use to initialise UAREA member
//    Author :       Aditya Dipak Shejwal
//    Date  :        13/01/2026
//
/////////////////////////////////////////////////////

void InitialiseUAREA()
{
    strcpy(uareaobj.ProcessName,"Myexe");
    
    int i = 0;

    for(i = 0; i < MAXOPENFILES; i++)
    {
        uareaobj.UFDT[i] = NULL;
    }
     printf("Marvellous CVFS : UAREA Gets Initialised Succesfully\n");
}

///////////////////////////////////////////////////////////
//
//    Function Name : InitialiseSuperBlock
//    Description :   it is use to initialise Super Block members
//    Author :        Aditya Dipak Shejwal
//    Date  :         13/01/2026
//
////////////////////////////////////////////////////////

void InitialiseSuperBlock()
{
    superobj.TotalInodes = MAXINODE;
    superobj.FreeInodes = MAXINODE;

    printf("Marvellous CVFS : Super Block Gets Initialised Succesfully\n");
}

///////////////////////////////////////////////////////////
//
//    Function Name : CreateDILB
//    Description :  it is use to create Linkedlist of inodes
//    Author :       Aditya Dipak Shejwal
//    Date  :        13/01/2026
//
/////////////////////////////////////////////////////

void CreateDILB()
{
    int i = 1;
    PINODE newn = NULL;
    PINODE temp = head;

    for(i = 1; i <= MAXINODE; i++)
    {
        newn = (PINODE)malloc(sizeof(INODE));   // Memory allocate
        
        strcpy(newn->FileName,"\0");
        newn->InodeNumber = i;
        newn->FileSize = 0;
        newn->ActualFileSize = 0;
        newn->FileType = 0;
        newn->ReferenceCount = 0;
        newn->Permission = 0;
        newn->Buffer = NULL;
        newn->next = NULL;

        if(temp == NULL)  // LL is Empty
        {
            head = newn;
            temp = head;
        }
        else             // LL Atleat 1 node
        {
            temp->next = newn;
            temp = temp->next;
        }
    }

    printf("Maevellous CVFS : DILB Created Succesfully\n");
}

///////////////////////////////////////////////////////////
//
//    Function Name : StartAuxillaryDataInitialisation
//    Description :  it is use to call all such function which are used
//                    initialise auxillary data  
//    Author :       Aditya Dipak Shejwal
//    Date  :        13/01/2026
//
/////////////////////////////////////////////////////

void StartAuxillaryDataInitilisation()
{
    printf(bootobj.Information,"Booting Process of Marvellous CVFS is Done");

    printf("%s\n",bootobj.Information);

    InitialiseSuperBlock();

    CreateDILB();

    InitialiseUAREA();

    printf("Marvellous CVFS : Auxillary data initialised succesfully\n");
}

///////////////////////////////////////////////////////////
//
//    Function Name : Display help
//    Description :  it is use to display the help page 
//    Author :       Aditya Dipak Shejwal
//    Date  :        14/01/2026
//
/////////////////////////////////////////////////////

void DisplayHelp()
{
    printf("-------------------------------------------------------\n");
    printf("----------- Marvellous CVFS Help Page -----------------\n");
    printf("-------------------------------------------------------\n");

    printf("man    : it is used to display manual page\n");  
    printf("Clear  : it is used to clear the terminal\n");
    printf("create : it is used to create new file\n");
    printf("write  : it is used to write the data into the file\n");
    printf("read   : it is used to read the data from file\n");
    printf("stat   : it is used to display statical information\n");
    printf("unlink : it is used to delete the file\n");
    printf("exit   : it is used to terminate MArvellous CVFS");
}

///////////////////////////////////////////////////////////
//
//    Function Name : ManOageDisplay
//    Description :  it is use to display Man page 
//    Author :       Aditya Dipak Shejwal
//    Date  :        14/01/2026
//
/////////////////////////////////////////////////////

void ManPageDisplay(char Name[])
{
    if(strcmp("ls",Name)==0)
    {
        printf("About : it is used to list the name of all files\n");
        printf("Usage : ls\n");
    }
    else if(strcmp("man",Name)==0)
    {
        printf("About : it is used to display manual pqge\n");
        printf("Usage : man command_name\n");
        printf("Command_name : it is the name of command\n");
    }
    else if(strcmp("exit",Name)==0)
    {
        printf("About : it is used to terminate the shell\n");
        printf("Usage : exit\n");
    }
    else if(strcmp("clear",Name)==0)
    {
        printf("About : it is used to clear the shell\n");
        printf("Usage : exit\n");
    }
    else
    {
        printf("No manual entry for %s\n",Name);
    }
}

///////////////////////////////////////////////////////////
//
//    Function Name : IsFileExist
//    Description :  it is use to chect whether file is already exist or not
//    Input       :  it accespts file name 
//    Output      :  it return true or flase
//    Author :       Aditya Dipak Shejwal
//    Date  :        14/01/2026
//
//////////////////////////////////////////////////////////

int IsFileExist(
                 char *name   // File Name
                )
{
   PINODE temp = head;
   bool bFlag = false;

   while(temp != NULL)
   {
       if((strcmp(name,temp->FileName)==0) && (temp->FileType == REGULARFILE))
       {
          bFlag = true;
          break;
       }
       temp=temp->next;
   }

   return bFlag;
}

///////////////////////////////////////////////////////////
//
//    Function Name : CreateFile
//    Description :  it is use to create newn regular file
//    Input       :  it accespts file name and permission
//    Output      :  it return the file descritor
//    Author :       Aditya Dipak Shejwal
//    Date  :        14/01/2026
//
//////////////////////////////////////////////////////////

int CreateFile(
                   char *name,      // Name of new file
                   int permission  // Permission for that file
              )
{
    PINODE temp = head;
    int i = 0;

    printf("Total number of inodes remaing : %d\n",superobj.FreeInodes);
 
    // if name is missing
    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    // if the permission value is wrong
    // permission -> 1 -> head
    // permission -> 2 -> WRITE
    // permission -> 3 -> READ + WRITE
    if(permission < 1 || permission > 3)
    {
        return ERR_INVALID_PARAMETER;
    }
    
    // if the inodes are full
    if(superobj.FreeInodes == 0)
    {
        return ERR_NO_INODES;
    }
     
    // if file is already present
    if(IsFileExist(name) == true)
    {
        return ERR_FILE_ALREADY_EXIST;
    }

    // Search Empty inode
    while(temp != NULL)
    {
        if(temp -> FileType == 0)
        {
            break;
        }
        temp = temp -> next;
    }

    if(temp == NULL)
    {
        printf("There is no inode\n");
        return ERR_NO_INODES;
    }
    
    // Search for Empty UFDT Entry
    // NOTE : 0 1 2 are reserved
    for(i = 3; i < MAXOPENFILES; i++)
    {
        if(uareaobj.UFDT[i]==NULL)
        {
            break;
        }
    }

    //UFDT is full [UFDT means->Array]
    if(i == MAXOPENFILES)
    {
        return ERR_MAX_FILES_OPEN;
    }

    // Allocate Memory for file table
    uareaobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FILETABLE));

    // Initialise File Table
    uareaobj.UFDT[i] -> ReadOffset = 0;
    uareaobj.UFDT[i] -> WriteOffset = 0;
    uareaobj.UFDT[i] -> Mode = permission;

    // Connect file table with Inode 
    uareaobj.UFDT[i] -> ptrinode = temp;

    // Initialise elements of Inode
    strcpy(uareaobj.UFDT[i] -> ptrinode -> FileName,name);
    uareaobj.UFDT[i] -> ptrinode -> FileSize = MAXFILESIZE;
    uareaobj.UFDT[i] -> ptrinode -> ActualFileSize = 0;
    uareaobj.UFDT[i] -> ptrinode -> FileType = REGULARFILE;
    uareaobj.UFDT[i] -> ptrinode -> ReferenceCount = 1;
    uareaobj.UFDT[i] -> ptrinode -> Permission = permission;
  
    // Allocate Memory for file data
    uareaobj.UFDT[i] -> ptrinode -> Buffer =(char *)malloc(MAXFILESIZE);

    superobj.FreeInodes--;

    return i;  // File Descriptor


}

////////////////////////////////////////////////////////////
//
//  Function Name :     LsFile()
//  Description :       It is used to list all files
//  Input :             Nothing
//  Output :            Nothing
//  Author :            Aditya Dipak Shejwal
//  Date :              16/01/2026
//
///////////////////////////////////////////////////////////////

// ls -1
void LsFile()
{
    PINODE temp = head;

    printf("-----------------------------------------------\n");
    printf("------ Marvellous CVFS Files Information ------\n");
    printf("-----------------------------------------------\n");

    while(temp != NULL)
    {
        if(temp -> FileType != 0)
        {
            printf("%d\t%s\t%d\n",temp->InodeNumber,temp->FileName,temp->ActualFileSize);
        }
         
        temp = temp -> next;
    }

    printf("-------------------------------------------------------\n");

}

///////////////////////////////////////////////////////////
//
//    Function Name : UnlinkFile()
//    Description :  it is use to Delete the file
//    Input       :   file name 
//    Output      :  Nothing
//    Author :       Aditya Dipak Shejwal
//    Date  :        22/01/2026
//
//////////////////////////////////////////////////////////

int UnlinkFile(
                char *name
              )
{
    int i = 0;

    if(name == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(IsFileExist(name) == false)
    {
        return ERR_FILE_NOT_EXIST;
    }

    // Travel the UFDT

    for(i = 0; i < MAXOPENFILES; i++)
    {
        if(uareaobj.UFDT[i] != NULL)
        {
            if(strcmp(uareaobj.UFDT[i]->ptrinode->FileName, name)==0)
            {
                // Dealocate Memory of Buffer
                free(uareaobj.UFDT[i]->ptrinode->Buffer);
                uareaobj.UFDT[i]->ptrinode->Buffer = NULL;

                // Reset All VAlue of inode
                // Dont deallocate memory of inode
                uareaobj.UFDT[i]->ptrinode->FileSize = 0;
                uareaobj.UFDT[i]->ptrinode->ActualFileSize = 0;
                uareaobj.UFDT[i]->ptrinode->FileType = 0;
                uareaobj.UFDT[i]->ptrinode->ReferenceCount = 0;
                uareaobj.UFDT[i]->ptrinode->Permission = 0;
                
                memset(uareaobj.UFDT[i]->ptrinode->FileName,'\0', sizeof(uareaobj.UFDT[i]->ptrinode->FileName));

                // Deallocate memory of file table
                free(uareaobj.UFDT[i]);

                // set NULL to UFDT
                uareaobj.UFDT[i] == NULL;

                // Increment free inode count
                superobj.FreeInodes++;

                break;   // IMP

            } // End of uf
        }    // End of if
    }       // End of for
}           // End of function     

///////////////////////////////////////////////////////////
//
//    Function Name : WriteFile()
//    Description :  it is use to write the data into the file
//    Input       :   File descriptor
//                    Address of buffer which contain data
//                    Size of data that we want  to write           
//    Output      :  Numbner of byutes succesfully written
//    Author :       Aditya Dipak Shejwal
//    Date  :        22/01/2026
//
//////////////////////////////////////////////////////////

int WriteFile(
              int fd,
              char *data,
              int size
            )
{
    printf("File descriptor : %d\n",fd);
    printf("Data that we want to write : %d\n",data);
    printf("Number of bytes that you want : %d\n",size);
    
    // Invalide Fd
    if(fd < 0 || fd > MAXOPENFILES)
    {
        return ERR_INVALID_PARAMETER;
    }
    
    //Fd Point to NULL
    if(uareaobj.UFDT[fd] == NULL)
    {
        return ERR_FILE_NOT_EXIST;
    }

    // there is NO permission write
    if(uareaobj.UFDT[fd]->ptrinode->Permission < WRITE)
    {
       return ERR_PERMISSION_DENIED;
    }
 
    // Insufficieant space
    if((MAXFILESIZE - uareaobj.UFDT[fd]->WriteOffset) < size)
    {
        return ERR_INSUFFICIENT_SPACE;
    }

    // Write the Data into the file
    strncpy(uareaobj.UFDT[fd]->ptrinode->Buffer + uareaobj.UFDT[fd]->WriteOffset, data, size);

    //Update the Write Offset
    uareaobj.UFDT[fd]->WriteOffset = uareaobj.UFDT[fd]->WriteOffset + size;

    // Update the Actual file size
    uareaobj.UFDT[fd]->ptrinode->ActualFileSize = uareaobj.UFDT[fd]->ptrinode->ActualFileSize + size;

    return size;
}


//////////////////////////////////////////////////////////
//
//  Function Name :     ReadFile()
//  Description :       It is used to read the data from the file
//  Input :             File descriptor
//                      Address of empty buffer
//                      Size of data that we want to read
//  Output :            Number of bytes succesfully read
//  Author :            Aditya Dipak Shejwal
//  Date :              22/01/2026
//
//////////////////////////////////////////////////////////

int ReadFile(
                int fd,
                char *data,
                int size
            )
            
{

    // Invalide FD
    if(fd < 0 || fd > MAXOPENFILES)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(data == NULL)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(size <= 0)
    {
        return ERR_INVALID_PARAMETER;
    }

    if(uareaobj.UFDT[fd] == NULL)
    {
        return ERR_FILE_NOT_EXIST;
    }

    // Filter for permission
    if(uareaobj.UFDT[fd]->ptrinode->Permission < READ)
    {
        return ERR_PERMISSION_DENIED;
    }

    //Insuficient data
    if((MAXFILESIZE - uareaobj.UFDT[fd]->ReadOffset) < size)
    {
        return ERR_INSUFFICIENT_DATA;
    }

    // Read the data
    strncpy(data,uareaobj.UFDT[fd]->ptrinode->Buffer + uareaobj.UFDT[fd]->ReadOffset, size);

    // Update the Read Offset
    uareaobj.UFDT[fd]->ReadOffset = uareaobj.UFDT[fd]->ReadOffset + size;
    
    return size;
}            
///////////////////////////////////////////////////////////////
//
//       Entry Point Function Of The Project
//
///////////////////////////////////////////////////////////////

int main()
{
    char str[80] = {'\0'};
    char Command[5][20] = {{'\0'}};
    char InputBuffer[MAXFILESIZE] = {'\0'};

    char *EmptyBuffer = NULL;
    
    int iCount = 0;
    int iRet = 0;

    StartAuxillaryDataInitilisation();

    printf("-------------------------------------------------------\n");
    printf("-------- Marvellous CVFS Started Succesfully ----------\n");
    printf("-------------------------------------------------------\n");

//// Infinite Listening Shell //////////////

    while(1)
    {
        fflush(stdin);

        strcpy(str,"");

        printf("\nMarvellous CVFS : > ");
        fgets(str,sizeof(str),stdin); 
 
        iCount = sscanf(str,"%s %s %s %s %s", Command[0],Command[1],Command[2],Command[3],Command[4]);
        
        fflush(stdin);

        if(iCount == 1)
        {
            // Marvellous CVFS : > exit 
            if(strcmp("exit",Command[0]) == 0)    // strcmp = String compareasam
             {
                printf("Thank you for Marvellous CVFS\n");
                printf("Deallocating all the allocated resources\n");

                break;
             }
             // Marvellous CVFS : > ls
             else if(strcmp("ls",Command[0])==0)
             {
                LsFile();
             }
             // Marvellous CVFS : > help
             else if(strcmp("help",Command[0])==0)
             {
                DisplayHelp();
             }
             // Marvellous CVFS : > clear
             else if(strcmp("clear",Command[0])==0)
             {
                 #ifdef _WIN32
                       system("cls");
                     #else
                       system("clear");
                     #endif 
             }

        }// End of else if 1
        else if(iCount == 2)
        {
            // Marvellous CVFS : > man ls
            if(strcmp("man",Command[0]) == 0)
            {
                ManPageDisplay(Command[1]);
            }
             // Marvellous CVFS : > Unlink Demo.txt
            if(strcmp("Unlink",Command[0]) == 0)
            {
                iRet = UnlinkFile(Command[1]);

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalide Parameter\n");
                }
                if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : Unable to delete as there is no such file\n");
                }
                if(iRet == EXECUTE_SUCCESS)
                {
                    printf("file get succesfully deleted\n");
                }
            }
            // Marvellous CVFS : > Write 2
            else if(strcmp("write",Command[0]) == 0)
            {
                printf("Enter the data that you want to write :\n");
                fgets(InputBuffer,MAXFILESIZE,stdin);

                iRet = WriteFile(atoi(Command[1]),InputBuffer,strlen(InputBuffer)-1);

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalide parameter\n");

                }
                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : There is no such file\n");
                }
                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error : Unable to write as there is no permission\n");
                }
                else if(iRet == ERR_INSUFFICIENT_SPACE)
                {
                    printf("Error : Unable to write as there is no space\n");
                }
                else
                {
                    printf("%d bytes gets succesfully written\n",iRet);
                }
            }
            else
            {
                printf("there is no such Command\n");
            }
        }// End of else if 2
        else if(iCount == 3)
        {
            // Marvellous CVFS : > creat Ganesh.txt 3
             if(strcmp("creat",Command[0])==0)
            {
                iRet = CreateFile(Command[1],atoi(Command[2]));

                 if(iRet == ERR_INVALID_PARAMETER)
                 {
                    printf("Error : Unable to Creat the file as parameters are invalid\n");
                    printf("Please refer man page\n");
                 }

                 if(iRet == ERR_NO_INODES)
                 {
                    printf("ERROR : Unable to creat file as there is NO inodes\n");
                 }

                 if(iRet == ERR_FILE_ALREADY_EXIST)
                 {
                    printf("ERROR : Unable to creat file because the file is already present\n");
                 }
                 if(iRet == ERR_MAX_FILES_OPEN)
                 {
                    printf("ERROR : Unable to create file\n");
                    printf("Max open opened file limit reached\n");
                 }

                 printf("File gets succesfully created with Fd : %d\n",iRet);

            }
            // Marvellous CVFS : > Read 3 10
            if(strcmp("read",Command[0]) == 0)
            {
                EmptyBuffer = (char *)malloc(sizeof(atoi(Command[2])));

                iRet = ReadFile(atoi(Command[1]), EmptyBuffer, atoi(Command[2]));

                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Invalide Parameter\n");
                }
                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : File Not Exist\n");
                }
                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error : Permission Denied\n");
                }
                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : Insufficient data\n");
                }
                else
                {
                    printf("Read Operation Is Succesfully\n");
                    printf("Data From File Is : %s\n, EmptyBuffer");

                    free(EmptyBuffer);
                }
            }
            else
            {
                printf("There is no such command\n");
            }
        } // End of else if 3
        else if(iCount == 4)
        {

        } // End of else if 4
        else
        {
            printf("Command Not Found\n");
            printf("Please refer help option to get more information\n");
        } // End Of Else
    } // End Of if

    return 0;
} // End Of Main