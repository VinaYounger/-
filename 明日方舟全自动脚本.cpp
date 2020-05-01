#include <iostream>
#include <string.h>
#include <windows.h>
#include <process.h>
using namespace std;
int a = 4;
bool b = false, c = false, first = false;
HWND hwnd = NULL, hwnddad = NULL, hnow = NULL;
HANDLE hnd = NULL;

bool SetPrivilege(LPCTSTR LpPrivilegestr, BOOL enable, DWORD Privilege = SE_PRIVILEGE_ENABLED)
{
	HANDLE hToken;
	TOKEN_PRIVILEGES Tp;
	LUID Luid;
	//获得Token
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
	{
		//printf("OpenProcessToken error: %s", GetLastError());
		return false;
	}
	//获得LUID
	if (!LookupPrivilegeValue(NULL, LpPrivilegestr, &Luid))
	{
		//printf("LookupPrivilegeValue: %s", GetLastError());
		return false;
	}
	Tp.PrivilegeCount = 1;
	Tp.Privileges[0].Luid = Luid;
	if (enable)
	{
		Tp.Privileges[0].Attributes = Privilege;
	}
	else
	{
		Tp.Privileges[0].Attributes = NULL;
	}
	//设置权限
	if (!AdjustTokenPrivileges(hToken, FALSE, &Tp, NULL, NULL, NULL))
	{
		//printf("AdjustTokenPrivileges: %s", GetLastError());
		return false;
	}
	if (GetLastError() == ERROR_NOT_ALL_ASSIGNED)
	{
		//printf("The token does not have the specified privilege. \n");
		return false;
	}
	return true;
}

void NoDisturb(void*)
{
	for (int i = 0; GetForegroundWindow() != hwnddad && i < 666666; i++);
	SetForegroundWindow(hnow);
	hnd = NULL;
}

void MCS(int x, int y, int delay)//给模拟器发送鼠标点击消息，参数（坐标x，坐标y，延迟）
{
	RECT rect;
	int x1, y1;
	Sleep(delay);
	GetWindowRect(hwnd, &rect);
	x1 = (int)((x - 125.0) *(rect.right - rect.left) / (1672.0));//125,37,1672,941这4个数是因为下面我用的坐标是以1080的分辨率以模拟器窗口最大化取的
	y1 = (int)((y - 37.0) *(rect.bottom - rect.top) / (941.0));//为了变成游戏窗口的点击坐标，通过减去顶角和乘宽高比例变成新坐标
	hnow = GetForegroundWindow();
	PostMessageA(hwnd, 513, 1, x1 + y1 * 65536);
	PostMessageA(hwnd, 514, 0, x1 + y1 * 65536);
	if (c&&hnd == NULL)
		hnd = (HANDLE)_beginthread(NoDisturb, 0, NULL);
}

void Substitution(bool dormitory)//换干员
{
	if (dormitory)
	{
		MCS(258, 385, 1545);
		MCS(1501, 269, 645);
		if (!first)
		{
			first = true;
			Sleep(5000);
		}
	}
	else
		MCS(560, 888, 666);
	MCS(748, 298, 888);
	MCS(785, 584, 30);
	MCS(969, 408, 30);
	MCS(898, 610, 30);
	MCS(1094, 366, 30);
	MCS(1138, 573, 30);
}

void Dormitory(int x, int y)//宿舍
{
	MCS(x, y, 1005);
	Substitution(true);
	MCS(1316, 613, 30);
	MCS(1354, 421, 30);
	MCS(1440, 363, 30);
	MCS(1545, 629, 30);
	MCS(1669, 926, 30);
	MCS(1220, 704, 200);
	MCS(1000, 500, 2000);
	MCS(249, 81, 300);
}

void TradingPost(int x, int y)//贸易站
{
	MCS(x, y, 1000);
	MCS(x, y, 1000);
	Substitution(true);
	MCS(1669, 926, 50);
	MCS(453, 858, 1140);
	MCS(453, 858, 1140);
	MCS(270, 430, 1200);
	Substitution(false);
	MCS(1669, 926, 30);
	MCS(241, 86, 1200);
	MCS(241, 86, 500);
}

void ManuFacturingStation(int x, int y)//制造站
{
	MCS(x, y, 1000);
	MCS(x, y, 1000);
	MCS(478, 848, 1005);
	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
			MCS(478, 848, 1205);
		else
			MCS(300, 315 + 110 * i, 2080);
		Substitution(false);
		MCS(1669, 926, 30);
		MCS(1388, 318, 1234);
		MCS(1351, 801, 555);
	}
}

