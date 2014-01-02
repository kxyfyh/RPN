#include "stdio.h"
#include "iostream"
#include "RPN.h"
#include <regex>

#ifdef _DEBUG
#define DEBUG_CLIENTBLOCK new( _CLIENT_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_CLIENTBLOCK
#endif
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#ifdef _DEBUG
#define new DEBUG_CLIENTBLOCK
#endif

int main() {  
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF); 
	std::string p ="12+22+22+(418+444/10-447+12)/12";
	 std::cout<<RPN::calStr(p.c_str())<<std::endl;
	auto f= fopen("","w"); 
}
