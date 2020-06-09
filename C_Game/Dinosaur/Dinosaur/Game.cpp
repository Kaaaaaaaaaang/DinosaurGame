#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>

#define DINO_BOTTOM_Y 12
#define TREE_BOTTOM_Y 20
#define TREE_BOTTOM_X 45

void SetConsoleView()
{
	system("mode con:cols=100 lines=25");
	//cols = 가로 lines = 세로
	system("title C언어_공룡 게임");
}

void gotoxy(int x, int y) //커서 이동 함수
{
	COORD Pos; //x값과 y갑을 멤버로 가지는 구조체
	Pos.X = 2*x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//키보드의 입력을 받고, 입력된 키의 값을 반환하는 함수
int getkey()
{
	if (_kbhit() != 0) //키보드가 입력되었는지 확인하는 함수
	{
		return _getch(); //키보드의 내용이 화면에 출력되지 않음
	}
	return 0;
}

void Dino(int dinoY) //공룡 모양
{
	gotoxy(0, dinoY);
	static bool leg_move = true;
	printf("        |-----| \n");
	printf("       |*     *|\n");
	printf("       |   ____|\n");
	printf("|-|    |   |    \n");
	printf("| |    |    -|  \n");
	printf("| |   |   |     \n");
	printf(" ||  |     ---| \n");
	printf(" | --       __|  \n");
	printf("  |          |   \n");
	printf("   |        |    \n");
	printf("     |     |     \n");
	if (leg_move)
	{
		printf("     $    $$$    \n");
		printf("     $$          ");
		leg_move = false;
	}
	else
	{
		printf("     $$$  $     \n");
		printf("          $$    ");
		leg_move = true;
	}
}

void Box(int boxX)
{
	gotoxy(boxX, TREE_BOTTOM_Y);
	printf("  $  ");
	gotoxy(boxX, TREE_BOTTOM_Y + 1);
	printf("#####");
	gotoxy(boxX, TREE_BOTTOM_Y + 2);
	printf("#   #");
	gotoxy(boxX, TREE_BOTTOM_Y + 3);
	printf("#   #");
	gotoxy(boxX, TREE_BOTTOM_Y + 4);
	printf("#####");
}

void GameOver(const int score)
{
	system("cls");
	int x = 18, y = 8;
	gotoxy(x, y);
	printf("===========================");
	gotoxy(x, y + 1);
	printf("=장애물에 걸리고 말았다!!!=");
	gotoxy(x, y + 2);
	printf("===========================");
	gotoxy(x, y + 5);
	printf("SCORE : %d", score);

	printf("\n\n\n\n\n\n\n\n\n");
	system("pause");
}

bool check(const int boxX, const int dinoY)
{
	if (boxX <= 8 && boxX >= 4 && dinoY > 8) 
	//나무의 위치가 공룡 몸통에 위치 + 공룡의 높이가 낮을 때 충돌
	{
		return true;
	}
	return false;
}

int main()
{
	SetConsoleView();

	while (true) //게임
	{
		bool Jumping = false, Bottom = true;
		const int gravity = 3;

		int dinoY = DINO_BOTTOM_Y;
		int boxX = TREE_BOTTOM_X;

		int score = 0; //점수 초기화
		clock_t start, current;	
		start = clock(); //시작 시간 초기화

		while (true) //한 판
		{
			if (check(boxX, dinoY)) //충돌 판단
				break;

			if (getkey() == 32 && Bottom)
			{
				Jumping = true;
				Bottom = false;
			}
			if (Jumping) //점프 중 -> 감소, 점프 끝 -> 증가
			{
				dinoY -= gravity;
			}
			else
			{
				dinoY += gravity;
			}
			if (dinoY >= DINO_BOTTOM_Y) //바닥 지정
			{
				dinoY = DINO_BOTTOM_Y;
				Bottom = true;
			}

			boxX -= 2;
			if (boxX <= 0)
			{
				boxX = TREE_BOTTOM_X;
			}
			if (dinoY <= 3) //점프 끝
			{
				Jumping = false;
			}

			Dino(dinoY);
			Box(boxX);	

			current = clock(); //현재 시간
			if (((current - start) / CLOCKS_PER_SEC) >= 1)
			//진행 시간이 1초가 넘을 때
			{
				score++;	//점수 +1
				start = clock();	//시작시간 초기화
			}
			Sleep(60);
			system("cls");

			gotoxy(0, 0);
			printf("점수 : %d점 ", score);
		}
		GameOver(score);
	}
	return 0;
}