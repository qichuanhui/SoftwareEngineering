#include<iostream>
#include "zhongju.h"
#include "qiujie.h"
#include "youxi.h"
using namespace std;

/*
处理命令行输入
*/

void help()
{

}
int convert_num(char* s)
{
	/*将输入的数字转为int型*/
	int len = strlen(s);
	if (len >= 7 && strcmp(s, "1000000"))//大于1e6的整数非法
		return -1;
	else if (s[0] == '0')//0和前缀0非法
		return -1;
	int num = 0;
	for (int i = 0; i < len; i++)
	{
		if (!isdigit(s[i]))//非数字字符非法
			return -1;
		else   num = num * 10 + s[i] - '0';
	}
	return num;
}
int find_min(char* s)
{
	/*将最小挖洞数字转为int型*/
	int len = strlen(s);
	if (s[0] == '0')//0和前缀0非法
		return -1;
	int num = 0;
	for (int i = 0; i < len; i++)
	{
		if (s[i] == '-')break;
		else if (!isdigit(s[i]))//非数字字符非法
			return -1;
		else   num = num * 10 + s[i] - '0';
	}
	return num;
}
int find_max(char* s)
{
	/*将最大挖洞数字转为int型*/
	int i;
	int len = strlen(s);
	for (i = 0; i < len; i++)
	{
		if (s[i] == '-')
		{
			i++;
			break;
		}
	}
	if (s[i] == '0')//0和前缀0非法
		return -1;
	int num = 0;
	for (; i < len; i++)
	{
		if (!isdigit(s[i]))//非数字字符非法
			return -1;
		else   num = num * 10 + s[i] - '0';
	}
	return num;
}
int main(int argc, char* argv[])
{
	clock_t start = clock();
	if (argc < 3)//参数数量出错
	{
		cout << "请输入正确的指令。" << endl;
		help();
		return 0;
	}

	if (strcmp(argv[1], "-c") == 0)//生成终局
	{	
		if (argc != 3)//参数数量出错
		{
			cout << "-c后参数仅为终局个数" << endl;
			help();
			return 0;
		}
		//检查argv[2]，如果合法，返回对应整数；如果不合法，返回-1
		int num = convert_num(argv[2]);
		if (num == -1)//argv[2]不合法
		{
			cout << "参数不合法，-c后参数为终局个数,范围1-1000000" << endl;
			return 0;
		}
		else//argv[2]合法
		{
			if (create_shudu(num))
			{
				cout << "创建数独终局成功" << endl;
			}
		}
	}
	else if (strcmp(argv[1], "-s") == 0)//解数独
	{
		if (argc != 3)//参数数量出错
		{
			cout << "-s后参数仅为数独路径" << endl;
			help();
			return 0;
		}
		solve_shudu(argv[2]);
	}
	else if (strcmp(argv[1], "-n") == 0)//生成数独游戏
	{
		int level = 0;//难度
		int minhole = 0;//最小坑数
		int maxhole = 0;//最大坑数
		bool only = false;
		int num = convert_num(argv[2]);
		if (num < 0 || num>10000)
		{
			cout << "参数不合法，-n后参数为游戏个数,范围1-10000" << endl;
			return 0;
		}
		if (argc > 3)
		{
			if (strcmp(argv[3], "-m") == 0)//游戏难度
			{
				level = convert_num(argv[4]);
				if (level <1||level>3)//argv[4]不合法
				{
					cout << "难度选择错误，仅有1-3三种难度" << endl;
					return 0;
				}
			}
			else if (strcmp(argv[3], "-r") == 0)//游戏挖坑数
			{
				minhole = find_min(argv[4]);
				maxhole = find_max(argv[4]);
				if (maxhole==-1||minhole < 20 || maxhole>55 || minhole > maxhole)
				{
					cout << "参数错误，挖洞个数范围为20-55" << endl;
					return 0;
				}
			}
			else if (strcmp(argv[3], "-u") == 0)//游戏解唯一
			{
				only = true;
			}
		}
		if (argc > 5)
		{
			if (strcmp(argv[3], "-m") == 0)//游戏难度
			{
				level = convert_num(argv[4]);
				if (level < 1 || level>3)//argv[4]不合法
				{
					cout << "难度选择错误，仅有1-3三种难度" << endl;
					return 0;
				}
			}
			if (strcmp(argv[3], "-r") == 0)//游戏挖坑数
			{
				minhole = find_min(argv[4]);
				maxhole = find_max(argv[4]);
			}
		}
		create_game(num, level , minhole , maxhole, only);
	}
	else//argv[1]既不是"-c"，也不是"-s",也不是"-n"
	{
		cout << "请输入正确的指令。" << endl;
		return 0;
	}
}

