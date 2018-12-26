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

//进行文件遍历，并把信息存储到列表中。
//path为开始查找的目录，filename为欲查找的文件的文件名 
//返回值：0 成功，-1 目录不存在或目录名错误，-2 文件名错误，-3文件不存在
int fileTraversal(char *path, const char *filename);

#endif