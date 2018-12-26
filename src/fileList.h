//filename: fileList.h
//author: PenG
//create time: 2018/12/23
//version: 1.0.0

#ifndef FILELIST_H
#define FILELIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//���ݣ�����ʵ����ýṹ�йأ������������޹أ����ݿ��޸ģ����ṹ�������޸� 
struct Data
{
	char filename[512];
	char directory[1024];
	unsigned int fileSize;
	//unsigned int indexes;	//�������� 
};

struct ListNode
{
	struct ListNode *last;
	struct Data *data;
	struct ListNode *next;
};

struct List
{
	unsigned int size;
	struct ListNode *head;	
};

//�б��ַ 
struct List *list;

//��ʼ���ļ��б��ڴ�ռ� 
void initList(void);

//��ȡ����������ֵ���Ľڵ��ָ�� 
struct ListNode *getDataNodePoint(int indexes);

//��ȡ�ڽڵ�����ֵ���Ľڵ�����ݣ���������ָ������ݵĽṹ�ĵ�ַ 
struct Data *getData(int indexes); 

//��ĳ�����ݺ�������ݣ�һ��ʹ��getDataPoint����ȡafterWhich��ֵ�����afterWhich
//ΪNULL�������Ϊ��һ������ 
//����ֵ��0 �ɹ���-1 ��������-2 �ڴ�ռ䲻�� 
int insertAfter(struct Data *data, struct ListNode *afterWhich);

#endif