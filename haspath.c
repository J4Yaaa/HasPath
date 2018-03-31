#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW 3
#define COL 4

int _HasPath(char arr[ROW][COL],char* buf,const char* str,int row,int col,int* index)
{
    //数据合法性判断
    if(arr == NULL || buf == NULL)
    {
        return 0;
    }
    //点的合法性判断
    if(row < 0 || row >= ROW || col < 0 || col >= COL)
    {
        return 0;
    }
    //一定要判断结束标志，不然永远都无法返回1
    if(str[*index] == '\0')
    {
        return 1;
    }
   int path = 0;
    if(arr[row][col] == str[*index] && buf[row*COL + col] == 0)
    {
        //如果当前坐标合理，就去探测str的下一个字符 -> ++(*index)
        //同时在buf中标记当前点，使当前点的值为1，表示当前存在在str中
        ++(*index);
        buf[row*COL + col] = 1;
        path =  _HasPath(arr,buf,str,row-1,col,index)
            ||  _HasPath(arr,buf,str,row,col-1,index)
            ||  _HasPath(arr,buf,str,row+1,col,index)
            ||  _HasPath(arr,buf,str,row,col+1,index);
        if(path == 0)
        {
            //如果探测了四周但是没有找到路径，那就回溯
            //回溯到上一个点再来找当前元素 
            //并且把该位置的标志置为0，表示当前没有存在在str中
            buf[row*COL  + col] = 0;
            --(*index);
        }
    }
    return path;
}

int HasPath(char arr[ROW][COL],const char* str)
{
    if(arr == NULL)
    {
        return 0;
    }
    //用一块额外的空间标记当前点是否已经走过
    //这块空间和arr大小相同，点对应
    char* buf = (char*)malloc(sizeof(char)*COL*ROW);
    //初始化为全0，表示当前矩阵走过
    memset(buf,0,sizeof(char)*ROW*COL);
    int i = 0;
    int index = 0;
    int path = 0;
    for(; i < ROW; ++i)
    {
        int j = 0;
        for(; j < COL; ++j)
        {
            if(_HasPath(arr,buf,str,i,j,&index))
            {
                path = 1;
            }
        }
    }
    free(buf);
    return path;
}

void Test()
{
//测试用例1
//    char arr[ROW][COL] = {
//        {'a','b','t','g'},
//        {'c','f','c','s'},
//        {'j','d','e','h'}
//    };

//测试用例2
//    char arr[ROW][COL] = {
//        {'a','a','a','a'},
//        {'a','a','a','a'},
//        {'a','a','a','a'}
//    };

//测试用例3
    char arr[ROW][COL] = {
        {'a','b','c','d'}
    };
    const char* str = "abcd";
    int ret = HasPath(arr,str);
    printf("ret = %d\n",ret);
}


int main()
{
    Test();
    return 0;
}
