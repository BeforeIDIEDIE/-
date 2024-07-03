#include <iostream>
#include <cstdlib>//ȭ���� ����� ����� �ϴ� �ý��� ��� system("cls")�� ����ϱ� ����
#include <windows.h>//�����ð����� ���α׷��� ���ߴ� Sleep�Լ��� ����ϱ� ����

using namespace std;

// ���� �� ����(�ٵϾ� + ��ǥ) ���� + ���� ��Ȳ ���
class Board // 1. ù ��° Ŭ����
{
private:
    string t[11] = { "��", "��", "��", "��������", "��������\n", "��", "��������\n", "������", "��", "��", "��" }; // ���� �׸��� ���� ���ڿ� ����
    int xMaxIndex, yMaxIndex;                                                              // ���� ũ�� ����
    char** currentPieces;                                                                  // ���� ���� ���� ����

    // ���� �� �ٵϾ� ���� �ʱ�ȭ
    void initBoardPieces(int yInput, int xInput)
    {
        // �ٵϾ� ���� �� ��ǥ ���� �� 2���� �迭 ����
        currentPieces = (char**)malloc(sizeof(char*) * (yInput + 1));
        for (int i = 0; i <= yInput; i++)
        {
            currentPieces[i] = (char*)malloc(sizeof(char) * (xInput + 1));
        }

        // ������ ��ǥ�� ��ĭ �ʱ�ȭ
        for (int i = 0; i <= yInput; i++)
        {
            for (int j = 0; j <= xInput; j++)
            {
                if (i == 0 && j == 0)
                    currentPieces[0][0] = '\\';
                else if (i == 0)
                    currentPieces[i][j] = (char)('0' + j); // y�� ��ǥ ����
                else if (j == 0)
                    currentPieces[i][j] = (char)('0' + i); // x�� ��ǥ ����
                else
                    currentPieces[i][j] = ' '; // �������� ��ĭ
            }
        }
    }

public:
    // �⺻ ������. �⺻ ���� ũ��� 5.
    Board() : xMaxIndex(5), yMaxIndex(5)
    {
        initBoardPieces(5, 5);
    }

    // ���� ũ�⸦ �Է¹޴� ������
    Board(int sole) : xMaxIndex(sole), yMaxIndex(sole)
    {
        initBoardPieces(sole, sole);
    }

    // �ٵϾ� ���� �Է� ����
    void setPiece(int x, int y, char piece)
    {
        currentPieces[y][x] = piece;
    }

    // Ư�� ��ǥ�� �ٵϾ� ���� ��ȯ
    char getPiece(int x, int y)
    {
        return currentPieces[y][x];
    }

