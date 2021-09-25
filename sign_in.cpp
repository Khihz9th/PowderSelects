#include <windows.h>
#include <stdio.h>
#include <string.h> 
#include <conio.h>

#include "sign_in.h"

static void HideCursor(int n);
static void SetPos(int  x, int  y);
static int choose1(void);
static int choose2(void);
int passwordINPUT(char password[17], int time);
static int choose3(void);
static int usernamecheck(char an[],int a);
/*已知bug合集 1，屏闪的问题。
2，输入的范围问题
*/
int sign_in(void)
{

	int kv, tv, lv = 1,ztm=0,cf=0;
sign_in_begin:	
	system("cls");
	//首界面
	HideCursor(0);
	printf("\n  预注册系统\n\n\n\n\n    ->1.预创建新用户\n      2.新用户审核结果查询\n      3.返回主界面\n");
	while (1) {

		if (_kbhit()) {
			Sleep(100);
			system("cls");
			printf("\n  预注册系统\n\n\n");
			kv = _getch();
			
			if ((kv >= 51 || kv <= 49) && kv != 224) printf("请使用方向键▲和▼移动。\n");

			//printf("%d\n", kv);
			if (kv == 224) {
				tv = _getch();
				switch (tv) {
				case 72:if (lv == 1) lv = 3; else lv = lv - 1; break;
				case 80:if (lv == 3) lv = 1; else lv = lv + 1; break;
				default:printf("      请使用方向键▲和▼移动光标。\n\n"); break;
				}
			}
			if (kv <= 51 && kv >= 49) lv = kv - 48;
			if ((kv <= 51 && kv >= 49) || (kv == 224 && (tv == 72 || tv == 80))) printf("\n\n");
			if (lv == 1) printf("    ->");
			else printf("      ");
			printf("1.预创建新用户\n");
			if (lv == 2) printf("    ->");
			else printf("      ");
			printf("2.新用户审核结果查询\n");
			if (lv == 3) printf("    ->");
			else printf("      ");
			printf("3.返回主界面\n");
			//printf("lv+%d\n",lv);

			if (kv == 13) goto next;
			
		}
		Sleep(100);
	}
next:


//登录界面
	if (lv == 1) {
		//用户名输入

		char username[13];
		char password[17] = "0", password2[17] = "0";
		char* ppa = password, * ppa2 = password2;
	case0start:
		system("cls");
		HideCursor(1);

		printf("\n\n            预注册系统  ->新用户注册\n\n");
		printf("            用户名：");
		printf("\n\n\n            用户名由大小写英文字母和数字组成，且只可以包含12个字符！\n"
			"            请不要使用非法字符进行用户名的注册。使用回车键确认。");
		SetPos(20, 4);

		scanf("%s", &username);	//用户检查
		cf=usernamecheck(username,0);
		if (cf != 0) {
			system("cls");
			printf("\n\n            预注册系统  ->新用户注册\n\n");
			printf("            :(   您的用户名已被占用。");

			kv = choose1();
			if (kv == 1) goto case0start;
			else if (kv == 2) goto sign_in_begin;
			else kv = 2;
		}
		for (kv = 0; username[kv] != '\0'; kv++) {

			//printf("%c", username[kv]);

			if (!((username[kv] >= 'A' && username[kv] <= 'Z') || \
				(username[kv] >= 'a' && username[kv] <= 'z')\
				|| (username[kv] >= '0' && username[kv] <= '9'))) {
				system("cls");

				printf("\n\n            预注册系统  ->新用户注册\n\n");
				printf("            :(   您的用户名：%s 至少含有%c这一个非法字符。", \
					username, username[kv]);
				kv = choose1();
				if (kv == 1) goto case0start;
				else if (kv == 2) goto sign_in_begin;
				else kv = 2;//返回主界面

			}

		}
		system("cls");
		printf("\n\n            预注册系统  ->新用户注册\n\n");
		printf("            :)   请确认您的用户名：%s。", username);
		kv = choose2();
		if (kv == 2) goto case0start;
		//if (ztm == 1); goto case4start; 
	//商户名注册
		char user_rname[24];
		if (ztm == 1) goto case4start;
	case1start://商户名注册
		system("cls");
		HideCursor(1);
		printf("\n\n            预注册系统  ->新用户注册\n\n");
		printf("           商户名：");
		printf("\n\n\n            请输入您的商家名称，且只可以包含12个字符！\n"
			"            如果超过12个字符请使用简称，请不要用非法字符\'，\'。回车键确认。");
		SetPos(20, 4);
		scanf("%s", &user_rname);
		cf = usernamecheck(user_rname, 0);
		if (cf != 0) {
			system("cls");
			printf("\n\n            预注册系统  ->新用户注册\n\n");
			printf("            :(   您的用户名已被占用。");

			kv = choose1();
			if (kv == 1) goto case0start;
			else if (kv == 2) goto sign_in_begin;
			else kv = 2;
		}

		for (kv = 0; user_rname[kv] != '\0'; kv++) {
			if (user_rname[kv] == ',') {
				system("cls");

				printf("\n\n            预注册系统  ->新用户注册\n\n");
				printf("            :(   您的用户名：%s 至少含有%c这一个非法字符。\n"
					"                请重新输入！按任意键继续");
				getch();
				goto case1start;
			}
		}
		system("cls");
		printf("\n\n            预注册系统  ->新用户注册\n\n");
		printf("            :)   请确认您的商家名：%s。", user_rname);
		kv = choose2();
		if (kv == 2) goto case1start;
		//else if (kv == 2) goto sign_in_begin;
		else kv = 3;//返回主界面
		if (ztm == 1) goto case4start;

	case2start:

		kv = passwordINPUT(ppa, 0);//return value meichuli
		kv = passwordINPUT(ppa2, 1);
		kv = strcmp(ppa, ppa2);
		if (kv != 0) {
			system("cls");
			HideCursor(0);
			printf("\n\n            预注册系统  ->新用户注册\n\n");
			printf("            :(   您的密码两次输入不一致。\n");
			printf("\n\n            密码由大小写英文字母和数字组成，且只可以包含12个字符！\n"
				"            请不要使用非法字符进行密码的注册。使用空格键重新输入密码。");
			getch();
			HideCursor(1);
			goto case2start;

		}
		printf("\npassword1=%s\npassword2=%s\n", ppa, ppa2);


		int feature2;
		if (ztm == 1) goto case4start;

	case3start:
		system("cls");
		HideCursor(0);
		printf("\n\n            预注册系统  ->新用户注册\n\n");
		printf("\n\n      用户类型选择：\n\n"
			"         1.商家：可以管理自己的货物；\n"
			"         2.普通用户：仅可以查看商业机密。");
		printf("\n\n            请输入你的选择(输入对应的数字)\n\n");
		feature2 = getch() - 48;
		fflush(stdin);
		if (feature2 != 1 && feature2 != 2) {
			system("cls");
			printf("\n\n            预注册系统  ->新用户注册\n\n");
			printf("\n\n      用户类型选择：\n\n"
				"         1.商家：可以管理自己的货物；\n"
				"         2.普通用户：仅可以查看商业机密。");
			printf("\n\n         你的输入非法，请重新输入！按空格键继续。");
			getch();
			goto case3start;
		}


	case4start:
		system("cls");
		ztm = 1;//修改后跳转
		HideCursor(0);
		printf("\n\n            预注册系统  ->新用户注册\n\n");
		printf("    1.登录用户名：  %s\n", username);
		printf("    2.  登录密码：  %s\n", password);
		printf("    3.  商户名称：  %s\n", user_rname);
		if (feature2 == 1) printf("    4.      类型：  商家账户\n");
		else ("    4.      类型：  普通账户\n");
		printf("\n\n    如果要修改，请点击对应的序号，确认无误请按空格键。");
		while (1) {
			if (_kbhit())
			{
				kv = getch();
				switch (kv) {
				case 49:goto case0start; break;
				case 50:goto case2start; break;
				case 51:goto case1start; break;
				case 52:goto case3start; break;
				default:goto uploadf;
				}
			}
		}
	uploadf: 
		FILE* NEW_N = fopen("D:\\cx4\\newsign\\sign_n.txt", "r+");
		int a;
		fscanf(NEW_N, "%d", &a);
		fclose(NEW_N);
		FILE* NEW_N2 = fopen("D:\\cx4\\newsign\\sign_n.txt", "w");
		fprintf(NEW_N2,"%d", a + 1);
		fclose(NEW_N2);
		FILE* NEW = fopen("D:\\cx4\\newsign\\sign.txt", "a+");
		fprintf(NEW, "%s,%s,%s,%d,", username, password, user_rname, feature2);
		fclose(NEW);
		system("cls");
		printf("\n\n            预注册系统  ->新用户注册\n\n");
		printf("            预创建用户成功，请联系管理员进行审核。\n            QQ:273672776"
			"\n按任意键返回主界面。");
		getch();
		goto sign_in_begin;
		
	}
	
	//用户查询界面
	if (lv == 2) {
		
		int c_a,c_b;
		char check_user[13]="0", load_user[13]="0";
		char* pcn = check_user, * plu = load_user;
		FILE* NEW_N = fopen("D:\\cx4\\newsign\\sign_n.txt", "r");
		fscanf(NEW_N, "%d", &c_a);
		printf("c_a=%d", c_a);
		fclose(NEW_N);
		FILE* CHECK= fopen("D:\\cx4\\newsign\\sign.txt", "r");

		printf("\n\n            预注册系统->新用户审核结果查询\n\n");
		printf("            请输入您创建的用户名：");
		scanf("%s", &check_user);
		for (int i = 0; i < c_a; i++) {
			fscanf(CHECK, "%[^,],%*[^,],%*[^,],%*[^,],", &load_user);
			c_b = strcmp(pcn, plu);
			if (c_b == 0) {
				printf("还在审核中...");
				
				break;
			}
			printf("第 %d次：check_name=%s ,load_name=%s\n", i, check_user, load_user);
		}
		printf("你输入的用户名不存在或审核没能通过");
		fclose(CHECK);
		printf("\n\n      按任意键返回主界面。");
		getch();
		goto sign_in_begin;



	}

	
		

			return 1;
	
}

