#include "Game.h";

// ZYARI METHODS
Zyari::Zyari() : _cubeUI{} {
    _dre.seed(_rd());
}

bool Zyari::IsKosha() {
    return (_zyari.first == _zyari.second);
}

uint Zyari::MakeRnd(uint x1, uint x2) {
    return _uid(_dre, std::uniform_int_distribution<>::param_type(x1, x2));
}

const pair<uint, uint>& Zyari::Drop(){
    _zyari={ MakeRnd(1, 6), MakeRnd(1, 6) };
    if (_zyari.second > _zyari.first) std::swap(_zyari.first, _zyari.second);
    return _zyari;
}

void Zyari::DrawZyari() {
    // Draw Cube Body 
    std::for_each(_cubeUI.begin(), _cubeUI.end(), [](auto& row) {
        std::fill(row.begin(), row.end(), ' ');
    });
    std::fill(_cubeUI[0].begin(), _cubeUI[0].end(), ToCh(HH));
    std::fill(_cubeUI[4].begin(), _cubeUI[4].end(), ToCh(HH));
    std::for_each(_cubeUI.begin(), _cubeUI.end(), [](auto& row) {
        row[1] = row[11] = row[14] = row[24] = ToCh(VV);
        row[0] = row[12] = row[13] = ' ';
        row[25] = '\n';
    });
    _cubeUI[0][1] = _cubeUI[0][14] = ToCh(LU);
    _cubeUI[0][11] = _cubeUI[0][24] = ToCh(RU);
    _cubeUI[4][1] = _cubeUI[4][14] = ToCh(LB);
    _cubeUI[4][11] = _cubeUI[4][24] = ToCh(RB);

    // Draw Zyari Nums
    switch (_zyari.first) {
    case 1: _cubeUI[2][6] = ToCh(SQR); break;
    case 2: _cubeUI[1][3] = _cubeUI[3][9] = ToCh(SQR); break;
    case 3: _cubeUI[1][3] = _cubeUI[2][6] = _cubeUI[3][9] = ToCh(SQR); break;
    case 4: _cubeUI[1][3] = _cubeUI[1][9] = _cubeUI[3][3] = _cubeUI[3][9] = ToCh(SQR); break;
    case 5: _cubeUI[1][3] = _cubeUI[1][9] = _cubeUI[2][6] = _cubeUI[3][3] = _cubeUI[3][9] = ToCh(SQR); break;
    case 6: _cubeUI[1][3] = _cubeUI[1][9] = _cubeUI[2][3] = _cubeUI[2][9] = _cubeUI[3][3] = _cubeUI[3][9] = ToCh(SQR); break;
    }
    switch (_zyari.second) {
    case 1: _cubeUI[2][19] = ToCh(SQR); break;
    case 2: _cubeUI[1][16] = _cubeUI[3][22] = ToCh(SQR); break;
    case 3: _cubeUI[1][16] = _cubeUI[2][19] = _cubeUI[3][22] = ToCh(SQR); break;
    case 4: _cubeUI[1][16] = _cubeUI[1][22] = _cubeUI[3][16] = _cubeUI[3][22] = ToCh(SQR); break;
    case 5: _cubeUI[1][16] = _cubeUI[1][22] = _cubeUI[2][19] = _cubeUI[3][16] = _cubeUI[3][22] = ToCh(SQR); break;
    case 6: _cubeUI[1][16] = _cubeUI[1][22] = _cubeUI[2][16] = _cubeUI[2][22] = _cubeUI[3][16] = _cubeUI[3][22] = ToCh(SQR); break;
    }

    // Final Draw
    std::for_each(_cubeUI.begin(), _cubeUI.end(), [](auto& row) { copy(row.begin(), row.end(), out<char>); });
}

// BOARD METHODS
Board::Board() {
    std::fill(_exitFringe[0].begin(), _exitFringe[0].end(), ToCh(RECT50));
    std::fill(_exitFringe[1].begin(), _exitFringe[1].end(), ToCh(RECT50));
}

auto& Board::operator()() { return this->_board; }

void Board::FillStarterBoard() {
    // STARTER INIT BOARD
    _board[0].resize(15);
    _board[12].resize(15);
    std::fill(_board[0].begin(), _board[0].end(), _O);
    std::fill(_board[12].begin(), _board[12].end(), _X);
}

///// TEST-CASE BEGIN ////////////////////////////////////////////////
void Board::FillBlockingBoard() {
    // STARTER INIT BOARD
    _board[0].push_back(_O);    _board[0].push_back(_O);    _board[2].push_back(_O);    _board[3].push_back(_X);    
    _board[4].push_back(_O);    _board[6].push_back(_O);    _board[6].push_back(_O);    _board[7].push_back(_O);
    _board[8].push_back(_O);    _board[10].push_back(_O);   _board[21].push_back(_X);   _board[23].push_back(_X);
    _board[11].push_back(_O);   _board[12].push_back(_X);   _board[12].push_back(_X);   _board[14].push_back(_O);
    _board[16].push_back(_X);   _board[16].push_back(_X);   _board[17].push_back(_X);   _board[17].push_back(_X);
    _board[18].push_back(_X);   _board[20].push_back(_X);
}
void Board::Fill_IV_Board() {
    // TESTDRIVE EXIT INIT BOARD
    _board[18].resize(2);   _board[19].resize(3);   _board[20].resize(2);   _board[21].resize(3);
    _board[22].resize(2);   _board[23].resize(3);   _board[6].resize(2);    _board[7].resize(3);
    _board[8].resize(2);    _board[9].resize(3);    _board[10].resize(2);   _board[11].resize(3);
    std::for_each(_board.begin() + 18, _board.end(), [](vector<char>& col) { std::fill(col.begin(), col.end(), _O); });
    std::for_each(_board.begin() + 6, _board.begin()+12, [](vector<char>& col) { std::fill(col.begin(), col.end(), _X); });
}
void Board::Fill_IV_Board_With_Enemy() {
    // TESTDRIVE EXIT INIT BOARD
    _board[19].resize(3);   _board[20].resize(4);   _board[21].resize(3);   _board[22].resize(5);   
    _board[7].resize(3);    _board[8].resize(4);    _board[9].resize(3);    _board[10].resize(5);
    _board[11].push_back('O');  
    _board[23].push_back('X');
    std::for_each(_board.begin() + 18, _board.end()-1, [](vector<char>& col) { std::fill(col.begin(), col.end(), _O);});
    std::for_each(_board.begin() + 6, _board.begin() + 11, [](vector<char>& col) { std::fill(col.begin(), col.end(), _X); });
}
void Board::Fill_ALMOST_IV_Board() {
    // TESTDRIVE EXIT INIT BOARD
    _board[19].resize(3);   _board[20].resize(2);   _board[21].resize(2);   _board[11].resize(3);
    _board[18].resize(2);   _board[23].resize(3);   _board[22].resize(2);   _board[10].resize(2);
    _board[6].resize(2);    _board[7].resize(2);    _board[8].resize(2);    _board[9].resize(3);
    _board[17].push_back(_O);
    _board[3].push_back(_X);
    std::for_each(_board.begin() + 18, _board.end(), [](vector<char>& col) { std::fill(col.begin(), col.end(), _O); });
    std::for_each(_board.begin() + 6, _board.begin() + 12, [](vector<char>& col) { std::fill(col.begin(), col.end(), _X); });
}
void Board::FillRandomBoard() {
    // RANDOM INIT BOARD
    _board[0].resize(8);    _board[7].resize(2);    _board[22].resize(2);
    _board[12].resize(6);   _board[15].resize(3);   _board[1].resize(2);
    _board[3].push_back(_O);    _board[11].push_back(_O);   _board[20].push_back(_O);    _board[23].push_back(_X);
    _board[9].push_back(_X);    _board[17].push_back(_X);   _board[21].push_back(_X);
    std::fill(_board[0].begin(), _board[0].end(), _O);
    std::fill(_board[7].begin(), _board[7].end(), _O);
    std::fill(_board[22].begin(), _board[22].end(), _O);
    std::fill(_board[12].begin(), _board[12].end(), _X);
    std::fill(_board[15].begin(), _board[15].end(), _X);
    std::fill(_board[1].begin(), _board[1].end(), _X);
}

