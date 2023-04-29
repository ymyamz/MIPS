#ifndef MIPS_H_
#define MIPS_H_

#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<stack>
using namespace std;

class MIPS{
    public:
    class instructor;
    MIPS();//初始化指令集
    void file_convert(string path1,string path2);//将整个文件汇编
    string convert(string line);//某条汇编语句转机器码

    private:
    vector<instructor> set;//指令集
    int find_instruction(string name);//在指令集中查找对应的指令
    string binary5(string r);//把十进制r转化为5位二进制形式
	string binary(int n,int k);//把十进制n转化为k位二进制形式
};

class MIPS::instructor{//指令结构
    public:
    string name;
    char type;
    string op;
    string func;
};


#endif


