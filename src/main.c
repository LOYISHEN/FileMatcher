//filename: main.c
//author: PenG
//create time: 2018/12/23
//version: 1.0.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileAndDirSolve.h"

int main(int argc,char **argv)
{
	char directory[1024];
	char filename[128];
	//参数输入处理
	if (3 != argc)
	{
		printf("请 如此 输入参数"); //需补充 
	}
	memcpy(directory, argv[1], strlen(argv[1]) + 1);
	memcpy(filename, argv[2], strlen(argv[2]) + 1); 
	//参数输入处理结束 
	
	//初始化文件列表内存
	initList(); 
	
	//开始文件遍历 
	fileTraversal(directory, filename);
	
	releaseList();
	return 0;
}