#include <iostream>
#include <cstdlib>//화면을 지우는 기능을 하는 시스템 명령 system("cls")를 사용하기 위함
#include <windows.h>//일정시간동안 프로그램을 멈추는 Sleep함수를 사용하기 위함

using namespace std;

// 보드 위 정보(바둑알 + 좌표) 저장 + 보드 현황 출력
class Board // 1. 첫 번째 클래스
{
private:
    string t[11] = { "│", "┴", "└", "───┘", "───┤\n", "├", "───┐\n", "───", "┬", "┌", "┼" }; // 보드 그리기 위한 문자열 저장
    int xMaxIndex, yMaxIndex;                                                              // 보드 크기 저장
    char** currentPieces;                                                                  // 현재 보드 상태 저장

    // 보드 위 바둑알 정보 초기화
    void initBoardPieces(int yInput, int xInput)
    {
        // 바둑알 정보 및 좌표 저장 할 2차원 배열 선언
        currentPieces = (char**)malloc(sizeof(char*) * (yInput + 1));
        for (int i = 0; i <= yInput; i++)
        {
            currentPieces[i] = (char*)malloc(sizeof(char) * (xInput + 1));
        }

        // 보드의 좌표와 빈칸 초기화
        for (int i = 0; i <= yInput; i++)
        {
            for (int j = 0; j <= xInput; j++)
            {
                if (i == 0 && j == 0)
                    currentPieces[0][0] = '\\';
                else if (i == 0)
                    currentPieces[i][j] = (char)('0' + j); // y축 좌표 저장
                else if (j == 0)
                    currentPieces[i][j] = (char)('0' + i); // x축 좌표 저장
                else
                    currentPieces[i][j] = ' '; // 나머지는 빈칸
            }
        }
    }

public:
    // 기본 생성자. 기본 보드 크기는 5.
    Board() : xMaxIndex(5), yMaxIndex(5)
    {
        initBoardPieces(5, 5);
    }

    // 보드 크기를 입력받는 생성자
    Board(int sole) : xMaxIndex(sole), yMaxIndex(sole)
    {
        initBoardPieces(sole, sole);
    }

    // 바둑알 정보 입력 받음
    void setPiece(int x, int y, char piece)
    {
        currentPieces[y][x] = piece;
    }

    // 특정 좌표의 바둑알 정보 반환
    char getPiece(int x, int y)
    {
        return currentPieces[y][x];
    }

    // 보드 출력
    void show()
    {
        int xIndex = 0;
        int yIndex = 0;
        cout << t[9];

        // 보드 윗 부분 모서리 출력
        for (int i = 0; i < xMaxIndex - 1; i++)
        {
            cout << t[7];
            cout << t[8];
        }
        cout << t[6];

        // 위에서 아래 방향으로 순회하며 보드 출력
        for (int i = 0; i < yMaxIndex - 1; i++)
        {
            cout << t[0];
            for (int j = 0; j < xMaxIndex - 1; j++)
            {
                if ((xIndex == 0 || yIndex == 0))
                {
                    if (yIndex == 0 && xIndex == 0)
                    {
                        cout << ' ' << "\\" << ' ';
                    }
                    else if (xIndex == 0 && yIndex > 9)
                    {
                        cout << ' ' << yIndex;
                    }
                    else if (xIndex == 0)
                    {
                        cout << ' ' << yIndex << ' ';
                    }
                    else if (yIndex == 0 && xIndex > 9)
                    {
                        cout << ' ' << xIndex;
                    }
                    else if (yIndex == 0)
                    {
                        cout << ' ' << xIndex << ' ';
                    }
                }
                else
                {
                    cout << ' ' << currentPieces[yIndex][xIndex] << ' ';
                }
                xIndex++;

                // 행 마지막까지 도달하면 xIndex 리셋 + yIndex 업데이트
                if (xIndex == xMaxIndex)
                {
                    yIndex++;
                    xIndex = 0;
                }
                cout << t[0];
            }

            if (xIndex > 9 && yIndex == 0)
            {
                cout << ' ' << xMaxIndex - 1;
            }
            else
            {
                cout << ' ' << currentPieces[yIndex][xIndex] << ' ';
            }

            xIndex++;
            if (xIndex == xMaxIndex)
            {
                yIndex++;
                xIndex = 0;
            }
            cout << t[0] << endl;

            cout << t[5];
            for (int j = 0; j < xMaxIndex - 1; j++)
            {
                cout << t[7];
                cout << t[10];
            }
            cout << t[4];
        }
        cout << t[0];

        // 마지막 행 출력
        for (int j = 0; j < xMaxIndex - 1; j++)
        {
            if (xIndex == 0 && yIndex > 9)
            {
                cout << ' ' << yIndex;
            }
            else
            {
                cout << ' ' << currentPieces[yIndex][xIndex] << ' ';
            }

            xIndex++;
            if (xIndex == xMaxIndex)
            {
                yIndex++;
                xIndex = 0;
            }
            cout << t[0];
        }

        cout << ' ' << currentPieces[yIndex][xIndex] << ' ';
        xIndex++;

        // 보드 아래쪽 모서리 출력
        if (xIndex == xMaxIndex)
        {
            yIndex++;
            xIndex = 0;
        }

        cout << t[0] << endl;
        cout << t[2];
        for (int i = 0; i < xMaxIndex - 1; i++)
        {
            cout << t[7];
            cout << t[1];
        }
        cout << t[3];
    }
};