void Board::FillBlockFullMoveBoard() {
    _board[0].push_back(_O);    _board[1].push_back(_X);    _board[2].push_back(_O);    _board[5].push_back(_X);
    _board[6].push_back(_O);    _board[7].push_back(_X);    _board[8].push_back(_O);    _board[9].push_back(_X);
    _board[10].push_back(_O);   _board[11].push_back(_X);   _board[12].push_back(_O);   _board[13].push_back(_X);
    _board[14].push_back(_O);   _board[15].push_back(_X);   _board[16].push_back(_O);   _board[17].push_back(_X);
    _board[17].push_back(_X);   _board[18].push_back(_O);   _board[19].push_back(_X);   _board[20].push_back(_O);
    _board[20].push_back(_O);   _board[23].push_back(_X);
}
void Board::FillNoMoves() {
    _board[0].push_back(_O);    _board[1].push_back(_X);    _board[2].push_back(_X);    _board[6].push_back(_X);
    _board[3].push_back(_X);    _board[4].push_back(_X);    _board[5].push_back(_X);
}
///// TEST-CASE END ////////////////////////////////////////////////
    
// Draw Game Board
void Board::DrawBoard() {
    // Re/load Player Board Cursor
    std::fill(_frame.begin(), _frame.end(), ToCh(RECT50));

    // Make Cursor Symbol
    if (_cursorPos >= 0 && _cursorPos < 12) _frame[_cursorPos] = ARROW_DOWN;
    else if (_cursorPos > 11 && _cursorPos < 24) _frame[_cursorPos] = ARROW_UP;
     
    // Numeration
    cout << ' ' << 1 << ' ' << 1 << endl;
    for (uint i = 0; i < _BOARD_WIDTH; i++) {
        cout << ' ';
        if (i < _COLS_COUNT / 2) cout << (11 - i) % 10;
        if (i == 5) cout << ' ';
    }
    cout << endl;

    // Upper Border Line
    cout << ToCh(RECT50);
    for (int i = 11; i >= 0; i--) {
        if (i == 5) cout << ToCh(RECT50);
        cout << _frame[i] << ToCh(RECT50);
    }
    cout << endl;

    // Base Field
    // Upper Rows [0-14]
    for (uint i = 0; i < _ROWS_COUNT/2; i++) {
        // Upper Columns [0-11]
        for (uint j = 0; j < _COLS_COUNT/2; j++) {
            // Accessoirs
            j == 6 ? i == 4 || i == 5 ? cout << ToCh(RECT75) << ToCh(RECT75) :
                cout << ToCh(RECT50) << ToCh(RECT50) :
                cout << (j == 0 ? _exitFringe[0][i] : ToCh(RECT25));
            // Figures
            cout << (_board[11 - j].size() > i ? _board[_COLS_COUNT/2 - 1 - j][i] : ' ');
        }
        cout << ToCh(RECT50) << endl;
    }

    // Lower Rows [15-29]
    for (uint i = _ROWS_COUNT-1; i >= _ROWS_COUNT/2; i--) {
        // Upper Columns [12-23]
        for (uint j = _COLS_COUNT/2; j < _COLS_COUNT; j++) {
            // Accessoirs
            j == 18 ? i == 20 || i == 19 ? cout << ToCh(RECT75) << ToCh(RECT75) :
                cout << ToCh(RECT50) << ToCh(RECT50) :
                cout << (j == 12 ? ToCh(RECT50) : ToCh(RECT25));
            // Figures
            cout << (_board[j].size() > i - 15 ? _board[j][i - 15] : ' ');
        }
        cout << _exitFringe[1][i-15] << endl;
    }

    // Bottom Board Line 
    cout << ToCh(RECT50);
    for (int i = 12; i < 24; i++) {
        cout << _frame[i] << ToCh(RECT50);
        if (i == 17) cout << ToCh(RECT50);
    }
    cout << endl;
        
    // Numeration
    for (uint i = 12; i < _COLS_COUNT; i++) {
        if (i == 18) cout << ' ';
        cout << ' ' << (i) / 10;
    }
    cout << endl;
    for (uint i = 12; i < _COLS_COUNT; i++) {
        if (i == 18) cout << ' ';
        cout << ' ' << (i) % 10;
    }
    cout << endl;
}

void Game::DrawEntry()
{
    string ce;
    ce += ToCh(RECT50);
    ce += ToCh(RECT50);

    string ol;
    ol += ToCh(RECT50);
    ol += ' ';

    string oR;
    oR += ' ';
    oR += ToCh(RECT50);

    string il;
    il += ToCh(RECT25);
    il += ' ';

    string iR;
    iR += ' ';
    iR += ToCh(RECT25);

    string jn;
    jn += ToCh(RECT75);
    jn += ToCh(RECT75);

    string rw1 =                "            " + ce + "            " + '\n';
    string rw2 =             "          " + ol + ce + oR + "          " + '\n';
    string rw3 =          "        " + ol + il + ce + iR + oR + "        " + '\n';
    string rw4 =       "      " + ol + il + il + ce + iR + iR + oR + "      " + '\n';
    string rw5 =    "    " + ol + il + il + il + ce + iR + iR + iR + oR + "    " + '\n';
    string rw6 = "  " + ol + il + il + il + il + ce + iR + iR + iR + iR + oR + "  " + '\n';
    string rw7 =   ol + il + il + il + il + il + ce + iR + iR + iR + iR + iR + oR + '\n';

    string rj1 =                "            " + jn + "            " + '\n';
    string rj2 =             "          " + ol + jn + oR + "          " + '\n';
    string rj3 =          "        " + ol + il + jn + iR + oR + "        " + '\n';
    string rj4 =       "      " + ol + il + il + jn + iR + iR + oR + "      " + '\n';
    string rj5 =    "    " + ol + il + il + il + jn + iR + iR + iR + oR + "    " + '\n';
    string rj6 = "  " + ol + il + il + il + il + jn + iR + iR + iR + iR + oR + "  " + '\n';
    string rj7 =   ol + il + il + il + il + il + jn + iR + iR + iR + iR + iR + oR + '\n';

    string hr[7];
    uint n = 2, k = 12;
    for (uint i = 0; i < 7; i++, n += 4, k -= 2) {
        for (uint j = 0; j < k; j++) hr[i].push_back(' ');
        for (uint j = 0; j < n; j++) hr[i].push_back(ToCh(RECT50));
        for (uint j = 0; j < k; j++) hr[i].push_back(' ');
        hr[i].push_back('\n');
    }

    string rw[7], rj[7], fr[7];
    rw[0] = rw1;    rw[1] = rw2;    rw[2] = rw3;    rw[3] = rw4;    rw[4] = rw5;    rw[5] = rw6;    rw[6] = rw7;
    rj[0] = rj1;    rj[1] = rj2;    rj[2] = rj3;    rj[3] = rj4;    rj[4] = rj5;    rj[5] = rj6;    rj[6] = rj7;

    for (uint i = 0; i < 7; i++) {
        for (uint j = 0; j < 32; j++) {
            fr[i] += (((j == 5 || j == 6 || j == 25 || j == 26) && i != 0) ? rj[i] : (j == 0 || j == 31 ? hr[i] : rw[i]));
        }
    }

    for (int i = _isExit ? 7 : 0; _isExit ? i >=0 : i < 7; _isExit ? i-- : i++) {
        cout << fr[i];
        Sleep(250);
        system("cls");
    }
}

