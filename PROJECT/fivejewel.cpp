#include <iostream>
#include <graphics.h>
#include <conio.h>
#include <queue>
#include <stack>
#include <string>
#include "fivejewel.h"
using namespace std;

int COLOR[] = {BLUE, GREEN, CYAN, RED, MAGENTA, LIGHTBLUE, LIGHTCYAN};

unsigned int seed = time(0);

int main()
{
	//int mode = 0;  // 模式切换 默认鼠标
	//cout << "请选择游玩模式：0 鼠标;1 键盘" << endl;
	//cout << "你的选择是:";
	//while (1)
	//{ 
	//	cin >> mode;
	//	if (mode > 1 || !cin.good())
	//	{
	//		cin.clear();
	//		cin.ignore(999, '\n');
	//		cout << "无此模式，请重新输入。" << endl;
	//	}
	//	else
	//		break;
	//}
	initgraph(DEFAULTCOL * CELL + 500, DEFAULTCOL * CELL);
reset:
	board B(DEFAULTCOL, DEFAULTCOL);
	jewel J[81];
	win_jewel W(DEFAULTCOL, 0);
	win_score W_S(DEFAULTCOL + 1, 2);
	int itr = 0;
	init(J, itr);
	map M(B, J, 81);
	W.refresh();
	W_S.refresh();
	int ch_x = -1, ch_y = -1;
	int st_x = -1, st_y = -1;
	int index = -1;
	while (1)
	{
		ExMessage m;
		m = getmessage(EX_MOUSE | EX_KEY);

		//if (mode)
		//{
		//	settextcolor(BLACK);
		//	RECT r = { (DEFAULTCOL + 1) * CELL, 4 * CELL + CELL, (DEFAULTCOL + 5) * CELL + 3 * CELL, 4 * CELL + 2 * CELL };
		//	drawtext(_T("                                                    "), &r, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		//	settextcolor(WHITE);
		//	drawtext(_T("列号：0-9；行号：A-I。请依次输入起始位置的列号与行号"), &r, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		//}

		for (int i = 0; i < DEFAULTCOL * DEFAULTCOL; i++)
		{
			if (J[i].be_gotten(m) == 1 && st_x < 0 && st_y < 0)
			{
				setlinecolor(WHITE);
				st_x = J[i].get_j_position_x();
				st_y = J[i].get_j_position_y();
				circle(st_x * 50 + JEWELST, st_y * 50 + JEWELST, 12);
				index = i;
				break;
			}
			else if (J[i].be_gotten(m) == 2 && st_x >= 0 && st_y >= 0)
			{
				setlinecolor(J[i].get_color());
				circle(J[i].get_j_position_x() * 50 + JEWELST, J[i].get_j_position_y() * 50 + JEWELST, 12);
				st_x = -1;
				st_y = -1;
				index = -1;
				break;
			}
		}
		//if (mode) // 键盘模块
		//{
		//	int f = 0;
		//	do
		//	{
		//		if ((m.vkcode <= '8' && m.vkcode >= '0'))
		//		{
		//			st_x = m.vkcode - '0';
		//		}
		//		else if ((m.vkcode >= 'A' && m.vkcode <= 'I'))
		//		{
		//			st_y = m.vkcode - 'A';
		//		}
		//		else if ((m.vkcode >= 'a' && m.vkcode <= 'i'))
		//		{
		//			st_y = m.vkcode - 'a';
		//		}
		//		for (int i = 0; i < DEFAULTCOL * DEFAULTCOL; i++)
		//		{
		//			if (J[i].be_gotten(st_x, st_y) == 1)
		//			{
		//				setlinecolor(WHITE);
		//				circle(st_x * 50 + JEWELST, st_y * 50 + JEWELST, 12);
		//				index = i;
		//				f = 1;
		//			}
		//		}
		//	} while (!f);

		//	settextcolor(BLACK);
		//	RECT r = { (DEFAULTCOL + 1) * CELL, 4 * CELL + CELL, (DEFAULTCOL + 1) * CELL + 3 * CELL, 4 * CELL + 2 * CELL };
		//	drawtext(_T("                                                    "), &r, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		//	settextcolor(WHITE);
		//	drawtext(_T("列号：0-9；行号：A-I。请依次输入目标位置的列号与行号"), &r, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
		//	do
		//	{
		//		if ((m.vkcode <= '8' && m.vkcode >= '0'))
		//		{
		//			ch_x = m.vkcode - '0';
		//		}
		//		else if ((m.vkcode >= 'A' && m.vkcode <= 'I'))
		//		{
		//			ch_y = m.vkcode - 'A';
		//		}
		//		else if ((m.vkcode >= 'a' && m.vkcode <= 'i'))
		//		{
		//			ch_y = m.vkcode - 'a';
		//		}
		//	} while (!B.be_choosen(ch_x, ch_y));
		//	bool flag = M.BFS(st_x, st_y, ch_x, ch_y, J[index]);
		//	st_x = st_y = -1;
		//	ch_x = ch_y = -1;
		//	int add = J[index].check_score(J, M, itr);
		//	if (add)
		//	{
		//		W_S.addscore(add);
		//		W_S.refresh();
		//		M.renew(J, itr);
		//	}
		//	else if (flag)
		//	{
		//		W.add_jewel(J, itr);
		//		cout << "itr:" << itr << endl;
		//		M.renew(J, itr);
		//		W.refresh();
		//	}
		//}
		//else 
		if (st_x >= 0 && st_y >= 0 && index >= 0)
		{
			if (m.lbutton)
				B.be_choosen(ch_x, ch_y, m);
			if(ch_x >= 0 && ch_y >= 0)
			{
				bool flag =	M.BFS(st_x, st_y, ch_x, ch_y, J[index]);
				st_x = st_y = -1;
				ch_x = ch_y = -1;
				int add = J[index].check_score(J, M, itr);
				if (add)
				{
					W_S.addscore(add);
					W_S.refresh();
					M.renew(J, itr);
				}
				else if(flag)
				{
					W.add_jewel(J, itr);
					cout << "itr:" << itr << endl;
					M.renew(J, itr);
					W.refresh();
				}

			}
		}
		if (m.vkcode == VK_ESCAPE || itr >= 81)
			break;
		if (m.vkcode == VK_F5)
			goto reset;
	}
	closegraph();			// 关闭绘图窗口
	return 0;
}

