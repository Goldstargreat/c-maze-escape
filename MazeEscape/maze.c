/*
 * 미로 탈출 게임 (C 콘솔)
 * 기능: W/A/S/D 이동 / 벽 충돌 / 이동 횟수 기록 / 2스테이지 / 중간 포기
 * 기호: # 벽, @ 플레이어, E 출구
 */
#define _CRT_SECURE_NO_WARNINGS   /* Visual Studio에서 scanf 오류 방지 */
#include <stdio.h>
#include <stdlib.h>   /* system */

#define ROWS 9
#define COLS 15

 /* 스테이지 2개: [스테이지][줄][칸] */
char maps[2][ROWS][COLS + 1] = 
{
    {
        "###############",
        "#@    #       #",
        "# ### # ##### #",
        "#   #   #   # #",
        "### ##### # # #",
        "#   #     #   #",
        "# ### ####### #",
        "#     #      E#",
        "###############"
    },
    {
        "###############",
        "#@  #     #   #",
        "### # ### # # #",
        "#   #   #   # #",
        "# ##### ##### #",
        "#     #     # #",
        "##### # ### # #",
        "#E      #     #",
        "###############"
    }
};

/* 화면 지우기: 윈도우는 cls, 그 외는 clear */
void clearScreen(void) 
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main(void) 
{
    char maze[ROWS][COLS + 1];
    int stage, i, j;
    int px, py;            /* 플레이어 위치 (py: 줄, px: 칸) */
    int nx, ny;            /* 이동하려는 위치 */
    int moves;             /* 이번 스테이지 이동 횟수 */
    int total = 0;         /* 전체 이동 횟수 */
    char key;
    char message[60] = "";

    for (stage = 0; stage < 2; stage++) 
    {
        /* 1. 스테이지 지도를 maze로 복사하고 @ 위치 찾기 */
        for (i = 0; i < ROWS; i++) 
        {
            for (j = 0; j <= COLS; j++) 
            {
                maze[i][j] = maps[stage][i][j];
                if (maze[i][j] == '@') 
                {
                    py = i;
                    px = j;
                }
            }
        }
        moves = 0;
        message[0] = '\0';

        /* 2. 출구에 도착할 때까지 반복 */
        while (1) {
            clearScreen();
            printf("===== 미로 탈출  [스테이지 %d / 2] =====\n\n", stage + 1);
            for (i = 0; i < ROWS; i++) {
                printf("  %s\n", maze[i]);
            }
            printf("\n이동 횟수: %d\n", moves);
            printf("%s\n", message);
            printf("이동(w:위 a:왼쪽 s:아래 d:오른쪽, q:포기) > ");
            scanf(" %c", &key);

            /* 3. 키에 따라 이동할 위치 계산 */
            ny = py;
            nx = px;
            if (key == 'w' || key == 'W') ny = py - 1;
            else if (key == 's' || key == 'S') ny = py + 1;
            else if (key == 'a' || key == 'A') nx = px - 1;
            else if (key == 'd' || key == 'D') nx = px + 1;
            else if (key == 'q' || key == 'Q') {
                printf("\n게임을 포기했습니다.\n");
                return 0;
            }
            else {
                sprintf(message, "w, a, s, d 중 하나를 입력하세요.");
                continue;
            }

            /* 4. 벽이면 못 움직임 */
            if (maze[ny][nx] == '#') {
                sprintf(message, "쿵! 벽입니다.");
                continue;
            }

            /* 5. 출구 도착 */
            if (maze[ny][nx] == 'E') 
            {
                moves++;
                total = total + moves;
                printf("\n*** 스테이지 %d 탈출 성공! (%d번 이동) ***\n", stage + 1, moves);
                if (stage == 0) {
                    printf("다음 스테이지로 가려면 아무 키나 입력 > ");
                    scanf(" %c", &key);
                }
                break;
            }

            /* 6. 이동: 원래 자리는 빈칸, 새 자리에 @ */
            maze[py][px] = ' ';
            maze[ny][nx] = '@';
            py = ny;
            px = nx;
            moves++;
            message[0] = '\0';
        }
    }

    printf("\n===== 모든 미로를 탈출했습니다! =====\n");
    printf("전체 이동 횟수: %d\n", total);
    return 0;
}