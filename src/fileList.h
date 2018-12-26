//filename: fileList.h
//author: PenG
//create time: 2018/12/23
//version: 1.0.0

#ifndef FILELIST_H
#define FILELIST_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//数据，代码实现与该结构有关，但与其内容无关，内容可修改，但结构名不可修改 
struct Data
{
	char filename[512];
	char directory[1024];
	unsigned int fileSize;
	//unsigned int indexes;	//数据索引 
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

//列表地址 
struct List *list;

//初始化文件列表内存空间 
void initList(void);

//获取在链表索引值处的节点的指针 
struct ListNode *getDataNodePoint(int indexes);

//获取在节点索引值处的节点的数据，函数返回指向该数据的结构的地址 
struct Data *getData(int indexes); 

//在某个数据后插入数据，一般使用getDataPoint来获取afterWhich的值，如果afterWhich
//为NULL，则插入为第一个数据 
//返回值：0 成功，-1 参数错误，-2 内存空间不足 
int insertAfter(struct Data *data, struct ListNode *afterWhich);

#endif