board::board()
{
	this->b_x = 0;
	this->b_y = 0;
}

board::board(int x, int y)
{
	this->b_x = x;
	this->b_y = y;
	setfillcolor(WHITE);
	fillrectangle(0, 0, this->b_x * CELL, this->b_y * CELL);
	setlinecolor(BLACK);
	for (int i = 0; i <= this->b_y + 1; i++)
	{
		line(0, i * CELL, this->b_x * CELL, i * CELL);
	}
	for (int i = 0; i <= this->b_x + 1; i++)
	{
		line(i * CELL, 0, i * CELL, this->b_y * CELL);
	}
}

int board::get_board_size(int xory)
{
	if (xory == 1)
		return this->b_x;
	else
		return this->b_y;
}

void board::be_choosen(int& ch_x, int& ch_y, ExMessage m)
{
	if (getpixel(m.x, m.y) == WHITE)
	{
		if (m.lbutton)
		{
			if (m.x % 50 != 0 && m.y % 50 != 0)
			{
				ch_x = (m.x / 50);
				ch_y = (m.y / 50);
			}
			cout << "choosen!" << endl;
		}
	}
	else if (m.lbutton)
		cout << "这里有珠子了！" << endl;
}

int board::be_choosen(int ch_x, int ch_y)
{
	return (getpixel(ch_x * CELL + JEWELST, ch_y * CELL + JEWELST) == WHITE);
}

Controller::Controller()
{
	this->score = 0;
	int v[8][2] = { {-1,-1},{1,1},{-1, 1}, {1, -1}, {0,1},{0,-1},{1,0},{-1,0} };
	for (int i = 0; i < 8; i++)
	{
		this->valid_move[i][0] = v[i][0];
		this->valid_move[i][1] = v[i][1];
	}
}

jewel::jewel()
{
	this->j_x = -1;
	this->j_y = -1;
	this->j_color = WHITE;
}

jewel::jewel(int x, int y)
{
	this->j_x = x;
	this->j_y = y;
	this->random_color();
}