    // ���� ���
    void show()
    {
        int xIndex = 0;
        int yIndex = 0;
        cout << t[9];

        // ���� �� �κ� �𼭸� ���
        for (int i = 0; i < xMaxIndex - 1; i++)
        {
            cout << t[7];
            cout << t[8];
        }
        cout << t[6];

        // ������ �Ʒ� �������� ��ȸ�ϸ� ���� ���
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

                // �� ���������� �����ϸ� xIndex ���� + yIndex ������Ʈ
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

        // ������ �� ���
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

        // ���� �Ʒ��� �𼭸� ���
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

// �÷��̾� ���� ����
// �÷��̾� �ٵϾ� ��� ('O', 'X') ����ϱ�
class Player
{
private:
    char piece;

public:
    Player() : piece('O') {};                         // �⺻ ������
    Player(char chosenPiece) : piece(chosenPiece) {}; // �ٸ� ����� �ٵϾ��� ���� ���� �� ���� ������.

    char getPiece()
    {
        return piece;
    }
};

// ���� ��Ģ Ŭ����
class Game_rule
{
private:
    int l;             // ���� ũ��
    Board board;       // ���� ��ü
    int turnCount = 0; // ���� �� Ƚ��. �÷��̾� �� ���� ���� �θ� turnCount�� 1�� �ö�.

    Player players[2] = { Player('O'), Player('X') };

public:
    // ������
    Game_rule(int l) : board(l), l(l) {};

    // �⺻ ������ (���� ũ�� �⺻���� 5)
    Game_rule() : board(5), l(5) {};

    // ���� ���
    void show()
    {
        board.show();
    }

    // �Է¹��� ��ǥ ���� ���� �� �ٵϾ� �߰�
    // ���� ������ ��ǥ�̸� true ��ȯ + �ٵϾ� �߰�
    // ���� �Ұ����ϸ� false ��ȯ + �ٵϾ� �߰� X
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

    // �� �� ��ȯ
    int getTurnCount()
    {
        return turnCount;
    }

    // �� �� ������Ʈ. �Էµ� newTurnCount�� �ٲ�.
    void updateTurnCount(int newTurnCount)
    {
        turnCount = newTurnCount;
    }

    // ���� �Ͽ� ���� �δ� �÷��̾� ��ȯ. ¦���� 'O', Ȧ���� 'X'
    Player getCurrentPlayer()
    {
        return players[turnCount % 2];
    }

    // ���� Ȯ�� �Լ�.
    // ���� ������ ���� ��ȯ�ϴ� ���� �ٸ�
    // ���� ������ -1 ��ȯ
    int checkBingo(int x, int y)
    {
        char currentPlayerPiece = players[turnCount % 2].getPiece();

        int result = -1;

        // �������� currentPlayerPiece�� ���� Ƚ�� ����
        int chainCount = 0;

        // ���� ���� Ȯ��
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
            return 0; // 0 ��ȯ �� ���� ����

        // �� ���� Ȯ��
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
            return 1; // 1 ��ȯ �� �� ����

        // �밢�� (1, 1) ���� Ȯ��
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
            return 2; // 2 ��ȯ �� (1, 1) ���� �밢�� ����

        // �밢�� (1, -1) ���� Ȯ��
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
            return 3; // 3 ��ȯ �� (1, -1) ���� �밢�� ����

        return result;
    }
};

int main()
{
    // �� ũ�� �����ϴ� ����. ���� ũ��� 5 ~ 37 ������
    int gameMode;

    do
    {
        system("cls");
        cout << "�� ũ�� n �Է�(4 < n < 38): ";
        cin >> gameMode;
    } while (gameMode < 5 || gameMode > 37);

    Game_rule system1(gameMode + 1); // ���� ��Ģ �ý��� ����

    // ī��Ʈ �ٿ�
    cout << "\n//��-�� ����//" << endl;
    cout << "\n���� �����ϰڽ��ϴ�......5" << endl;
    int end = 0;
    Sleep(1000);

    int count = 5;
    while (count-- != 1)
    {
        system("cls");
        system1.show();
        cout << "\n//��-�� ����//" << endl;
        cout << "\n���� �����ϰڽ��ϴ�......" << count << endl;
        Sleep(1000);
    }

    /*
    ���� ����
    1. ����ڿ��� ��ǥ �Է��� �޴´�
    2. �Է� �޴� ��ǥ�� ������ ������ Ȯ���Ѵ�.
        2-1 ���� �ƴ� ��� 1�� ���ư�
        2-2 ���� ������ ���̸� Board Ŭ������ ������Ʈ ��
    3. ��� ���� ������ ������� Ȯ���Ѵ�.
        3-1 ���� �������� ���� ��� �̰���� ��� �� ���α׷� ����
        3-2 ���� ������ �� �� ���� �� 1������ ���ư�.
    */

    int x, y; // �Է� ���� ��ǥ
    while (true)
    {
        system("cls");  // ȭ�� �ʱ�ȭ
        system1.show(); // ���� ��Ȳ ���
        cout << "\n__" << (system1.getTurnCount() + 1) << "��__" << endl;
        cout << "����, ���� ������ ��ǥ�� �����ϼ��� : "; // �޼��� ���

        bool isLegalMove;
        do
        {
            cin >> x >> y;

            // �Է¹��� xy ��ǥ�� ������ ������ Ȯ���ϰ� ��� ��ȯ
            isLegalMove = system1.updateBoard(x, y);

            if (!isLegalMove)
            {
                system("cls");
                system1.show();
                cout << "\n" << x << ", " << y << " ���� �� �� �����ϴ�!" << endl;
                cout << "�ٽ� ����, ���� ������ ��ǥ�� �����ϼ��� : ";
            }

        } while (!isLegalMove);

        // ����� ���� �������� ���� ���� Ȯ��
        // gameResult == -1 �� ��� ���� �����Ƿ� ���� �� ����
        // �ٸ� ���ڸ� ��Ȳ�� ���� winningMessage ������.
        int gameResult = system1.checkBingo(x, y);
        string winningMessage;

        switch (gameResult)
        {
        case 0:
            winningMessage = "���η� ����!";
            break;
        case 1:
            winningMessage = "���η� ����!";
            break;
        case 2:
            winningMessage = "�밢��(1) ����!";
            break;
        case 3:
            winningMessage = "�밢��(2) ����!";
            break;
        default: // gameResult == -1
            break;
        }

        system("cls");

        // ������ �������� ���� ��� �̰���� ��� + ���α׷� ����
        if (gameResult != -1)
        {
            system1.show();
            cout << '\n' << winningMessage << endl;
            cout << "�÷��̾�: " << system1.getCurrentPlayer().getPiece() << " �� �̰���ϴ�!";
            break;
        }

        // ������ �� �������� �� �� +1 �ϰ� �ٽ� �ݺ�.
        system1.updateTurnCount(system1.getTurnCount() + 1);
    }
}