// 플레이어 정보 저장
// 플레이어 바둑알 모양 ('O', 'X') 기억하기
class Player
{
private:
    char piece;

public:
    Player() : piece('O') {};                         // 기본 생성자
    Player(char chosenPiece) : piece(chosenPiece) {}; // 다른 모양의 바둑알을 쓰고 싶을 때 쓰는 생성자.

    char getPiece()
    {
        return piece;
    }
};

// 게임 규칙 클래스
class Game_rule
{
private:
    int l;             // 보드 크기
    Board board;       // 보드 객체
    int turnCount = 0; // 게임 턴 횟수. 플레이어 한 명이 수를 두면 turnCount가 1씩 올라감.

    Player players[2] = { Player('O'), Player('X') };

public:
    // 생성자
    Game_rule(int l) : board(l), l(l) {};

    // 기본 생성자 (보드 크기 기본값은 5)
    Game_rule() : board(5), l(5) {};

    // 보드 출력
    void show()
    {
        board.show();
    }

    // 입력받은 좌표 토대로 보드 위 바둑알 추가
    // 만일 가능한 좌표이면 true 반환 + 바둑알 추가
    // 만일 불가능하면 false 반환 + 바둑알 추가 X
    bool updateBoard(int x, int y)
    {
        if ((x >= l || x <= 0) || (y <= 0 || y >= l))
            return false;

        if (board.getPiece(x, y) == ' ')
        {
            board.setPiece(x, y, players[turnCount % 2].getPiece());
            return true;
        }

        return false;
    }

    // 턴 수 반환
    int getTurnCount()
    {
        return turnCount;
    }

    // 턴 수 업데이트. 입력된 newTurnCount로 바뀜.
    void updateTurnCount(int newTurnCount)
    {
        turnCount = newTurnCount;
    }

    // 현재 턴에 수를 두는 플레이어 반환. 짝수면 'O', 홀수면 'X'
    Player getCurrentPlayer()
    {
        return players[turnCount % 2];
    }

    // 빙고 확인 함수.
    // 빙고 종류에 따라 반환하는 숫자 다름
    // 빙고 없으면 -1 반환
    int checkBingo(int x, int y)
    {
        char currentPlayerPiece = players[turnCount % 2].getPiece();

        int result = -1;

        // 연속으로 currentPlayerPiece가 나온 횟수 저장
        int chainCount = 0;

        // 가로 빙고 확인
        for (int dx = -4; dx < 5; dx++)
        {
            int currentx = x + dx;
            if (currentx < 0 || currentx >= l)
                continue;

            if (currentPlayerPiece == board.getPiece(currentx, y))
                chainCount++;
            else
                chainCount = 0;

            if (chainCount >= 5)
                break;
        }

        if (chainCount >= 5)
            return 0; // 0 반환 시 가로 빙고

        // 열 빙고 확인
        chainCount = 0;
        for (int dy = -4; dy < 5; dy++)
        {
            int currenty = y + dy;
            if (currenty < 0 || currenty >= l)
                continue;

            if (currentPlayerPiece == board.getPiece(x, currenty))
                chainCount++;
            else
                chainCount = 0;

            if (chainCount >= 5)
                break;
        }

        if (chainCount >= 5)
            return 1; // 1 반환 시 열 빙고

        // 대각선 (1, 1) 방향 확인
        chainCount = 0;
        for (int dv = -4; dv < 5; dv++)
        {
            int currentx = x + dv;
            int currenty = y + dv;

            if ((currenty < 0 || currenty >= l) || (currentx < 0 || currentx >= l))
                continue;

            if (currentPlayerPiece == board.getPiece(currentx, currenty))
                chainCount++;
            else
                chainCount = 0;

            if (chainCount >= 5)
                break;
        }

        if (chainCount >= 5)
            return 2; // 2 반환 시 (1, 1) 방향 대각선 빙고

        // 대각선 (1, -1) 방향 확인
        chainCount = 0;
        for (int dv = -4; dv < 5; dv++)
        {
            int currentx = x + dv;
            int currenty = y - dv;

            if ((currenty < 0 || currenty >= l) || (currentx < 0 || currentx >= l))
                continue;

            if (currentPlayerPiece == board.getPiece(currentx, currenty))
                chainCount++;
            else
                chainCount = 0;

            if (chainCount >= 5)
                break;
        }

        if (chainCount >= 5)
            return 3; // 3 반환 시 (1, -1) 방향 대각선 빙고

        return result;
    }
};