int jewel::check_score(jewel J[], map& M, int& itr)
{
	int curr_x = this->j_x, curr_y = this->j_y; //记录当前检查位置
	int should_be_delete[9][2] = { 0 }; //记录应当被消除的珠子
	int you_get = 0;
	int count = 1;
	should_be_delete[0][0] = curr_x;
	should_be_delete[0][1] = curr_y;
	//四种判分方式
	for (int i = 0; i < 8; i++)
	{
		while (get_jewel_color(curr_x, curr_y) == this->j_color)
		{
			if (curr_x != this->j_x || curr_y != this->j_y)
			{
				should_be_delete[count][0] = curr_x;
				should_be_delete[count][1] = curr_y;
				count++;
			}
			curr_x += this->valid_move[i][0];
			curr_y += this->valid_move[i][1];
		}
		if (count >= 5)
		{
			you_get += count * 2;
			break;
		}
		if ((i + 1) % 2 == 0)
		{
			for (int j = 1; j < count; j++)
			{
				should_be_delete[j][0] = 0;
				should_be_delete[j][1] = 0;
			}
			count = 1;
		}
		curr_x = this->j_x;
		curr_y = this->j_y;
	}
	if (you_get)
	{
		BeginBatchDraw();
		for (int i = 0; i < count; i++)
		{
			for (int j = 0; j < itr; j++)
			{
				if (J[j].get_j_position_x() == should_be_delete[i][0] && J[j].get_j_position_y() == should_be_delete[i][1])
				{
					M.m[J[j].get_j_position_x()][J[j].get_j_position_y()] = 0;
					J[j].set_new_color(WHITE);
					cout << "deleting" << endl;
					J[j].print_j();
					J[j].set_new_position(-1, -1);
					itr--;
				}
			}
		}
		EndBatchDraw();
	}
	cout << you_get << endl;
	return you_get;
}

int jewel::random_color()
{
	srand(++seed);
	this->j_color = COLOR[rand() % 7];
	return this->j_color;
}

int jewel::get_j_position_x()
{
	return this->j_x;
}

int jewel::get_j_position_y()
{
	return this->j_y;
}

void jewel::set_new_position(int x, int y)
{
	this->j_x = x;
	this->j_y = y;
}

void jewel::set_new_color(int COLOR)
{
	this->j_color = COLOR;
}

int jewel::get_color()
{
	return this->j_color;
}

int jewel::be_gotten(ExMessage m)
{
	if (m.x <= (this->j_x + 1) * 50 && m.x >= (this->j_x) * 50 && m.y <= (this->j_y + 1) * 50 && m.y >= (this->j_y) * 50)
		if (m.lbutton)
			return 1;
		else if(m.rbutton)
			return 2;
	return 0;
}

int jewel::be_gotten(int x, int y)
{
	return this->j_x == x && this->j_y == y;
}

void jewel::print_j()
{
	cout << "now is adding" << endl;
	setfillcolor(this->j_color);
	solidcircle(JEWELST + this->j_x * CELL, JEWELST + this->j_y * CELL, 24);
}

void random_create_jewels(jewel J[], int& j, int create_num)
{
	BeginBatchDraw();
	for (int i = 0; i < create_num;)
	{
		srand(++seed);
		int c_x = rand() % 9, c_y = rand() % 9;
		if (getpixel(JEWELST + c_x * CELL, JEWELST + c_y * CELL) == WHITE)
		{
			jewel new_j(c_x, c_y);
			J[j] = new_j;
			setlinecolor(J[j].get_color());
			setfillcolor(J[j].get_color());
			solidcircle(JEWELST + J[j].get_j_position_x() * CELL, JEWELST + J[j].get_j_position_y() * CELL, 24);
			j++;
			i++;
		}
	}
	EndBatchDraw();
}

void random_create_jewels(jewel J[], int& j, int create_num, win_jewel win)
{
	int c_x = win.w_x, c_y = win.w_y;
	for (int i = 0; i < create_num; i++)
	{
		jewel new_j(c_x, c_y);
		J[j] = new_j;
		setlinecolor(J[i].get_color());
		setfillcolor(J[i].get_color());
		solidcircle(JEWELST + J[i].get_j_position_x() * CELL, JEWELST + J[i].get_j_position_y() * CELL, 24);
		j++;
		c_x++;
	}
}

