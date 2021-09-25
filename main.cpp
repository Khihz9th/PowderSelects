#include <stdio.h>
#include <string.h> 
#include <conio.h>
#include <windows.h>

#include "sudo.h"
#include "inter.h"//交互界面
#include "sign_in.h"//预注册界面
#include "log_in_page.h"//登陆界面

static void Hideursor(int n);
int welcome(void);
 
int main()
{   
	int welret;
	int logret, usefea = -1;
	int* puf = &usefea;

	
	int wel;
	wel:
	welret = welcome();
	switch (welret) {
	case 1:
		logret = log_in_page(puf);
		if (puf == 0 && logret == 1)
		{
			printf("是否进入管理界面：输入Y进入管理界面，否者进入其他页面。\n");
			if (getch() == 'Y') sudo(usefea);
		}
		if (logret == 1) logret = inter(usefea);
		break;
	case 2:
		logret = sign_in();
		goto wel;
		break;
	case 3:
		logret = 0;
		return 0;
		break;
	}
	

}

int welcome(void) {
	printf("小型商品管理系统demo(ljr)\n初始化完成，按任意键继续。");
	Hideursor(0);
	int kv=0,lv=3,tv;//kv:键盘值，lv：垂直数值
	while (1) {		
		if (_kbhit()) {

			system("cls");

			kv = _getch();
			//printf("%d", kv);
			if(kv==224){
				tv = _getch();
				switch (tv) {
				case 72:if (lv == 1) lv = 3;else lv = lv - 1; break;
				case 80:if (lv == 3) lv = 1; else lv = lv + 1; break;
				default:printf("请使用方向键▲和▼移动光标。\n"); break;
				}
			}
			if (kv <= 51 && kv >= 49) lv = kv - 48;
			if (lv == 1) printf("->");
			else printf("  ");
			printf("1.登录系统\n");
			if (lv == 2) printf("->");
			else printf("  ");
			printf("2.创建用户\n");
			if (lv == 3) printf("->");
			else printf("  ");
			printf("3.退出系统\n");
			//printf("lv+%d\n",lv);
			 
			if (kv == 13) goto ab;
			if((kv >= 51 && kv <= 49)&&kv!=224)	printf("请使用方向键▲和▼移动光标。按任意键继续\n");
			
		}
			Sleep(100);
	}
	system("cls");
	ab:
	Hideursor(1);
	return lv;

}

static void Hideursor(int n) /*隐藏光标*/
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,n };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}