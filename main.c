
/***************************
    2023 1학기 텀 프로젝트
    우주방위대 ( 슈팅게임 ) 
****************************/
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.lib")

// 색상 정의
#define BLACK   0
#define BLUE1   1
#define GREEN1   2
#define CYAN1   3
#define RED1   4
#define MAGENTA1 5
#define YELLOW1   6
#define GRAY1   7
#define GRAY2   8
#define BLUE2   9
#define GREEN2   10
#define CYAN2   11
#define RED2   12
#define MAGENTA2 13
#define YELLOW2   14
#define WHITE   15

//키보드
#define SPECIAL1 0XE0
#define SPECIAL2 0x00
#define SPACE 0x20
#define UP 0x48   //방향키 위
#define DOWN 0x50  //방향기 다운
#define LEFT 0x4b  //방향기 왼쪽
#define RIGHT 0x4d  //방향키 오른쪽

#define WIDTH 60   //맵 가로 크기
#define HEIGHT 50  // 맵 세로 크기
#define UX 30  //시작 유저의 x좌표
#define UY 45  //시작 유저의 y좌표
#define NUM_STARS 10// 메인화면 별
#define MAXBULLET 6//플레이어의 최대 총알 수
#define MAXMISILE 1// 플레이어의 궁극기 수

#define MAXENEMY 6 //최대 적 수
#define MAXENEMY2 1 //적2의 최대 적 수
#define MAXENEMYBULLET 23// 적 최대 총알 수
#define MAXENEMY2BULLET 2 // 적2 최대 총알 수
#define MAXMINIMOSTER 1// 미니 몬스터
#define MAXBOSSBULLET 8// 보스 총알
#define SPEEDITEM "<S>"//플레이어 스피드// 적 스피드 아이템은 빨간색

#define ITEM "<H>"//하트
#define BOOM "<B>"//전멸
#define POWERITEM "<C>"// 갤러그 아이템
#define MISILEITEM "<Q>"//필살기
#define TIME "<T>"//시간 추가


int heart = 4;//플레이어 목숨
int score = 0;//점수
int keep_moving = 1;  //1:계속이동
int called = 0;
int oldx = UX, oldy = UY; // 플레이어의 old 좌표
int newx = UX, newy = UY; //플레이어의 new 좌표
int time_out = 99; //제한시간
int last_remain_time;
int remain_time;
int frame_count = 0; // game 진행 frame count 로 속도 조절용으로 사용된다.
int Delay = 10;      //while문 속도조절용으로 사용된다

int p1_frame_sync = 4; //플레이어의 이동속도
int p1_frame_sync_count = 0;
int bullet_frame_sync = 3.5;// 플레이어 총알속도
int misile_frame_sync = 2;// 플레이어 궁극기 속도

int enemy_frame_sync = 8;//적 움직임 속도
int enemy2_frame_sync = 4;//적2 움직임 속도
int miniMonster_frame_sync = 14;//미니 몬스터 속도
int enemyuse = 1;  //1초마다 적 생성
int enemy2use = 1;  //10초마다 적 생성
int enemybulletuse = 1; //적 총알 1초마다 생성
int enemy2bulletuse = 4; //적2 총알 4초마다 생성
int miniMonsteruse = 20;//미니 몬스터 1초마다 생성
int enemybullet_frame_sync = 9;// 적 총알 속도
int enemy2bullet_frame_sync = 2;// 적2 총알 속도
int item_frame_sync = 10;//아이템 움직이는 속도

int items[WIDTH][HEIGHT] = { 0 };
int items_count = 0;
int items_use = 18; //아이템 나타나는 시간(목숨 아이템) 게임시작 10초 경과 후
int boom[WIDTH][HEIGHT] = { 0 };
int boom_count = 0;
int boom_use = 20; //아이템 나타나는 시간(종알지움) 게임시작 10초 경과 후

int timeitems[WIDTH][HEIGHT] = { 0 };
int timeitems_count = 0;
int timeitems_use = 30; //아이템 나타나는 시간(시간 아이템) 게임시작 10초 경과 후

int misile = 0;
int misileitems[WIDTH][HEIGHT] = { 0 };
int misileitems_count = 0;
int misileitems_use = 25;// 아이템 나타나는 시간(미사일)
int speeditems[WIDTH][HEIGHT] = { 0 };
int speeditems_count = 0;
int speeditems_use = 23; //아이템 나타나는 시간(플레이어 스피드 아이템)
int speed2items[WIDTH][HEIGHT] = { 0 };
int speed2items_count = 0;
int speed2items_use = 21; //아이템 나타나는 시간(적 스피드 아이템)
int power[WIDTH][HEIGHT] = { 0 };
int power_count = 0;
int power_use = 28; //아이템 나타나는 시간(파워 아이템)
int p = 0;//업그레이드 변수
int bossspeedup = 15;// 15초마다 보스가 빨라짐
int speedupem = 10;// 10초마다 적이 빨라짐

int last_remain_time;
int remain_time;
char* Enemyunit[] = { "☎※☎","☜▼☞","◀▩▶","◎§◎" };
char* Enemy2unit[] = { "★※★","★※★" };

int bossheart = 180;
int bossbulletuse = 1;
int boss_frame_sync = 15;  //보스 프레임단위
int bossbullet_frame_sync = 8; //보스총알속도
int bossx = 30, bossy = 10;

#define TRUE 1
#define FALSE 0

struct {
    int exist;
    int x, y;
}Bullet[MAXBULLET];//플레이어 총알

struct {
    int exist;
    int x, y;
}Misile[MAXMISILE];//플레이어 궁극기

struct {
    int exist;
    int x, y;
    int number;
    int move;
    int type;
}Enemy[MAXENEMY];//적(몬스터)

struct {
    int exist;
    int x, y;
    int number;
    int move;
    int type;
}Enemy2[MAXENEMY2];//적2(몬스터)

struct {
    int exist;
    int x, y;
    int frame;
    int stay;
}miniMonster[MAXMINIMOSTER];//미니 몬스터-(플레이어 따라다님)

struct {
    int exist;
    int x, y;
    int frame;
    int stay;
}EnemyBullet[MAXENEMYBULLET];// 적의 총알

struct {
    int exist;
    int x, y;
    int frame;
    int stay;
}Enemy2Bullet[MAXENEMYBULLET];// 적2의 총알

struct {
    int exist;
    int x, y;
}BossBullet[MAXBOSSBULLET];// 보스 총알

typedef struct {
    int x;
    int y;
    int exist;
} Star;// 메인화면 별



//내가 원하는 위치로 커서 이동
void gotoxy(int x, int y)
{
    COORD pos; // Windows.h 에 정의
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
//텍스트 컬러
void textcolor(int fg_color, int bg_color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), fg_color | bg_color << 4);
}
// 커서를 안보이게 한다
void removeCursor(void) {
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
void showCursor(void) { // 커서를 보이게 한다
    CONSOLE_CURSOR_INFO curInfo;
    GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
    curInfo.bVisible = 1;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curInfo);
}
// 화면 지우기
void cls(int bg_color, int text_color)
{
    char cmd[100];
    system("cls");
    sprintf(cmd, "COLOR %x%x", bg_color, text_color);
    system(cmd);
}
//별 위치
void initializeStars(Star stars[], int numStars) {
    srand(time(NULL));
    stars[0].x = 5; stars[0].y = 3;
    stars[1].x = 5; stars[1].y = 20;
    stars[2].x = 35; stars[2].y = 24;
    stars[3].x = 20; stars[3].y = 29;
    stars[4].x = 55; stars[4].y = 20;
    stars[5].x = 40; stars[5].y = 30;
    stars[6].x = 45; stars[6].y = 36;
    stars[7].x = 15; stars[7].y = 35;
    stars[8].x = 49; stars[8].y = 32;
    stars[9].x = 8; stars[9].y = 30;
    //stars[10].x = 40; stars[10].y = 30;


}
//별 그리기
void printStars(Star stars[], int numStars) {
    for (int i = 0; i < numStars; i++) {
        if (stars[i].exist == 1) {
            int r = rand() % 16;
            gotoxy(stars[i].x, stars[i].y);
            textcolor(r, 0);
            printf("*");
        }
        else {
            gotoxy(stars[i].x, stars[i].y);
            printf(" ");
        }
    }
    fflush(stdout);
}
//별 랜덤값
void updateStars(Star stars[], int numStars) {
    for (int i = 0; i < numStars; i++) {
        if (rand() % 2 == 0) {
            stars[i].exist = !stars[i].exist;
        }
    }
}


void DrawBullet(int i) {
    textcolor(GREEN1, BLACK);
    gotoxy(Bullet[i].x, Bullet[i].y);
    printf("↑");
}
void EraseBullet(int i) {
    gotoxy(Bullet[i].x, Bullet[i].y);
    printf("   ");
}
void DrawUpBullet(int i) {
    textcolor(CYAN1, BLACK);
    gotoxy(Bullet[i].x, Bullet[i].y);
    printf("w      w");
}
void EraseUpBullet(int i) {
    gotoxy(Bullet[i].x, Bullet[i].y);
    printf("         ");
}
void bulletmove() {
    int i, j;
    if (p == 0) {
        for (i = 0; i < MAXBULLET; i++) {
            if (Bullet[i].exist == TRUE) {
                EraseBullet(i);
                if (Bullet[i].y < 4) {
                    Bullet[i].exist = FALSE;
                }
                else {
                    Bullet[i].y--;
                    DrawBullet(i);
                }
            }
        }
    }
    else {
        for (i = 0; i < MAXBULLET; i++) {
            if (Bullet[i].exist == TRUE) {
                EraseUpBullet(i);
                if (Bullet[i].y < 4) {
                    Bullet[i].exist = FALSE;
                }
                else {
                    Bullet[i].y--;
                    DrawUpBullet(i);
                }
            }
        }
    }

}

void drawmisile(int i) {
    gotoxy(Misile[i].x, Misile[i].y - 2); printf("★★");
    gotoxy(Misile[i].x, Misile[i].y - 1); printf("§§");
    gotoxy(Misile[i].x, Misile[i].y); printf("§§");
}
void erasemisile(int i) {
    gotoxy(Misile[i].x, Misile[i].y - 2); printf("    ");
    gotoxy(Misile[i].x, Misile[i].y - 1); printf("    ");
    gotoxy(Misile[i].x, Misile[i].y); printf("    ");
}
void misilemove() {
    int i;
    for (i = 0; i < MAXMISILE; i++) {
        if (Misile[i].exist == TRUE) {
            erasemisile(i);
            if (Misile[i].y - 2 < 4) {
                Misile[i].exist = FALSE;
            }
            else {
                Misile[i].y--;
                drawmisile(i);
            }
        }
    }
}


