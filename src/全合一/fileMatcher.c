//filename: main.c
//author: PenG
//create time: 2018/12/23
//version: 1.0.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <io.h>

//���ݣ�����ʵ����ýṹ�йأ������������޹أ����ݿ��޸ģ����ṹ�������޸� 
typedef struct Data
{
	char filename[512];
	char directory[1024];
	unsigned int fileSize;
	//unsigned int indexes;	//�������� 
}FileData;

struct ListNode
{
	struct ListNode *last;
	FileData *data;
	struct ListNode *next;
};

struct List
{
	unsigned int size;
	struct ListNode *head;	
};

//�б��ַ 
struct List *list = NULL;

//�ͷ��б�ռ�
void releaseList(void)
{
	struct ListNode *temp;
	temp = list->head;
	while (NULL != temp->next)
	{
		temp = temp->next;
		free(temp->last);
	}
	free(temp);
	free(list);
	list = NULL;
} 

//�����б�ռ�
void createList(void)
{
	list = (struct List *)malloc(sizeof(struct List));
	list->head = NULL;
	list->size = 0;
} 

//��ʼ���ļ��б��ڴ�ռ� 
void initList(void)
{
	if (NULL != list)
	{
		releaseList();
	}
	createList();
}

//��ȡ����������ֵ���Ľڵ��ָ�룬����ֵ�����б��Сʱȡ���һ���ڵ� 
struct ListNode *getDataNodePoint(int indexes)
{
	struct ListNode *temp = list->head;
	int i;
	if (NULL == temp)
	{
		return NULL;
	}
	
	for (i=0; i<indexes && NULL!=temp->next; i++)
	{
		temp = temp->next;
	}
	return temp;
}

//��ȡ�ڽڵ�����ֵ���Ľڵ�����ݣ���������ָ������ݵĽṹ�ĵ�ַ������ֵ�����б�
//��Сʱȡ���һ������ 
struct Data *getData(int indexes)
{
	struct ListNode *temp = list->head;
	int i;
	if (NULL == temp)
	{
		return NULL;
	}
	
	for (i=0; i<indexes && NULL!=temp->next; i++)
	{
		temp = temp->next;
	}
	return temp->data;
} 

//��ĳ�����ݺ�������ݣ�һ��ʹ��getDataPoint����ȡafterWhich��ֵ�����afterWhich
//ΪNULL�������Ϊ��һ������ 
//����ֵ��0 �ɹ���-1 ��������-2 �ڴ�ռ䲻�� 
int insertAfter(struct Data *data, struct ListNode *afterWhich)
{ 
	if (NULL == data)
	{
		return -1;
	}
	
	struct ListNode *t_node = (struct ListNode *)malloc(sizeof(struct ListNode));
	if (NULL == t_node)
	{
		return -2;
	}
	
	struct Data *t_data = (struct Data *)malloc(sizeof(struct Data));
	if (NULL == t_data)
	{
		free(t_node);
		return -2;
	}
	
	//�ж��Ƿ����Ϊ��һ���ڵ� 
	if (NULL == afterWhich)
	{
		//û�нڵ�����ʱ����Ϊͷ�ڵ� 
		if (0 == list->size)
		{
			list->head = t_node;
			//�ڵ����ƴ�� 
			t_node->last = NULL;
			t_node->next = NULL;
		}
		//�нڵ�����ʱ����Ϊͷ�ڵ� 
		else
		{
			t_node->last = NULL;
			t_node->next = list->head;
			list->head->last = t_node;
			list->head = t_node;
		}
		
		
	}
	//�����һ���ڵ�
	else if (NULL == afterWhich->next)
	{
		t_node->last = afterWhich;
		t_node->next = NULL;
		afterWhich->next = t_node;
	} 
	//���ǵ�һ���ڵ�Ҳ�������һ���ڵ� 
	else
	{
		//�ڵ����ƴ�� 
		t_node->last = afterWhich;
		t_node->next = afterWhich->next;
		afterWhich->next->last = t_node;
		afterWhich->next = t_node;
	}
	
	//���ݸ��� 
	memcpy(t_data, data, sizeof(struct Data));
	t_node->data = t_data;
	
	list->size++;
	
	return 0;
}

//ƥ�����в��룬����ʽ���� 
void matchInseart(FileData *data)
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
		insertAfter(data, getDataNodePoint(list->size-1));
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


int main(int argc, char **argv)
{
	//char directory[1024];
	//char filename[128];
	//�������봦��
	//if (3 != argc)
	//{
	//	printf("����������%d", argc);
	//	printf("�� ��� �������"); //�貹�� 
	//	return -1;
	//}
	//memcpy(directory, argv[1], strlen(argv[1]) + 1);
	//memcpy(filename, argv[2], strlen(argv[2]) + 1); 
	//�������봦����� 
	
	//��ʼ���ļ��б��ڴ�
	initList(); 
	
	//��ʼ�ļ����� 
	fileTraversal("f:\\", "*.*");
	
	struct Data *data;
	
	int i;
	for (i=0; i<1000; i++)
	{
		data = getData(i);
		printf("path: %s\tfilename: %s\tsize: %dKB\n", data->directory, data->filename, data->fileSize);
	} 
	printf("total: %d files\n", list->size);
	
	//�ͷ��ļ��б��ڴ� 
	releaseList(); 
	system("pause");
	return 0;
}