// GAME METHODS

Game::Game() : _isExit{ 0 }, _isGameLoaded { 0 }, _gameMode{ 1 }, _isWin{ 0 }, _isFromHeadValid{ 1 },
            _isFindingEnd{ 0 }, _isMoveComplete{ 0 },
            _player1{ _O }, _player2{ _X }, _curPlayer{ nullptr } {
    DrawEntry();
    InitMenuBody();
    _board.FillStarterBoard();
        
}

void Game::InitMenuBody() {
    // Full Body
    for (auto& vec : _menuBody) {
        std::fill(vec.begin(), vec.end(), ' ');
    }
    // Frame
    std::fill(_menuBody[0].begin(), _menuBody[0].begin()+4, HH);
    std::fill(_menuBody[0].begin()+10, _menuBody[0].begin()+14, HH);
    std::fill(_menuBody[23].begin(), _menuBody[23].end(), HH);
    for (uint i = 0; i < 24; i++) {
        _menuBody[i][0] = VV;
        _menuBody[i][13] = VV;
    }
    // Corners
    _chCrnPos[0] = { 2,3 };
    _chCrnPos[1] = { 2,10 };
    _chCrnPos[2] = { 6,3 };
    _chCrnPos[3] = { 6,10 };
    _menuBody[0][0] = _menuBody[3][4] = _menuBody[8][4] = _menuBody[13][4] = _menuBody[18][4]
        = _menuBody[_chCrnPos[0].first][_chCrnPos[0].second] = LU;
    _menuBody[0][13] = _menuBody[3][9] = _menuBody[8][9] = _menuBody[13][9] = _menuBody[18][9] 
        = _menuBody[_chCrnPos[1].first][_chCrnPos[1].second] = RU;
    _menuBody[23][0] = _menuBody[5][4] = _menuBody[10][4] = _menuBody[15][4] = _menuBody[20][4] 
        = _menuBody[_chCrnPos[2].first][_chCrnPos[2].second] = LB;
    _menuBody[23][13] = _menuBody[5][9] = _menuBody[10][9] = _menuBody[15][9] = _menuBody[20][9] 
        = _menuBody[_chCrnPos[3].first][_chCrnPos[3].second] = RB;
    // Texts
    string menuText = "MENUNEW SAVELOADEXIT";
    for (uint i = 0; i < 4; i++) {
        _menuBody[0][5+i] = menuText[i];
        _menuBody[4][5+i] = menuText[4+i];
        _menuBody[9][5+i] = menuText[8+i];
        _menuBody[14][5+i] = menuText[12+i];
        _menuBody[19][5+i] = menuText[16+i];
    }
    // Text Frame
    std::fill(_menuBody[3].begin()+5, _menuBody[3].begin() + 9, HH);
    std::fill(_menuBody[5].begin()+5, _menuBody[5].begin() + 9, HH);
    std::fill(_menuBody[8].begin()+5, _menuBody[8].begin() + 9, HH);
    std::fill(_menuBody[10].begin()+5, _menuBody[10].begin() + 9, HH);
    std::fill(_menuBody[13].begin()+5, _menuBody[13].begin() + 9, HH);
    std::fill(_menuBody[15].begin()+5, _menuBody[15].begin() + 9, HH);
    std::fill(_menuBody[18].begin()+5, _menuBody[18].begin() + 9, HH);
    std::fill(_menuBody[20].begin()+5, _menuBody[20].begin() + 9, HH);
}

void Game::DrawMenu()
{
    system("cls");
    cout << "\n\n\n";
    for (auto ito = _menuBody.begin(); ito != _menuBody.end(); ito++) {
        cout << "      ";
        std::copy(ito->begin(), ito->end(), out<char>);
        cout << endl;
    }
}
        
void Game::PlayMenu() {
    // Inside menu
    char ch;
    do {
        DrawMenu();
        switch (ch = _getch())
        {
        case KEY_DOWN:
            if (_chCrnPos[0].first < 17) {
                // Old Frame Choise
                for (uint i=0; i<4; i++) _menuBody[_chCrnPos[i].first][_chCrnPos[i].second] = ' ';
                // New Frame Choise
                _menuBody[_chCrnPos[0].first += 5][_chCrnPos[0].second] = LU;
                _menuBody[_chCrnPos[1].first += 5][_chCrnPos[1].second] = RU;
                _menuBody[_chCrnPos[2].first += 5][_chCrnPos[2].second] = LB;
                _menuBody[_chCrnPos[3].first += 5][_chCrnPos[3].second] = RB;
            }
            break;
        case KEY_UP:
            if (_chCrnPos[0].first > 2) {
                // Old Frame Choise
                for (uint i = 0; i < 4; i++) _menuBody[_chCrnPos[i].first][_chCrnPos[i].second] = ' ';
                // New Frame Choise
                _menuBody[_chCrnPos[0].first -= 5][_chCrnPos[0].second] = LU;
                _menuBody[_chCrnPos[1].first -= 5][_chCrnPos[1].second] = RU;
                _menuBody[_chCrnPos[2].first -= 5][_chCrnPos[2].second] = LB;
                _menuBody[_chCrnPos[3].first -= 5][_chCrnPos[3].second] = RB;
            }
            break;
        case KEY_ENTER:
            switch (_chCrnPos[0].first) {
            case 2:
                // Start New Game
                StartNewGame();
                break;
            case 7:
                // Save Current Game (Write It Into File If Enable)
                SaveGame();
                break;
            case 12:
                // Load Saved Game (Read It From File If Enable)
                LoadSavedGame();
                break;
            case 17:
                // Exit From Game
                Exit();
                break;
            }
        }
        if (ch == KEY_MENU && _isGameLoaded) break;
    } while (1);
}