//적 총알, 움직임
void EnemyBulletshow() {
    int j;
    int random = rand() % MAXENEMY;
    for (j = 0; j < MAXENEMYBULLET && EnemyBullet[j].exist == TRUE; j++) {}
    if (j != MAXENEMYBULLET && Enemy[random].exist == TRUE) {
        EnemyBullet[j].x = Enemy[random].x + 1;
        EnemyBullet[j].y = Enemy[random].y + 1;
        EnemyBullet[j].exist = TRUE;
    }
}
void EnemyBulletdraw(int i) {
    textcolor(RED1, BLACK);
    gotoxy(EnemyBullet[i].x, EnemyBullet[i].y);
    printf("▲");
}
void EnemyBulleterase(int i) {
    //textcolor(RED1, BLACK);
    gotoxy(EnemyBullet[i].x, EnemyBullet[i].y);
    printf(" ");
}
void EnemyBulletMove() {
    int random;
    random = 1;
    for (int i = 0; i < MAXENEMYBULLET; i++) {
        if (EnemyBullet[i].exist == TRUE) {
            EnemyBulleterase(i);
            if (EnemyBullet[i].y > HEIGHT - 3) {
                EnemyBullet[i].exist = FALSE;
            }
            else {
                EnemyBullet[i].y++;
                EnemyBulletdraw(i);
            }
        }
    }
}
void Enemy2Bulletshow() {
    int j;
    int random = rand() % MAXENEMY2;
    for (j = 0; j < MAXENEMY2BULLET && Enemy2Bullet[j].exist == TRUE; j++) {}
    if (j != MAXENEMY2BULLET && Enemy2[random].exist == TRUE) {
        Enemy2Bullet[j].x = Enemy2[random].x + 2;
        Enemy2Bullet[j].y = Enemy2[random].y + 1;
        Enemy2Bullet[j].exist = TRUE;
    }
}
void Enemy2Bulletdraw(int i) {
    textcolor(BLUE2, BLACK);
    gotoxy(Enemy2Bullet[i].x, Enemy2Bullet[i].y);
    printf("l l");
    gotoxy(Enemy2Bullet[i].x, Enemy2Bullet[i].y + 1);
    printf("l l");
    gotoxy(Enemy2Bullet[i].x, Enemy2Bullet[i].y + 2);
    printf("w w");


}
void Enemy2Bulleterase(int i) {
    //textcolor(RED1, BLACK);
    gotoxy(Enemy2Bullet[i].x, Enemy2Bullet[i].y);
    printf("   ");
    gotoxy(Enemy2Bullet[i].x, Enemy2Bullet[i].y + 1);
    printf("   ");
    gotoxy(Enemy2Bullet[i].x, Enemy2Bullet[i].y + 2);
    printf("   ");
}
void Enemy2BulletMove() {
    int random;
    random = 1;
    for (int i = 0; i < MAXENEMY2BULLET; i++) {
        if (Enemy2Bullet[i].exist == TRUE) {
            Enemy2Bulleterase(i);
            if (Enemy2Bullet[i].y > HEIGHT - 5) {
                Enemy2Bullet[i].exist = FALSE;
            }
            else {
                Enemy2Bullet[i].y++;
                Enemy2Bulletdraw(i);
            }
        }
    }
}

void EnemyBulletMove2() {// 총알이 플레이어 따라다님 x축으로만
    int random;
    random = 1;
    for (int i = 0; i < MAXENEMYBULLET; i++) {
        if (EnemyBullet[i].exist == TRUE) {
            EnemyBulleterase(i);
            if (EnemyBullet[i].y > HEIGHT - 3) {
                EnemyBullet[i].exist = FALSE;
            }
            else {
                if (random) {
                    if (EnemyBullet[i].x <= newx)
                        EnemyBullet[i].x++;
                    else
                        EnemyBullet[i].x--;
                }
                EnemyBullet[i].y++;
                EnemyBulletdraw(i);
            }
        }
    }
}
//적
void showenemy() {
    int i, location, direct, hieght;
    srand(time(NULL));
    location = rand() % 2;
    direct = 5 + rand() % 55;//x축 생성
    hieght = 6 + rand() % 10;//y축 생성
    for (i = 0; i < MAXENEMY && Enemy[i].exist == TRUE; i++) {}
    if (i != MAXENEMY) {
        if (location == 1) {
            Enemy[i].x = direct;
            Enemy[i].y = hieght;
            Enemy[i].move = 1;
        }
        else {
            Enemy[i].x = direct;
            Enemy[i].y = hieght;
            Enemy[i].move = -1;
        }
        Enemy[i].type = rand() % 4;
        Enemy[i].exist = TRUE;
    }
}
void Enemymove() {
    int i;
    for (i = 0; i < MAXENEMY; i++) {
        if (Enemy[i].exist == TRUE) {
            if (Enemy[i].type == -1) {
                gotoxy(Enemy[i].x - 1, Enemy[i].y);
                printf("          ");
                Enemy[i].exist = FALSE;
                continue;
            }
            if (Enemy[i].x > 49) {
                Enemy[i].x -= 1;
                Enemy[i].move = -1;
            }
            else if (Enemy[i].x <= 7) {

                Enemy[i].move = 1;
                Enemy[i].x += 1;
                gotoxy(Enemy[i].x, Enemy[i].y);
                printf(" ");
            }
            else {
                Enemy[i].x += Enemy[i].move;// move값을 받아 1이면 오른쪽 -1이면 왼쪽
                gotoxy(Enemy[i].x, Enemy[i].y);
                printf(Enemyunit[Enemy[i].type]);
                printf(" ");
            }
        }
    }
}
void showenemy2() {
    int i, location, direct, hieght;
    i = 0;
    srand(time(NULL));
    location = rand() % 2;
    direct = 5 + rand() % 55;//x축 생성
    hieght = 3 + rand() % 1;//y축 생성
    for (i = 0; i < MAXENEMY2 && Enemy2[i].exist == TRUE; i++) {}
    if (i != MAXENEMY2) {
        if (location == 1) {
            Enemy2[i].x = direct;
            Enemy2[i].y = hieght;
            Enemy2[i].move = 1;
        }
        else {
            Enemy2[i].x = direct;
            Enemy2[i].y = hieght;
            Enemy2[i].move = -1;
        }
        Enemy2[i].type = rand() % 2;
        Enemy2[i].exist = TRUE;
    }
}
void Enemy2move() {
    int i;
    for (i = 0; i < MAXENEMY2; i++) {
        if (Enemy2[i].exist == TRUE) {
            if (Enemy2[i].type == -1) {
                gotoxy(Enemy2[i].x - 1, Enemy2[i].y);
                printf("          ");
                Enemy2[i].exist = FALSE;
                continue;
            }
            if (Enemy2[i].x > 49) {
                Enemy2[i].x -= 1;
                Enemy2[i].move = -1;
            }
            else if (Enemy2[i].x <= 7) {

                Enemy2[i].move = 1;
                Enemy2[i].x += 1;
                gotoxy(Enemy2[i].x, Enemy2[i].y);
                printf(" ");
            }
            else {
                Enemy2[i].x += Enemy2[i].move;// move값을 받아 1이면 오른쪽 -1이면 왼쪽
                gotoxy(Enemy2[i].x, Enemy2[i].y);
                printf(Enemy2unit[Enemy2[i].type]);
                printf(" ");
            }
        }
    }
}

//플레이어 그리기
void playerdraw(int x, int y) {
    if (p == 0) {
        textcolor(GREEN1, BLACK);
        gotoxy(x, y);
        printf("◀◈▶");
    }
    else {
        textcolor(GREEN2, BLACK);
        gotoxy(x, y);
        printf("◀◈▶◀◈▶");
    }
}
//플레이어 지우기
void playererase(int x, int y) {
    if (p == 0) {
        gotoxy(x, y);
        printf("     ");
    }
    else {
        gotoxy(x, y);
        printf("            ");
    }
}
void playermove(unsigned char ch) {

    int move_flag = 0;
    static unsigned char last_ch = 0;  //static이므로 전역변수라고 생각하면 된다 (메모리에 계속 올라가있음)


    if (called == 0) {  //플레이어 호출 함수가 처음 불렸다면 ?
        removeCursor();
        playerdraw(oldx, oldy);  //플레이어를 글려줌
        called = 1;
    }

    if (keep_moving && ch == 0)
        ch = last_ch;
    last_ch = ch;

    switch (ch) {
    case UP:  //방향키 위쪽이 눌렸다면?
        if (oldy > 25)  //플레이어의 y좌표가 25보다 크다면?
            newy = oldy - 1;    //플레이어의 새로윈 y좌표는 현재위치  Y위치 -1
        else {   //벽을 만났다면 반대로 움직이는 로직
            //else문 움직이면 반대로 안움직이고 벽만나면 그냥 막힌다
            newy = oldy + 1;
            last_ch = DOWN; //벽을 만났기 때문에 DOWN해줘서 내려가게 해준다
        }
        move_flag = 1; //계속 움직이게 해줌
        break;
    case DOWN:
        if (oldy < HEIGHT - 3)  //플레이어의 Y좌표가 맵의 크기 -3 보다 작다면
            newy = oldy + 1;   //플레이어의 새로운 Y좌표는 현재 Y위치 +1
        else {  //벽만나는 로직
            newy = oldy - 1;
            last_ch = UP;
        }
        move_flag = 1;
        break;
    case LEFT:
        if (oldx > 4)  //플레이어의 X좌표가 2보다 크다면 왼쪽으로 이동 가능
            newx = oldx - 1;
        else {  //그게아니라면 반대로 이동
            newx = oldx + 1;
            last_ch = RIGHT;
        }
        move_flag = 1;
        break;
    case RIGHT:
        if (p == 0) {
            if (oldx < WIDTH - 6)  //플레이어의 X좌표가 맵 크기-6보다 작다면 오른쪽으로 이동 가능
                newx = oldx + 1;
            else { //반대로 이동
                newx = oldx - 1;
                last_ch = LEFT;
            }
        }
        else {
            if (oldx < WIDTH - 12)  //플레이어의 X좌표가 맵 크기-6보다 작다면 오른쪽으로 이동 가능
                newx = oldx + 1;
            else { //반대로 이동
                newx = oldx - 1;
                last_ch = LEFT;
            }
        }
        move_flag = 1;
        break;
    }
    if (move_flag) {
        playererase(oldx, oldy); //플레이어를 예전위치를 지우고
        playerdraw(newx, newy); // 새로운 위치에서 플레이어 그려준다
        oldx = newx; // 마지막 위치를 기억한다.
        oldy = newy; // 마지막 위치를 기억한다.
        if (items[newx][newy]) {
            heart++;
            items[newx][newy] = 0;
            items_count--;
        }
        if (timeitems[newx][newy]) {
            last_remain_time += 10;
            time_out += 10;
            timeitems[newx][newy] = 0;
            timeitems_count--;
            remain_time += 10; // 남은 시간에 10초 추가
        }

        if (boom[newx][newy]) {
            for (int i = 0; i < MAXENEMYBULLET; i++) {
                if (EnemyBullet[i].exist == FALSE)
                    continue;
                else {
                    EnemyBullet[i].exist = FALSE;
                    gotoxy(EnemyBullet[i].x, EnemyBullet[i].y);
                    printf("    ");
                }
            }
            for (int i = 0; i < MAXENEMY2BULLET; i++) {
                if (Enemy2Bullet[i].exist == FALSE)
                    continue;
                else {
                    Enemy2Bullet[i].exist = FALSE;
                    gotoxy(Enemy2Bullet[i].x, Enemy2Bullet[i].y);
                    printf("   ");
                    gotoxy(Enemy2Bullet[i].x, Enemy2Bullet[i].y + 1);
                    printf("   ");
                    gotoxy(Enemy2Bullet[i].x, Enemy2Bullet[i].y + 2);
                    printf("   ");
                }
            }
            for (int i = 0; i < MAXBOSSBULLET; i++) {
                if (BossBullet[i].exist == FALSE)
                    continue;
                else {
                    BossBullet[i].exist = FALSE;
                    gotoxy(BossBullet[i].x, BossBullet[i].y);
                    printf("                   ");
                }
            }

            boom[newx][newy] = 0;
            boom_count--;
        }
        if (speeditems[newx][newy]) {
            speeditems[newx][newy] = 0;
            speeditems_count--;
            if (p1_frame_sync > 2)
                p1_frame_sync--;
            if (bullet_frame_sync > 2)
                bullet_frame_sync--;
        }
        if (speed2items[newx][newy]) {
            speed2items[newx][newy] = 0;
            speed2items_count--;

            if (enemy_frame_sync < 20)
                enemy_frame_sync += 2;
            if (enemybullet_frame_sync < 20)
                enemybullet_frame_sync += 2;
            if (bossbullet_frame_sync < 12)
                bossbullet_frame_sync += 2;

        }

        if (power[newx][newy]) {
            p++;
            for (int i = 0; i < MAXBULLET; i++) {
                if (Bullet[i].exist == FALSE)
                    continue;
                else {
                    Bullet[i].exist = FALSE;
                    gotoxy(Bullet[i].x, Bullet[i].y);
                    printf("      ");
                }
            }
            power[newx][newy] = 0;
            power_count--;
        }
        if (misileitems[newx][newy]) {
            misile++;
            misileitems[newx][newy] = 0;
            misileitems_count--;
        }

    }
}

