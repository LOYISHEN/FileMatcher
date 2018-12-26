//filename: fileAndDirSolve.h
//author: PenG
//create time: 2018/12/23
//version: 1.0.0

#ifndef FILEANDDIRSOLVE_H
#define FILEANDDIRSOLVE_H

#include <stdio.h>
#include <io.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h> 

#include "fileList.h"

//�����ļ�������������Ϣ�洢���б��С�
//pathΪ��ʼ���ҵ�Ŀ¼��filenameΪ�����ҵ��ļ����ļ��� 
//����ֵ��0 �ɹ���-1 Ŀ¼�����ڻ�Ŀ¼������-2 �ļ�������-3�ļ�������
int fileTraversal(char *path, const char *filename);

#endif