void start(void*)
{
	int i, j;
	MCS(600, 90, 100);//返回首页
	MCS(268, 333, 530);
	MCS(1474, 823, 1000);//进入基建 
	MCS(1733, 148, 6666);//收取信赖和制造站产物
	MCS(424, 925, 300);
	MCS(424, 925, 1000);
	MCS(1749, 216, 300);
	MCS(424, 925, 300);
	MCS(424, 925, 1000);
	MCS(1220, 777, 500);
	Dormitory(1220, 777);//宿舍
	Dormitory(1181, 718);
	Dormitory(1193, 578);
	Dormitory(1151, 443);
	Dormitory(1216, 245);
	TradingPost(315, 444);//贸易站坐标
	ManuFacturingStation(474, 438);//制造站坐标
	MCS(238, 94, 500);
	MCS(238, 94, 500);
	MCS(1775, 568, 1265);//办公室
	MCS(528, 811, 1095);
	MCS(741, 698, 735);
	MCS(1644, 943, 720);
	MCS(238, 94, 2000);
	MCS(1709, 298, 1220);//会议室
	MCS(480, 855, 680);
	MCS(1679, 278, 575);
	MCS(1168, 785, 530);
	MCS(1408, 163, 560);
	MCS(305, 328, 820);
	MCS(753, 384, 888);
	MCS(753, 660, 30);
	MCS(913, 388, 30);
	MCS(906, 608, 30);
	MCS(1613, 929, 100);
	MCS(600, 90, 1525);//退出基建 
	MCS(268, 333, 530);
	//信用商城 
	MCS(1205, 664, 6666);
	MCS(1645, 163, 5000);
	MCS(1463, 85, 1080);
	MCS(1463, 85, 1580);
	MCS(1463, 85, 1480);
	MCS(1463, 85, 1480);
	MCS(646, 418, 600);
	MCS(1265, 796, 735);
	MCS(1153, 403, 1380);
	MCS(600, 90, 1125);
	MCS(268, 333, 530);
	//招募收取 
	MCS(1429, 709, 885);
	MCS(763, 513, 1125);
	MCS(1713, 93, 3780);
	MCS(1713, 93, 2265);
	MCS(1640, 555, 1205);
	MCS(1716, 100, 3825);
	MCS(1716, 100, 2295);
	MCS(635, 876, 1250);
	MCS(1710, 94, 3630);
	MCS(1710, 94, 2230);
	MCS(1528, 879, 840);
	MCS(1731, 85, 3870);
	MCS(1731, 85, 2260);
	MCS(600, 90, 1125);
	MCS(268, 333, 530);
	//剿灭刷怪数 
	MCS(1250, 300, 1810);
	MCS(845, 898, 1140);
	MCS(400, 395, 1035);
	for (i = 0; i < 3 + a; i++) //计次循环刷图 
	{
		for (j = 0; j < 15; j++)
			MCS(1606, 873, 500);
		MCS(234, 103, 144000);//关卡耗时 
		MCS(1328, 791, 1230);
		MCS(1328, 791, 6540);
		MCS(1328, 791, 3640);
		Sleep(2020);
	}
	MCS(600, 90, 5525);
	MCS(268, 333, 830);
	MCS(600, 90, 1525);
	MCS(268, 333, 830);
	//TR-1刷关数 
	MCS(1250, 300, 1870);
	MCS(226, 408, 1230);
	MCS(1400, 908, 1425);
	MCS(1400, 903, 1190);
	MCS(1400, 903, 1050);
	MCS(1400, 903, 1110);
	MCS(1400, 903, 1110);
	for (i = 0; i < 4 + a; i++)
	{
		MCS(918, 614, 1380);
		MCS(918, 614, 138);
		MCS(1606, 873, 1095);
		MCS(1606, 873, 1230);
		MCS(1606, 873, 1230);
		MCS(1628, 119, 7560);
		MCS(1628, 119, 160);
		MCS(1306, 680, 915);
		MCS(1560, 106, 885);
		MCS(1628, 119, 18065);
		MCS(1628, 119, 160);
		MCS(1191, 693, 1020);
		MCS(1561, 108, 1005);
		MCS(918, 614, 22360);
		MCS(918, 614, 2530);
		Sleep(5000);
	}
	if (a == 0)//是否为全耗理智模式
	{
		MCS(600, 90, 1125);
		MCS(268, 333, 830);
		MCS(1250, 300, 1350);//LS-5刷4次 
		MCS(441, 921, 1275);
		MCS(414, 495, 645);
		MCS(1350, 289, 1395);
		for (i = 0; i < 4 - a; i++) //4次循环刷图 
		{
			for (j = 0; j < 13; j++)
				MCS(1550, 870 + 99 * (j % 3 > 0), 500);
			Sleep(150000);//关卡耗时 
			MCS(860, 266, 1230);
			MCS(860, 266, 2540);
			MCS(860, 266, 2640);
			Sleep(2020);
		}
	}
	MCS(600, 90, 1525);
	MCS(565, 411, 530);
	MCS(600, 90, 1525);
	MCS(565, 411, 530);
	//一个绿录像强化干员任务 
	MCS(238, 743, 5055);
	MCS(1580, 165, 3030);
	MCS(1143, 228, 855);
	MCS(1628, 908, 690);
	MCS(433, 73, 3760);
	MCS(278, 328, 975);
	//领每日任务奖励 
	MCS(1188, 828, 1500);
	for (i = 0; i < 130; i++)
		MCS(1575, 227, 200);
	MCS(600, 90, 1125);
	MCS(268, 333, 530);//返回首页
	first = b = false;
	cout << "自动化日常操作完毕！" << endl;
}