//충돌구현
void Enemyfall() {
    int i, j, k;
    k = (p == 0 ? 7 : 11);//7, 11
    for (i = 0; i < MAXENEMY; i++) {
        if (Enemy[i].exist == FALSE || Enemy[i].type == -1)
            continue;
        if (Enemy[i].y == Bullet[i].y && abs(Enemy[i].x - Bullet[i].x) <= k) {//abs절댓갑..//7~-7..
            gotoxy(Bullet[i].x, Bullet[i].y);
            printf("         ");
            Bullet[i].exist = FALSE;
            Enemy[i].type = -1;
            score += 10;
            break;
        }
        if (Enemy[i].y == Misile[i].y && abs(Enemy[i].x - Misile[i].x) <= 10) {
            gotoxy(Misile[i].x - 2, Misile[i].y); printf("       ");
            gotoxy(Misile[i].x, Misile[i].y - 1); printf("    ");
            gotoxy(Misile[i].x, Misile[i].y - 2); printf("    ");
            Enemy[i].type = -1;
            Misile[i].exist = FALSE;
            score += 10;
        }

    }
    for (j = 0; j < MAXENEMY2; j++) {
        if (Enemy2[j].exist == FALSE || Enemy2[j].type == -1)
            continue;
        if (Enemy2[j].y == Bullet[j].y && abs(Enemy2[j].x - Bullet[j].x) <= k) {//abs절댓갑..//7~-7..
            gotoxy(Bullet[j].x, Bullet[j].y);
            printf("         ");
            Bullet[j].exist = FALSE;
            Enemy2[j].type = -1;
            score += 10;
            break;
        }
        if (Enemy2[j].y == Misile[j].y && abs(Enemy2[j].x - Misile[j].x) <= 10) {
            gotoxy(Misile[j].x - 2, Misile[j].y); printf("       ");
            gotoxy(Misile[j].x, Misile[j].y - 1); printf("    ");
            gotoxy(Misile[j].x, Misile[j].y - 2); printf("    ");
            Enemy2[j].type = -1;
            Misile[j].exist = FALSE;
            score += 10;
        }


    }


}

//적총알 충돌
void playerfall() {
    int i, j, k;
    k = (p == 0 ? 3 : 7);
    for (i = 0; i < MAXENEMYBULLET; i++) {
        if (EnemyBullet[i].exist == FALSE)
            continue;
        if (EnemyBullet[i].y == newy && abs(EnemyBullet[i].x - newx) <= k) {
            EnemyBullet[i].exist = FALSE;
            gotoxy(EnemyBullet[i].x, EnemyBullet[i].y);
            printf("    ");
            heart--;

            if (p == 1) {
                for (int i = 0; i < MAXBULLET; i++) {
                    Bullet[i].exist = FALSE;
                    gotoxy(Bullet[i].x, Bullet[i].y);
                    printf("            ");
                }
            }

            p = 0;
            gotoxy(oldx, oldy);
            printf("            ");
            /*for (int n = 0; n < MAXBULLET; n++) {
               EraseBullet(n);
            }*/

        }
    }
    for (j = 0; j < MAXENEMY2BULLET; j++) {
        if (Enemy2Bullet[j].exist == FALSE)
            continue;
        if (Enemy2Bullet[j].y == newy && abs(Enemy2Bullet[j].x - newx) <= k) {
            Enemy2Bullet[j].exist = FALSE;
            gotoxy(Enemy2Bullet[j].x, Enemy2Bullet[j].y);
            printf("    ");
            gotoxy(Enemy2Bullet[j].x, Enemy2Bullet[j].y + 1);
            printf("    ");
            gotoxy(Enemy2Bullet[j].x, Enemy2Bullet[j].y + 2);
            printf("    ");
            heart--;


            if (p == 1) {
                for (int i = 0; i < MAXBULLET; i++) {
                    /*if (Bullet[i].exist == FALSE)
                       continue;
                    else {*/
                    Bullet[i].exist = FALSE;
                    gotoxy(Bullet[i].x, Bullet[i].y);
                    printf("            ");
                    //}
                       //////////////////////////// 적 총알 맞으면 총알 두발 나가던게 다 사라지고, 일반총알로 바뀜
                }
            }
            p = 0;
            gotoxy(oldx, oldy);
            printf("            ");
            //system("cls");
        }
    }
    for (int n = 0; n < MAXMINIMOSTER; n++) {
        if (miniMonster[n].exist == FALSE)
            continue;
        if (miniMonster[n].y == newy && abs(miniMonster[n].x - newx) <= k) {
            miniMonster[n].exist = FALSE;
            gotoxy(miniMonster[n].x, miniMonster[n].y);
            printf("    ");
            heart--;
            p = 0;
            gotoxy(oldx, oldy);
            printf("            ");
            //system("cls");
        }
    }
}


//보스충돌
void bossfall() {
    int i, k, n;
    k = (p == 0 ? 12 : 17);
    n = (p == 0 ? 11 : 9);

    for (i = 0; i < MAXBULLET; i++) {
        if (Bullet[i].exist == FALSE)
            continue;
        if (bossy + 7 == Bullet[i].y && abs((bossx + n) - Bullet[i].x) <= k) {
            gotoxy(Bullet[i].x, Bullet[i].y);
            printf("           ");
            Bullet[i].exist = FALSE;
            if (p == 0) {
                bossheart--;
            }
            else {
                bossheart -= 5;
            }
            break;
        }
    }
    for (i = 0; i < MAXMISILE; i++) {
        if (Misile[i].exist == FALSE)
            continue;
        if (bossy + 7 == Misile[i].y && abs((bossx + 11) - Misile[i].x) <= 12) {
            gotoxy(Misile[i].x, Misile[i].y); printf("    ");
            gotoxy(Misile[i].x, Misile[i].y - 1); printf("    ");
            gotoxy(Misile[i].x, Misile[i].y - 2); printf("    ");
            Misile[i].exist = FALSE;
            bossheart -= 10;
        }
    }
}
//보스 총알충돌
void playerbossfall() {
    int i;
    for (i = 0; i < MAXBOSSBULLET; i++) {
        if (BossBullet[i].exist == FALSE)
            continue;
        if (BossBullet[i].y == newy && abs((BossBullet[i].x + 9) - newx) <= 10) {
            BossBullet[i].exist = FALSE;
            gotoxy(BossBullet[i].x + 6, BossBullet[i].y);
            printf("            ");
            heart--;
            p = 0;
        }
    }
}


//아이템
void showitem() {
    int x, y;
    x = 7 + rand() % 40;
    y = 4;
    textcolor(YELLOW2, BLACK);
    gotoxy(x, y);
    printf(ITEM);
    items[x][y] = 1;
    items_count++;
    textcolor(YELLOW2, BLACK);
}
void moveitem() {
    int x, y, dx, dy, nx, ny;
    int newitems[WIDTH][HEIGHT] = { 0 };


    // gold 수가 없을 수 있다.
    if (items_count == 0)
        return;
    for (x = 0; x < WIDTH - 2; x++) {
        for (y = 0; y < HEIGHT; y++) {
            if (items[x][y]) {
                dx = rand() % 3 - 1; // -1 0 1
                dy = 1;
                nx = x + dx;
                ny = y + dy;
                if (nx == WIDTH - 5) nx = WIDTH - 6;
                if (nx < 7) nx = 8;
                if (ny < 1) ny = 1;
                if (ny > HEIGHT - 1) {
                    gotoxy(x, y);
                    printf("   ");
                    items_count--;
                }
                else {
                    gotoxy(x, y);
                    textcolor(YELLOW2, BLACK);
                    printf("   "); // erase gold
                    gotoxy(nx, ny);
                    printf(ITEM);
                    newitems[nx][ny] = 1; // 이동된 golds의 좌표
                    textcolor(YELLOW2, BLACK);
                }
            }
        }
    }
    memcpy(items, newitems, sizeof(newitems)); // 한번에 gold 위치를 조정한다.
}

void showboom() {
    int x, y;
    x = 7 + rand() % 40;
    y = 4;
    textcolor(YELLOW2, BLACK);
    gotoxy(x, y);
    printf(BOOM);
    boom[x][y] = 1;
    boom_count++;
    textcolor(YELLOW2, BLACK);
}
void moveboom() {
    int x, y, dx, dy, nx, ny;
    int newboom[WIDTH][HEIGHT] = { 0 };


    // gold 수가 없을 수 있다.
    if (boom_count == 0)
        return;
    for (x = 0; x < WIDTH - 2; x++) {
        for (y = 0; y < HEIGHT; y++) {
            if (boom[x][y]) {
                dx = rand() % 3 - 1; // -1 0 1
                dy = 1;
                nx = x + dx;
                ny = y + dy;
                if (nx == WIDTH - 5) nx = WIDTH - 6;
                if (nx < 7) nx = 8;
                if (ny < 1) ny = 1;
                if (ny > HEIGHT - 1) {
                    gotoxy(x, y);
                    printf("   ");
                    boom_count--;
                }
                else {
                    gotoxy(x, y);
                    textcolor(YELLOW2, BLACK);
                    printf("   "); // erase gold
                    gotoxy(nx, ny);
                    printf(BOOM);
                    newboom[nx][ny] = 1; // 이동된 golds의 좌표
                    textcolor(YELLOW2, BLACK);
                }
            }
        }
    }
    memcpy(boom, newboom, sizeof(newboom)); // 한번에 gold 위치를 조정한다.
}


void showtimeitem() {
    int x, y;
    x = 7 + rand() % 40;
    y = 4;
    textcolor(YELLOW2, BLACK);
    gotoxy(x, y);
    printf(TIME);
    timeitems[x][y] = 1;
    timeitems_count++;
    textcolor(YELLOW2, BLACK);
}
void movetimeitem() {
    int x, y, dx, dy, nx, ny;
    int newtimeitems[WIDTH][HEIGHT] = { 0 };


    // gold 수가 없을 수 있다.
    if (timeitems_count == 0)
        return;
    for (x = 0; x < WIDTH - 2; x++) {
        for (y = 0; y < HEIGHT; y++) {
            if (timeitems[x][y]) {
                dx = rand() % 3 - 1; // -1 0 1
                dy = 1;
                nx = x + dx;
                ny = y + dy;
                if (nx == WIDTH - 5) nx = WIDTH - 6;
                if (nx < 7) nx = 8;
                if (ny < 1) ny = 1;
                if (ny > HEIGHT - 1) {
                    gotoxy(x, y);
                    printf("   ");
                    timeitems_count--;
                }
                else {
                    gotoxy(x, y);
                    textcolor(YELLOW2, BLACK);
                    printf("   "); // erase gold
                    gotoxy(nx, ny);
                    printf(TIME);
                    newtimeitems[nx][ny] = 1; // 이동된 golds의 좌표
                    textcolor(YELLOW2, BLACK);
                }
            }
        }
    }
    memcpy(timeitems, newtimeitems, sizeof(newtimeitems)); // 한번에 gold 위치를 조정한다.
}



