#pragma once
#include<stdio.h>
#pragma once
#include<string.h>
#pragma once
int logpage(int* p_pMp);//用户登陆页面
#pragma once

/*缺少用户特征，而且txt在数据处理上并不是特别优秀，所以建议使用csv文件*/
#pragma once
struct user{
	char name[6];
	char pass[6];
	char rname[12];
	int star;//1为管理员,2为高级用户,3为普通用户
	int naL;//姓名字长
	int paL;//密码字长
}ren[3] = {
	{"star","123","长得的",1,4,3},
	{"vip","vip","长得",2,3,3},
	{"norm","wan5","长",3,4,5} };

//登录信息库，在正式调用后把初始值注译#pragma once
#pragma once
struct user* pren = ren;
//return pren;
//*pren = &ren[3];