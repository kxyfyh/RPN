#include "RPN.h"
#include <assert.h>
static const char* symbol="+-*/()";
#define MAX_NUMLENGTH 24

double RPN::calStr(const char* str ){
#ifdef _DEBUG
	printf("str=%s\n",str);
#endif // _DEBUG  
	std::vector<char*> expList;
	std::vector<char*> suffix_list;
	RPN::split(str,expList);

#ifdef _DEBUG
	std::string outstr="[";
	for (char* var:expList)
	{
		outstr+=var;
		outstr+=" ";
	}	
	outstr+="]";
	printf("expList=%s\n",outstr.c_str());
#endif // _DEBUG


	RPN::prefixToSuffix(expList,suffix_list);

#ifdef _DEBUG
	outstr="[";
	for (char* var:suffix_list)
	{
		outstr+=var;
		outstr+=" ";
	}
	outstr+="]";
	printf("suffix_list=%s\n",outstr.c_str());
	
#endif // _DEBUG
	double re=RPN::calList(suffix_list);
	for (char* var : expList)
	{
		free(var);
	} 
	return re;
}

double RPN::calList( std::vector<char*>& list )
{

	std::vector<char*> stack; 
	std::vector<char*> buff;
	char* tmp=nullptr;

	for (char* item : list) {
		bool isSymbol=strchr(symbol,item[0])!=NULL;
		if (!isSymbol) {
			stack.push_back(item);
			continue;
		} else {
			double one = atof(stack.back()); 
			stack.pop_back();
			double two = atof(stack.back());
			stack.pop_back();
			double value = 0;
			if (item[0]=='+') {
				value = two + one;
			} else if (item[0]=='-') {
				value = two - one;
			} else if (item[0]=='*') {
				value = two * one;
			} else if (item[0]=='/') {
				value = two / one;
			}
			tmp=nullptr;
			tmp=(char*)malloc(MAX_NUMLENGTH);
			sprintf(tmp,"%f",value,NULL);
			buff.push_back(tmp);
			stack.push_back(tmp);
		}
	}
	double re= atof(stack.back());
	stack.pop_back();
	for (char* var : buff)
	{
		free(var); 
	}
	return re;
}

bool RPN::priority( char* one, char* two )
{

	if ((one[0]=='*' || one[0]=='/') && (two[0]!='*' && two[0]!='/')) {
		return true;
	}
	if ((one[0]=='+' || one[0]=='-') && (two[0]!='*' && two[0]!='/')) {
		return true;
	}
	return false;
}

void RPN::prefixToSuffix( std::vector<char*>& prefix_list,std::vector<char*>& suffix_list )
{ 
	assert(suffix_list.size()==0);//"vector size must empty"
	std::vector<char*> stack;
	for (char* item : prefix_list) {
		bool isSymbol=strchr(symbol,item[0])!=NULL;
		if (!isSymbol) {
			// 不是符号就输出
			suffix_list.push_back(item);
			continue;
		}
		if (item[0]=='(' || stack.empty()) {
			stack.push_back(item);
			continue;
		}
		if (item[0]==')') {
			while (stack.back()[0]!='(') {					 
				suffix_list.push_back(stack.back());
				stack.pop_back();
			}
			stack.pop_back();
			continue;
		}
		while (priority(stack.back(), item)) {
			suffix_list.push_back(stack.back());
			stack.pop_back();
			if (stack.empty())
				break;
		}
		stack.push_back(item);
	}
	while (!stack.empty()) {
		suffix_list.push_back(stack.back());
		stack.pop_back();
	}
}

void RPN::split( const char* src,std::vector<char*>& expList )
{
	assert(expList.size()==0);//"vector size must empty"
	int m_cpLen;
	int begin;
	int i=0;
	char* tmp;
	begin=i;
	for (; ; i++) {
		bool isSymbol=src[i]!=NULL&&strchr(symbol,src[i])!=NULL;

		if(isSymbol) {
			m_cpLen=i-begin;
			if(m_cpLen>0){
				tmp=(char*)malloc(m_cpLen+1);
				memset(tmp,0,m_cpLen+1);
				memcpy(tmp,src+begin,m_cpLen);
				expList.push_back(tmp);//添加之前数字
			}

			tmp=(char*)malloc(2);
			memset(tmp,0,2);
			memcpy(tmp,src+i,1);
			expList.push_back(tmp);
			begin=i+1;
		}else{
			if(src[i]=='.'){
				continue;
			}
			if(src[i]>='0'&&src[i]<='9'){
				continue;
			}

			m_cpLen=i-begin+1;
			tmp=(char*)malloc(m_cpLen+1);
			memset(tmp,0,m_cpLen+1);
			memcpy(tmp,src+begin,m_cpLen);
			expList.push_back(tmp);//添加之前数字
			break;
		} 

	}

}
