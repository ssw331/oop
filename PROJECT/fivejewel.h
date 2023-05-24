#pragma once

#include <queue>
using namespace std;

#define JEWELST 25
#define CELL 50
#define DEFAULTCOL 9

int get_jewel_color(int x, int y);

class jewel;
class win_score;
class map;

class Controller
{
protected:
	int score;
	int valid_move[8][2];  // ¼ì²é·½Ïò´æ´¢
	friend jewel;
	friend win_score;
	friend map;
public:
	Controller();
};

class jewel : public Controller
{
private:
	int j_x;
	int j_y;
	int j_color;  
	friend Controller;
public:
	jewel();
	jewel(int x, int y);
	jewel(const jewel& j);
	int check_score(jewel J[],map& M, int& itr);
	int random_color();
	int get_j_position_x();
	int get_j_position_y();
	void set_new_position(int x, int y);
	void set_new_color(int COLOR);
	int get_color();
	int be_gotten(ExMessage m);
	void print_j();
};

class board : public Controller
{
private:
	int b_x;
	int b_y;
public:
	board();
	board(int x, int y);
	int get_board_size(int xory);
	void be_choosen(int& ch_x, int& ch_y, ExMessage m);
};

class windows
{
protected:
	int w_x;
	int w_y;
public:
	windows();
};

class win_jewel : public windows
{
private:
	jewel* J;
	jewel* previous_J;  // for backtrace
	friend void random_create_jewels(jewel J[], int& j, int create_num, win_jewel win);
	friend board;  // for next create on board
public:
	win_jewel();
	win_jewel(int x, int y);
	void refresh();
	bool traceback();
	void add_jewel(jewel Jew[], int& itr);
};

class win_score : public windows
{
private:
	int previous_score;
	int score;
public:
	win_score();
	win_score(int x, int y);
	void addscore(int add);
	void refresh();
	bool traceback();
};

class map
{
private:
	int m[DEFAULTCOL][DEFAULTCOL];
	Controller* C;
	queue<int> bfs_x, bfs_y;
	int way[DEFAULTCOL][DEFAULTCOL];
	int visited[DEFAULTCOL][DEFAULTCOL];
	friend jewel;
public:
	map();
	map(board& B, jewel J[], int n);
	void renew(jewel J[], int n);
	bool BFS(int st_x, int st_y, int end_x, int end_y, jewel& j);
	void printway(int st_x, int st_y, int color);
	~map();
};

void random_create_jewels(jewel J[], int& j, int create_num);

void random_create_jewels(jewel J[], int& j, int create_num, win_jewel win);

void init(jewel J[], int& itr);  // reset