void HideCursor(int n) /*隐藏光标*/
{
	CONSOLE_CURSOR_INFO cursor_info = { 1,n };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
static  void  SetPos(int  x, int  y)
{
	COORD  point = { x ,  y }; //光标要设置的位置x,y
	HANDLE  HOutput = GetStdHandle(STD_OUTPUT_HANDLE); //使用GetStdHandle(STD_OUTPUT_HANDLE)来获取标准输出的句柄
	SetConsoleCursorPosition(HOutput, point); //设置光标位置
}
//登陆界面用户名校验失败选项
static int choose1(void)// ->1.重新输入      2.返回上一级      3.回到主页面
{
	int kv, tv, lv=1;
	HideCursor(0);
	printf("\n\n\n\n    ->1.重新输入      2.返回上一级      3.回到主页面\n");
	while (1)
	{
		if (_kbhit()) {
			system("cls");
			printf("\n\n            预注册系统  ->新用户注册\n\n\n");


			kv = _getch();

			if ((kv >= 51 || kv <= 49) && kv != 224) printf("\n      请使用方向键<和>移动。\n");
			if (kv == 224) {
				tv = _getch();
				switch (tv) {
				case 75:if (lv == 1) lv = 3; else lv = lv - 1; break;
				case 77:if (lv == 3) lv = 1; else lv = lv + 1; break;
				default:
					if(kv <= 51 && kv >= 49)
						printf("\n\n\n"); 
					else 
						printf("\n      请使用方向键<和>移动光标。\n\n");
					break;
				}
			}
			if (kv <= 51 && kv >= 49) lv = kv - 48;
			if ((kv <= 51 && kv >= 49) || (kv == 224 && (tv == 75 || tv == 77))) printf("\n\n\n");
			if (lv == 1) printf("    ->");
			else printf("      ");
			printf("1.重新输入");
			if (lv == 2) printf("    ->");
			else printf("      ");
			printf("2.返回上一级");
			if (lv == 3) printf("    ->");
			else printf("      ");
			printf("3.回到主页面\n");
			//printf("lv+%d\n",lv);

			if (kv == 13) goto choose1ret;
			Sleep(100);
		}
		
	}
choose1ret:
	system("cls");
	HideCursor(1);
	return lv;
}
//商户名二次确认选项
static int choose2(void)// ->1.重新输入      2.返回上一级      3.回到主页面
{
	int kv, tv, lv = 1;
	HideCursor(0);
	printf("\n\n\n\n    ->1.确认      2.重新输入      3.回到主页面\n");
	while (1)
	{
		if (_kbhit()) {
			system("cls");
			printf("\n\n            预注册系统  ->新用户注册\n\n\n");


			kv = _getch();

			if ((kv >= 51 || kv <= 49) && kv != 224) printf("\n      请使用方向键<和>移动。\n");
			if (kv == 224) {
				tv = _getch();
				switch (tv) {
				case 75:if (lv == 1) lv = 3; else lv = lv - 1; break;
				case 77:if (lv == 3) lv = 1; else lv = lv + 1; break;
				default:
					if (kv <= 51 && kv >= 49)
						printf("\n\n\n");
					else
						printf("\n      请使用方向键<和>移动光标。\n\n");
					break;
				}
			}
			if (kv <= 51 && kv >= 49) lv = kv - 48;
			if ((kv <= 51 && kv >= 49) || (kv == 224 && (tv == 75 || tv == 77))) printf("\n\n\n");
			if (lv == 1) printf("    ->");
			else printf("      ");
			printf("1.确认");
			if (lv == 2) printf("    ->");
			else printf("      ");
			printf("2.重新输入");
			if (lv == 3) printf("    ->");
			else printf("      ");
			printf("3.回到主页面\n");
			//printf("lv+%d\n",lv);

			if (kv == 13) goto choose2ret;
			Sleep(100);
		}

	}
choose2ret:
	system("cls");
	HideCursor(1);
	return lv;
}
//密码输入
static int passwordINPUT(char password[17], int time)
{
ppasswordINPUT:
	int kv, j5;
	char passwo[17], tep[17];
	char* ppas = passwo;
	system("cls");
	printf("\n\n            预注册系统  ->新用户注册\n\n");
	if (time == 0) {
		
		printf("              密码：");
		printf("\n\n\n            密码由大小写英文字母和数字组成，且只可以包含12个字符！\n"
			"            请不要使用非法字符进行密码的注册。使用回车键确认。");
	}
	else {
		printf("             密码：");
		printf("\n\n\n            请重新输入你刚才的密码。使用回车键确认。\n"
			"            密码由大小写英文字母和数字组成，且只可以包含12个字符！");
	}
	SetPos(20, 4);
	//scanf("%s", &passwo);//
	fflush(stdin);
	for (j5 = 0; (tep[j5] = getch()) != '\r' && j5 < 16; j5++) {
		if (tep[j5] == '\b') {
			if (j5 != 0) {
				printf("\b \b");
				j5 -= 2;
			}
			else { j5--; }
		}
		else {
			printf("*");
			passwo[j5] = tep[j5];
		}
	}
	passwo[j5] = '\0';
	//for (int ja = 0; ja < j5 + 1; ja++) printf("\n%c", passwo[ja]);//
//用户检查
	for (kv = 0; passwo[kv] != '\0'; kv++) {
	
		//printf("%c", passwo[kv]);//
	
		if (!((passwo[kv] >= 'A' && passwo[kv] <= 'Z') || \
			(passwo[kv] >= 'a' && passwo[kv] <= 'z')\
			|| (passwo[kv] >= '0' && passwo[kv] <= '9'))) {
			system("cls");
	
			printf("\n\n            预注册系统  ->新用户注册\n\n");
			printf("            :(   您的密码：至少含有%c这一个非法字符。按任意键重新输入。\n", passwo[kv]);
			//kv = choose1();
			//if (kv == 1) goto ppasswordINPUT;
			////else if (kv == 2) goto sign_in_begin;
			//else kv = 2;//返回主界面
			getch();
			goto ppasswordINPUT;
		}
	}
	strcpy(password, ppas);
	return kv;
}
//用户类型选择
static int choose3(void)// ->1.重新输入      2.返回上一级      3.回到主页面
{
	int kv, tv, lv = 1;
	HideCursor(0);
	printf("\n\n\n\n    ->1.商家      2.普通用户      3.回到主页面\n");
	while (1)
	{
		if (_kbhit()) {
			system("cls");
			printf("\n\n            预注册系统  ->新用户注册\n\n\n");


			kv = _getch();

			if ((kv >= 51 || kv <= 49) && kv != 224) printf("\n      请使用方向键<和>移动。\n");
			if (kv == 224) {
				tv = _getch();
				switch (tv) {
				case 75:if (lv == 1) lv = 3; else lv = lv - 1; break;
				case 77:if (lv == 3) lv = 1; else lv = lv + 1; break;
				default:
					if (kv <= 51 && kv >= 49)
						printf("\n\n\n");
					else
						printf("\n      请使用方向键<和>移动光标。\n\n");
					break;
				}
			}
			if (kv <= 51 && kv >= 49) lv = kv - 48;
			if ((kv <= 51 && kv >= 49) || (kv == 224 && (tv == 75 || tv == 77))) printf("\n\n\n");
			if (lv == 1) printf("    ->");
			else printf("      ");
			printf("1.商家");
			if (lv == 2) printf("    ->");
			else printf("      ");
			printf("2.普通用户");
			if (lv == 3) printf("    ->");
			else printf("      ");
			printf("3.回到主页面\n");
			//printf("lv+%d\n",lv);

			if (kv == 13) goto choose1ret;
			Sleep(100);
		}

	}
choose1ret:
	system("cls");
	HideCursor(1);
	return lv;
}
static int usernamecheck(char an[], int ju)
{
	char bn[13]="0", bm[24]="0";
	char* bnp = bn, * bmp = bm;
	
	FILE *usLOG;
	usLOG = fopen("D:\\cx4\\loginf.txt", "r");
	int zrs, ret=0;
	fscanf(usLOG, "%d,", &zrs);
	for (int i = 0; i < zrs; i++) {
		if(ju==0) fscanf(usLOG, "%[^,],%*[^,],%*[^,],%*d,%*d,", &bn);
		else fscanf(usLOG, "%*[^,],%[^,],%*[^,],%*d,%*d,", &bn);
		if (!(strcmp(an, bnp))) {
			ret = 1;
			break;
		}
	}
	fclose(usLOG);

	FILE* NEW_N = fopen("D:\\cx4\\newsign\\sign_n.txt", "r");
	fscanf(NEW_N, "%d", &zrs);
	fclose(NEW_N);
	FILE* CHECK = fopen("D:\\cx4\\newsign\\sign.txt", "r");
	for (int i = 0; i < zrs; i++) {
		if(ju==0) fscanf(CHECK, "%[^,],%*[^,],%*[^,],%*d,%*d,", &bn);
		else fscanf(CHECK, "%*[^,],%*[^,],%[^,],%*d,%*d,", &bn);
		if (!(strcmp(an, bnp))) {
			ret = 1;
			break;
		}
	}
	fclose(CHECK);

	return ret;
}