void showspeeditem() {
    int x, y;
    x = 7 + rand() % 40;
    y = 4;
    textcolor(YELLOW2, BLACK);
    gotoxy(x, y);
    printf(SPEEDITEM);
    speeditems[x][y] = 1;
    speeditems_count++;
    textcolor(YELLOW2, BLACK);
}
void movespeeditem() {
    int x, y, dx, dy, nx, ny;
    int newspeeditems[WIDTH][HEIGHT] = { 0 };


    // gold 수가 없을 수 있다.
    if (speeditems_count == 0)
        return;
    for (x = 0; x < WIDTH - 2; x++) {
        for (y = 0; y < HEIGHT; y++) {
            if (speeditems[x][y]) {
                dx = rand() % 3 - 1; // -1 0 1
                dy = 1;
                nx = x + dx;
                ny = y + dy;
                if (nx == WIDTH - 5) nx = WIDTH - 6;
                if (nx < 7) nx = 8;
                if (ny < 1) ny = 1;
                if (ny > HEIGHT - 1) {
                    gotoxy(x, y);
                    printf("   ");
                    speeditems_count--;
                }
                else {
                    gotoxy(x, y);
                    textcolor(YELLOW2, BLACK);
                    printf("   "); // erase gold
                    gotoxy(nx, ny);
                    printf(SPEEDITEM);
                    newspeeditems[nx][ny] = 1; // 이동된 golds의 좌표
                    textcolor(YELLOW2, BLACK);
                }
            }
        }
    }
    memcpy(speeditems, newspeeditems, sizeof(newspeeditems)); // 한번에 speed 위치를 조정한다.
}


void showspeed2item() {
    int x, y;
    x = 7 + rand() % 40;
    y = 4;
    textcolor(RED1, BLACK);
    gotoxy(x, y);
    printf(SPEEDITEM);
    speed2items[x][y] = 1;
    speed2items_count++;
    textcolor(RED1, BLACK);
}
void movespeed2item() {
    int x, y, dx, dy, nx, ny;
    int newspeed2items[WIDTH][HEIGHT] = { 0 };


    // gold 수가 없을 수 있다.
    if (speed2items_count == 0)
        return;
    for (x = 0; x < WIDTH - 2; x++) {
        for (y = 0; y < HEIGHT; y++) {
            if (speed2items[x][y]) {
                dx = rand() % 3 - 1; // -1 0 1
                dy = 1;
                nx = x + dx;
                ny = y + dy;
                if (nx == WIDTH - 5) nx = WIDTH - 6;
                if (nx < 7) nx = 8;
                if (ny < 1) ny = 1;
                if (ny > HEIGHT - 1) {
                    gotoxy(x, y);
                    printf("   ");
                    speed2items_count--;
                }
                else {
                    gotoxy(x, y);
                    textcolor(RED1, BLACK);
                    printf("   "); // erase gold
                    gotoxy(nx, ny);
                    printf(SPEEDITEM);
                    newspeed2items[nx][ny] = 1; // 이동된 golds의 좌표
                    textcolor(RED1, BLACK);
                }
            }
        }
    }
    memcpy(speed2items, newspeed2items, sizeof(newspeed2items)); // 한번에 speed 위치를 조정한다.
}


void powershow() {
    int x, y;
    x = 7 + rand() % 40;
    y = 4;
    textcolor(YELLOW2, BLACK);
    gotoxy(x, y);
    printf(POWERITEM);
    power[x][y] = 1;
    power_count++;
    textcolor(YELLOW2, BLACK);
}
void powermove() {
    int x, y, dx, dy, nx, ny;
    int newpoweritems[WIDTH][HEIGHT] = { 0 };

    if (power_count == 0)
        return;
    for (x = 0; x < WIDTH - 2; x++) {
        for (y = 0; y < HEIGHT; y++) {
            if (power[x][y]) {
                dx = rand() % 3 - 1; // -1 0 1
                dy = 1;
                nx = x + dx;
                ny = y + dy;
                if (nx == WIDTH - 5) nx = WIDTH - 6;
                if (nx < 7) nx = 8;
                if (ny < 1) ny = 1;
                if (ny > HEIGHT - 1) {
                    gotoxy(x, y);
                    printf("   ");
                    power_count--;
                }
                else {
                    gotoxy(x, y);
                    textcolor(YELLOW2, BLACK);
                    printf("   ");
                    gotoxy(nx, ny);
                    printf(POWERITEM);
                    newpoweritems[nx][ny] = 1;
                    textcolor(YELLOW2, BLACK);
                }
            }
        }
    }
    memcpy(power, newpoweritems, sizeof(newpoweritems)); // 한번에 위치를 조정한다.
}
void misileitem() {
    int x, y;
    x = 7 + rand() % 40;
    y = 4;
    textcolor(YELLOW2, BLACK);
    gotoxy(x, y);
    printf(MISILEITEM);
    misileitems[x][y] = 1;
    misileitems_count++;
    textcolor(YELLOW2, BLACK);
}
void misileitemmove() {
    int x, y, dx, dy, nx, ny;
    int newmisileitem[WIDTH][HEIGHT] = { 0 };
    // gold 수가 없을 수 있다.
    if (misileitems_count == 0)
        return;
    for (x = 0; x < WIDTH - 2; x++) {
        for (y = 0; y < HEIGHT; y++) {
            if (misileitems[x][y]) {
                dx = rand() % 3 - 1; // -1 0 1
                dy = 1;
                nx = x + dx;
                ny = y + dy;
                if (nx == WIDTH - 5) nx = WIDTH - 6;
                if (nx < 7) nx = 8;
                if (ny < 1) ny = 1;
                if (ny > HEIGHT - 1) {
                    gotoxy(x, y);
                    printf("   ");
                    misileitems_count--;
                }
                else {
                    gotoxy(x, y);
                    textcolor(YELLOW2, BLACK);
                    printf("   ");
                    gotoxy(nx, ny);
                    printf(MISILEITEM);
                    newmisileitem[nx][ny] = 1; // 이동된 misile item 좌표
                    textcolor(YELLOW2, BLACK);
                }
            }
        }
    }
    memcpy(misileitems, newmisileitem, sizeof(newmisileitem)); // 한번에 위치를 조정한다.
}

// 미니 몬스터
void miniMostershow() {
    int j;
    int randomX = rand() % 30 + 6;
    int randomY = rand() % 15 + 6;

    for (j = 0; j < MAXMINIMOSTER && miniMonster[j].exist == TRUE; j++) {}
    if (j != MAXMINIMOSTER) {
        miniMonster[j].x = randomX;
        miniMonster[j].y = randomY;
        miniMonster[j].exist = TRUE;
    }
}
void miniMosterdraw(int i) {
    textcolor(BLUE1, BLACK);
    gotoxy(miniMonster[i].x, miniMonster[i].y);
    printf("@");
}
void miniMonstererase(int i) {
    gotoxy(miniMonster[i].x, miniMonster[i].y);
    printf(" ");
}
void miniMonsterMove() {
    int random;
    random = 1;
    for (int i = 0; i < MAXMINIMOSTER; i++) {
        if (miniMonster[i].exist == TRUE) {
            miniMonstererase(i);
            if (miniMonster[i].y > HEIGHT - 3) {
                miniMonster[i].exist = FALSE;
            }
            else {
                if (random) {
                    if (miniMonster[i].x <= newx)
                        miniMonster[i].x++;
                    else
                        miniMonster[i].x--;
                    if (miniMonster[i].y <= newy)
                        miniMonster[i].y++;
                    else
                        miniMonster[i].y--;
                }
                miniMosterdraw(i);
            }
        }
    }
}// 미니 몬스터

//보스
void bossdraw(int x, int y) {

    int color3 = rand() % 15 + 1;
    textcolor(color3, BLACK);

    gotoxy(x, y);
    printf("    ■            ■    \n");
    gotoxy(x, y + 1);
    printf("      ■        ■      \n");
    gotoxy(x, y + 2);
    printf("     ■■■■■■■     \n");
    gotoxy(x, y + 3);
    printf("    ■  ■■■■  ■    \n");
    gotoxy(x, y + 4);
    printf("  ■■  ■■■■  ■■  \n");
    gotoxy(x, y + 5);
    printf("■■■■■■■■■■■■\n");
    gotoxy(x, y + 6);
    printf("■  ■■■■■■■■  ■\n");
    gotoxy(x, y + 7);
    printf("■  ■            ■  ■\n");
    gotoxy(x, y + 8);
    printf("      ■■    ■■     \n");
}

void bosserase(int x, int y) {
    gotoxy(x, y - 1);
    printf("                        \n");
    gotoxy(x, y);
    printf("                        \n");
    gotoxy(x, y + 1);
    printf("                        \n");
    gotoxy(x, y + 2);
    printf("                        \n");
    gotoxy(x, y + 3);
    printf("                        \n");
    gotoxy(x, y + 4);
    printf("                        \n");
    gotoxy(x, y + 5);
    printf("                        \n");
    gotoxy(x, y + 6);
    printf("                        \n");
    gotoxy(x, y + 7);
    printf("                        \n");
    gotoxy(x, y + 8);
    printf("                        \n");
    gotoxy(x, y + 9);
    printf("                        \n");

}
//보스 총알
void BossBulleterase(int b) {
    gotoxy(BossBullet[b].x + 6, BossBullet[b].y);
    printf("              ");
}
void BossBulletdraw(int b) {
    textcolor(GREEN1, BLACK);
    gotoxy(BossBullet[b].x + 6, BossBullet[b].y);
    printf("▦▦ * * ▦▦");
}
void bossbulletmove() {
    int b;
    int random = rand() % MAXBOSSBULLET;
    int rm = rand() % 3 - 1;
    for (b = 0; b < MAXBOSSBULLET; b++) {
        if (BossBullet[b].exist == TRUE) {
            BossBulleterase(b);
            if (BossBullet[b].y > HEIGHT - 3) {
                BossBullet[b].exist = FALSE;
            }
            else {
                BossBullet[b].y++;
                BossBulletdraw(b);
            }
        }
    }
}
void bossbulletshow() {
    int k;
    for (k = 0; k < MAXBOSSBULLET && BossBullet[k].exist == TRUE; k++) {}
    if (k != MAXBOSSBULLET) {
        BossBullet[k].x = bossx;
        BossBullet[k].y = bossy + 9;
        BossBullet[k].exist = TRUE;
    }
}



//박스 그리기
void draw_box1(int x1, int y1, int x2, int y2, char* ch)
{
    int x, y;
    //완성할것
    for (x = x1; x <= x2; x += 2) {
        gotoxy(x, y1);
        printf("%s", ch);
    }
    for (x = x1; x <= x2; x += 2) {
        gotoxy(x, y2);
        printf("%s", ch);
    }
    for (y = y1; y <= y2; y++) {
        gotoxy(x1, y);
        printf("%s", ch);
    }
    for (y = y1; y <= y2; y++) {
        gotoxy(x2, y);
        printf("%s", ch);
    }
}
void draw_box2(int x1, int y1, int x2, int y2)
{
    int x, y;
    //int len = strlen(ch);
    for (x = x1; x <= x2; x += 2) { // 한글은 2칸씩 차지한다.
        gotoxy(x, y1);
        printf("%s", "─"); // ㅂ 누르고 한자키 누르고 선택
        gotoxy(x, y2);
        printf("%s", "─");
    }
    for (y = y1; y <= y2; y++) {
        gotoxy(x1, y);
        printf("%s", "│");
        gotoxy(x2, y);
        printf("%s", "│");
    }
    gotoxy(x1, y1); printf("┌");
    gotoxy(x1, y2); printf("└");
    gotoxy(x2, y1); printf("┐");
    gotoxy(x2, y2); printf("┘");
}
void draw_box2_fill(int x1, int y1, int x2, int y2, int color)
{
    int x, y;
    for (y = y1 + 1; y < y2; y++) {
        for (x = x1 + 2; x < x2; x++) {
            textcolor(color, color);
            gotoxy(x, y);
            printf(" ");
        }
    }

}
//시간 출력
void show_time(int remain_time)
{
    textcolor(YELLOW2, BLACK);
    gotoxy(66, 6);
    printf("남은시간: %3d", remain_time);
    //textcolor(BLACK, WHITE);
}
// 기본정보
void info() {

    textcolor(YELLOW2, BLACK);
    gotoxy(68, 14); printf("점수:      ");
    gotoxy(68, 14); printf("점수: %d", score);


    if (heart >= 4) {

        //heart = 4;
        gotoxy(69, 22); printf("       ");
        gotoxy(69, 22); printf("♥♥♥♥");
    }
    else if (heart == 3) {
        gotoxy(69, 22); printf("        ");
        gotoxy(69, 22); printf("♥♥♥");
    }
    else if (heart == 2) {
        gotoxy(69, 22); printf("        ");
        gotoxy(69, 22); printf("♥♥");
    }
    else if (heart == 1) {
        gotoxy(69, 22); printf("        ");
        gotoxy(69, 22); printf("♥");
    }
    else {
        gotoxy(69, 22);
        printf("  ");
    }
}

