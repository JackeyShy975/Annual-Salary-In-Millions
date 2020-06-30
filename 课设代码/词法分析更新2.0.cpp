#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector> 
#include <string>
using namespace std;
//�ʷ������궨��
#define kt_num 16//�ؼ��ֱ�Ĵ�С
#define s_pt_num 15//���ַ������Ĵ�С
#define token_num 400//token��Ĵ�С
#define d_pt_num 3//˫�ַ������Ĵ�С
#define error_s -1 //����״̬
#define end_s  0//����״̬
//�������ֱ�����
#define iT 1//��ʶ�� 
#define cT 2//�ַ� 
#define sT 3//�ַ��� 
#define CT 4//���� 
#define KT 5//�ؼ��� 
#define PT 6//��� 
struct token
{
    string token_value;//tokenֵ
    int token_code;//������
};
vector<token> token_list;//����ʷ��������õ�token�� 
//****************�ؼ��ֱ�*******************
    string K_T[kt_num] = { "int"   , "main"  , "void" , "if"    , "else",
                            "return", "string", "float", "double", "case",
                            "switch", "while" , "break", "bool"  , "char",
                            "default" };
//****************�����*******************
    //  ���ֽ��
    string single_PT[s_pt_num]={ "=" ,">" ,"<" ,"+" ,"-" ,
                                        "*" ,"/" ,"{" ,"}" ,"," ,
                                        ";" ,"(" ,")" ,"[" ,"]" };
    //˫�ֽ��
    string double_PT[d_pt_num]={ ">=","<=","==" };
