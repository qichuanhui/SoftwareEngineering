#include"zhongju.h"


int init[9] = { 1, 2, 3 ,4, 5, 6, 7, 8, 9 };//��1�еĳ�ʼ����
//ͨ����1�еĸ������ƣ�1-3�С�4-6�С�7-9�и�6�α任
int row_trans_13[6][3] = { {0, 3, 6}, {0, 6, 3}, {3, 0, 6}, {3, 6, 0}, {6, 0, 3}, {6, 3, 0} };//����1-3�е���������
int row_trans_46[6][3] = { {1, 4, 7}, {1, 7, 4}, {4, 1, 7}, {4, 7, 1}, {7, 1, 4}, {7, 4, 1} };//����4-6�е���������
int row_trans_79[6][3] = { {2, 5, 8}, {2, 8, 5}, {5, 2, 8}, {5, 8, 2}, {8, 2, 5}, {8, 5, 2} };//����7-9�е���������

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
	/*trans_13:row_trans_13�ĵ�һάλ��
	  trans_46:row_trans_46�ĵ�һάλ��
	  trans_79:row_trans_79�ĵ�һάλ�� */
	for (int i = 0; i < 3; i++)//д��1-3����buffer��
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
	for (int i = 3; i < 6; i++)//д��4-6����buffer��
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
	for (int i = 6; i < 9; i++)//д��7-9����buffer��
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
	/* n:�����ɵ��վָ��� */
	ofstream out("shudu.txt");//���ļ�
	if (!out)
	{
		cout << "Open File Failed!" << endl;
		return;
	}
	memset(buffer, ' ', sizeof(buffer));
	pos = 0;
	Init();
	int num = 0;//�����ɵ��վָ���
	do
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				for (int k = 0; k < 6; k++)
				{
					num += 1;
					if (num < n)//�����վָ���δ��꣬�վ�֮�任��
					{
						translate_row(i, j, k, false);
					}
					else//�����վָ����Ѵ�꣬д���ļ����˳�
					{
						translate_row(i, j, k, true);
						out.write(buffer, pos - 1);
						out.clear();
						out.close();
						cout << "���������վֳɹ�" << endl;
						return;
					}
				}
			}
		}
	} while (next_permutation(init, init + 9));//��init�ڶ������ֿ�ʼȫ����

}