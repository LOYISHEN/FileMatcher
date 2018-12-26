//filename: fileAndDirSolve.c
//author: PenG
//create time: 2018/12/23
//version: 1.0.0

#include "fileAndDirSolve.h"

//ƥ�����в��룬����ʽ���� 
void matchInseart(struct Data *data)
{
	//��ǰ����С��������
	//ʵ�֣���ǰ���������Ȼ��ȶ�filename�ͽڵ��filename�����filename��һ��С 
	//�ڽڵ��filename�����ȡǰһ���ڵ�ĵ�ַ�����ò��뺯�� 
	struct ListNode *temp = list->head;
	//���б��Ƿ�Ϊ�գ�Ϊ��ֱ�Ӳ���Ϊ�б�ͷ 
	if (NULL == list->head)
	{
		insertAfter(data, NULL);
		return;
	}
	//------->�����뵽�Ƿ�Ҫ�Ե�ǰָ��Ľڵ�Ϊԭʼ�ڵ㣬������ͷ�ڵ�<------- 
	//��ʼ���� 
	while (NULL != temp)
	{
		if (strcmp(data->filename, temp->data->filename) <= 0)
		{
			break;
		} 
		
		//��Ҫ��ֹ�������б�β
		if (NULL == temp->next)
		{
			break;
		} 
		temp = temp->next;
	}
	
	//�Ѿ����б�β�Ͳ��뵽��β���� 
	if (NULL == temp->next)
	{
		insertAfter(data, getDataNodePoint(list->size));
	}
	else
	{
		insertAfter(data, temp->last);
	}
} 

//ƴ��Ŀ¼���ļ���Ϊȫ����д��fullname�� 
int jointPathAndFilename(char *fullname, char *path, char *filename)
{
	assert(NULL != fullname && NULL != path && NULL != filename);
	int pathLen = strlen(path);
	int filenameLen = strlen(filename);
	memcpy(fullname, path, pathLen);
	fullname[pathLen] = '\\';
	strcpy(&fullname[pathLen+1], filename);
	
	return 0;
}

//�����ļ�������������Ϣ�洢���б��С�
//pathΪ��ʼ���ҵ�Ŀ¼��filenameΪ�����ҵ��ļ����ļ��� 
//����ֵ��0 �ɹ���-1 Ŀ¼�����ڻ�Ŀ¼������-2 �ļ�������-3�ļ������� 
int fileTraversal(char *path, char *filename)
{
	struct _finddata_t fileinfo;
	long fileHandle;
	struct Data fileData;
	
	char *fullname = (char *)malloc(sizeof(char)*(strlen(path)+strlen(filename)+2));
	
	
	//-------->> �����뵽�����ҵ��ļ�֮��Ӧ��Ҫ����Ƿ�ɶ� <<--------- 
	
	//���Ŀ¼���ĺϷ��Ժ��Ƿ����
	if (NULL == path || 0 == strlen(path) || 0 != _access(path, F_OK))
	{
		return -1;
	}
	//����ļ����Ƿ�Ϸ� 
	if (NULL == filename || 0 == strlen(filename))
	{
		return -2;
	}
	
	jointPathAndFilename(fullname, path, filename);
	//��ʼ��һ�β��� 
	if (-1 == (fileHandle = _findfirst(fullname, &fileinfo)))
	{
		free(fullname);
		return -3;
	} 
	free(fullname);
	
	//�ļ���Ϊ��ǰĿ¼����һĿ¼ 
	if (0 == strcmp(fileinfo.name, ".") || 0 == strcmp(fileinfo.name, ".."))
	{
		NULL;
	}
	//������һ��Ŀ¼ 
	else if (_A_SUBDIR == (_A_SUBDIR & fileinfo.attrib))
	{
		char *t_path = (char *)malloc(sizeof(char)*(strlen(path)+strlen(fileinfo.name)+2));
		jointPathAndFilename(t_path, path, fileinfo.name);
		fileTraversal(t_path, filename);
		free(t_path);
	}
	//������һ���ļ� 
	else
	{
		strcpy(fileData.filename, fileinfo.name);
		strcpy(fileData.directory, path);
		fileData.fileSize = fileinfo.size;
		matchInseart(&fileData);
	}
	
	
	//�������� 
	while (0 == _findnext(fileHandle, &fileinfo))
	{
		//�ļ���Ϊ��ǰĿ¼����һĿ¼ 
		if (0 == strcmp(fileinfo.name, ".") || 0 == strcmp(fileinfo.name, ".."))
		{
			continue;
		}
		//������һ��Ŀ¼ 
		else if (_A_SUBDIR == (_A_SUBDIR & fileinfo.attrib))
		{
			//�ݹ��ȥ
			char *t_path = (char *)malloc(sizeof(char)*(strlen(path)+strlen(fileinfo.name)+2));
			jointPathAndFilename(t_path, path, fileinfo.name);
			fileTraversal(t_path, filename);
			free(t_path);
		}
		//������һ���ļ� 
		else
		{
			strcpy(fileData.filename, fileinfo.name);
			strcpy(fileData.directory, path);
			fileData.fileSize = fileinfo.size;	
			matchInseart(&fileData);
		}
	}
	
	_findclose(fileHandle);
}