//게임 초기화 함수
void init_game() {
    int x, y;
    srand(time(NULL));
    called = 0;
    for (x = 0; x < WIDTH - 2; x++) {
        for (y = 0; y < HEIGHT; y++) {
            items[x][y] = 0;
            speeditems[x][y] = 0;
            power[x][y] = 0;
            misileitems[x][y] = 0;
            timeitems[x][y] = 0;
            speed2items[x][y] = 0;
            boom[x][y] = 0;
        }
    }
    for (x = 0; x < MAXENEMYBULLET; x++)
        EnemyBullet[x].exist = FALSE;
    for (x = 0; x < MAXENEMY; x++)
        Enemy[x].exist = FALSE;
    for (x = 0; x < MAXENEMY2BULLET; x++)
        Enemy2Bullet[x].exist = FALSE;
    for (x = 0; x < MAXENEMY2; x++)
        Enemy2[x].exist = FALSE;
    for (x = 0; x < MAXBULLET; x++)
        Bullet[x].exist = FALSE;
    for (x = 0; x < MAXBOSSBULLET; x++)
        BossBullet[x].exist = FALSE;
    for (x = 0; x < MAXMISILE; x++)
        Misile[x].exist = FALSE;
    for (x = 0; x < MAXMINIMOSTER; x++)
        miniMonster[x].exist = FALSE;

    newx = 30;
    newy = 45;
    keep_moving = 1, misile = 0;
    time_out = 60;
    heart = 4;
    speedupem = 10;
    bossheart = 180, called = 0, score = 0, p = 0;
    p1_frame_sync = 4, bullet_frame_sync = 3.5;
    enemybullet_frame_sync = 9;
    enemybulletuse = 1;
    boss_frame_sync = 15;
    bossbullet_frame_sync = 8;
    enemy2bullet_frame_sync = 2;// 적2 총알 속도

    removeCursor();
}


#define MAX_PLAYERS 1000 // 최대 플레이어 수(점수판)
#define MAX_NAME_LENGTH 20 // 플레이어 이름 최대 길이(점수판)
char playerName[MAX_NAME_LENGTH];// 플레이어 이름(점수판)

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
} Player;

Player players[MAX_PLAYERS];
int numPlayers = 0;

