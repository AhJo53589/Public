# Linux学习笔记

## 20190819
安装gcc，g++和gdb，编译和调试helloworld。  


g++一直安装不上，直到找到了这篇文章。  
[linux下安装gcc,g++](https://blog.csdn.net/u011131874/article/details/52853234)  

gdb调试，看的这一篇，讲得比较细。  
[linux下gdb调试](https://www.jianshu.com/p/cd04aabb94a0)  



## 20190726
遇到第一个问题是，建立的服务外部无法访问，猜测原因是防火墙，查询了关闭防火墙的方法但是失败。  
请教了周蒙之后，发现是CentOS7关闭防火墙的方法有变更。  
另外还需要修改SELinux配置。  
[CentOS7关闭防火墙和SELinux](https://jingyan.baidu.com/article/86112f1362a63e2737978719.html)