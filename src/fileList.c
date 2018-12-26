//filename: fileList.c
//author: PenG
//create time: 2018/12/23
//version: 1.0.0

#include "fileList.h"

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