void Game::StartNewGame() {
    system("cls");
    cout << "\n\n        Your game\n      will be lost!!\n      Are your sure?\n";
    cout << "    [ESC - to cancel]\n\n";
    string confirm;
    confirm += '\t';
    confirm += LU;
    for (uint i = 0; i < 7; i++) confirm += HH;
    confirm += RU;
    confirm += '\n';
    confirm += '\t';
    confirm += VV;
    confirm += " ENTER ";
    confirm += VV;
    confirm += '\n';
    confirm += '\t';
    confirm += LB;
    for (uint i = 0; i < 7; i++) confirm += HH;
    confirm += RB;
    confirm += '\n';
    cout << confirm;

    char ch;
    while (1) {
        ch = _getch();
        if (ch == KEY_ESCAPE) {
            return;
        }
        else if (ch == KEY_ENTER) {
            // Init Start Game
            string mode;
            mode = "\tPLAYER  AI\n\t______    \n";

            while (1) {
                system("cls");
                cout << "\n\n\tPLAY VS ...\n\n";
                cout << mode;
                ch = _getch();
                if (ch == KEY_LEFT) {
                    std::fill(mode.begin()+13, mode.begin()+19, '_');
                    std::fill(mode.begin()+21, mode.begin()+23, ' ');
                }
                else if (ch == KEY_RIGHT) {
                    std::fill(mode.begin() + 13, mode.begin() + 19, ' ');
                    std::fill(mode.begin() + 21, mode.begin() + 23, '_');
                }
                if (ch == KEY_ENTER) break;
            }

            // Detect Game Version
            _gameMode = (mode[13] == '_' ? 1 : 0);
            system("cls");
            cout << "\n\n\t      NICE CHOISE!\n\t";
            cout << (_gameMode ? "Let's Go With Your Opponent..." : "Be Smart. AI Is The One...");
            Sleep(2000);

            // Rebuild Game
            ResetGame();
            system("cls");
            cout << "\n\n\tWait, Creating New Game...";
            Sleep(2000);
            system("cls");
            cout << "\n\n\t\tREADY!";
            Sleep(500);
            Play();
        }
    }
}

void Game::SaveGame() {
    system("cls");
    cout << "\n\n\n";
    if (!_isGameLoaded) {
        cout << "\tThere Is No Game Yet To Save...";
        Sleep(2000);
        return;
    }
    std::ofstream file;
    file.open("game.txt", std::ios::out);
    // Try Opening File With Game Data
    if (!file.is_open()) {
        cout << "\tSorry, Couldn't Save Game Data!";
        Sleep(1500);
        return;
    }
    // Writing Game Data Into File
    try {
        // Board Items
        for (auto it = _board().begin(); it != _board().end(); it++) {
            file << (it[0].empty() ? '?' : it[0][0]) << '\t' << it[0].size();
            file << '\n';
        }
        // Board Fringe Count Items
        file << _board._exitFringeCounters.first << '\t' << _board._exitFringeCounters.second << '\n';
        // Board Fringe X
        for (auto it = _board._exitFringe[0].begin(); it != _board._exitFringe[0].end(); it++) {
            file << *it << '\t';
        }
        file << '\n';
        // Board Fringe O
        for (auto it = _board._exitFringe[1].begin(); it != _board._exitFringe[1].end(); it++) {
            file << *it << '\t';
        }
        file << '\n';
        // CursorPos
        file << _board._cursorPos << '\n';
        // Player1
        file << _player1._countKoshaMoves << '\t' << _player1._playerSymbol << '\t' <<
            _player1._isFirstMove << '\t' << _player1._isLeaveEnable << '\n';
        // Player2
        file << _player2._countKoshaMoves << '\t' << _player2._playerSymbol << '\t' <<
            _player2._isFirstMove << '\t' << _player2._isLeaveEnable << '\n';
        // Zayri
        file << _zyari._zyari.first << '\t' << _zyari._zyari.second << '\n';
        // Game
        file << _gameMode << '\t' << _isWin << '\t' << _isFromHeadValid << '\t';
        file << (_curPlayer == &_player1 ? 'O' : 'X') << '\n';
        file << _curMoveSum << '\t' << _countMoveRequired << '\n';
        file << _isFindingEnd << '\t' << _isMoveComplete << '\n';
        // Enable Moves
        file << _validInitPoses.size() << '\n';
        for (auto& pos : _validInitPoses) file << pos << '\t';
        file << '\n';
        file << _validEndPoses.size() << '\n';
        for (auto& pos : _validEndPoses) file << pos << '\t';
        file << '\n';
        file << _enableMoves.size() << '\n';
        for (auto& pr : _enableMoves) file << pr.first << '\t' << pr.second.first << '\t' << pr.second.second << '\n';
        file << _isMenuActive;

        // Done
        Sleep(1000);
        cout << "\tSaved!";
    }
    catch (std::exception ex) {
        file.clear();
        cout << "\tError Saving Data!";
    }
    file.close();
    Sleep(1000);
    return;
}

void Game::LoadSavedGame() {
    system("cls");
    cout << "\n\n        Your game\n      will be lost!!\n      Are your sure?\n";
    cout << "    [ESC - to cancel]\n\n";
    string confirm;
    confirm += '\t';
    confirm += LU;
    for (uint i = 0; i < 7; i++) confirm += HH;
    confirm += RU;
    confirm += '\n';
    confirm += '\t';
    confirm += VV;
    confirm += " ENTER ";
    confirm += VV;
    confirm += '\n';
    confirm += '\t';
    confirm += LB;
    for (uint i = 0; i < 7; i++) confirm += HH;
    confirm += RB;
    confirm += '\n';
    cout << confirm;

    char ch;
    while ((ch = _getch()) != KEY_ESCAPE) {
        if (ch == KEY_ESCAPE) {
            return;
        }
        else if (ch == KEY_ENTER) {
            // LOAD Game
            system("cls");
            cout << "\n\n\n";
            std::ifstream file;
            file.open("game.txt", std::ios::in);
            if (!file.is_open()) {
                cout << "\tSorry, Couldn't Load Game Data!";
                Sleep(1500);
                return;
            }
            // Writing Game Data Into File
            try {
                ResetGame();
                char sym;
                uint num;
                // Board Items
                for (uint i = 0; i < 24; i++) {
                    file >> sym >> num;
                    if (sym != '?') for (uint k = 0; k < num; k++) _board()[i].push_back(sym);
                }
                // Board Fringe Count Items
                file >> _board._exitFringeCounters.first >> _board._exitFringeCounters.second;
                // Board Fringe X
                for (uint i = 0; i < 15; i++) {
                    file >> _board._exitFringe[0][i];
                }
                cout << endl;
                // Board Fringe O
                for (uint i = 0; i < 15; i++) {
                    file >> _board._exitFringe[1][i];
                }
                // CursorPos
                file >> _board._cursorPos;
                // Player1
                file >> _player1._countKoshaMoves >> _player1._playerSymbol
                    >> _player1._isFirstMove >> _player1._isLeaveEnable;
                // Player2
                file >> _player2._countKoshaMoves >> _player2._playerSymbol
                    >> _player2._isFirstMove >> _player2._isLeaveEnable;
                // Zayri
                file >> _zyari._zyari.first >> _zyari._zyari.second;
                // Game
                file >> _gameMode >> _isWin >> _isFromHeadValid;
                file >> sym;
                _curPlayer = &(sym == 'O' ? _player1 : _player2);
                file >> _curMoveSum >> _countMoveRequired;
                file >> _isFindingEnd >> _isMoveComplete;
                // Enable Moves
                file >> num;
                uint size = num;
                for (uint i = 0; i < size; i++) {
                    file >> num;
                    _validInitPoses.insert(num);
                }
                file >> num;
                size = num;
                for (uint i = 0; i < size; i++) {
                    file >> num;
                    _validEndPoses.insert(num);
                }
                uint p1, p2;
                file >> size;
                for (uint i = 0; i < size; i++) {
                    file >> num >> p1 >> p2;
                    _enableMoves.insert(pair(num, pair{ p1, p2 }));
                }
                file >> _isMenuActive;

                // Done
                Sleep(700);
                cout << "\n\tLoading";
                for (uint i = 0; i < 20; i++) {
                    cout << ".";
                    Sleep(70);
                }
                Play();
            }
            catch (std::exception ex) {
                file.clear();
                cout << "\tError Loading Game Data!";
            }
            file.close();
            return;
        }
    }
}

