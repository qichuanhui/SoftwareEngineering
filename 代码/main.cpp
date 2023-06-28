#include<iostream>
#include "zhongju.h"

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


int main(int argc, char* argv[])
{
	clock_t start = clock();
	if (argc < 3)//参数数量出错
	{
		cout << "请输入正确的指令。" << endl;
		help();
		return 0;
	}

	if (strcmp(argv[1], "-c") == 0)
	{
		/*
		检查argv[2]，如果合法，返回对应整数；
		如果不合法，返回-1
		*/
		int num = convert_num(argv[2]);
		if (num == -1)//argv[2]不合法
		{
			cout << "请输入正确的指令。" << endl;
			return 0;
		}
		else//argv[2]合法
		{
			create_shudu(num);
		}
	}
	else if (strcmp(argv[1], "-s") == 0)
	{
		cout << "求解数独指令暂未实现，敬请期待" << endl;
	}
	else if (strcmp(argv[1], "-n") == 0)
	{
		cout << "生成游戏指令暂未实现，敬请期待" << endl;
	}
	else//argv[1]既不是"-c"，也不是"-s",也不是"-n"
	{
		cout << "请输入正确的指令。" << endl;
		return 0;
	}
}

