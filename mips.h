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
    MIPS();//��ʼ��ָ�
    void file_convert(string path1,string path2);//�������ļ����
    string convert(string line);//ĳ��������ת������

    private:
    vector<instructor> set;//ָ�
    int find_instruction(string name);//��ָ��в��Ҷ�Ӧ��ָ��
    string binary5(string r);//��ʮ����rת��Ϊ5λ��������ʽ
	string binary(int n,int k);//��ʮ����nת��Ϊkλ��������ʽ
};

class MIPS::instructor{//ָ��ṹ
    public:
    string name;
    char type;
    string op;
    string func;
};


#endif