void Game::ResetGame() {
    _isGameLoaded = true;
    for (auto& vec : _board()) vec.clear();
    _board.FillStarterBoard();
    _board._exitFringeCounters = { 0, 0 };
    for (auto& ar : _board._exitFringe[0]) ar = ToCh(RECT50);
    for (auto& ar : _board._exitFringe[1]) ar = ToCh(RECT50);
    _player1._countKoshaMoves = 2;
    _player1._isFirstMove = true;
    _player1._isLeaveEnable = false;
    _player2._countKoshaMoves = 2;
    _player2._isFirstMove = true;
    _player2._isLeaveEnable = false;
    _isWin = false;
    _isFromHeadValid = true;
    _isFindingEnd = false;
    _isMoveComplete = false;
    _curPlayer = nullptr;
    _countMoveRequired = 0;
    _curMoveSum = 0;
    _validInitPoses.clear();
    _validEndPoses.clear();
    _enableMoves.clear();
}

void Game::Exit() {
    system("cls");
    cout << "\n\n      Are your sure?\n";
    cout << "    [ESC - to cancel]\n\n";
    string confirm;
    confirm += '\t';
    confirm += LU;
    for (uint i = 0; i < 7; i++) confirm += HH;
    confirm += RU;
    confirm += '\n';
    confirm += '\t';
    confirm += VV;
    confirm += " ENTER ";
    confirm += VV;
    confirm += '\n';
    confirm += '\t';
    confirm += LB;
    for (uint i = 0; i < 7; i++) confirm += HH;
    confirm += RB;
    confirm += '\n';
    cout << confirm;

    char ch;
    while ((ch = _getch()) != KEY_ESCAPE) {
        if (ch == KEY_ESCAPE) {
            return;
        }
        else if (ch == KEY_ENTER) {
            // Exit Game
            system("cls");
            cout << "\n\n\n\t   BYE!";
            Sleep(1000);
            system("cls");
            _isExit = true;
            DrawEntry();
            Sleep(250);
            exit(0);
        }
    }
}

void Game::MoveLeft() {
    // If Possible Make Left Move Into Valid Cell
        
    // Finding Init Pos
    if (!_isFindingEnd) {
        auto resFnd = std::find(_validInitPoses.begin(), _validInitPoses.end(), _board._cursorPos);
        if (_board._frame[_board._cursorPos] == ARROW_DOWN && ++resFnd != _validInitPoses.end() && *resFnd < 12 ||
            _board._frame[_board._cursorPos] == ARROW_UP && resFnd != _validInitPoses.begin() && *--resFnd >= 11)
            _board._cursorPos = *resFnd;
    }
    // Finding End Pos
    else {
        auto iterPos = std::find(_validEndPoses.begin(), _validEndPoses.end(), _board._cursorPos);
        if (_board._cursorPos >= 0 && _board._cursorPos < 12 &&
            ++iterPos != _validEndPoses.end() && *iterPos < 12 ||
            iterPos-- != _validEndPoses.begin()) {
                _board._cursorPos = *iterPos;
        }
    }
}

void Game::MoveRight() {
    // If Possible Make Right Move Into Valid Cell

    // Finding Init Pos
    if (!_isFindingEnd) { 
        auto resFnd = std::find(_validInitPoses.begin(), _validInitPoses.end(), _board._cursorPos);
        if (_board._frame[_board._cursorPos] == ARROW_DOWN && resFnd != _validInitPoses.begin() && *--resFnd >= 0 ||
            _board._frame[_board._cursorPos] == ARROW_UP && ++resFnd != _validInitPoses.end() && *resFnd < 24)
            _board._cursorPos = *resFnd;
    }
    // Finding End Pos
    else {
        auto iterPos = std::find(_validEndPoses.begin(), _validEndPoses.end(), _board._cursorPos);
        if (_board._cursorPos >= 12 && _board._cursorPos < 24 &&
            ++iterPos != _validEndPoses.end() && *iterPos < 24 && *iterPos >= 12 ||
            iterPos-- != _validEndPoses.begin()) {
                _board._cursorPos = *iterPos;
        }
    }
}

void Game::MoveUp() {
    // If Possible Make Up Move Into Valid Cell

    // Finding Init Pos
    if (!_isFindingEnd) {
        if (_board._frame[_board._cursorPos] == ARROW_UP) {
            auto resFnd = std::find_if(_validInitPoses.begin(), _validInitPoses.end(), [](auto& pos) {
                return (pos >= 0 && pos < 12) ? true : false;
            });
            if (resFnd != _validInitPoses.end()) _board._cursorPos = *resFnd;
        }
    }
    // Finding End Pos
    else {
        auto iterPos = std::find(_validEndPoses.begin(), _validEndPoses.end(), _board._cursorPos);
        if (_board._cursorPos >= 12 && _board._cursorPos < 24 &&
            iterPos != _validEndPoses.begin() && *--iterPos >=0 && *iterPos < 12) {
            _board._cursorPos = *iterPos;
        }
    }
}

void Game::MoveDown() {
    // If Possible Make Down Move Into Valid Cell

    // Finding Init Pos
    if (!_isFindingEnd) {
        if (_board._frame[_board._cursorPos] == ARROW_DOWN) {
            auto resFnd = std::find_if(_validInitPoses.begin(), _validInitPoses.end(), [](auto& pos) {
                return (pos > 11 && pos < 24) ? true : false;
            });
            if (resFnd != _validInitPoses.end()) _board._cursorPos = *resFnd;
        }
    }
    // Finding End Pos
    else {
        auto iterPos = std::find(_validEndPoses.begin(), _validEndPoses.end(), _board._cursorPos);
        if (_board._cursorPos >= 0 && _board._cursorPos < 12 &&
            ++iterPos != _validEndPoses.end() && *iterPos >= 12 && *iterPos < 24) {
            _board._cursorPos = *iterPos;
        }
    }
}