void repeat(void*)//重复刷关
{
	for (int i = 0;; i++)
	{
		MCS(1550, 870 + 99 * (i % 3 > 0), 666);
	}
}

int main()
{
	HANDLE handle = NULL;
	POINT point, screen = { GetSystemMetrics(0) ,GetSystemMetrics(1) };
	HWND pointhwnd;
	char title[11];
	if (!SetPrivilege(SE_SECURITY_NAME, TRUE))
	{
		if (MessageBoxA(0, "检测到操作权限受限，建议用管理员模式运行，是否继续打开？", "权限提示：", 4) != 5)
			exit(0);
	}
	cout << "脚本功能：自动处理基建(订单制造站信赖宿舍干员替换等),信用收取使用,\n公开招募收取,0理智刷图完成每日任务并领取所有奖励\n" << endl;
	cout << "热键及对应功能：\nF10启动/终止自动化日常操作\nF9开启/关闭自动化刷图操作\nF8切换不耗/全耗理智模式\nF7开启/关闭免打扰模式\nF6结束脚本\n" << endl;
	cout << "注意：全耗理智模式为自动刷4次LS-5,默认不耗\nF10(操作结束自动关闭)和F9同一时间只能开启一个,同时开启会统一关闭功能" << endl;
	cout << "免打扰模式指在脚本进行自动操作时，会激活模拟器窗口\n此模式下会自动切回原来的窗口，CPU占用会略高一点\n" << endl;
	cout << "正在检测游戏..." << endl;
	while (1)
	{
		for (point.x = 50; point.x < screen.x; point.x += 50)
			for (point.y = 50; point.y < screen.y; point.y += 50)
			{
				pointhwnd = WindowFromPoint(point);
				GetWindowTextA(pointhwnd, title, sizeof(title));
				if (strcmp(title, "NemuPlayer") == 0)
				{
					hwnd = pointhwnd;
					hwnddad = GetParent(pointhwnd);
					goto GO;
				}
			}
		Sleep(233);
	}
GO:cout << "成功检测到游戏！\n" << endl;
	while (1)
	{
		if (GetAsyncKeyState(121) != 0)//F10键
		{
			if (!b)
			{
				b = true;
				handle = (HANDLE)_beginthread(start, 0, NULL);
				cout << "启动自动化日常操作！" << endl;
			}
			else
			{
				b = first = false;
				TerminateThread(handle, 0);
				CloseHandle(handle);
				cout << "终止自动化日常操作！" << endl;
			}
			Sleep(666);
		}
		if (GetAsyncKeyState(120) != 0) {//F9键
			if (!b)
			{
				b = true;
				handle = (HANDLE)_beginthread(repeat, 0, NULL);
				cout << "开启自动化刷图操作！" << endl;
			}
			else
			{
				b = false;
				TerminateThread(handle, 0);
				CloseHandle(handle);
				cout << "关闭自动化刷图操作！" << endl;
			}
			Sleep(666);
		}
		if (GetAsyncKeyState(119) != 0)//F8键
		{
			if (a == 0)
			{
				a = 4;
				cout << "切换为不耗理智模式！" << endl;
			}
			else
			{
				a = 0;
				cout << "切换为全耗理智模式！" << endl;
			}
			Sleep(666);
		}
		if (GetAsyncKeyState(118) != 0)//F7键
		{
			c = !c;
			if (c)
				cout << "开启免打扰模式！" << endl;
			else
				cout << "关闭免打扰模式！" << endl;
			Sleep(666);
		}
		if (GetAsyncKeyState(117) != 0)//F6键
			break;
		Sleep(10);
	}
	return 0;
}
