# FileMatcher（文件匹配器）
## 0 介绍
  工程名称： FileMatcher（文件匹配器）
  作    者： PenG
  用    途： 匹配一个目录下的重复文件，并作出相应处理
  版    本： 1.0.1
## 1 涉及技术
### 1.0 文件遍历查找
  对提供的目录进行遍历操作，获取文件和目录的基本信息，并交于处理程序。
  主要是遍历出目录中所有的文件，然后获取文件名、目录和文件大小，然后写到链表中记录好。
### 1.1 文件读写操作
  对文件名和大小匹配成功的文件，需要从中获取所有数据，交于处理程序。
### 1.2 内存操作
  主要是对下面要进行的信息处理分配堆内存和操作这一内存。即建立一个存储空间，具体数据结构可能会用到链表或树。
  这里用到的是双向链表。每一个节点记录一个文件的数据，数据的保存按照文件名的字符码的大小排序。
### 1.3 信息处理
  对遍历出来的文件的信息进行储存，包括 文件名，文件路径，文件大小。使用链表的话就用插入法进行存储排序，方便处理；用树结构的话也行。
  首先对文件名进行模糊匹配，达到一定程度的匹配（这里的模糊匹配比较难想），也就是有多个文件的文件名相似，就对他们的大小进行比较，这里初定是文件大小完全一 样，当文件的阿晓完全一样时，就进行文件内容的进一步的比较，完全相同时则视为重复文件，然后存储到另一个链表中，等待下一步处理。
上面过程完毕后，就进行下一步处理。根据给出的策略，或者直接交给用户来选择该怎么去取舍。这里有一个想法，就是有可能两个文件夹是完全相同或者只有一点改动，这时就可以对两个目录进行大范围的处理。

## 2 操作条件
### 2.0 文件匹配条件
  从上到下匹配
    ·文件名	达到一定程度的匹配
    ·文件大小	相同
    ·文件内容	完全相同
### 2.1 向上匹配（文件到文件夹的匹配）
  这里说的是上面的那个想法，也就是当有多个文件来自相同名称的文件夹时，可以对这些文件进行大批量的处理，比如更新文件夹内容（文件少或旧的服从文件多的新的）。
示意图：