void Game::MoveEnter() {
    // First Enter
    _validEndPoses.clear();
    static uint oldPos, newPos;
    if (!_isFindingEnd && !_isMoveComplete) {
        // Start Moving
        if (!_enableMoves.empty()) {
            oldPos = _board._cursorPos;
            // Accum Valid End Poses For Current Start Pos
            // Check Moved Zyarya
            uint curLow = _zyari._zyari.second;
            uint curUp = _zyari._zyari.first;
            if (_zyari._zyari.first != _zyari._zyari.second && _curMoveSum != 0) {
                curLow = curUp = (_zyari._zyari.first == _curMoveSum ? _zyari._zyari.second : _zyari._zyari.first);
            }
            auto resFnd = std::for_each(_enableMoves.lower_bound(curLow),
                _enableMoves.upper_bound(curUp),
                [&](auto& pr) {
                    if (_board._cursorPos == pr.second.first) {
                        _validEndPoses.insert(pr.second.second);
                    }
                }
            );
            _board._cursorPos = *_validEndPoses.begin();
            _isFindingEnd = true;
            return;
        }
    }
    // Second Enter
    if (_isFindingEnd && !_isMoveComplete) {

        // Check Double-Kosha At First Move
        if (_curPlayer == &_player1 && oldPos == 0 || (_gameMode && _curPlayer == &_player2 && oldPos == 12)) {
            if (_zyari.IsKosha() && _curPlayer->_isFirstMove)
                if (_curPlayer->_countKoshaMoves < 2) _curPlayer->_countKoshaMoves++;
                else _curPlayer->_isFirstMove = false;
            else {
                _isFromHeadValid = false;
                _curPlayer->_isFirstMove = false;
            }
        }

        newPos = _board._cursorPos;
        // Check Move From Bigger To Less (Prevent Overflow Pos Number)
        _curMoveSum += (newPos < oldPos ?
            24 - std::abs(static_cast<int>(newPos) - static_cast<int>(oldPos)) : newPos - oldPos);

        // End Moving
        _board()[oldPos].pop_back();
        // Popout Figure When Exit
        if (_curPlayer->_isLeaveEnable && newPos >= (_curPlayer == &_player1 ? 0 : 12)) {
            _board._exitFringe[_curPlayer == &_player2 ? 0 : 1][(_curPlayer == &_player2 ? _board._exitFringeCounters.first : _board._exitFringeCounters.second)++] = _curPlayer->_playerSymbol;
        }
        else {
            _board()[newPos].push_back(_curPlayer->_playerSymbol);
        }

        _isFindingEnd = false;
        _isMoveComplete = true;

        _validInitPoses.clear();
        _validEndPoses.clear();
    }
}

void Game::MoveCancel() {
    // Cancel Moving
    _board._cursorPos = *_validInitPoses.begin();
    _validEndPoses.clear();
    _validInitPoses.clear();
    _isMoveComplete = false;
    _isFindingEnd = false;
}

void Game::DrawMoves() {
    // Show Enable Moves Matrix With Count Of Required Moves
    cout << "\nEnable moves:\n";
    std::for_each(_enableMoves.begin(), _enableMoves.end(), [this](pair<const uint, pair<uint, uint>>& thePair) {
        cout << "zr[" << thePair.first << "]:\t";
        cout << thePair.second.first << " -> " << thePair.second.second << endl;
    });
    cout << "FROM:\t";
    std::for_each(_validInitPoses.begin(), _validInitPoses.end(), [](auto& pos) {
        cout << pos << " ";
        });
    cout << "\nWHERE:\t";
    std::for_each(_validEndPoses.begin(), _validEndPoses.end(), [](auto& pos) {
        cout << pos << " ";
    });
    cout << endl;
    cout << "Kosha N : " <<_curPlayer->_countKoshaMoves << endl;
}

void Game::Draw() {
    // GAME 
    system("cls");
    if (_isMoveComplete) {
        _board._cursorPos = *_validInitPoses.begin();
    }
    _board.DrawBoard();
    _zyari.DrawZyari();
    cout << "      PLAYER " << (_curPlayer == &_player1 ? '1' : '2') << " MOVES\n";
    if (_enableMoves.empty()) cout << "         NO MOVES\n Press Enter To Skip Move\n";
    // else DrawMoves(); // Show All Enable Move Cells
    if (!_isFindingEnd && !_isMoveComplete) cout << "   CHOISE START POSITION";
    if (_isFindingEnd) cout << "   CHOISE END POSITION";
    if (_isMoveComplete) {
        _isMoveComplete = false;
        cout << "         MOVE DONE";
    }
    cout << "\n    Moves:\t" << _curMoveSum << " / " << _countMoveRequired << endl;
}

void Game::WhoMoves() {
    uint t1, t2;
    do {
        t1 = _zyari.MakeRnd(1, 6);
        t2 = _zyari.MakeRnd(1, 6);
    } while (t1 == t2);
    _curPlayer = &(t1 > t2 ? _player1 : _player2);
    _board._cursorPos = (_curPlayer == &_player1 ? 0 : 12);
}

void Game::SwitchPlayer() {
    _curPlayer = &(_curPlayer == &_player1 ? _player2 : _player1);
}

// Helper To Find Count of Player's items in array's range
// Use it for check IsExitEnable (last field in game flow)
uint Game::CountPlayerItemsInRange(char sym, uint fromIdx, uint toIdx) {
    uint total = 0;
    std::for_each(_board().begin() + fromIdx, _board().begin() + toIdx + 1, [&](vector<char>& col) {
        if (col.size() > 0 && col[0] == sym) {
            total += col.size();
        }
    });
    return total;
}

// Helper Method Find Count Of NearBy Equal Cells
uint Game::GetNearbyCellsMaxCount(Player* curPlr, vChIt itBeg, vChIt itEnd) {
    vChIt it = itBeg - 1;
    int maxN = 0;
    int N = 0;
    do {
        it = std::adjacent_find(it + 1, itEnd + 1, [&](vector<char>& v1, vector<char>& v2) {
            // Both Cells Are Equal (Player Symb)
            if (v1.size() != 0 && v2.size() != 0 && 
                v1[0] == curPlr->_playerSymbol && v2[0] == curPlr->_playerSymbol) {
                N++;
                maxN = max(maxN, N);
                return false;
            }
            // Cells Differ
            maxN = max(maxN, N);
            N = 0;
            return true;
        });
    } while (it != itEnd+1);
    return ++maxN;
}

// Helper Find Enemy Symbol
char Game::GetEnemySymb() {
    return _curPlayer == &_player1 ? _player2._playerSymbol : _player1._playerSymbol;
}