int main()
{
    // 판 크기 저장하는 변수. 판의 크기는 5 ~ 37 까지만
    int gameMode;

    do
    {
        system("cls");
        cout << "판 크기 n 입력(4 < n < 38): ";
        cin >> gameMode;
    } while (gameMode < 5 || gameMode > 37);

    Game_rule system1(gameMode + 1); // 게임 규칙 시스템 생성

    // 카운트 다운
    cout << "\n//오-목 게임//" << endl;
    cout << "\n게임 시작하겠습니다......5" << endl;
    int end = 0;
    Sleep(1000);

    int count = 5;
    while (count-- != 1)
    {
        system("cls");
        system1.show();
        cout << "\n//오-목 게임//" << endl;
        cout << "\n게임 시작하겠습니다......" << count << endl;
        Sleep(1000);
    }

    /*
    게임 루프
    1. 사용자에게 좌표 입력을 받는다
    2. 입력 받는 좌표가 가능한 수인지 확인한다.
        2-1 만일 아닌 경우 1로 돌아감
        2-2 만일 가능한 수이면 Board 클래스에 업데이트 됨
    3. 방금 수로 오목이 생겼는지 확인한다.
        3-1 만일 생겼으면 누가 어떻게 이겼는지 출력 및 프로그램 종료
        3-2 만일 없으면 턴 수 증가 및 1번으로 돌아감.
    */

    int x, y; // 입력 받을 좌표
    while (true)
    {
        system("cls");  // 화면 초기화
        system1.show(); // 보드 현황 출력
        cout << "\n__" << (system1.getTurnCount() + 1) << "턴__" << endl;
        cout << "가로, 세로 순으로 좌표를 기입하세요 : "; // 메세지 출력

        bool isLegalMove;
        do
        {
            cin >> x >> y;

            // 입력받은 xy 좌표가 가능한 수인지 확인하고 결과 반환
            isLegalMove = system1.updateBoard(x, y);

            if (!isLegalMove)
            {
                system("cls");
                system1.show();
                cout << "\n" << x << ", " << y << " 에는 둘 수 없습니다!" << endl;
                cout << "다시 가로, 세로 순으로 좌표를 기입하세요 : ";
            }

        } while (!isLegalMove);

        // 방금의 수를 바탕으로 게임 상태 확인
        // gameResult == -1 인 경우 빙고가 없으므로 게임 안 끝남
        // 다른 숫자면 상황에 따라 winningMessage 설정됨.
        int gameResult = system1.checkBingo(x, y);
        string winningMessage;

        switch (gameResult)
        {
        case 0:
            winningMessage = "가로로 오목!";
            break;
        case 1:
            winningMessage = "세로로 오목!";
            break;
        case 2:
            winningMessage = "대각선(1) 오목!";
            break;
        case 3:
            winningMessage = "대각선(2) 오목!";
            break;
        default: // gameResult == -1
            break;
        }

        system("cls");

        // 게임이 끝났으면 누가 어떻게 이겼는지 출력 + 프로그램 종료
        if (gameResult != -1)
        {
            system1.show();
            cout << '\n' << winningMessage << endl;
            cout << "플레이어: " << system1.getCurrentPlayer().getPiece() << " 가 이겼습니다!";
            break;
        }

        // 게임이 안 끝났으면 턴 수 +1 하고 다시 반복.
        system1.updateTurnCount(system1.getTurnCount() + 1);
    }
}
