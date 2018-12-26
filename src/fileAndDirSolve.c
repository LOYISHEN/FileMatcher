//filename: fileAndDirSolve.c
//author: PenG
//create time: 2018/12/23
//version: 1.0.0

#include "fileAndDirSolve.h"

//匹配后进行插入，字码式排序 
void matchInseart(struct Data *data)
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
		insertAfter(data, getDataNodePoint(list->size));
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