void init(jewel J[], int& itr)
{
	random_create_jewels(J, itr, 7);
}

int get_jewel_color(int x, int y)
{
	return getpixel(JEWELST + x * CELL, JEWELST + y * CELL);
}

windows::windows()
{
	this->w_x = 0;
	this->w_y = 0;
}

win_jewel::win_jewel()
{
	this->w_x = 0;
	this->w_y = 0;
	this->J = this->previous_J = NULL;
}

win_jewel::win_jewel(int x, int y)
{
	this->w_x = x;
	this->w_y = y;
	this->J = new jewel[3];
	this->previous_J = new jewel[3];
	setfillcolor(WHITE);
	fillrectangle(this->w_x * CELL, this->w_y * CELL, this->w_x * CELL + 3 * CELL, this->w_y * CELL + CELL);
	settextcolor(WHITE);
	RECT r = { this->w_x * CELL, this->w_y * CELL + CELL, this->w_x * CELL + 3 * CELL, this->w_y * CELL + 2 * CELL };
	drawtext(_T("接下来的三个珠子"), &r, DT_CENTER | DT_SINGLELINE | DT_VCENTER);
}

void win_jewel::refresh()
{
	for (int i = 0; i < 3; i++)
	{
		this->previous_J[i] = this->J[i];
	}
	int itr = 0;
	random_create_jewels(this->J, itr, 3, *this);
}

bool win_jewel::traceback()
{
	if (this->previous_J == NULL)
		return false;
	else
	{
		this->J = this->previous_J;
		this->previous_J = NULL;
	}
	return true;
}

void win_jewel::add_jewel(jewel Jew[], int& itr)
{
	for (int i = 0; i < 3; i++)
	{
		while (1)
		{
			srand(++seed);
			int c_x = rand() % 9, c_y = rand() % 9;
			if (getpixel(JEWELST + c_x * CELL, JEWELST + c_y * CELL) == WHITE)
			{
				this->J[i].set_new_position(c_x, c_y);
				break;
			}
		}
		Jew[itr] = this->J[i];
		this->J[i].print_j();
		itr++;
		if (itr >= DEFAULTCOL * DEFAULTCOL)
			break;
	}
}

win_score::win_score()
{
	this->w_x = 0;
	this->w_y = 0;
	this->score = this->previous_score = -1;
}

win_score::win_score(int x, int y)
{
	this->w_x = x;
	this->w_y = y;
	this->score = 0;
	this->previous_score = 0;
	setfillcolor(WHITE);
	fillrectangle(this->w_x * CELL, this->w_y * CELL, this->w_x * CELL + 3 * CELL, this->w_y * CELL + CELL);
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	RECT r = { (this->w_x) * CELL, (this->w_y - 1) * CELL + CELL, this->w_x * CELL + 3 * CELL, this->w_y * CELL + 2 * CELL };
	drawtext(_T("得分:"), &r, DT_TOP);
}

void win_score::addscore(int add)
{
	this->score += add;
}

void win_score::refresh()
{
	setbkcolor(WHITE);
	setbkmode(OPAQUE);
	settextcolor(WHITE);
	outtextxy((this->w_x) * CELL + 2 * CELL, (this->w_y) * CELL + JEWELST, _T("      "));
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	string str = to_string(this->score);
	TCHAR c[99];
	int i = 0;
	for (; i < str.size(); i++)
	{
		c[i] = str[i];
	}
	c[i] = '\0';
	outtextxy((this->w_x) * CELL + 2 * CELL, (this->w_y) * CELL +JEWELST, c);
}

map::map()
{
	this->m[0][0] = -1;
	this->C = NULL;
	this->visited[0][0] = -1;
	this->way[0][0] = -1;
}

map::map(board& B, jewel J[], int n)
{
	int x = B.get_board_size(1), y = B.get_board_size(0);
	for (int i = 0; i < x; i++)
	{
		for (int j = 0; j < y; j++)
		{
			this->visited[i][j] = this->m[i][j] = 0;
			this->way[i][j] = -1;
		}
	}
	this->C = new Controller;
	for (int i = 0; i < n; i++)
	{
		if (J[i].get_j_position_x() >= 0 && J[i].get_j_position_y() >= 0)
		{
			m[J[i].get_j_position_x()][J[i].get_j_position_y()] = 1;//转置了
		}
	}
}