// Helper To Check Are Previous Cells Empty
bool Game::IsPrevCellEmpty(uint curCell) {
    for (uint idx = (_curPlayer == &_player1 ? 18 : 6); idx < curCell; idx++) {
        if (_board()[idx].size() != 0 && _board()[idx][0] == _curPlayer->_playerSymbol) {
            return false;
        }
    }
    return true;
}

// Helper To Check Is The Starter Cell Is Valid To Move From
// Involves The Value Of Zyari
bool Game::IsInitPosValid(uint from, uint deltaZr) {
        
    uint finPos = from + deltaZr; // Find End Position
    // Try To Exit
    if (_curPlayer == &_player1 ? (finPos > 23) : (from > 5 && from < 12 && finPos > 11)) {
        if (IsAllReadyToExit() == true || _curPlayer->_isLeaveEnable == true) {
            _curPlayer->_isLeaveEnable = true;
            // Check The Start Pos Is Valid To Leave The Board
            // Precise Match
            if (_curPlayer == &_player1 ? (finPos == 24) : (finPos == 12)) {
                return true;
            }
            // Greater FinPos But Match To Leave
            else {
                // Check Are Prev Items Not Exist
                if ((_curPlayer == &_player1 ? (finPos > 24) : (finPos > 12)) && IsPrevCellEmpty(from)) {
                    return true;
                }
            }
        }
        return false;
    }
    // Inner Field
    else {
        // X-Transition Down->Up
        if (_curPlayer == &_player2 && finPos > 23) {
            finPos -= 24;
        }
        // Check Own Or Empty Cell To Move
        if (_board()[finPos].size() > 0) {
            if (_board()[finPos][0] != _curPlayer->_playerSymbol) {
                return false;
            }
        }
        // Check Cell Is Empty To Avoid Blocking On First X-Move
        else {
            // No One Enemy And EndPos Are At Home Fields 
            if (_curPlayer == &_player1 ? (finPos > 0 && finPos < 12) : (finPos > 12 && finPos < 24)) {
                // No One Enemy Figure Yet
                uint pos1 = (_curPlayer == &_player1 ? 6 : 18);
                uint pos2 = (_curPlayer == &_player1 ? 11 : 23);
                uint posSt = (_curPlayer == &_player1 ? 0 : 12);
                if (CountPlayerItemsInRange(GetEnemySymb(), pos1, pos2) == 0) {
                    // Try To Put In The Fin-Figure (For Checking 6 figures at least)
                    _board()[finPos].push_back(_curPlayer->_playerSymbol); // ONLY TRY
                    _board()[from].pop_back(); // ONLY TRY
                    if (GetNearbyCellsMaxCount(_curPlayer, _board().begin() + posSt, _board().begin() + pos2) >= 6) {
                        _board()[from].push_back(_curPlayer->_playerSymbol); // ONLY TRY
                        _board()[finPos].clear(); // ONLY TRY
                        return false;
                    }
                    else {
                        _board()[from].push_back(_curPlayer->_playerSymbol); // ONLY TRY
                        _board()[finPos].clear(); // ONLY TRY
                        return true;
                    }
                }
            }
        }
        return true;
    }
}

// Helper Method To Check Are All Figs At IV-field And Ready To Exit 
bool Game::IsAllReadyToExit() {
    if ((_curPlayer == &_player1 && CountPlayerItemsInRange(_curPlayer->_playerSymbol, 18, 23) == 15) ||
        (_curPlayer == &_player2 && CountPlayerItemsInRange(_curPlayer->_playerSymbol, 6, 11) == 15)) {
        return true;
    }
    return false;
}

// Helper Method To Search In Board Good Poses
void Game::MovesFinding() {

    // Player Start Positions Search
    vector<uint> startPoses;
    uint idx = 0;
    std::for_each(_board().begin(), _board().end(), [&](vector<char> &col) {                
        if (col.size() > 0 && col[0] == _curPlayer->_playerSymbol) {
            startPoses.push_back(idx);
        }
        ++idx;
    });

    // First Kosha-Head-Move
    if (_curPlayer->_isFirstMove == true && _zyari.IsKosha() == true) {
        uint stPos = (_curPlayer == &_player1 ? 0 : 12);
        if (_board()[stPos].size() > 13) {
            if (IsInitPosValid(stPos, _zyari._zyari.first)) {
                _enableMoves.insert({ _zyari._zyari.first, {stPos, stPos + _zyari._zyari.first} });
                startPoses.erase(std::find(startPoses.begin(), startPoses.end(), stPos));
            };
        }
    }

    // Search Place To Move 
    std::for_each(startPoses.begin(), startPoses.end(), [this](uint& stPos) {
        // First Zyarya
        if (IsInitPosValid(stPos, _zyari._zyari.first)) {
            uint sum1 = stPos + _zyari._zyari.first;
            if (sum1 > 23) sum1 -= 24;
            _enableMoves.insert({ _zyari._zyari.first, {stPos, sum1} });
        };
        if (!_zyari.IsKosha()) {
            // Second Zyarya (If Differ)
            if (IsInitPosValid(stPos, _zyari._zyari.second)) {
                uint sum2 = stPos + _zyari._zyari.second;
                if (sum2 > 23) sum2 -= 24;
                _enableMoves.insert({ _zyari._zyari.second, {stPos, sum2} });
            };
        }
    });

    // Check Zyarya-moves are enable
    bool noZ1 = _enableMoves.contains(_zyari._zyari.first);
    bool noZ2 = _enableMoves.contains(_zyari._zyari.second);

    // No moves
    if ((!noZ1 && !noZ2)) {
        _enableMoves.clear();
    }
    // Only 1 zyarya enable
    else if (!noZ1 || !noZ2) {
        uint emptyZyarya = (noZ1 ? _zyari._zyari.second : _zyari._zyari.first);
        uint validZyarya = (noZ1 ? _zyari._zyari.first : _zyari._zyari.second);
        // Correct Enable Moves According To Blocking Rule
        if (!_enableMoves.contains(emptyZyarya)) {
            cout << "NO " << emptyZyarya << endl;
            // Collect Potential Bad Init Poses to Remove 
            vector<uint> badInitIndices;
            uint nextInit, nextFin, countGoodIndices = 0;
            for (auto it = _enableMoves.begin(); it != _enableMoves.end(); it++) {
                nextInit = it->second.second;
                nextFin = nextInit + emptyZyarya;
                // Down-Up X-Transition
                if (_curPlayer == &_player2 && nextFin > 23) nextFin -= 24;
                // Check Is This Cell Valid To Move Into
                if (nextFin < 24 && nextFin != GetEnemySymb()) {
                    // ONLY TRY
                    _board()[nextFin].push_back(_curPlayer->_playerSymbol);
                    if (IsInitPosValid(nextInit, emptyZyarya) == false) {
                        badInitIndices.push_back(it->second.first);
                    }
                    else {
                        ++countGoodIndices;
                    }
                    _board()[nextFin].pop_back();
                }
            }
            // Clearing Enable Moves If Needed
            if (countGoodIndices) {
                for (auto vecIt = badInitIndices.begin(); vecIt != badInitIndices.end(); vecIt++) {
                    for (auto it = _enableMoves.begin(); it != _enableMoves.end(); it++) {
                        if (it->second.first == *vecIt) {
                            _enableMoves.extract(it);
                        }
                    }
                }
            }
        }
    }

    // Collect All Zyarya Cells
    uint curLow = _zyari._zyari.second;
    uint curUp = _zyari._zyari.first;
    if (_zyari._zyari.first != _zyari._zyari.second && _curMoveSum != 0) {
        curLow = curUp = (_zyari._zyari.first == _curMoveSum ? _zyari._zyari.second : _zyari._zyari.first);
    }

    std::for_each(_enableMoves.lower_bound(curLow), _enableMoves.upper_bound(curUp),
        [&, this](auto& pr) {
            _validInitPoses.insert(pr.second.first);
    });

    if (!_isFromHeadValid) {
        _validInitPoses.erase(_curPlayer == &_player1 ? 0 : 12);
        _enableMoves.extract(_curPlayer == &_player1 ? 0 : 12);
    }

    // Move To Exit
    if (_curPlayer->_isLeaveEnable) {
        _enableMoves.erase(_curPlayer == &_player1 ? 0 : 12);
        _validInitPoses.erase(_curPlayer == &_player1 ? 0 : 12);
    }

    // If No Moves More Should To Switch Player
    if (_validInitPoses.empty()) {
        _countMoveRequired = _curMoveSum;
        _enableMoves.clear();
    }
}

