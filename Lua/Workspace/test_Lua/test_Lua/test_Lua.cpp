// test_Lua.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


//////////////////////////////////////////////////////////////////////////
// Hello AhJo
//////////////////////////////////////////////////////////////////////////
//#include <tchar.h>
//#include <stdio.h>  
//#include <string.h>  
//#include <iostream>  
//
//extern "C"
//{
//#include <lua.h>  
//#include <lualib.h>  
//#include <lauxlib.h>  
//}
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	using namespace std;
//
//	lua_State *L = luaL_newstate();
//	luaL_openlibs(L);
//	luaL_dofile(L, "test.lua");
//
//	lua_close(L);
//
//	cin.get();
//	return 0;
//}





//////////////////////////////////////////////////////////////////////////
// lua调用C++
//////////////////////////////////////////////////////////////////////////
//#include<iostream>
//using namespace std;
//#include<stdio.h>
//extern "C" {
//#include <lua.h>
//#include <lualib.h>
//#include <lauxlib.h>
//}
////#pragma comment(lib, "lua5.1.lib")
//lua_State* L;
//static int average(lua_State *L)
//{
//	//返回栈中元素的个数
//	int n = lua_gettop(L);
//	double sum = 0;
//	int i;
//	for (i = 1; i <= n; i++)
//	{
//		if (!lua_isnumber(L, i))
//		{
//			lua_pushstring(L, "Incorrect argument to 'average'");
//			lua_error(L);
//		}
//		sum += lua_tonumber(L, i);
//	}
//	/* push the average */
//	lua_pushnumber(L, sum / n);
//	/* push the sum */
//	lua_pushnumber(L, sum);
//
//	/* return the number of results */
//	return 2;
//}
//
//int main(int argc, char*argv[])
//{
//	/* initialize Lua */
//	L = luaL_newstate();
//	/* load Lua libraries */
//	luaL_openlibs(L);
//	/* register our function */
//	lua_register(L, "average", average);
//	/* run the script */
//	luaL_dofile(L, "test_average.lua");
//
//	lua_getglobal(L, "avg");
//	cout << "c++: avg is:" << lua_tointeger(L, -1) << endl;
//	lua_pop(L, 1);
//	lua_getglobal(L, "sum");
//	cout << "c++: sum is:" << lua_tointeger(L, -1) << endl;
//	/* cleanup Lua */
//	lua_close(L);
//
//	return 0;
//}




//////////////////////////////////////////////////////////////////////////
// C++调用lua
//////////////////////////////////////////////////////////////////////////
#include <stdio.h> 
extern "C" {
#include <lua.h> 
#include <lualib.h>
#include <lauxlib.h>
}
//#pragma comment(lib, "lua5.1.lib")

/* the Lua interpreter */
lua_State* L;
int luaadd(int x, int y)
{
	int sum;
	/* the function name */
	lua_getglobal(L, "add");		

	int nTop = lua_gettop(L); //得到栈的元素个数。栈顶的位置。
	/* the first argument */
	lua_pushnumber(L, x);			
	nTop = lua_gettop(L);

	/* the second argument */
	lua_pushnumber(L, y);			
	nTop = lua_gettop(L);

	/* call the function with 2
	arguments, return 1 result */
	lua_call(L, 2, 1);				
	nTop = lua_gettop(L);

	/* get the result */
	sum = (int)lua_tonumber(L, -1);	
	nTop = lua_gettop(L);

	/*清掉返回值*/
	lua_pop(L, 1);					
	nTop = lua_gettop(L);



	/*取出脚本中的变量z的值*/
	lua_getglobal(L, "z");			
	nTop = lua_gettop(L);

	int z = (int)lua_tonumber(L, 1); 
	nTop = lua_gettop(L);
	lua_pop(L, 1);				

	nTop = lua_gettop(L);

	return sum;
}
int main(int argc, char *argv[])
{
	int sum;
	/* initialize Lua */
	L = luaL_newstate();
	/* load Lua base libraries */
	//lua_baselibopen(L);
	/* load the script */
	luaL_dofile(L, "test_add.lua");
	/* call the add function */
	sum = luaadd(10, 15);
	/* print the result */
	printf("The sum is %d", sum);
	/* cleanup Lua */
	lua_close(L);
	return 0;
}