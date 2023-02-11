#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <array>
#include <list>
#include <map>
#include <set>
#include <ctime>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <random>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::pair;
using std::string;
using std::array;
using std::vector;
using std::set;
using std::multimap;

// CLASSES DEFINITIONS /////////////////////////////////////////////////////////////////
// Simplifying Unsigned Integer Type Declaration
typedef size_t uint;
typedef std::array<vector<char>, 24>::iterator vChIt;

// Helper Inline Function To Simplify Char-Convertation
constexpr char ToCh(uint type) { return static_cast<char>(type); }

// Collection Of Constant Symbols 
enum Chars {
    // FIGURES
    _X = 'X', _O = 'O',
    // FRAMES
    LU = 201, RU = 187, LB = 200, RB = 188, HH = 205, VV = 186, HB = 202, HU = 203,
    // FILLRECTS
    RECT25 = 176, RECT50 = 177, RECT75 = 178, RECT100 = 219, SQR = 254,
    // TARGETS
    CRS1 = 197, CRS2 = 206, CRSCIR = 253,
    // KEYBOARD GAMEPLAY
    KEY_ENTER = 13, KEY_ESCAPE = 27, KEY_UP = 72, KEY_DOWN = 80, KEY_LEFT = 75, KEY_RIGHT = 77,
    // KEYBOARD MENU
    KEY_MENU = 'm', KEY_NEW_GAME = 'n', KEY_LOAD_GAME = 'l',
    KEY_SAVE_GAME = 's', KEY_QUIT_GAME = 'q', KEY_STARTER_GAME = 'e', KEY_GENERATE_GAME = 'g',
    // ARROWS
    ARROW_UP = 30, ARROW_DOWN = 31
};

// Helper Lambda Object To Write Data Into Console Flow (without whitespace separator)
template<typename T> std::ostream_iterator<T> out(cout, "");
// Helper Lambda Object To Write Data Into Console Flow (with whitespace separator)
template<typename T> std::ostream_iterator<T> outSpace(cout, " ");

// CLASSES DEFINITIONS /////////////////////////////////////////////////////////////////
// Class Of Classic Gaming Cube 1-6 Numerated
// (In Indigenous Game Cube Called "Zyarya")
class Zyari {
private:
    // The Way To Have Access To Any Part Of Game
    friend class Game;
    // Body Of Zyari UI
    array<array<char, 26>, 5> _cubeUI;
    // Both Zyari Values
    pair<uint, uint> _zyari;
    // Random Generating Engine
    std::default_random_engine _dre;
    // Random Generating Device
    std::random_device _rd;
    // Adjucent Randomization
    std::uniform_int_distribution<> _uid;
public:
    // CTOR (Initialize Randomizer)
    Zyari();
    // Check If The Both Zyarya Values Are Equal
    // (In Indigenous Game This State Called "Kosha")
    bool IsKosha();
    // Randomize The Values Of Zyari
    uint MakeRnd(uint x1, uint x2);
    // "Drop" zyari (Get Random Values For Player Next Move)
    const pair<uint, uint>& Drop();
    // Show Zyari In Gameflow
    void DrawZyari();
};

// Board Moving Testing Interface Required To Be Definited In Gameboard Class
// Simplify Moving Validation Test 
class IBoardTest {
public:
    virtual void FillBlockingBoard() = 0;
    virtual void Fill_IV_Board() = 0;
    virtual void Fill_IV_Board_With_Enemy() = 0;
    virtual void Fill_ALMOST_IV_Board() = 0;
    virtual void FillRandomBoard() = 0;
    virtual void FillBlockFullMoveBoard() = 0;
    virtual void FillNoMoves() = 0;
};

// Moveable Interface Required To Be Definited In Main Game Class
// To Be Enable To Move In Game / Make Menu Choises
class IMoveable {
public:
    virtual void MoveRight() = 0;
    virtual void MoveLeft() = 0;
    virtual void MoveUp() = 0;
    virtual void MoveDown() = 0;
    virtual void MoveEnter() = 0;
    virtual void MoveCancel() = 0;
};

// Drawable Interface Required To Be Definited In Main Game Class
class IDrawable {
public:
    virtual void DrawMoves() = 0;
    virtual void DrawMenu() = 0;
    virtual void Draw() = 0;
    virtual void DrawEntry() = 0;
};

// Gameboard Class With All Required Methods And Attributes
class Board : public IBoardTest {
private:
    // The Way To Have Access To Any Part Of Game
    friend class Game;
    // Helper Constants For Drawing Gameboard
    const uint _BOARD_WIDTH = 26;
    const uint _BOARD_HEIGHT = 32;
    const uint _COLS_COUNT = 24;
    const uint _ROWS_COUNT = 30;
    // Current Cursor Position 
    uint _cursorPos;
    // The Side Of Gameboard Contains Player Leaved Figures
    array<array<char, 15>, 2> _exitFringe;
    // Counters Of Player Leaved Figures
    pair<uint, uint> _exitFringeCounters;
    // Board Frame Contains Current Cursor
    array<char, 24> _frame;
    // Game Board Containes Player Figures
    array<vector<char>, 24> _board;
public:
    // CTOR With Initial Filled Player Figures
    Board();
    // Use Overloading To Simplify Board Query
    auto& operator()();
    // Draw Game Board
    void DrawBoard();
    // Starter Positions Of Players
    void FillStarterBoard();
    // Test Method Block /////////////////////////////////////
    void FillBlockingBoard() override;
    // Player's Figures Go Outside The Gameboard
    void Fill_IV_Board() override;
    // Player Has Enemies On His Way To Leave The Board
    void Fill_IV_Board_With_Enemy() override;
    // Player's Figures Are Almost Ready To Leave The Board
    void Fill_ALMOST_IV_Board() override;
    // Randomly Filled Gameboard (Middle Game State Imitation)
    void FillRandomBoard() override;
    // Totally Filled Gameboard Fields
    void FillBlockFullMoveBoard() override;
    // There're No Moves Almost For Player
    void FillNoMoves() override;
    //////////////////////////////////////////////////////////
};

