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
	//�������봦��
	if (3 != argc)
	{
		printf("�� ��� �������"); //�貹�� 
	}
	memcpy(directory, argv[1], strlen(argv[1]) + 1);
	memcpy(filename, argv[2], strlen(argv[2]) + 1); 
	//�������봦����� 
	
	//��ʼ���ļ��б��ڴ�
	initList(); 
	
	//��ʼ�ļ����� 
	fileTraversal(directory, filename);
	
	releaseList();
	return 0;
}