#include"mips.h"

MIPS::MIPS(){

    char type;
    string func;
    string name;
    string op;

    //����ָ�
    ifstream file("instruction_set.txt");
    while( file>>type){
        instructor temp;
        temp.type=type;
        switch (type)
        {
            case 'R':
                file>>name>>op>>func;
                temp.name=name;
                temp.func=func;
                temp.op=op;
                break;
                            
            case 'I':
            case 'J':
                file>>name>>op;
                temp.name=name;
                temp.op=op;
				if (type=='J')
					cout<<name<<" "<<op<<endl;
                break;
        }
        set.push_back(temp);
    }
    file.close();
    cout<<"instruction_set load!"<<endl;

}
void MIPS::file_convert(string path1,string path2){
    ifstream in(path1);
    ofstream out(path2);

    string line; 
    string binarycode;

    while(getline(in,line)){

        binarycode=convert(line);
        out<<binarycode<<endl;

    }
    in.close();
    out.close();
}

string MIPS::convert(string line) {
	string name;
	int i=0;
	while(line[i]!=' ') {
		name+=line[i];
		i++;
	}
	int index=find_instruction(name);
	if(index==-1) {
		cout<<"error:can't find instruction";
	}
	//set[index]�Ƕ�Ӧ��ָ������

	//zx����������ʱ�洢���¶���line�������
	const char *z0;
	char z1[20];
	int z2,z3,z4;
	z0=line.c_str();//��lineתΪchar��ʽ���洢��z0��

	string rs,rt,rd,shamt,imm,off,tar;

	if(set[index].type=='R') {


		//sll rd,rt,sa ��ʽ
		if(name == "sll" || name == "srl" || name == "sra") {
			sscanf(z0,"%s $%d,$%d,%d",z1,&z2,&z3,&z4);
			rs="00000",rt=binary(z3,5),rd=binary(z2,5),shamt=binary(z4,5);
			return set[index].op+rs+rt+rd+shamt+set[index].func;
		}
		//sllv rd,rt,rs ��ʽ 
		else if(name=="sllv"||name=="srlv"||name=="srav"){
			sscanf(z0,"%s $%d,$%d,$%d",z1,&z2,&z3,&z4);
			rs=binary(z4,5),rt=binary(z3,5),rd=binary(z2,5);
			return set[index].op+rs+rt+rd+"00000"+set[index].func;
		
		}
		//jr $31 ��ʽ
		else if(name =="jr") {
			i=i+1;
			if(line[i]=='$') {
				i++;
				while(i<line.size() && line[i]<='9' && line[i]>='0')
					rs+=line[i++];
			}
			rs=binary5(rs);
			rt=rd="00000";
			return set[index].op+rs+rt+rd+"00000"+set[index].func;
		}
		// add rd,rs,rt ���͸�ʽ
		else {
			i=i+1;
			if(line[i]=='$') {
				i++;
				while(line[i]!=',')
					rd+=line[i++];
			}
			i++;
			if(line[i]=='$') {
				i++;
				while(line[i]!=',')
					rs+=line[i++];
			}
			i++;
			if(line[i]=='$') {
				i++;
				while(i<line.size() && line[i]<='9' && line[i]>='0')
					rt+=line[i++];
			}
			rs=binary5(rs);
			rt=binary5(rt);
			rd=binary5(rd);
			//cout<<rs<<" "<<rt<<" "<<rd<<endl;
			return set[index].op+rs+rt+rd+"00000"+set[index].func;
		}


	} else if(set[index].type=='I') {
		//lui rt,imm ��ʽ
		if(name=="lui") {
			sscanf(z0,"%s $%d,%d",z1,&z2,&z3);
			rs="00000",rt=binary(z2,5),imm=binary(z3,16);
			return set[index].op+rs+rt+imm;
		}
		//lw rt,off(rs)��ʽ
		else if(name=="lw"||name=="sw") {
			sscanf(z0,"%s $%d,%d($%d)",z1,&z2,&z3,&z4);
			rs=binary(z4,5),rt=binary(z2,5),off=binary(z3,16);
			return set[index].op+rs+rt+off;
		}
		//bne rs,rt,off
		else if(name=="beq"||name=="bne") {
			sscanf(z0,"%s $%d,$%d,%d",z1,&z2,&z3,&z4);
			rs=binary(z2,5),rt=binary(z3,5),off=binary(z4,16);
			return set[index].op+rt+rs+off;
		}
		//addi rt,rs,imm ��ʽ
		else {
			sscanf(z0,"%s $%d,$%d,%d",z1,&z2,&z3,&z4);
			rs=binary(z3,5),rt=binary(z2,5),imm=binary(z4,16);
			return set[index].op+rs+rt+imm;
		}
	} else {//j tar ��ʽ
		sscanf(z0,"%s %d",z1,&z2);
		
		tar=binary(z2,26);
		return set[index].op+tar;
	}

}

int MIPS::find_instruction(string name){
    for(int i=0;i<set.size();i++){
        if(set[i].name==name){
            return i;
        }
    }
    return -1;
}

string MIPS::binary5(string r){
    int n=stoi(r);
    string bin;
    while(n!=0){
        if(n%2==1)
            bin='1'+bin;
        else
            bin='0'+bin;
        n=n/2;
    }
    while(bin.size()<5)
        bin='0'+bin;
    return bin;
}
string MIPS::binary(int n,int k) {
	string bin;
	while(n!=0) {
		if(n%2==1)
			bin='1'+bin;
		else
			bin='0'+bin;
		n=n/2;
	}
	while(bin.size()<k)
		bin='0'+bin;
	return bin;
}