void map::renew(jewel J[], int n)
{
	for (int i = 0; i < n; i++)
	{
		if (J[i].get_j_position_x() >= 0 && J[i].get_j_position_y() >= 0)
		{
			m[J[i].get_j_position_x()][J[i].get_j_position_y()] = 1;
		}
	}
}

bool map::BFS(int st_x, int st_y, int end_x, int end_y, jewel& j)
{
	int move[4][2] = { {-1,0},{0,-1},{1,0},{0,1} };
	int n_x = st_x, n_y = st_y;
	while ((n_x != end_x || n_y != end_y))
	{
		int t_x = n_x, t_y = n_y;
		for (int i = 0; i < 4; i++)
		{
			t_x = n_x + move[i][0];
			t_y = n_y + move[i][1];
			if (t_x <= 8 && t_x >= 0 && t_y <= 8 && t_y >= 0 && this->m[t_x][t_y] != 1 && this->visited[t_x][t_y] != 1)
			{
				this->bfs_x.push(t_x);
				this->bfs_y.push(t_y);
				this->way[t_x][t_y] = i;
				this->visited[t_x][t_y] = 1;
			}
		}
		if (bfs_x.empty() || bfs_y.empty())
			break;
		n_x = this->bfs_x.front();
		n_y = this->bfs_y.front();
		bfs_x.pop();
		bfs_y.pop();
	}
	bool flag = 1;
	if(n_x != end_x || n_y != end_y)
	{
		cout << "No way" << endl;
		flag = 0;
		//增加无法前往的提示
	}
	else if (n_x == end_x && n_y == end_y)
	{
		this->bfs_x.push(n_x);
		this->bfs_y.push(n_y);
		j.set_new_position(n_x, n_y);
		this->printway(st_x, st_y, j.get_color());
	}
	cout << "m:" << endl;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			cout << m[i][j] << " ";
		}
		cout << endl;
	}
	for (int i = 0; i < DEFAULTCOL; i++)
	{
		for (int j = 0; j < DEFAULTCOL; j++)
		{
			this->visited[i][j] = 0;
			this->way[i][j] = -1;
		}
	}
	while (!this->bfs_x.empty())
		this->bfs_x.pop();
	while(!this->bfs_y.empty())
		this->bfs_y.pop();
	return flag;
}

void map::printway(int st_x, int st_y, int color)
{
	int move[4][2] = { {-1,0},{0,-1},{1,0},{0,1} };
	int end_x = this->bfs_x.back(), end_y = this->bfs_y.back();
	stack<int> way_x, way_y;
	while(end_x != st_x || end_y != st_y)
	{
		way_x.push(end_x);
		way_y.push(end_y);
		int curr_x = end_x, curr_y = end_y;
		end_x -= move[way[curr_x][curr_y]][0];
		end_y -= move[way[curr_x][curr_y]][1];
	}
	way_x.push(end_x);
	way_y.push(end_y);
	cout << "printing" << endl;
	if (way_x.size() == 1 && way_y.size() == 1)
		return;
	setfillcolor(WHITE);
	fillcircle(way_x.top() * CELL + JEWELST, way_y.top() * CELL + JEWELST, 24);
	this->m[way_x.top()][way_y.top()] = 0;
	way_x.pop();
	way_y.pop();
	setfillcolor(color);
	fillcircle(way_x.top() * CELL + JEWELST, way_y.top() * CELL + JEWELST, 24);
	while (way_x.size() != 1 || way_y.size() != 1)
	{
		Sleep(100);
		setfillcolor(WHITE);
		fillcircle(way_x.top() * CELL + JEWELST, way_y.top() * CELL + JEWELST, 24);
		way_x.pop();
		way_y.pop();
		setfillcolor(color);
		fillcircle(way_x.top() * CELL + JEWELST, way_y.top() * CELL + JEWELST, 24);
	}
	this->m[way_x.top()][way_y.top()] = 1;
}

