#pragma once
#include<iostream>
#include <fstream>
#include<algorithm>
using namespace std;

static char buffer[165000000];//�����ַ�
static int pos;//�����ַ����ĵ�ǰд��λ��

static void Init();
void create_shudu(int n);
void translate_row(int trans_13, int trans_46, int trans_79, bool flag);



