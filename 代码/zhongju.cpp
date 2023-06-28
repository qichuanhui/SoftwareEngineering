#include"zhongju.h"


int init[9] = { 1, 2, 3 ,4, 5, 6, 7, 8, 9 };//第1行的初始排列
//通过第1行的各列右移，1-3行、4-6行、7-9行各6次变换
int row_trans_13[6][3] = { {0, 3, 6}, {0, 6, 3}, {3, 0, 6}, {3, 6, 0}, {6, 0, 3}, {6, 3, 0} };//生成1-3行的右移列数
int row_trans_46[6][3] = { {1, 4, 7}, {1, 7, 4}, {4, 1, 7}, {4, 7, 1}, {7, 1, 4}, {7, 4, 1} };//生成4-6行的右移列数
int row_trans_79[6][3] = { {2, 5, 8}, {2, 8, 5}, {5, 2, 8}, {5, 8, 2}, {8, 2, 5}, {8, 5, 2} };//生成7-9行的右移列数

static void Init()
{
	init[0] = 1;
	init[1] = 2;
	init[2] = 3;
	init[3] = 4;
	init[4] = 5;
	init[5] = 6;
	init[6] = 7;
	init[7] = 8;
	init[8] = 9;
}

void translate_row(int trans_13, int trans_46, int trans_79, bool flag)//
{
	/*trans_13:row_trans_13的第一维位置
	  trans_46:row_trans_46的第一维位置
	  trans_79:row_trans_79的第一维位置 */
	for (int i = 0; i < 3; i++)//写入1-3行至buffer中
	{
		int trans = 9 - row_trans_13[trans_13][i];
		for (int j = 0; j < 8; j++)
		{
			buffer[pos] = init[(j + trans) % 9] + '0';
			pos += 2;
		}
		buffer[pos++] = init[(8 + trans) % 9] + '0';
		buffer[pos++] = '\n';
	}
	for (int i = 3; i < 6; i++)//写入4-6行至buffer中
	{
		int trans = 9 - row_trans_46[trans_46][i - 3];
		for (int j = 0; j < 8; j++)
		{
			buffer[pos] = init[(j + trans) % 9] + '0';
			pos += 2;
		}
		buffer[pos++] = init[(8 + trans) % 9] + '0';
		buffer[pos++] = '\n';
	}
	for (int i = 6; i < 9; i++)//写入7-9行至buffer中
	{
		int trans = 9 - row_trans_79[trans_79][i - 6];
		for (int j = 0; j < 8; j++)
		{
			buffer[pos] = init[(j + trans) % 9] + '0';
			pos += 2;
		}
		buffer[pos++] = init[(8 + trans) % 9] + '0';
		buffer[pos++] = '\n';
	}
	if (flag == false)
		buffer[pos++] = '\n';
}

void create_shudu(int n)
{
	/* n:需生成的终局个数 */
	ofstream out("shudu.txt");//打开文件
	if (!out)
	{
		cout << "Open File Failed!" << endl;
		return;
	}
	memset(buffer, ' ', sizeof(buffer));
	pos = 0;
	Init();
	int num = 0;//已生成的终局个数
	do
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				for (int k = 0; k < 6; k++)
				{
					num += 1;
					if (num < n)//生成终局个数未达标，终局之间换行
					{
						translate_row(i, j, k, false);
					}
					else//生成终局个数已达标，写入文件并退出
					{
						translate_row(i, j, k, true);
						out.write(buffer, pos - 1);
						out.clear();
						out.close();
						cout << "创建数独终局成功" << endl;
						return;
					}
				}
			}
		}
	} while (next_permutation(init, init + 9));//从init第二个数字开始全排列

}