// Class Incapsulates All Required Player's Attributes
class Player {
private:
public:
    char _playerSymbol;
    bool _isFirstMove = true;
    bool _isLeaveEnable = false;
    uint _countKoshaMoves = 2;
};

// Main Game Class Incapsulates All Required Game Elements And Attributes
class Game : public IMoveable, public IDrawable {
private:
    // Is Menu Open
    bool _isMenuActive;
    // Is Game Is Exit (Animation Mode)
    bool _isExit;
    // Is Game Is Load (Validation File Data)
    bool _isGameLoaded;
    // 1 - Player vs Player | 2 - Player vs AI 
    bool _gameMode;
    // Is Any Player Has Win The Game
    bool _isWin;
    // Is Valid Move From Head Cell
    bool _isFromHeadValid;
    // Is Player Has Found Cell To Move Into
    bool _isFindingEnd;
    // Is Current Move Is Done
    bool _isMoveComplete;
    // Menu Items Data
    array<array<char, 14>, 24> _menuBody;
    // Coordinates Of Activated Menu Choise Items
    array<pair<uint, uint>, 4> _chCrnPos;
    // Two Typicle Game Cubes
    Zyari _zyari;
    // All Cells Info
    Board _board;
    // Player Moves O (Home Is 0-Pos)
    Player _player1;
    // Player Moves X (Home Is 12-Pos)
    Player _player2;
    // Current Player Pointer 
    Player* _curPlayer;
    // Total Required Cell-Sum To Move
    uint _countMoveRequired;
    // Current Accumulated Cell-Sum Od Moves
    uint _curMoveSum;
    // Valid Cells Player Can Make Current Move From
    std::set<uint> _validInitPoses;
    // Valid Cells Player Can Make Current Move Into
    std::set<uint> _validEndPoses;
    // Total Current Move Valid Data Info 
    multimap<uint, pair<uint, uint>> _enableMoves;
public:
    // CTOR With Default Settings
    Game();
    // User UI Start Method
    void Start();
private:
    // Construct Menu Items Data
    void InitMenuBody();
    // Init Game Menu
    void PlayMenu();
    // Initialize New Game
    void StartNewGame();
    // Save Current Game State (Write Data Into File)
    void SaveGame();
    // Loading Previously Saved Game (Read Data From File)
    void LoadSavedGame();
    // Restart Game
    void ResetGame();
    // Exit Game
    void Exit();
    // Arrow Left
    void MoveLeft() override;
    // Arrow Right
    void MoveRight() override;
    // Arrow Up
    void MoveUp() override;
    // Arrow Down
    void MoveDown() override;
    // Start Or Confirm Moving / Confirm Menu Choise
    void MoveEnter() override;
    // Cancel Current Initial Move / Cancel Menu Action
    void MoveCancel() override;
    // Show Total Info About Current Enable Moves (Deactivated)
    void DrawMoves() override;
    // Show UI Menu 
    void DrawMenu() override;
    // Incapsulates All Partitial Drawing Method
    void Draw() override;
    // Some UI Intro/Outro Animation
    void DrawEntry() override;
    // Detect Which Player Is Required To Move
    void WhoMoves();
    // Switch Player If Whole Move Is Done Or There're No Moves 
    void SwitchPlayer();
    // Helper To Find Count Of Player's Items In Array's Range
    // Use It For Check IsExitEnable (Last Field In Game Flow)
    uint CountPlayerItemsInRange(char sym, uint fromIdx, uint toIdx);
    // Helper Method Find Count Of NearBy Equal Cells
    uint GetNearbyCellsMaxCount(Player* curPlr, vChIt itBeg, vChIt itEnd);
    // Helper Find Enemy Symbol
    char GetEnemySymb();
    // Helper To Check Are Previous Cells Empty
    bool IsPrevCellEmpty(uint curCell);
    // Helper To Check Is The Starter Cell Is Valid To Move From
    // Involves The Value Of Zyari
    bool IsInitPosValid(uint from, uint deltaZr);
    // Helper Method To Check Are All Figs At IV-field And Ready To Exit 
    bool IsAllReadyToExit();
    // Helper Method To Search In Board Good Poses
    void MovesFinding();
    // AI Move Logic
    void AIMove();
    // Main Move Logic
    void WholeMove();
    // Player Keyboard Input 
    void MakeMove();
    // Start Game
    void Play();
};