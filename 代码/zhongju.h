#pragma once
#include<iostream>
#include <fstream>
#include<algorithm>
using namespace std;

static char buffer[165000000];//»º³å×Ö·û
static int pos;//»º³å×Ö·û´®µÄµ±Ç°Ğ´ÈëÎ»ÖÃ

static void Init();
void create_shudu(int n);
void translate_row(int trans_13, int trans_46, int trans_79, bool flag);



