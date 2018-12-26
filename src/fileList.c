//filename: fileList.c
//author: PenG
//create time: 2018/12/23
//version: 1.0.0

#include "fileList.h"

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