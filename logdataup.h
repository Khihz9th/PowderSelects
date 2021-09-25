#pragma once
void logdataup(void);//信息库导入文jian
#pragma once
extern struct user {
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

//extern struct user ren[3];
//extern struct user* pren;