// AI Move Logic
void Game::AIMove() {
    cout << "\n      Wait, please.\n AI is thinking hardly...";
    // No moves
    if (_enableMoves.empty()) {
        cout << "NO MOVES FOR AI. SKIP.";
        return;
    }
    // There're some moves
    else {
        // AI Random Logic

        // Check Moved Zyary
        if (_curMoveSum && !_zyari.IsKosha()) {
            _enableMoves.erase(_curMoveSum);
        }

        // Find Valid Init Poses
        std::for_each(_enableMoves.lower_bound(_zyari._zyari.second),
                        _enableMoves.upper_bound(_zyari._zyari.first),
                        [&](auto& pr) {
                        _validInitPoses.insert(pr.second.first);
                        }
        );

        // Prevent Double Moving From Head Per WholeMowe
        if (_curPlayer->_isFirstMove && _zyari.IsKosha() && _curPlayer->_countKoshaMoves > 0)
            --_curPlayer->_countKoshaMoves;
        else if ((!_isFromHeadValid && (!_curPlayer->_isFirstMove || !_zyari.IsKosha())) || (_curPlayer->_isFirstMove && !_zyari.IsKosha() && !_curPlayer->_countKoshaMoves))
            _validInitPoses.erase(12);
        else if (_isFromHeadValid && (!_curPlayer->_isFirstMove || !_zyari.IsKosha()))
            _isFromHeadValid = false;

        // Choise Pos From
        uint rndIdx = _zyari.MakeRnd(0, _validInitPoses.size());
        uint pickedInit = *_validInitPoses.begin(), k = 0;
        for (auto it = _validInitPoses.begin(); it != _validInitPoses.end(); it++, k++) {
            if (k == rndIdx) pickedInit = *it;
        }
        cout << "\nWant to go from " << pickedInit;

        if (pickedInit == 12) _isFromHeadValid = false;

        // Find Valid End Poses
        std::for_each(_enableMoves.lower_bound(_zyari._zyari.second), 
                        _enableMoves.upper_bound(_zyari._zyari.first),
                        [&](auto& pr) {
                        if (pickedInit == pr.second.first) {
                            _validEndPoses.insert(pr.second.second);
                        }
                        }
        );

        // Choise Pos To
        rndIdx = _zyari.MakeRnd(0, _validEndPoses.size());
        uint pickedEnd = *_validEndPoses.begin(), p = 0;
        for (auto it = _validEndPoses.begin(); it != _validEndPoses.end(); it++, p++) {
            if (p == rndIdx) pickedEnd = *it;
        }
        cout << " to " << pickedEnd << endl;
        _board._cursorPos = pickedInit;
        Sleep(1000);
        //cin.get();

        // Remove Old Pos Figure
        _board()[pickedInit].pop_back();

        // Adding New Pos Figure (Or Move Away If Exit Is Enable)
        if (_curPlayer->_isLeaveEnable && pickedEnd >= 12) {
            _board._exitFringe[0][(_board._exitFringeCounters.first++)] = _curPlayer->_playerSymbol;
            _board._cursorPos = 12;
        }
        else {
            _board()[pickedEnd].push_back(_curPlayer->_playerSymbol);
            _board._cursorPos = pickedEnd;
        }

        // Check Move From Bigger To Less (Prevent Overflow Pos Number)
        _curMoveSum += (pickedEnd < pickedInit ?
            24 - std::abs(static_cast<int>(pickedEnd) - static_cast<int>(pickedInit)) : pickedEnd - pickedInit);
        Sleep(1000);
        //cin.get();

        // Clear Old Sets
        _validInitPoses.clear();
        _validEndPoses.clear();
    }
}

// Main Move Logic
void Game::WholeMove() {
    // Head-Move Is Enable At First
    _isFromHeadValid = true;
    // Moves Required By Zyari
    _countMoveRequired = (_zyari.IsKosha() ? _zyari._zyari.first * 4 : _zyari._zyari.first + _zyari._zyari.second);
    // Current Sum Of Moves
    _curMoveSum = 0;

    // Move Till End
    do {
        _enableMoves.clear();
        MovesFinding();
        Draw();
        (!_gameMode && _curPlayer == &_player2) ? AIMove() : MakeMove();
    } while (_curMoveSum != _countMoveRequired && !_enableMoves.empty());
    _isMoveComplete = true;

    if (_curPlayer == &_player2 && !_gameMode) _curPlayer->_isFirstMove = false;
    if (_board._exitFringeCounters.first == 15 || _board._exitFringeCounters.second == 15) _isWin = true;
}

// Player Keyboard Input 
void Game::MakeMove() {
    char key;
    _kbhit();
    key = _getch();
    // Cases Of Inputs
    switch (key) {
    case KEY_UP: MoveUp(); break;
    case KEY_DOWN: MoveDown(); break;
    case KEY_LEFT: MoveLeft(); break;
    case KEY_RIGHT: MoveRight(); break;
    case KEY_ENTER: MoveEnter(); break;
    case KEY_ESCAPE: MoveCancel(); break;
    case KEY_MENU: if (_isFindingEnd && !_isMoveComplete) return; PlayMenu(); break;
    }
}

// Start Game
void Game::Play()
{
    WhoMoves();
    do {
        _zyari.Drop();
        WholeMove();
        if (_isWin) break;
        SwitchPlayer();
    } while (1);
    // Win State
    if (_isWin) {
        system("cls");
        cout << "\n\t" << (_curPlayer == &_player1 ? "YOU WIN!" : "YOU LOOSE!");
        _isGameLoaded = false;
        Sleep(2000);
        PlayMenu();
    }
}

void Game::Start() {
    PlayMenu();
}