//플레이어 점수 저장
void savePlayerScore(const char* name, int score) {
    FILE* file = fopen("scores.txt", "a");
    if (file == NULL) {
        gotoxy(15, 20);
        printf("점수 파일을 열 수 없습니다.");
        return;
    }
    fprintf(file, "%s %d\n", name, score);
    fclose(file);
}
//플레이어 점수 로드
void loadPlayerScores() {
    FILE* file = fopen("scores.txt", "r");
    if (file == NULL) {
        gotoxy(15, 20);
        printf("점수 파일을 열 수 없습니다.");
        return;
    }
    numPlayers = 0;
    while (fscanf(file, "%s %d", players[numPlayers].name, &players[numPlayers].score) == 2) {
        numPlayers++;
        if (numPlayers >= MAX_PLAYERS)
            break;
    }
    fclose(file);
}
void showPlayerScores() {
    textcolor(YELLOW1, BLACK);
    draw_box2(10, 20, 50, 40); // 작은 틀
    // 플레이어 점수를 기준으로 내림차순 정렬
    for (int i = 0; i < numPlayers - 1; i++) {
        for (int j = i + 1; j < numPlayers; j++) {
            if (players[i].score < players[j].score) {
                Player temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }
    // 상위 7명의 기록 출력
    int count = 0;
    int k = 0;
    textcolor(WHITE, BLACK);
    for (int i = 0; i < numPlayers && count < 7; i++) {
        gotoxy(20, 26 + k);
        printf("\t%s \t %d", players[i].name, players[i].score);
        count++;
        k += 2;
    }
}

void loose() {
    textcolor(YELLOW1, BLACK);
    draw_box2(2, 2, 60, 50);//작은 틀
    int c1, c2, c3;
    do {
        c1 = rand() % 16;
        c2 = rand() % 16;
    } while (c1 == c2);
    c3 = rand() % 15 + 1;
    textcolor(c3, BLACK);
    gotoxy(10, 6);
    printf(" ■         ◆■◆    ◆■■  ◆■■*    ■   ");
    gotoxy(10, 7);
    printf(" ■        ■    ■  ■       ■         ■   ");
    gotoxy(10, 8);
    printf(" ■        ■    ■   ■■◆  ■■■■   ■   ");
    gotoxy(10, 9);
    printf(" ■        ■    ■        ■ ■              ");
    gotoxy(10, 10);
    printf(" ◆■■■   ◆■◆    ■■◆  ◆■■■   ◆   ");
    textcolor(c1, c2);
    gotoxy(25, 16);
    printf("**게임 오버**");
    gotoxy(17, 17);
    textcolor(WHITE, BLACK);
    printf("Hit (R) to Restart (Q) to Quit");

    Sleep(300);
}

void win() {
    textcolor(YELLOW1, BLACK);
    draw_box2(2, 2, 60, 50);//작은 틀
    int c1, c2, c3;
    do {
        c1 = rand() % 16;
        c2 = rand() % 16;
    } while (c1 == c2);
    c3 = rand() % 15 + 1;
    textcolor(c3, BLACK);
    gotoxy(10, 6);
    printf("  ◆      ◆*     ◆  ■■■   ◆■■■   ■  ");
    gotoxy(10, 7);
    printf("   ◆    ◆◆    ◆     ■     ■    ■   ■  ");
    gotoxy(10, 8);
    printf("    ◆  ◆  ◆  ◆      ■     ■    ■   ■  ");
    gotoxy(10, 9);
    printf("     ◆◆    ◆◆       ■     ■    ■       ");
    gotoxy(10, 10);
    printf("      ◆      ◆      ■■■   ■    ■   ◆  ");
    textcolor(c1, c2);
    gotoxy(25, 16);
    printf("**게임 오버**");
    gotoxy(17, 17);
    textcolor(WHITE, BLACK);
    printf("Hit (R) to Restart (Q) to Quit");

    Sleep(300);
}

//스테이지 1
void stage1() {

START:
    init_game();
    //int heart = 4;
    unsigned char ch;
    int run_time, start_time;
    int enemy_time = 0;
    int enemy2_time = 0;
    int enemybullettime = 0;
    int enemy2bullettime = 0;
    int miniMonster_time = 0;
    int items_time = 0;
    int boom_time = 0;
    int timeitems_time = 0;
    int speedupemtime = 0;
    int speeditems_time = 0;
    int speed2items_time = 0;
    int powertime = 0;
    int misiletime = 0;
    int i;

    draw_box2_fill(1, 1, 70, 55, BLACK);
    Sleep(500);
    system("cls"); //화면 지우기
    textcolor(YELLOW1, BLACK);
    draw_box2(0, 1, 84, 51);//큰틀
    draw_box2(2, 2, 60, 50);//작은 틀
    draw_box1(63, 3, 81, 9, "▩");//오른쪽 첫번째틀
    draw_box1(63, 11, 81, 17, "▩");//오른쪽 두번째틀
    draw_box1(63, 19, 81, 25, "▩");//오른쪽 세번째틀
    draw_box1(63, 27, 81, 33, "▩");//오른쪽 네번째틀
    textcolor(YELLOW2, BLACK);
    gotoxy(69, 14);

    textcolor(WHITE, BLACK);
    PlaySound(TEXT("GameStartMusic.wav"), NULL, SND_ASYNC);//음악 일반 재생
    gotoxy(25, 20);
    printf("PLAYER 1");
    Sleep(2300);
    gotoxy(25, 20);
    printf("STAGE 1  ");
    Sleep(2300);
    gotoxy(25, 18);
    printf("PLAYER 1");
    Sleep(2300);
    gotoxy(25, 20);
    printf("        ");;
    gotoxy(25, 18);
    printf("          ");


    textcolor(YELLOW2, BLACK);
    gotoxy(70, 30);
    printf("STAGE 1");
    textcolor(YELLOW1, BLACK);
    start_time = time(NULL);
    last_remain_time = remain_time = time_out;
    show_time(remain_time);
    while (1) {
        info();
        Enemyfall();
        playerfall();
        if (heart <= 0) {
            break;
        }
        run_time = time(NULL) - start_time;
        remain_time = time_out - run_time;

        if (remain_time < last_remain_time) {
            show_time(remain_time); // 시간이 변할때만 출력
            last_remain_time = remain_time;
        }
        if (remain_time == 0) { // 시간 종료
            //time_out += 10;
            //stage2();
            break;
        }
        if (run_time > speedupemtime && (run_time % speedupem == 0)) {
            if (enemybullet_frame_sync > 5)//10초마다 적의 총알 속도가 빨라짐
                enemybullet_frame_sync--;
            speedupemtime = run_time;
        }
        if (run_time > items_time && (run_time % items_use == 0)) {
            showitem();//x초마다 목숨아이템생성
            items_time = run_time; // 마지막 item 표시 시간 기억
        }
        if (run_time > boom_time && (run_time % boom_use == 0)) {
            showboom();//x초마다 총알 전멸생성
            boom_time = run_time; // 마지막 item 표시 시간 기억
        }
        if (run_time > misiletime && (run_time % misileitems_use == 0)) {
            misileitem();//x초마다 미사일아이템생성
            misiletime = run_time; // 마지막 item 표시 시간 기억
        }
        if (run_time > speeditems_time && (run_time % speeditems_use == 0)) {
            showspeeditem();//x초마다 플레이어 스피드아이템생성
            speeditems_time = run_time; // 마지막 speeditem 표시 시간 기억
        }
        if (run_time > speed2items_time && (run_time % speed2items_use == 0)) {
            showspeed2item();//x초마다 적 스피드아이템생성
            speed2items_time = run_time; // 마지막 speeditem 표시 시간 기억
        }
        if (run_time > powertime && (run_time % power_use == 0)) {
            powershow();// 갤러그아이템출력
            powertime = run_time;
        }
        if (run_time > timeitems_time && (run_time % timeitems_use == 0)) {
            showtimeitem();//x초마다 타임 아이템생성
            timeitems_time = run_time; // 마지막 item 표시 시간 기억
        }
        if (run_time > enemy_time && (run_time % enemyuse == 0)) {
            showenemy();//1초마다 적 생산
            enemy_time = run_time; // 마지막 item 표시 시간 기억
        }

        if (run_time > enemybullettime && (run_time % enemybulletuse == 0)) {
            EnemyBulletshow();//1초마다 적 총알 출력
            enemybullettime = run_time;
        }

        if (remain_time < 30) {// 제한 시간 35남으면 적 2 출력
            if (run_time > enemy2_time && (run_time % enemy2use == 0)) {
                showenemy2();;//5초마다 적2 생산
                enemy2_time = run_time; // 마지막 item 표시 시간 기억
            }
        }

        if (run_time > enemy2bullettime && (run_time % enemy2bulletuse == 0)) {
            Enemy2Bulletshow();//1초마다 적2 총알 출력
            enemy2bullettime = run_time;
        }

        if (kbhit() == 1) {  // 키보드가 눌려져 있으면
            ch = getch(); // key 값을 읽는다
            if (ch == SPECIAL1 || ch == SPECIAL2) { // 만약 특수키
                // 예를 들어 UP key의 경우 0xe0 0x48 두개의 문자가 들어온다.
                ch = getch();
                // Player1은 방향키로 움직인다.
                switch (ch) {
                case UP:
                case DOWN:
                case LEFT:
                case RIGHT:
                    playermove(ch);
                    if (frame_count % p1_frame_sync == 0)
                        playermove(0);
                    break;
                default: // 방향 전환이 아니면
                    if (frame_count % p1_frame_sync == 0)
                        playermove(0);
                }
            }
            if (ch == SPACE) {
                for (i = 0; i < MAXBULLET && Bullet[i].exist == TRUE; i++) {}
                if (i != MAXBULLET) {
                    PlaySound(TEXT("Shot.wav"), NULL, SND_ASYNC);//음악 일반 재생
                    Bullet[i].x = newx + 1;
                    Bullet[i].y = newy - 1;
                    Bullet[i].exist = TRUE;
                }
            }
            if (ch == 'd') {
                if (misile != 0) {
                    for (i = 0; i < MAXMISILE && Misile[i].exist == TRUE; i++) {}
                    if (i != MAXMISILE) {
                        PlaySound(TEXT("missile.wav"), NULL, SND_ASYNC);//음악 일반 재생
                        Misile[i].x = newx + 1;
                        Misile[i].y = newy - 1;
                        Misile[i].exist = TRUE;
                        misile--;
                    }
                }
            }
            if (ch == 'h') {
                PlaySound(TEXT("coin.wav"), NULL, SND_ASYNC);//음악 일반 재생
                heart++;
            }
        }
        else {
            // keyboard 가 눌려지지 않으면 계속 움직인다.
            // 이동중이던 방향으로 계속 이동
            if (frame_count % p1_frame_sync == 0)
                playermove(0);
        }

        if (frame_count % bullet_frame_sync == 0)
            bulletmove();

        if (frame_count % misile_frame_sync == 0) {
            textcolor(YELLOW2, BLACK);
            misilemove();
        }
        if (frame_count % enemy_frame_sync == 0) {
            textcolor(RED2, BLACK);
            Enemymove();
        }
        if (frame_count % enemy2_frame_sync == 0) {
            textcolor(BLUE2, BLACK);
            Enemy2move();
        }
        if (frame_count % enemybullet_frame_sync == 0) {
            EnemyBulletMove();
        }
        if (frame_count % enemy2bullet_frame_sync == 0) {
            Enemy2BulletMove();
        }
        if (frame_count % item_frame_sync == 0)
            moveitem();
        if (frame_count % item_frame_sync == 0)
            moveboom();
        if (frame_count % item_frame_sync == 0)
            movetimeitem();
        if (frame_count % item_frame_sync == 0)
            movespeeditem();
        if (frame_count % item_frame_sync == 0)
            movespeed2item();
        if (frame_count % item_frame_sync == 0)
            powermove();
        if (frame_count % item_frame_sync == 0)
            misileitemmove();
        Sleep(Delay); // Delay 값을 줄이고
        frame_count++;// frame_count 값으로 속도 조절을 한다.
    }
    if (heart <= 0) {
        system("cls"); //화면 지우기
        PlaySound(TEXT("loose.wav"), NULL, SND_ASYNC);//음악 일반 재생
        // 게임이 끝나면 플레이어 이름과 점수 출력 및 저장
        gotoxy(18, 23);
        printf("player : %s   ", playerName);
        printf("score : %d", score);
        savePlayerScore(playerName, score);

        // 이전 플레이어 기록 출력
        gotoxy(10, 10);
        loadPlayerScores();
        showPlayerScores();
        while (1) {
            loose();
            if (kbhit()) {
                ch = getch();
                if (ch == 'r' || ch == 'q')
                    break;
            }
        }
        if (ch == 'r')
            goto START;
        if (ch == 'q')
            exit(0);
    }
    /////////////////////////////////////////////////////////////////////////////////////////
    //stage 2
    /////////////////////////////////////////////////////////////////////////////////////////

    draw_box2_fill(1, 1, 61, 51, YELLOW1);
    Sleep(500);
    //system("cls"); //화면 지우기
    cls(BLACK, YELLOW1);
    //Sleep(5000);

    textcolor(YELLOW1, BLACK);
    draw_box2(0, 1, 84, 51);//큰틀
    draw_box2(2, 2, 60, 50);//작은 틀
    draw_box1(63, 3, 81, 9, "▩");//오른쪽 첫번째틀
    draw_box1(63, 11, 81, 17, "▩");//오른쪽 두번째틀
    draw_box1(63, 19, 81, 25, "▩");//오른쪽 세번째틀
    draw_box1(63, 27, 81, 33, "▩");//오른쪽 네번째틀

    textcolor(WHITE, BLACK);
    PlaySound(TEXT("GameStartMusic.wav"), NULL, SND_ASYNC);//음악 일반 재생
    gotoxy(25, 20);
    printf("PLAYER 1");
    Sleep(2300);
    gotoxy(25, 20);
    printf("STAGE 2  ");
    Sleep(2300);
    gotoxy(25, 18);
    printf("PLAYER 1");
    Sleep(2300);
    gotoxy(25, 20);
    printf("        ");;
    gotoxy(25, 18);
    printf("         ");
    textcolor(YELLOW2, BLACK);
    gotoxy(69, 14);
    printf("STAGE 2");

    int x, y;
    //srand(time(NULL));
    called = 0;
    for (x = 0; x < WIDTH - 2; x++) {
        for (y = 0; y < HEIGHT; y++) {
            items[x][y] = 0;
            speeditems[x][y] = 0;
            power[x][y] = 0;
            misileitems[x][y] = 0;
            timeitems[x][y] = 0;
            speed2items[x][y] = 0;
            boom[x][y] = 0;
        }
    }
    for (x = 0; x < MAXENEMYBULLET; x++)
        EnemyBullet[x].exist = FALSE;
    for (x = 0; x < MAXENEMY; x++)
        Enemy[x].exist = FALSE;
    for (x = 0; x < MAXENEMY2BULLET; x++)
        Enemy2Bullet[x].exist = FALSE;
    for (x = 0; x < MAXENEMY2; x++)
        Enemy2[x].exist = FALSE;
    for (x = 0; x < MAXBULLET; x++)
        Bullet[x].exist = FALSE;
    for (x = 0; x < MAXBOSSBULLET; x++)
        BossBullet[x].exist = FALSE;
    for (x = 0; x < MAXMISILE; x++)
        Misile[x].exist = FALSE;
    for (x = 0; x < MAXMINIMOSTER; x++)
        miniMonster[x].exist = FALSE;

    p1_frame_sync = 4; //플레이어의 이동속도
    bullet_frame_sync = 3.5;// 플레이어 총알속도
    enemy_frame_sync = 8;//적 움직임 속도
    enemy2_frame_sync = 4;//적2 움직임 속도
    miniMonster_frame_sync = 14;//미니 몬스터 속도
    enemybullet_frame_sync = 9;// 적 총알 속도
    enemy2bullet_frame_sync = 2;// 적2 총알 속도
    item_frame_sync = 10;//아이템 움직이는 속도

    enemy_time = 0;
    enemy2_time = 0;
    enemybullettime = 0;
    enemy2bullettime = 0;
    miniMonster_time = 0;
    items_time = 0;
    boom_time = 0;
    misiletime = 0;
    speeditems_time = 0;
    speed2items_time = 0;
    speedupemtime = 0;
    powertime = 0;
    powertime = 0;
    timeitems_time = 0;

    time_out = 60;

    textcolor(YELLOW2, BLACK);
    gotoxy(70, 30);
    printf("STAGE 2");
    textcolor(YELLOW1, BLACK);
    start_time = time(NULL);
    last_remain_time = remain_time = time_out;
    show_time(remain_time);
    while (1) {
        info();
        Enemyfall();
        playerfall();
        if (heart <= 0) {
            break;
        }
        run_time = time(NULL) - start_time;
        remain_time = time_out - run_time;

        if (remain_time < last_remain_time) {
            show_time(remain_time); // 시간이 변할때만 출력
            last_remain_time = remain_time;
        }
        if (remain_time == 0) { // 시간 종료
            break;
        }
        if (run_time > items_time && (run_time % items_use == 0)) {
            showitem();//x초마다 목숨아이템생성
            items_time = run_time; // 마지막 item 표시 시간 기억
        }
        if (run_time > boom_time && (run_time % boom_use == 0)) {
            showboom();//x초마다 총알 전멸생성
            boom_time = run_time; // 마지막 item 표시 시간 기억
        }
        if (run_time > speedupemtime && (run_time % speedupem == 0)) {
            if (enemybullet_frame_sync > 5)//10초마다 적의 총알 속도가 빨라짐
                enemybullet_frame_sync--;
            speedupemtime = run_time;
        }
        if (run_time > misiletime && (run_time % misileitems_use == 0)) {
            misileitem();//x초마다 미사일아이템생성
            misiletime = run_time; // 마지막 item 표시 시간 기억
        }
        if (run_time > speeditems_time && (run_time % speeditems_use == 0)) {
            showspeeditem();//x초마다 플레이어 스피드아이템생성
            speeditems_time = run_time; // 마지막 speeditem 표시 시간 기억
        }
        if (run_time > speed2items_time && (run_time % speed2items_use == 0)) {
            showspeed2item();//x초마다 적 스피드아이템생성
            speed2items_time = run_time; // 마지막 speeditem 표시 시간 기억
        }

        if (run_time > powertime && (run_time % power_use == 0)) {
            powershow();// 갤러그아이템출력
            powertime = run_time;
        }
        if (run_time > timeitems_time && (run_time % timeitems_use == 0)) {
            showtimeitem();//x초마다 타임 아이템생성
            timeitems_time = run_time; // 마지막 item 표시 시간 기억
        }

        if (run_time > enemy_time && (run_time % enemyuse == 0)) {
            showenemy();//1초마다 적 생산
            enemy_time = run_time; // 마지막 item 표시 시간 기억
        }

        if (run_time > enemybullettime && (run_time % enemybulletuse == 0)) {
            EnemyBulletshow();//1초마다 적 총알 출력
            enemybullettime = run_time;
        }

        if (run_time > enemy2bullettime && (run_time % enemy2bulletuse == 0)) {
            Enemy2Bulletshow();//1초마다 적2 총알 출력
            enemy2bullettime = run_time;
        }

        if (remain_time < 60) {// 제한 시간 10남으면 미니몬스터 출력
            if (run_time > miniMonster_time && (run_time % miniMonsteruse == 0)) {
                miniMostershow();//1초마다 적 총알 출력
                miniMonster_time = run_time;
            }
        }

        if (remain_time < 100) {// 제한 시간 35남으면 적 2 출력
            if (run_time > enemy2_time && (run_time % enemy2use == 0)) {
                showenemy2();;//5초마다 적2 생산
                enemy2_time = run_time; // 마지막 item 표시 시간 기억
            }
        }

        if (kbhit() == 1) {  // 키보드가 눌려져 있으면
            ch = getch(); // key 값을 읽는다
            if (ch == SPECIAL1 || ch == SPECIAL2) { // 만약 특수키
                // 예를 들어 UP key의 경우 0xe0 0x48 두개의 문자가 들어온다.
                ch = getch();
                // Player1은 방향키로 움직인다.
                switch (ch) {
                case UP:
                case DOWN:
                case LEFT:
                case RIGHT:
                    playermove(ch);
                    if (frame_count % p1_frame_sync == 0)
                        playermove(0);
                    break;
                default: // 방향 전환이 아니면
                    if (frame_count % p1_frame_sync == 0)
                        playermove(0);
                }
            }
            if (ch == SPACE) {
                for (i = 0; i < MAXBULLET && Bullet[i].exist == TRUE; i++) {}
                if (i != MAXBULLET) {
                    PlaySound(TEXT("Shot.wav"), NULL, SND_ASYNC);//음악 일반 재생
                    Bullet[i].x = newx + 1;
                    Bullet[i].y = newy - 1;
                    Bullet[i].exist = TRUE;
                }
            }
            if (ch == 'd') {
                if (misile != 0) {
                    for (i = 0; i < MAXMISILE && Misile[i].exist == TRUE; i++) {}
                    if (i != MAXMISILE) {
                        PlaySound(TEXT("missile.wav"), NULL, SND_ASYNC);//음악 일반 재생
                        Misile[i].x = newx + 1;
                        Misile[i].y = newy - 1;
                        Misile[i].exist = TRUE;
                        misile--;
                    }
                }
            }
            if (ch == 'h') {
                PlaySound(TEXT("coin.wav"), NULL, SND_ASYNC);//음악 일반 재생
                heart++;
            }
        }
        else {
            // keyboard 가 눌려지지 않으면 계속 움직인다.
            // 이동중이던 방향으로 계속 이동
            if (frame_count % p1_frame_sync == 0)
                playermove(0);
        }

        if (frame_count % miniMonster_frame_sync == 0) {
            miniMonsterMove();
        }
        if (frame_count % bullet_frame_sync == 0)
            bulletmove();

        if (frame_count % misile_frame_sync == 0) {
            textcolor(YELLOW2, BLACK);
            misilemove();
        }
        if (frame_count % enemy_frame_sync == 0) {
            textcolor(RED2, BLACK);
            Enemymove();
        }
        if (frame_count % enemy2_frame_sync == 0) {
            textcolor(BLUE2, BLACK);
            Enemy2move();
        }
        if (frame_count % enemybullet_frame_sync == 0) {
            EnemyBulletMove2();
        }
        if (frame_count % enemy2bullet_frame_sync == 0) {
            Enemy2BulletMove();
        }
        if (frame_count % item_frame_sync == 0)
            moveitem();
        if (frame_count % item_frame_sync == 0)
            moveboom();
        if (frame_count % item_frame_sync == 0)
            movetimeitem();
        if (frame_count % item_frame_sync == 0)
            movespeeditem();
        if (frame_count % item_frame_sync == 0)
            movespeed2item();
        if (frame_count % item_frame_sync == 0)
            powermove();
        if (frame_count % item_frame_sync == 0)
            misileitemmove();
        Sleep(Delay); // Delay 값을 줄이고
        frame_count++;// frame_count 값으로 속도 조절을 한다.
    }
    if (heart <= 0) {
        system("cls"); //화면 지우기
        PlaySound(TEXT("loose.wav"), NULL, SND_ASYNC);//음악 일반 재생
        // 게임이 끝나면 플레이어 이름과 점수 출력 및 저장
        gotoxy(18, 23);
        printf("player : %s   ", playerName);
        printf("score : %d", score);
        savePlayerScore(playerName, score);

        // 이전 플레이어 기록 출력
        gotoxy(10, 10);
        loadPlayerScores();
        showPlayerScores();
        while (1) {
            loose();
            if (kbhit()) {
                ch = getch();
                if (ch == 'r' || ch == 'q')
                    break;
            }
        }
        if (ch == 'r')
            goto START;
        if (ch == 'q')
            exit(0);
    }

    ///////////////////////////////////////////////////////////////////////////
    /////stage BOSS!
    ///////////////////////////////////////////////////////////////////////////
    draw_box2_fill(1, 1, 61, 51, YELLOW1);
    Sleep(500);
    //system("cls"); //화면 지우기
    cls(BLACK, YELLOW1);
    //Sleep(5000);

    textcolor(YELLOW1, BLACK);
    draw_box2(0, 1, 84, 51);//큰틀
    draw_box2(2, 2, 60, 50);//작은 틀
    draw_box1(63, 3, 81, 9, "▩");//오른쪽 첫번째틀
    draw_box1(63, 11, 81, 17, "▩");//오른쪽 두번째틀
    draw_box1(63, 19, 81, 25, "▩");//오른쪽 세번째틀
    draw_box1(63, 27, 81, 33, "▩");//오른쪽 네번째틀


    textcolor(WHITE, BLACK);
    PlaySound(TEXT("GameStartMusic.wav"), NULL, SND_ASYNC);//음악 일반 재생
    gotoxy(25, 20);
    printf("PLAYER 1");
    Sleep(2300);
    gotoxy(23, 20);
    printf("STAGE BOSS  ");
    Sleep(2300);
    gotoxy(23, 18);
    printf("  PLAYER 1");
    Sleep(2300);
    gotoxy(23, 20);
    printf("          ");;
    gotoxy(23, 18);
    printf("          ");
    textcolor(YELLOW2, BLACK);
    gotoxy(67, 30);
    printf("STAGE BOSS");

    srand(time(NULL));
    called = 0;
    for (x = 0; x < WIDTH - 2; x++) {
        for (y = 0; y < HEIGHT; y++) {
            items[x][y] = 0;
            speeditems[x][y] = 0;
            power[x][y] = 0;
            misileitems[x][y] = 0;
            timeitems[x][y] = 0;
            speed2items[x][y] = 0;
            boom[x][y] = 0;
        }
    }
    for (x = 0; x < MAXENEMYBULLET; x++)
        EnemyBullet[x].exist = FALSE;
    for (x = 0; x < MAXENEMY; x++)
        Enemy[x].exist = FALSE;
    for (x = 0; x < MAXENEMY2BULLET; x++)
        Enemy2Bullet[x].exist = FALSE;
    for (x = 0; x < MAXENEMY2; x++)
        Enemy2[x].exist = FALSE;
    for (x = 0; x < MAXBULLET; x++)
        Bullet[x].exist = FALSE;
    for (x = 0; x < MAXBOSSBULLET; x++)
        BossBullet[x].exist = FALSE;
    for (x = 0; x < MAXMISILE; x++)
        Misile[x].exist = FALSE;
    for (x = 0; x < MAXMINIMOSTER; x++)
        miniMonster[x].exist = FALSE;

    int bossrun_time;
    int boss_start_time = 0;
    int boss_bulletshow = 0;
    p1_frame_sync = 4; //플레이어의 이동속도
    bullet_frame_sync = 3.5;// 플레이어 총알속도

    start_time = time(NULL);
    last_remain_time = remain_time = time_out;
    show_time(remain_time);
    //보스 스테이지
    while (1) {
        textcolor(YELLOW2, BLACK);
        gotoxy(66, 6);
        printf("보스체력: %3d", bossheart);
        bossrun_time = time(NULL) - boss_start_time;
        info();
        bossfall();
        playerbossfall();
        Enemyfall();
        playerfall();

        if (heart <= 0) {
            break;
        }
        if (bossheart <= 0)
            break;

        if (bossrun_time > bossspeedup && (bossrun_time % bossspeedup == 0)) {
            if (boss_frame_sync > 10)//15초마다 보스의 속도가 빨라짐
                boss_frame_sync--;
            bossspeedup = bossrun_time;
        }
        if (bossrun_time > bossspeedup && (bossrun_time % bossspeedup == 0)) {
            if (bossbullet_frame_sync > 3)//15초마다 보스의 총알 속도가 빨라짐
                bossbullet_frame_sync--;
            bossspeedup = bossrun_time;
        }
        if (bossrun_time > items_time && (bossrun_time % items_use == 0)) {
            showitem();//x초마다 목숨아이템생성
            items_time = bossrun_time; // 마지막 item 표시 시간 기억
        }
        if (bossrun_time > boom_time && (bossrun_time % boom_use == 0)) {
            showboom();//x초마다 총알 전멸생성
            boom_time = bossrun_time; // 마지막 item 표시 시간 기억
        }
        if (bossrun_time > misiletime && (bossrun_time % misileitems_use == 0)) {
            misileitem();//x초마다 미사일아이템생성
            misiletime = bossrun_time; // 마지막 item 표시 시간 기억
        }
        if (bossrun_time > speeditems_time && (bossrun_time % speeditems_use == 0)) {
            showspeeditem();//x초마다 플레이어 스피드아이템생성
            speeditems_time = bossrun_time; // 마지막 speeditem 표시 시간 기억
        }
        if (bossrun_time > speed2items_time && (bossrun_time % speed2items_use == 0)) {
            showspeed2item();//x초마다 적 스피드아이템생성
            speed2items_time = bossrun_time; // 마지막 speeditem 표시 시간 기억
        }
        if (bossrun_time > powertime && bossrun_time % power_use == 0) {
            powershow();// 갤러그아이템출력
            powertime = bossrun_time;
        }


        if (bossrun_time > enemy2bullettime && (bossrun_time % enemy2bulletuse == 0)) {
            Enemy2Bulletshow();//1초마다 적2 총알 출력
            enemy2bullettime = bossrun_time;
        }

        if (bossrun_time > miniMonster_time && (bossrun_time % miniMonsteruse == 0)) {
            miniMostershow();
            miniMonster_time = bossrun_time;
        }


        if (bossrun_time > enemy2_time && (bossrun_time % enemy2use == 0)) {
            showenemy2();//5초마다 적2 생산
            enemy2_time = bossrun_time; // 마지막 item 표시 시간 기억
        }


        if (bossrun_time > boss_bulletshow && (bossrun_time % bossbulletuse == 0)) {
            bossbulletshow();//  1초마다 보스총알 생성
            boss_bulletshow = bossrun_time; // 마지막 총알 표시 기억
        }


        if (bossrun_time > bossspeedup && (bossrun_time % bossspeedup == 0)) {
            if (boss_frame_sync > 10)//15초마다 보스의 속도가 빨라짐
                boss_frame_sync--;
            bossspeedup = bossrun_time;
        }
        if (bossrun_time > bossspeedup && (bossrun_time % bossspeedup == 0)) {
            if (bossbullet_frame_sync > 3)//15초마다 보스의 총알 속도가 빨라짐
                bossbullet_frame_sync--;
            bossspeedup = bossrun_time;
        }
        if (frame_count % boss_frame_sync == 0) {

            int randomx = newx - bossx;
            if (randomx > 1) randomx = 1;
            if (randomx < -1) randomx = -1;

            int randomy = rand() % 10;//0~9
            if (randomy < 4)randomy = 1;
            else randomy = -1;

            textcolor(RED2, BLACK);
            if (bossx > 34)
                bossx -= 1;
            if (bossx < 10) {
                bossx += 1;
            }
            if (bossy > 18) {
                bossy -= 1;
            }
            if (bossy < 7) {
                bossy += 1;
            }
            bosserase(bossx, bossy);
            bossdraw(bossx + randomx, bossy + randomy);
            bossx += randomx, bossy += randomy;
        }

        if (kbhit() == 1) {
            ch = getch();
            if (ch == SPECIAL1 || ch == SPECIAL2) {
                ch = getch();
                switch (ch) {
                case UP: case DOWN: case LEFT: case RIGHT:
                    playermove(ch);
                    if (frame_count % p1_frame_sync == 0)
                        playermove(0);
                    break;
                default:
                    if (frame_count % p1_frame_sync == 0)
                        playermove(0);
                }
            }
            if (ch == SPACE) {
                for (i = 0; i < MAXBULLET && Bullet[i].exist == TRUE; i++) {}
                if (i != MAXBULLET) {
                    PlaySound(TEXT("Shot.wav"), NULL, SND_ASYNC);//음악 일반 재생
                    Bullet[i].x = newx + 1;
                    Bullet[i].y = newy - 1;
                    Bullet[i].exist = TRUE;
                }
            }
            if (ch == 'd') {
                if (misile != 0) {
                    for (i = 0; i < MAXMISILE && Misile[i].exist == TRUE; i++) {}
                    if (i != MAXMISILE) {
                        PlaySound(TEXT("missile.wav"), NULL, SND_ASYNC);//음악 일반 재생
                        Misile[i].x = newx + 1;
                        Misile[i].y = newy - 1;
                        Misile[i].exist = TRUE;
                        misile--;
                    }
                }
            }
            if (ch == 'h') {
                PlaySound(TEXT("coin.wav"), NULL, SND_ASYNC);//음악 일반 재생
                heart++;
            }

        }
        else {
            if (frame_count % p1_frame_sync == 0)
                playermove(0);
        }
        if (frame_count % bullet_frame_sync == 0)
            bulletmove();  //플레이어의 총알 속도제어

        if (frame_count % bossbullet_frame_sync == 0) {
            textcolor(RED2, BLACK);
            bossbulletmove();//보스의 총알 속도제어
        }
        if (frame_count % enemy2_frame_sync == 0) {
            textcolor(BLUE2, BLACK);
            Enemy2move();
        }
        if (frame_count % enemy2bullet_frame_sync == 0) {
            Enemy2BulletMove();
        }

        if (frame_count % miniMonster_frame_sync == 0) {
            miniMonsterMove();
        }

        if (frame_count % misile_frame_sync == 0) {
            textcolor(YELLOW2, BLACK);
            misilemove();
        }
        if (frame_count % enemybullet_frame_sync == 0) {
            EnemyBulletMove();
        }
        if (frame_count % item_frame_sync == 0) {
            moveitem();
        }
        if (frame_count % item_frame_sync == 0) {
            moveboom();
        }
        if (frame_count % item_frame_sync == 0) {
            movetimeitem();
        }
        if (frame_count % item_frame_sync == 0) {
            movespeeditem();
        }
        if (frame_count % item_frame_sync == 0) {
            movespeed2item();
        }
        if (frame_count % item_frame_sync == 0) {
            powermove();
        }
        if (frame_count % item_frame_sync == 0) {
            misileitemmove();
        }
        Sleep(Delay); // Delay 값을 줄이고
        frame_count++;// frame_count 값으로 속도 조절을 한다.
    }
    if (heart <= 0) {
        system("cls"); //화면 지우기
        // 게임이 끝나면 플레이어 이름과 점수 출력 및 저장
        gotoxy(18, 23);
        printf("player : %s   ", playerName);
        printf("score : %d", score);
        savePlayerScore(playerName, score);

        // 이전 플레이어 기록 출력
        gotoxy(10, 10);
        loadPlayerScores();
        showPlayerScores();
        while (1) {
            loose();
            if (kbhit()) {
                ch = getch();
                if (ch == 'r' || ch == 'q')
                    break;
            }
        }
        if (ch == 'r')
            goto START;
        if (ch == 'q')
            exit(0);
    }

    if (bossheart <= 0) {
        PlaySound(TEXT("bossdie.wav"), NULL, SND_ASYNC);//음악 일반 재생
        score += 300;
        system("cls"); //화면 지우기
        Sleep(2000);
        PlaySound(TEXT("win.wav"), NULL, SND_ASYNC);//음악 일반 재생

        // 게임이 끝나면 플레이어 이름과 점수 출력 및 저장
        gotoxy(18, 23);
        printf("player : %s   ", playerName);
        printf("score : %d", score);
        savePlayerScore(playerName, score);

        // 이전 플레이어 기록 출력
        gotoxy(10, 10);
        loadPlayerScores();
        showPlayerScores();
        while (1) {
            win();
            if (kbhit()) {
                ch = getch();
                if (ch == 'r' || ch == 'q')
                    break;
            }
        }
        if (ch == 'r')
            goto START;
        if (ch == 'q')
            exit(0);
    }

}

void tutorial() {
    system("cls"); //화면 지우기
    textcolor(YELLOW1, BLACK);
    draw_box2(2, 2, 60, 50);//작은 틀
    //unsigned char ch;
    while (1) {
        int c1, c2;
        do {
            c1 = rand() % 16;
            c2 = rand() % 16;
        } while (c1 == c2);
        textcolor(c1, c2);
        gotoxy(10, 8);
        printf("※※※ 우주에 몬스터가 나타났다...! ※※※");
        gotoxy(10, 10);
        printf("       우주 방위대!!    출동 !!!!!!!    ");

        textcolor(YELLOW2, BLACK);
        gotoxy(4, 14);
        printf(" 각 stage의 제한시간을 통과 해 보스몬스터를 처치하세요");
        gotoxy(13, 18);
        printf("이동: 방향키(버튼)");
        gotoxy(13, 20);
        printf("총알 발사: SPACE(버튼)");
        gotoxy(13, 22);
        printf("궁극기: D(버튼)");
        gotoxy(13, 24);
        printf("<H> : 생명 + 1");
        gotoxy(13, 26);
        printf("<B> : 몬스터 1의 총알 전멸");
        gotoxy(13, 28);
        printf("<C> : 플레이어 복제(체력 감소 시 리셋)");
        gotoxy(13, 30);
        printf("<Q> :궁극기");
        gotoxy(13, 32);
        printf("<S> : 플레이어의 총알 및 이동속도 증가 ");
        gotoxy(13, 34);
        textcolor(RED1, BLACK);
        printf("<S>");
        textcolor(YELLOW2, BLACK);
        gotoxy(16, 34);
        printf(" :몬스터의 총알 및 이동속도 감소");
        gotoxy(13, 36);
        printf("<T>: 시간 추가 ");
        gotoxy(13, 38);
        printf("H(버튼) 생명 + 1");

        gotoxy(10, 42);
        printf("계속 하려면 아무키나 누르세요");
        textcolor(BLUE1, BLACK);
        gotoxy(11, 18); printf("◆");
        gotoxy(11, 20); printf("◆");
        gotoxy(11, 22); printf("◆");
        gotoxy(11, 24); printf("◆");
        gotoxy(11, 26); printf("◆");
        gotoxy(11, 28); printf("◆");
        gotoxy(11, 30); printf("◆");
        gotoxy(11, 32); printf("◆");
        gotoxy(11, 34); printf("◆");
        gotoxy(11, 36); printf("◆");
        Sleep(300);

        if (kbhit()) {
            //ch = getch();
            break;
        }
    }
    system("cls"); //화면 지우기  
    textcolor(YELLOW1, BLACK);
    draw_box2(2, 2, 60, 50);//작은 틀
}

void startpage() {

    PlaySound(TEXT("starOpen.wav"), NULL, SND_ASYNC);//음악 일반 재생

    Star stars[NUM_STARS];
    initializeStars(stars, NUM_STARS);
    int a;
    unsigned char ch;
    draw_box2(2, 2, 60, 50);//작은 틀
    int color1, color2;
    while (1) {
        //system("cls"); //화면 지우기  
        color1 = rand() % 15 + 1;
        color2 = rand() % 16;

        if (kbhit()) {
            ch = getch();
            if (ch == '1') {
                //PlaySound("NULL", 0, 0);//음악 멈춤
                stage1();
                break;
            }
            else if (ch == '2') {
                tutorial();
            }
            else if (ch == '3') {
                break;
            }
        }
        textcolor(YELLOW1, BLACK);
        gotoxy(25, 32);
        printf("게임시작(1)");
        gotoxy(26, 34);
        printf("도움말(2)");
        gotoxy(27, 36);
        printf("종료(3)");
        gotoxy(20, 38);
        printf("번호를 입력하시오:");

        gotoxy(5, 18);
        printf("      //   //  ///////  //      //      ///////    ");
        gotoxy(5, 19);
        printf("     //   //  //       //      //     //     //    ");
        gotoxy(5, 20);
        printf("    ///////  ///////  //      //     //     //     ");
        gotoxy(5, 21);
        printf("   //   //  //       //      //     //     //    ");
        gotoxy(5, 22);
        printf("  //   //  ///////  //////  //////  ///////       ");


        updateStars(stars, NUM_STARS);
        printStars(stars, NUM_STARS);

        textcolor(color1, BLACK);
        gotoxy(5, 4);
        printf("              ■                  ■              \n");
        gotoxy(5, 5);
        printf("                ■              ■                \n");
        gotoxy(5, 6);
        printf("                ■■          ■■                \n");
        gotoxy(5, 7);
        printf("              ■■■■■■■■■■■              \n");
        gotoxy(5, 8);
        printf("              ■■■■■■■■■■■              \n");
        gotoxy(5, 9);
        printf("          ■■■    ■■■■■    ■■■          \n");
        gotoxy(5, 10);
        printf("          ■■■    ■■■■■    ■■■          \n");
        gotoxy(5, 11);
        printf("      ■■■■■■■■■■■■■■■■■■■      \n");
        gotoxy(5, 12);
        printf("      ■■    ■■■■■■■■■■■    ■■      \n");
        gotoxy(5, 13);
        printf("      ■■    ■■■■■■■■■■■    ■■      \n");
        gotoxy(5, 14);
        printf("      ■■    ■                  ■    ■■      \n");
        gotoxy(5, 15);
        printf("              ■                  ■              \n");
        gotoxy(5, 16);
        printf("                ■■■      ■■■                \n");

        Sleep(500);
        textcolor(color1, BLACK);
        gotoxy(5, 4);
        printf("              ■                  ■              \n");
        gotoxy(5, 5);
        printf("                ■              ■                \n");
        gotoxy(5, 6);
        printf("                ■■          ■■                \n");
        gotoxy(5, 7);
        printf("    ■■      ■■■■■■■■■■■      ■■    \n");
        gotoxy(5, 8);
        printf("    ■■      ■■■■■■■■■■■      ■■    \n");
        gotoxy(5, 9);
        printf("    ■■  ■■■    ■■■■■    ■■■  ■■    \n");
        gotoxy(5, 10);
        printf("    ■■■■■■    ■■■■■    ■■■■■      \n");
        gotoxy(5, 11);
        printf("      ■■■■■■■■■■■■■■■■■■        \n");
        gotoxy(5, 12);
        printf("              ■■■■■■■■■■■              \n");
        gotoxy(5, 13);
        printf("              ■■■■■■■■■■■              \n");
        gotoxy(5, 14);
        printf("              ■                  ■              \n");
        gotoxy(5, 15);
        printf("              ■                  ■              \n");
        gotoxy(5, 16);
        printf("        ■■■                      ■■■        \n");
        Sleep(500);

    }
}

void main()
{
    //unsigned char ch; // 특수키 0xe0 을 입력받으려면 unsigned char 로 선언해야 함
    int i, x, y;
    char buf[100];
    cls(BLACK, YELLOW1);
    removeCursor(); // 커서를 안보이게 한다

    PlaySound(TEXT("start.wav"), NULL, SND_ASYNC);//음악 일반 재생
    // 이전 플레이어 기록 불러오기
    loadPlayerScores();

    // 플레이어 이름 입력받기
    gotoxy(15, 26);
    printf("플레이어 이름을 입력하세요: ");
    scanf("%s", playerName);
    system("cls"); //화면 지우기	

    startpage();

}
