#pragma once
#include <vector>
/************************************************************************/
/* 逆波兰式                                                                     */
/************************************************************************/
class RPN
{ 
public:
	/************************************************************************/
	/* 中缀表达式直接计算                                                                     */
	/************************************************************************/
	static double calStr(const char* str);
	/************************************************************************/
	/* 计算后缀表达式                                                                     */
	/************************************************************************/
	static double calList(std::vector<char*>& suffix_list);
	/************************************************************************/
	/* 中缀表达式转换成后缀表达式                                          */
	/************************************************************************/
	static void prefixToSuffix(std::vector<char*>& prefix_list,std::vector<char*>& suffix_list);
	/************************************************************************/
	/* 容器(expList)中的指针需要调用free清理内存                                     */
	/************************************************************************/
	static void split(const char* src,std::vector<char*>& expList);
private: 
	static bool priority(char* one, char* two);

};


