#include <string>
#include <vector>
using namespace std;

//����ʵ�ʽ����޸�
enum CAT {f,c,t,d,v,vn,vf};
//����ʵ�ʽ����޸�
enum TVAL {Int,Double,String,Char};
//���ͱ�
struct TYPEL
{
	TVAL tval;
	void* tpoint;
};
vector<TYPEL> typel_list;

//�ܱ�
struct SYNBL
{
	string name;
	TYPEL* TYPE;
	CAT cat;
	void* addr;
};
vector<SYNBL> synbel_list;

//�����
struct AINFL
{
	int low;
	int up;
	TYPEL* ctp;
	int clen;
};
vector<AINFL> ainfl_list;

//�ṹ�� ��ʱ�ò���
struct RINFL
{
	string name;
	int off;
	TYPEL* tp;
};
vector<RINFL> rinfl_list;

//�βα�
struct FPL
{
	string name;
	TYPEL *tp;
	CAT cat;
	int level; //��Ӧ���¼�еĵڼ���
	int off; //��Ӧ��ƫ�Ƶ�ַ
};
vector<FPL> fpl_list;

//������
struct PFINFL
{
	int level;
	int off;
	int FN;
	long ENTRY;
	FPL *fpl_pointer;
	int data_long;//�ú�������Ҫ���ٵĿռ�Ĵ�С Ϊ��Ŀ��������ɷ���
};
vector<PFINFL> pfinfl_list;

//��ʶ���� Ϊ�˷����ж��Ƿ��ض����Լ������Ƿ�ƥ�� ��������һ����ʶ����
struct IDENTIFY
{
	string name;
	TYPEL *tp;
	int level;//��ǰ��������Ĳ��� 0Ϊȫ�������� 1Ϊmain������ �����������з��ص�ʱ����Ҫɾ����
};
