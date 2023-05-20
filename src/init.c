#include <stdio.h>
#include <stdlib.h>

#include "main.h"

void init(DirectoryTree *p_directoryTree, char *command) {
    char *str;
    char *str1;
    char *str2;
    int isDirectoryExist;
    if (strcmp(command, "") == 0 || command[0] == ' ') {
        return;
    }
    str = strtok(command, " ");

    // cli 창 비우기 -> clear or cls
    if (strcmp(str, "clear") == 0 || strcmp(str, "cls") == 0) {
        system("clear");

    // 폴더 생성하기 mkdir [폴더이름 ...]
    // mkdir -m 777 [폴더이름] -> 권한 설정하면서 생성
    // mkdir -p /경로/폴더이름 -> 상위 폴더도 같이 생성
    } else if (strcmp(str, "mkdir") == 0) {
        str = strtok(NULL, " ");
        // 현재 있는 폴더인지 확인
        isDirectoryExist = mkdir(p_directoryTree, str);
        // 없으면 폴더 생성
        if (isDirectoryExist == 0) {
            save_directory(p_directoryTree, gp_directoryStack);
        }
    // 파일 생성하기 touch [파일이름]
    // touch -t 월일시분 [파일이름] -> 생성시간 변경
    // touch -m [파일 이름] -> 서버시간으로 변경
    } else if (strcmp(str, "touch") == 0) {
        str = strtok(NULL, " ");
        // 현재 있는 파일인지 확인
        isDirectoryExist = touch(p_directoryTree, str);
          // 없으면 파일 생성
        if (isDirectoryExist == 0) {
            save_directory(p_directoryTree, gp_directoryStack);
        }
    
    // 파일 복사 cp [복사할 파일 이름] [생성할 파일 이름]
    // 파일 복사 cp -r [복사할 폴더 이름] [생성할 폴더 이름]
    } else if (strcmp(str, "cp") == 0) {
        str = strtok(NULL, " ");
        isDirectoryExist = cp(p_directoryTree, str);
        if (isDirectoryExist == 0) {
            save_directory(p_directoryTree, gp_directoryStack);
        }

    // 파일 삭제 rm [삭제할 파일 이름]
    // rm -f [삭제할 파일 이름] -> 없어도 메세지 x
    // rm -r [삭제할 폴더 이름] -> 하위 폴더도 다삭제
    } else if (strcmp(str, "rm") == 0) {
        str = strtok(NULL, " ");
        isDirectoryExist = rm(p_directoryTree, str);
        if (isDirectoryExist == 0) {
            save_directory(p_directoryTree, gp_directoryStack);
        }

    // 경로 이동 ..하면 이전 경로로 이동
    // /는 홈디렉토리로 이동
    } else if (strcmp(str, "cd") == 0) {
        str = strtok(NULL, " ");
        cd(p_directoryTree, str);

    // 현재 경로 확인
    } else if (strcmp(str, "pwd") == 0) {
        str = strtok(NULL, " ");
        pwd(p_directoryTree, gp_directoryStack, str);

    // 현재 있는 내용 리스트 출력
    // -a 숨김파일도 출력
    // -l 긴 목록으로 출력 -> -al도 됨
    } else if (strcmp(str, "ls") == 0) {
        str = strtok(NULL, " ");
        ls(p_directoryTree, str);

    // txt파일 읽기
    // cat [파일.txt] -b, -n 하면 앞에 숫자 붙음
    // cat > [파일] -> txt파일 생성 (마지막에 :wq 하면 끝)
    } else if (strcmp(str, "cat") == 0) {
        str = strtok(NULL, " ");
        isDirectoryExist = cat(p_directoryTree, str);
        if (isDirectoryExist == 0) {
            save_directory(p_directoryTree, gp_directoryStack);
        }
    
    // 권한 변경 chmod [8진수 세자리] [파일 or 폴더명]
    // -R 붙으면 하위까지
    } else if (strcmp(str, "chmod") == 0) {
        str = strtok(NULL, " ");
        isDirectoryExist = chmod(p_directoryTree, str);
        if (isDirectoryExist == 0) {
            save_directory(p_directoryTree, gp_directoryStack);
        }

    // 파일 찾기 find [파일 or 폴더명]
    } else if (strcmp(str, "find") == 0) {
        str = strtok(NULL, " ");
        find_(p_directoryTree, str);
    } 

	// 파일 권한 변경 chown
	else if (strcmp(str, "chown") == 0) {
		str = strtok(NULL, " ");
		isDirectoryExist = chown_(p_directoryTree, str);
		if (isDirectoryExist == 0) {
			save_directory(p_directoryTree, gp_directoryStack);
		}
    }
	// 파일 내의 텍스트 찾기 grep
	else if (strcmp(str, "grep") == 0) {
		str = strtok(NULL, " ");
		grep(str);
    }
	// 종료
	else if (strcmp(command, "exit") == 0) {
		printf("로그아웃\n");
		exit(0);
	}
		else {
			printf("'%s': 명령을 찾을 수 없습니다\n", command);
		}

    return;
}

void print_start() {
    printf("\n");
    printf("Last login: ");
    get_weekday(gp_userList->current->wday);
    get_month(gp_userList->current->month);
    printf("%d %02d:%02d:%02d %d\n", gp_userList->current->day, gp_userList->current->hour, gp_userList->current->minute, gp_userList->current->sec, gp_userList->current->year);

    BOLD;
    BLUE;
    printf("miniOneS 1.0.0\n\n");
    printf("2023 OS team project\n");
    DEFAULT;
}

void print_head(DirectoryTree *p_directoryTree, Stack *p_directoryStack) {
    // variables
    DirectoryNode *tmpNode = NULL;
    char tmp[MAX_DIRECTORY_SIZE] = "";
    char tmp2[MAX_DIRECTORY_SIZE] = "";
    char usr;

    if (gp_userList->current == gp_userList->head)
        usr = '#';
    else
        usr = '$';

    BOLD;
    GREEN;
    printf("%s@miniOneS", gp_userList->current->name);
    DEFAULT;
    printf(":");
    tmpNode = p_directoryTree->current;

    if (tmpNode == p_directoryTree->root) {
        strcpy(tmp, "/");
    } else {
        while (tmpNode->Parent != NULL) {
            push(p_directoryStack, tmpNode->name);
            tmpNode = tmpNode->Parent;
        }
        while (is_empty(p_directoryStack) == 0) {
            strcat(tmp, "/");
            strcat(tmp, pop(p_directoryStack));
        }
    }

    strncpy(tmp2, tmp, strlen(gp_userList->current->dir));

    if (gp_userList->current == gp_userList->head) {
        BOLD;
        BLUE;
        printf("%s", tmp);
    } else if (strcmp(gp_userList->current->dir, tmp2) != 0) {
        BOLD;
        BLUE;
        printf("%s", tmp);
    } else {
        tmpNode = p_directoryTree->current;
        while (tmpNode->Parent != NULL) {
            push(p_directoryStack, tmpNode->name);
            tmpNode = tmpNode->Parent;
        }
        pop(p_directoryStack);
        pop(p_directoryStack);
        BOLD;
        BLUE;
        printf("~");
        while (is_empty(p_directoryStack) == 0) {
            printf("/");
            printf("%s", pop(p_directoryStack));
        }
    }
    DEFAULT;
    printf("%c ", usr);
}
