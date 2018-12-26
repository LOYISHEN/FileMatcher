//filename: main.c
//author: PenG
//create time: 2018/12/23
//version: 1.0.0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <io.h>

//数据，代码实现与该结构有关，但与其内容无关，内容可修改，但结构名不可修改 
typedef struct Data
{
	char filename[512];
	char directory[1024];
	unsigned int fileSize;
	//unsigned int indexes;	//数据索引 
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

//列表地址 
struct List *list = NULL;

//释放列表空间
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

//创建列表空间
void createList(void)
{
	list = (struct List *)malloc(sizeof(struct List));
	list->head = NULL;
	list->size = 0;
} 

//初始化文件列表内存空间 
void initList(void)
{
	if (NULL != list)
	{
		releaseList();
	}
	createList();
}

//获取在链表索引值处的节点的指针，索引值超过列表大小时取最后一个节点 
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

//获取在节点索引值处的节点的数据，函数返回指向该数据的结构的地址，索引值超过列表
//大小时取最后一个数据 
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

//在某个数据后插入数据，一般使用getDataPoint来获取afterWhich的值，如果afterWhich
//为NULL，则插入为第一个数据 
//返回值：0 成功，-1 参数错误，-2 内存空间不足 
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
	
	//判断是否插入为第一个节点 
	if (NULL == afterWhich)
	{
		//没有节点数据时，作为头节点 
		if (0 == list->size)
		{
			list->head = t_node;
			//节点插入拼接 
			t_node->last = NULL;
			t_node->next = NULL;
		}
		//有节点数据时，作为头节点 
		else
		{
			t_node->last = NULL;
			t_node->next = list->head;
			list->head->last = t_node;
			list->head = t_node;
		}
		
		
	}
	//是最后一个节点
	else if (NULL == afterWhich->next)
	{
		t_node->last = afterWhich;
		t_node->next = NULL;
		afterWhich->next = t_node;
	} 
	//不是第一个节点也不是最后一个节点 
	else
	{
		//节点插入拼接 
		t_node->last = afterWhich;
		t_node->next = afterWhich->next;
		afterWhich->next->last = t_node;
		afterWhich->next = t_node;
	}
	
	//数据复制 
	memcpy(t_data, data, sizeof(struct Data));
	t_node->data = t_data;
	
	list->size++;
	
	return 0;
}

//匹配后进行插入，字码式排序 
void matchInseart(FileData *data)
{
	//从前往后按小到大排序
	//实现：从前往后遍历，然后比对filename和节点的filename，如果filename第一次小 
	//于节点的filename，则获取前一个节点的地址，调用插入函数 
	struct ListNode *temp = list->head;
	//看列表是否为空，为空直接插入为列表头 
	if (NULL == list->head)
	{
		insertAfter(data, NULL);
		return;
	}
	//------->这里想到是否要以当前指向的节点为原始节点，而不是头节点<------- 
	//开始遍历 
	while (NULL != temp)
	{
		if (strcmp(data->filename, temp->data->filename) <= 0)
		{
			break;
		} 
		
		//还要防止遍历到列表尾
		if (NULL == temp->next)
		{
			break;
		} 
		temp = temp->next;
	}
	
	//已经到列表尾就插入到表尾后面 
	if (NULL == temp->next)
	{
		insertAfter(data, getDataNodePoint(list->size-1));
	}
	else
	{
		insertAfter(data, temp->last);
	}
} 

//拼接目录和文件名为全名，写到fullname中 
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

//进行文件遍历，并把信息存储到列表中。
//path为开始查找的目录，filename为欲查找的文件的文件名 
//返回值：0 成功，-1 目录不存在或目录名错误，-2 文件名错误，-3文件不存在 
int fileTraversal(char *path, char *filename)
{
	struct _finddata_t fileinfo;
	long fileHandle;
	struct Data fileData;
	
	char *fullname = (char *)malloc(sizeof(char)*(strlen(path)+strlen(filename)+2));
	
	
	//-------->> 这里想到后面找到文件之后应该要检查是否可读 <<--------- 
	
	//检查目录名的合法性和是否存在
	if (NULL == path || 0 == strlen(path) || 0 != _access(path, F_OK))
	{
		return -1;
	}
	//检查文件名是否合法 
	if (NULL == filename || 0 == strlen(filename))
	{
		return -2;
	}
	
	jointPathAndFilename(fullname, path, filename);
	//开始第一次查找 
	if (-1 == (fileHandle = _findfirst(fullname, &fileinfo)))
	{
		free(fullname);
		return -3;
	} 
	free(fullname);
	
	//文件名为当前目录或上一目录 
	if (0 == strcmp(fileinfo.name, ".") || 0 == strcmp(fileinfo.name, ".."))
	{
		NULL;
	}
	//遍历到一个目录 
	else if (_A_SUBDIR == (_A_SUBDIR & fileinfo.attrib))
	{
		char *t_path = (char *)malloc(sizeof(char)*(strlen(path)+strlen(fileinfo.name)+2));
		jointPathAndFilename(t_path, path, fileinfo.name);
		fileTraversal(t_path, filename);
		free(t_path);
	}
	//遍历到一个文件 
	else
	{
		strcpy(fileData.filename, fileinfo.name);
		strcpy(fileData.directory, path);
		fileData.fileSize = fileinfo.size;
		matchInseart(&fileData);
	}
	
	
	//继续查找 
	while (0 == _findnext(fileHandle, &fileinfo))
	{
		//文件名为当前目录或上一目录 
		if (0 == strcmp(fileinfo.name, ".") || 0 == strcmp(fileinfo.name, ".."))
		{
			continue;
		}
		//遍历到一个目录 
		else if (_A_SUBDIR == (_A_SUBDIR & fileinfo.attrib))
		{
			//递归进去
			char *t_path = (char *)malloc(sizeof(char)*(strlen(path)+strlen(fileinfo.name)+2));
			jointPathAndFilename(t_path, path, fileinfo.name);
			fileTraversal(t_path, filename);
			free(t_path);
		}
		//遍历到一个文件 
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
	//参数输入处理
	//if (3 != argc)
	//{
	//	printf("参数个数：%d", argc);
	//	printf("请 如此 输入参数"); //需补充 
	//	return -1;
	//}
	//memcpy(directory, argv[1], strlen(argv[1]) + 1);
	//memcpy(filename, argv[2], strlen(argv[2]) + 1); 
	//参数输入处理结束 
	
	//初始化文件列表内存
	initList(); 
	
	//开始文件遍历 
	fileTraversal("f:\\", "*.*");
	
	struct Data *data;
	
	int i;
	for (i=0; i<1000; i++)
	{
		data = getData(i);
		printf("path: %s\tfilename: %s\tsize: %dKB\n", data->directory, data->filename, data->fileSize);
	} 
	printf("total: %d files\n", list->size);
	
	//释放文件列表内存 
	releaseList(); 
	system("pause");
	return 0;
}