//Token����
class lexic
{
public:
      lexic(){ i_T_num=c_T_num=s_T_num=C_T_num=1;};
      void open_file();//�򿪲����ļ�
      void close_file();//�رղ����ļ�a
    FILE *f =NULL;
    //�������Զ����ı�
    int i_T_num,c_T_num,s_T_num,C_T_num;//�ֱ�Ϊ�ĸ��������
    bool lexic_analyze();//�ʷ���������
    int change_num(char buffer);//�ַ�ת���ɴ���
    int s_change(int s_now,char buffer);//ͨ������״̬�Զ���ʵ��״̬��ת��
    int token_code(int s_before,string value);//ͨ��������״̬������token����Ų��洢����Ӧ�ı���
    int token_kind(int s_before,string value);//����token����������
};
void lexic::open_file()
{
    f= fopen("����.txt", "r"); //  ���д��ļ�
    if(f == NULL){
        cout << "�ļ���ʧ�ܣ�" << endl;
        exit(0);
    }
    else
    {
        cout<<"�ļ��򿪳ɹ���"<<endl;
    }
}
void lexic::close_file()
{
     fclose(f); // �رմ򿪵��ļ�
}
bool lexic::lexic_analyze()
{
    int kind;
    int s_now=1,s_before;//��ǰ״̬��֮ǰ״̬
    int token_n=0;//token����±�
    char buffer;//ÿ�ζ�����ַ�
    token temp;
    buffer = fgetc(f);
    while(buffer!= '#')
        {
            s_before = s_now;       		 //����ǰһ��״̬
            s_now = s_change(s_now,buffer);//״̬ת��

            if(s_now == error_s)//��������
            {
                cout<<"ʶ���ַ�:"<<buffer<<"ʱ��������!"<<endl;//����ĳ�ַ�ʱ��������
                return false;
            }
            else if(s_now == 13)	//״̬����ʼ�������ո����
            {
                s_now = 1;
            }
            else if(s_now != end_s)  	//δ����ֹ״̬
            {
                temp.token_value+= buffer;
            }
            else if(s_now == end_s)		//����ֹ״̬
            {
                temp.token_code = token_code(s_before,temp.token_value);//����token������
                fseek(f,-1,SEEK_CUR);
                token_list.push_back(temp);
                temp.token_value="";//���³�ʼ��һ����ʱ���� 
                s_now = 1;
            }
            else
            {
                cout<<"���ַǷ�״̬��"<<endl;//������������״̬
                return false;
            }
            buffer = fgetc(f);//��ȡ��һ���ַ�
        }
        s_before = s_now;
    return true;


}
int lexic::change_num(char buffer)
{//���ַ�ת��Ϊ��Ӧ�Ĵ���
    int n;
    if((buffer >= 'a' && buffer <= 'z')||(buffer >= 'A' && buffer <= 'Z')) n = 1;
    else if(buffer >= '0' && buffer <= '9') n = 2;
    else if(buffer == '.') n = 3;
    else if(buffer == ' '||buffer == '\n'||buffer == '\t') n= 4;//�ո���л�tab
    else if(buffer == 39) n = 5;//''
    else if(buffer == 34) n = 6;//""
    else if(buffer == '>') n = 7;//˫�ַ����
    else if(buffer == '<') n = 8;//˫�ַ����
    else if(buffer == '=') n = 9;//˫�ַ����
    else n= 10;
    return n;

}
int lexic::s_change(int s_now,char buffer)
{//ͨ���Զ�����ʵ��״̬ת��
    int n,s_next;
    n=change_num(buffer);
    switch(s_now)
        {
        case 1:
            if(n == 1) s_next = 2;
            else if(n == 2) s_next = 3;
            else if(n == 5) s_next= 6;
            else if(n== 6)  s_next = 9;
            else if(n == 7) s_next = 12;	//˫�ַ����
            else if(n == 8) s_next = 14;	//˫�ַ����
            else if(n == 9) s_next = 16;	//˫�ַ����
            else if(n== 10) s_next = 18; //���ַ����
            else if(n == 4) s_next = 13;//��ʼ�����ո����
            else s_next = error_s;//ʵ�ֱ�����
            break;
        case 2:
            if((n== 1)||(n == 2)||(buffer == 95)) s_next = 2;//��ʶ����ĸ��ͷ-��ĸ�����»������
            else s_next = 0;
            break;
        case 3:
            if(n == 2) s_next = 3; //����
            else if(n == 3) s_next = 4;//С��
            else if((n == 4)||(n == 7)||(n == 8)||(n == 9)||(n == 10)) s_next = 0;//���������ո����ֹͣ
            else s_next = error_s;
            break;
        case 4:
            if(n == 2) s_next = 5;
            else s_next = error_s;
            break;
        case 5:
            if(n== 2) s_next=5;
            else if((n == 4)||(n== 7)||(n== 8)||(n== 9)||(n== 10)) s_next = 0;//���������ո����ֹͣ
            else s_next = error_s;
            break;
        case 6:
            if(n== 1) s_next = 7;
            else s_next = error_s;
            break;
        case 7:
            if(n== 5) s_next = 8;
            else s_next = -1;
            break;
        case 8:
            s_next = 0;
            break;
        case 9:
            if(n== 1) s_next = 10;
            else s_next = -1;
            break;
        case 10:
            if(n == 1) s_next = 10;
            else if(n == 6) s_next = 11;
            else s_next=-1;  //�ַ���ֻ����ĸ
            break;
        case 11:
            s_next = 0;
            break;
        case 12:
            if(n == 9) s_next = 13;//>=
            else s_next = 0;
            break;
        case 13:
            s_next = 0;
            break;
        case 14:
            if(n == 9) s_next = 15;//<=
            else s_next = 0;
            break;
        case 15:
            s_next = 0;
            break;
        case 16:
            if(n == 9) s_next = 17;//==
            else s_next = 0;
            break;
        case 17:
            s_next = 0;
            break;
        case 18://���ַ����
            s_next = 0;
            break;
        default:
            cout << endl << "�����޷�ʶ����ַ��� '"<<buffer<<endl;//�����޷�ʶ����ַ�
            break;
        }
        return s_next;
}
int lexic::token_code(int s_before,string value)
{
    int i=0;
    if(s_before == 2)
    {
        for(i = 0; i < kt_num; i++)
        {
            if(K_T[i].compare(value) == 0)
            {
                return KT;//�ɹ�ƥ�䵽���ǹؼ��� 
            }
        }
        return iT;//δ�鵽�Ļ���Ϊ��ʶ�� 
    }
    else if((s_before == 5)||(s_before == 3)) return CT;
    else if(s_before == 8)  return cT;
    else if(s_before == 11) return sT;
    else if((s_before == 13)||(s_before == 15)||(s_before == 17))
    {//ͳһ���������ȥ��
        for(i = 0; i < d_pt_num; i++)
        {
            if(double_PT[i].compare(value) == 0)
            {
                return PT;
            }
        }
    }
    else if((s_before == 12)||(s_before == 14)||(s_before ==16)||(s_before == 18))
    {//ͳһ�����������ȥ��
        for(i = 0; i < s_pt_num; i++)
        {
            if(single_PT[i].compare(value) == 0)
            {
                return PT;
            }
        }
    }

}
int main()
{
    bool test;
    lexic a;
    a.open_file();
    test=a.lexic_analyze();
    a.close_file();
    if(test)
        cout<<"�ʷ������ɹ���"<<endl;
    else
        cout<<"�ʷ�����ʧ�ܣ�"<<endl;
    cout<<endl;
    for(auto it=token_list.begin();it!=token_list.end();it++)
    {
    	cout<<"<"<<(*it).token_code<<","<<(*it).token_value<<">"<<endl;
	}
    return 0;
}

