#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <ctype.h>

#ifndef MAIN_H_
#define MAIN_H_
#define DEFAULT printf("%c[%dm", 0x1B, 0)
#define BOLD printf("%c[%dm", 0x1B, 1)
#define WHITE printf("\x1b[37m")
#define BLUE printf("\x1b[34m")
#define GREEN printf("\x1b[32m")

#define MAX_BUFFER_SIZE 512
#define MAX_LENGTH_SIZE 200
#define MAX_DIRECTORY_SIZE 50
#define MAX_NAME_SIZE 20
#define MAX_THREAD_SIZE 50

// User
typedef struct tagUserNode {
    char name[MAX_NAME_SIZE];
    char dir[MAX_DIRECTORY_SIZE];
    int UID;
    int GID;
    int year;
    int month;
    int wday;
    int day;
    int hour;
    int minute;
    int sec;
    struct tagUserNode *LinkNode;
} UserNode;

typedef struct tagUser {
    int topUID;
    int topGID;
    UserNode *head;
    UserNode *tail;
    UserNode *current;
} UserList;

// Directory
typedef struct tagDirectoryNode {
    char name[MAX_NAME_SIZE];
    char type;
    int mode;
    int permission[9];
    int SIZE;
    int UID;
    int GID;
    int month;
    int day;
    int hour;
    int minute;
    struct tagDirectoryNode *Parent;
    struct tagDirectoryNode *LeftChild;
    struct tagDirectoryNode *RightSibling;
} DirectoryNode;

typedef struct tagDirectoryTree {
    DirectoryNode *root;
    DirectoryNode *current;
} DirectoryTree;

// stack using linked list
typedef struct tagStackNode {
    char name[MAX_NAME_SIZE];
    struct tagStackNode *LinkNode;
} StackNode;

typedef struct tagStack {
    StackNode *TopNode;
    int cnt;
} Stack;

typedef struct tagThread {
    DirectoryTree *p_directoryTree;
    char *command;
    char *additionalValue;
    char *copyPath;
    DirectoryNode *fileNameNode;
} ThreadArg;

// path
char gPath[MAX_DIRECTORY_SIZE];

// time
time_t ltime;
struct tm *today;

// command.c
int mkdir(DirectoryTree *p_directoryTree, char *command);
int touch(DirectoryTree *p_directoryTree, char *command);
int cp(DirectoryTree *p_directoryTree, char *command);
int rm(DirectoryTree *p_directoryTree, char *command);
int cd(DirectoryTree *p_directoryTree, char *command);
int pwd(DirectoryTree *p_directoryTree, Stack *p_directoryStack, char *command);
int ls(DirectoryTree *p_directoryTree, char *command);
int cat(DirectoryTree *p_directoryTree, char *command);
int chmod(DirectoryTree *p_directoryTree, char *command);
int chown(DirectoryTree *p_directoryTree, char *command);
int find_(DirectoryTree *p_directoryTree, char *command);
void grep(char *command, char* Word_Search, char* f_name);

// init.c
void init(DirectoryTree *p_directoryTree, char *command);
void print_start();
void print_head(DirectoryTree *p_directoryTree, Stack *p_directoryStack);

// directory.c
// utility
int mode_to_permission(DirectoryNode *p_directoryNode);
void print_permission(DirectoryNode *p_directoryNode);
void destory_node(DirectoryNode *p_directoryNode);
void destory_directory(DirectoryNode *p_directoryNode);
DirectoryNode *is_exist_directory(DirectoryTree *p_directoryTree, char *directoryName, char type);
char *get_directory(char *directoryPath);
void copy_directory(DirectoryTree *p_directoryTree, DirectoryNode *p_directoryNode, char *copyName, char type, int level);

// save & load
void get_directory_path(DirectoryTree *p_directoryTree, DirectoryNode *p_directoryNode, Stack *p_directoryStack);
void write_directory_node(DirectoryTree *p_directoryTree, DirectoryNode *p_directoryNode, Stack *p_directoryStack);
void save_directory(DirectoryTree *p_directoryTree, Stack *p_directoryStack);
int read_directory_node(DirectoryTree *p_directoryTree, char *tmp);
DirectoryTree *load_directory();

// mkdir
DirectoryTree *initialize_directory_tree();
int make_new(DirectoryTree *p_directoryTree, char *directoryName, char type, char *additionalValue);
// rm
int remove_directory(DirectoryTree *p_directoryTree, char *directoryName);
// cd
int move_current_tree(DirectoryTree *p_directoryTree, char *directoryPath);
int move_directory_path(DirectoryTree *p_directoryTree, char *directoryPath);
// pwd
int print_directory_path(DirectoryTree *p_directoryTree, Stack *p_directoryStack);
void save_directory_path(DirectoryTree *p_directoryTree, Stack *p_directoryStack);
// ls
int list_directory(DirectoryTree *p_directoryTree, int a, int l);
// cat
int concatenate(DirectoryTree *p_directoryTree, char *fName, int o);
// chmod
int change_mode(DirectoryTree *p_directoryTree, int mode, char *directoryName);
void change_all_mode(DirectoryNode *p_directoryNode, int mode);
// chown
int change_owner(DirectoryTree *p_directoryTree, char *userName, char *directoryName);
void change_all_owner(DirectoryNode *p_directoryNode, char *userName);
// find
int read_directory(DirectoryTree *p_directoryTree, char *tmp, char *directoryName, int o);
void find_directory(DirectoryTree *p_directoryTree, char *directoryName, int o);
// grep
int strncasecmp(const char* str1, const char* str2, size_t n);
char *strcasestr(const char *haystack, const char *needle);

// user.c
UserList *initialize_user();
void write_user(UserList *p_userList, UserNode *userNode);
void save_user_list(UserList *p_userList);
int read_user(UserList *p_userList, char *tmp);
UserList *load_user_list();
UserNode *is_exist_user(UserList *p_userList, char *userName);
char *get_UID(DirectoryNode *p_directoryNode);
char *get_GID(DirectoryNode *p_directoryNode);
int is_node_has_permission(DirectoryNode *p_directoryNode, char o);
void login(UserList *p_userList, DirectoryTree *p_directoryTree);

// stack.c
Stack *initialize_stack();
int is_empty(Stack *p_directoryStack);
int push(Stack *p_directoryStack, char *directoryName);
char *pop(Stack *p_directoryStack);

// time.c
void get_month(int i);
void get_weekday(int i);

// thread.c
void *thread_routine_make_directory(void *arg);
void *thread_routine_touch(void *arg);
void *thread_routine_copy(void *arg);

// global pointer variable
DirectoryTree *gp_directoryTree;
Stack *gp_directoryStack;
UserList *gp_userList;
FILE *gp_file_directory;
FILE *gp_file_user;

#endif  // MAIN_H_
