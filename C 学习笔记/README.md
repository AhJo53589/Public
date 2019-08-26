# C 面试题学习笔记

## 语法

### 命令行启动参数
```C++
int main(int argc, char * argv[])
{
	for (int i = 0; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}
}
```


### scanf不定长度的数据输入到数组
```C
char c;
if ((c = getchar()) == '\n') break;
```

[关于不定长度的数据输入到数组](https://blog.csdn.net/liuyang19890710/article/details/8965306)
---

## 知识

