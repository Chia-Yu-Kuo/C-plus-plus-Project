#include <iostream>
#include <string>
#include <list>
#include <tchar.h>
#include <iterator>
#include <vector>
#include <fstream>

using namespace std;




class Process
{
public:
	
	string name;
	
	list<string> List;
	// TID Count
	int Value;
	// �Ψӭp��TID������
	list< const Process*> TID;


public:
	// A or B 
	Process(const Process& a, const Process& b)
	{
		Value = 0;
		List = a.List;
		// A U B
		check_add(b.get_list());


		// TID ��̳s���ɥ[�J
		Support(a.TID);
		Support(b.TID);

		name = list_to_string();
		//	AddValue( inVA._mTID );
	}
	Process()
	{
		Value = 0;
		name = "";
	}

	Process(const Process& inValue)
	{
		*this = inValue;
	}
	Process(const char* inStr)
	{
		Value = 0;
		name = inStr;
	}
	

	
public:

	void operator = (const Process& a)
	{
		name = a.name;
		Value = a.Value;
		List = a.List;
		TID = a.TID;
	}

	// ���o�C��
	const list<string>& get_list()const
	{ 
		return List; 
	}
	// ���o
	int get_value() const 
	{ 
		return Value;
	}


public:
	// ��z



	// ���_�Ǫ��r
	static void arrange(char* ioStr)
	{
		while (ioStr[0] != 0)
		{
			char current_point_to_char = *ioStr;
			if (  ((current_point_to_char >= '0') && (current_point_to_char <= '9')) == false)              //�Ʀr�M�p�g�]�i�H
			{                    
				if (((current_point_to_char >= 'a') && (current_point_to_char <= 'z')) == false)
				{ 
					if (((current_point_to_char >= 'A') && (current_point_to_char <= 'Z')) == false)
					{
						break;
					}
					else
					{
						++ioStr;
					}
				}

			}
			
		}

		ioStr[0] = 0;
	}



	// list to str
	string list_to_string()const
	{
		string ret = "";
		for (list<string>::const_iterator i = List.begin(); i != List.end(); i++)
		{
			ret += *i;
		}
		return ret;
	}

	// �[ �C��
	void Add_Items(const char* b)
	{
		char ch[100];
		const char* str;
		const char* next;
		int length;

		str = b;
		while (true)
		{
			
			while ( str[0] == ',' )// ���L�r��(�u���r��ptr)
			{ 
				str++;
			}

			
			if (str[0] == 0)// �P�_�O�_����
			{ 
				break;
			}

			// ����r��
			next = strchr(str, ',');
			if (next == NULL)
			{
				length = strlen(str);
			}
			else
			{
				length = next - str;
			}


			memset(ch, 0, sizeof(ch));      //��l��ch
			strncpy_s(ch, sizeof(ch), str, length);
			arrange(ch);// ��z
			// �[�� Buffer
			if (strlen(ch) > 0)
			{
				List.push_back(ch);
			}
			
			str += length;
		}
	}

	// �����[
	void add(const string& inStr)
	{
		List.push_back(inStr);
	}

	// �����ƪ��N���[
	void check_add(const string& inStr)
	{
		if (false == whether_have_string(inStr))
		{
			List.push_back(inStr);
		}
	}

	void check_add(const list<string>& inStr)
	{
		for (list<string>::const_iterator i = inStr.begin(); i != inStr.end(); i++)
		{ 
			if (false == whether_have_string(*i))
			{ 
				List.push_back(*i);
			}
		}
	}


	// find �b�C���O�_���Ӧr��
	bool whether_have_string(const string& inStr) const
	{
		string str;
		for (list<string>::const_iterator i = List.begin(); i != List.end(); i++)
		{ 
			if (inStr == *i)
			{ 
				return true;
			}
		}
		return false;
	}

	// �����ۦP list ���� str �b list ���� B 
	bool whether_equal(const list<string>& inStr) const
	{
		for (list<string>::const_iterator i = inStr.begin(); i != inStr.end(); i++)
		{ 
			if (false == whether_have_string(*i))
			{
				return false;
			}
		}
		return true;
	}
	// TID Count
	int get_tid_count(const string& inStr) const
	{
		int ret = 0;
		list<const Process*>::const_iterator i;
		for (i = TID.begin(); i != TID.end(); i++)
		{ 
			if ((*i)->whether_have_string(inStr))
			{
				ret++;
			}
		}
		return ret;
	}

	// �s���å[�J
	void Support(const list< const Process*>& inItem)
	{
		for (list< const Process*>::const_iterator v = inItem.begin(); v != inItem.end(); v++)
		{
			Support(**v);
		}
	}

	void Support(const Process& inValue)
	{
		// ��C��
		if (inValue.whether_equal(this->List))
		{
			list<const Process*>::const_iterator i;
			for (i = TID.begin(); i != TID.end(); i++)
			{ 
				if ((*i) == &inValue)
				{
					break;
				}
			}
			if (i != TID.end())
			{ 
				return;
			}
			Value++;
			TID.push_back(&inValue);
		}
	}


	// �[�� TID �A���ƪ��N���[�F
	void add_tid(const Process& inValue)
	{
		list<const Process*>::const_iterator i;
		for (i = TID.begin(); i != TID.end(); i++)
		{ 
			if ((*i) == &inValue)
			{ 
				break;
			}
		}
		if (i != TID.end())
		{ 
			return;
		}
		Value++;
		TID.push_back(&inValue);
	}
};

// �[�J base
class Item
{
private:

	// �s����A��K�d��
	vector<list<Process>*> _mVector;
	// Base
	list<string> Base;
	// item
	list<Process> TID;
public:
	// �Ѻc
	virtual ~Item()
	{
		Clear();
	}

	void Clear()
	{
		// �M _mVector ���O����
		int i;
		const int n = _mVector.size();
		for (i = 0; i < n; ++i)
		{ 
			delete _mVector[i];
		}
		_mVector.clear();
	}
private:
	

	// �[�� Bae
	void add_base(const string& inName)
	{
		for (list<string>::iterator i = Base.begin(); i != Base.end(); i++)
		{
			if (inName == *i)
			{ 
				return;
			}
		}
		Base.push_back(inName);


	}


	// �[�� Bae
	void add_base(list<string> inList)
	{
		string str;
		for (list<string>::iterator i = inList.begin(); i != inList.end(); i++)
		{
			add_base(*i);
		}

	}
public:

	// Ū��



	void Input(fstream& input_file)
	{
		char temp[100];
		char real[100];
		char* str;
		while (true)
		{
			memset(temp, 0, sizeof(temp));   //��l��ch
			input_file.get(temp, sizeof(temp), '\n');  //����string
			if (0 == input_file.gcount())
			{ 
				break;
			}
			input_file.ignore(1, '\n'); //������\0


			// ����ť�
			str = strchr(temp, ' ');
			if (NULL == str)
			{ 
				continue;
			}
			memset(real, 0, sizeof(real));

			strncpy_s(real, sizeof(real), temp, str - temp);//�u�ƻs�ťի᪺


			// �ظ�� 
			Process v(real);
			v.Add_Items(str + 1);                  //118


			// �[�� base
			add_base(v.get_list());             //273
			
			TID.push_back(v);
		}
	}



	// Add List
	string add_to_output(const list<Process>& inValue)const
	{
		string str = "";
		for (list<Process>::const_iterator i = inValue.begin(); i != inValue.end(); i++)
		{
			str += i->list_to_string() + " ";
		}

		return str;
	}

	// add Vector
	void add_to_vector(const list<Process>& inStr)
	{
		list<Process>* v = new list<Process>(inStr);
		_mVector.push_back(v);
	}

	// Frequent Patterns

	void Support(list<string>& outString, const float min_support)
	{
		list<Process> base;
		// ���� base copy �� value
		{
			for (list<string>::iterator i = Base.begin(); i != Base.end(); i++)
			{
				string name = (*i);
				Process v(name.c_str());
				v.add(name);

				base.push_back(v);
			}
		}
		// new �����A�N base �ŦX���� TIP �[�J
		{
			for (list<Process>::iterator v = base.begin(); v != base.end(); v++)
			{
				Process& value = *v;
				const list<string>& vStr = value.get_list();
				for (list<Process>::const_iterator i = TID.begin(); i != TID.end(); i++)
				{
					if (i->whether_equal(vStr))
						value.add_tid(*i);
				}
			}
		}
		// ���
		Support(outString, base, min_support);
	}

	// ���
	void Support(list<string>& outString, list<Process> inBase, const float min_support)
	{
		list<Process>::iterator i;
		int k, j, n;
		unsigned support_count, check_count;
		int counter;
		list<Process> item;

		support_count = (int)(min_support * (float)TID.size());
		counter = 0;
		while (true)
		{
				// item �M��
			item.clear();
			// ���
			Select(item, inBase, support_count);
			if (item.size() <= 0)
			{ 
				return;
			}
			// �����[�Jstr
			outString.push_back(add_to_output(item));
			// ��Buffer
			add_to_vector(inBase);
			// item re
			inBase.clear();
			// ����
			// �ؼȦs�� array 
			n = item.size();
			vector<Process*> buf;
			//	buf2.setsiz
			//	MValue ** buf2 = (MValue **)malloc( sizeof( MValue* ) * n ) ;
			k = 0;
			for (i = item.begin(); i != item.end(); i++, ++k)
			{
				buf.push_back(&(*i));
				//		buf[k] = &(*i) ;
			}

			n = buf.size();
			// �t��
			for (j = 0; j < n; ++j)
			{
				const Process& bufJ = *buf[j];
				check_count = bufJ.get_list().size() + 1;
				for (k = j + 1; k < n; ++k)
				{
					//		const MValue &bufK = *buf[k] ;

					Process v(bufJ, *buf[k]);
					if (v.get_list().size() == check_count)
					{
						const list<string>& inStr = v.get_list();
						for (i = inBase.begin(); i != inBase.end(); i++)
						{
							if (i->whether_equal(inStr))// �����ۦP
							{
								break;
							}
						}
						if (i == inBase.end()) //���@�ˡA�[�J
						{
							inBase.push_back(v);
						}
					}
				}
			}

		}


	}

	// ��� 
	void Select(list<Process>& outValue, const list<Process>& inMValue, const int inCount)
	{
		for (list<Process>::const_iterator v = inMValue.begin(); v != inMValue.end(); v++)
		{
			const Process& mv = *v;
			string str = mv.list_to_string();
			if (inCount <= v->get_value())
			{
				outValue.push_back(*v);
			}
		}

	}

	// Association
	void Association(list<string>& outStr, const float min_conf)
	{
		// �s����A��K�d��
		unsigned int i;
		int a, b;
		char ch[1024];
		for (i = 0; i < _mVector.size(); ++i)
		{
			const list<Process>& buf = *_mVector[i];
			for (list<Process>::const_iterator v = buf.begin(); v != buf.end(); v++)
			{

				const Process& mv = *v;
				for (list<string>::iterator vstr = Base.begin(); vstr != Base.end(); vstr++)
				{
					const string& str = *vstr;
					if (false == mv.whether_have_string(str))
					{
						a = mv.get_value(); // �����ƶq
						b = mv.get_tid_count(str); //
						if (min_conf <= ((float)b / ((float)a)))
						{
							sprintf_s(ch, sizeof(ch), "%s %s->(%d/%d)", mv.list_to_string().c_str(), str.c_str(), b, a);
							outStr.push_back(ch);
						}
					}
				}
			}

		}
	}

	// Association
	string Association(const list<string>& inKey, const string& inB, const float min_conf)
	{
		unsigned int keyCount = inKey.size() - 1;
		int a, b;

		if (keyCount >= _mVector.size())
		{
			return "Confidence Error";
		}
		const list<Process>& buf = *_mVector[keyCount];
		a = b = 0;
		for (list<Process>::const_iterator v = buf.begin(); v != buf.end(); v++)
		{
			//		const MValue &value = *v ;
			if (v->whether_equal(inKey))
			{
				const Process& mv = *v;
				a += mv.get_value(); // �����ƶq
				b += mv.get_tid_count(inB); //
			}

			if (a > 0)
			{
				char ch[1024];
				cout << b << a;
				if (min_conf <= ((float)b / ((float)a)))
				{
					strcat_s(ch, sizeof(ch), "....ok");
				}
				else
				{
					strcat_s(ch, sizeof(ch), "....err");

				}

				return ch;
			}
		}

		return "No Find ";
	}






	// �� Confidence
	string get_confidence(const char* inStr, const float min_conf)
	{
		//���Rfile

		list<string> buffer;

		string to = "";        //�h�ťժ�
		string ret = "";       //�h�A��
		// �� key
		{
			char ch[1024];
			char ch2[1024];
			strcpy_s(ch, sizeof(ch), inStr);

			char* str1, * str2;

			
			str1 = strchr(ch, ' ');    //��ť�

			if (NULL == str1)
			{ 
				return " Error ";
			}
			// �᭱
			str1[0] = 0;
			str1++;
			if (0 >= strlen(str1))
			{
				return "Error";
			}

			Process::arrange(str1);// ��z
			to = str1;
			// �e��
			str1 = ch;
			// �h�ť�


			while (str1[0] != 0)
			{
				str2 = strchr(str1, ',');      //��,
				memset(ch2, 0, sizeof(ch2));       //��l��ch2

				if (NULL == str2)//�䤣��
				{
					strcpy_s(ch2, sizeof(ch2), str1);  //
					str1 += strlen(str1);
				}
				else
				{
					str2[0] = 0;
					memcpy(ch2, str1, strlen(str1));
					str1 = str2 + 1;
				}

				Process::arrange(ch2);// ��z

				if (0 < strlen(ch2))
				{
					buffer.push_back(ch2);
				}

			}


			ret = Association(buffer, to, min_conf);
		}

		return ret;
	}


};
/// Main 

int main()
{

	fstream input_file;
	char input[1024];
	
	float min_support;
	float min_conf;
	Item item;
	list<string> outList;

	// ���J�ɮ�
//	FILE *fd = fopen( "input.txt" , "r" );
	input_file.open("input.txt");
	if (false == input_file.is_open())
	{
		cerr << "open file error" << endl;
		return 0;
	}

	// ��Jmin support confidence

	while (true)
	{
		cout << "Please input the min support (from 0 to 1 ):" << endl;
		memset(input, 0, sizeof(input));      //��l��input
		cin >> input;
		//���b
		min_support = (float)atof(input);
		if ((min_support <= 1.0f) && (min_support > 0.0f))
		{ 
			break;
		}
	}

	while (true)
	{
		cout << "Please input the min confidence (from 0 to 1 ):" << endl;
		memset(input, 0, sizeof(input));
		cin >> input;
		//���b
		min_conf = (float)atof(input);
		if ((min_conf <= 1.0f) && (min_conf > 0.0f))
		{
			break;
		}
	}

	/*
	for (int i = 0; i < _mVector.size(); ++i)
	{
		const list<Process>& buf = *_mVector[i];
		for (list<string>::iterator vstr = Base.begin(); vstr != Base.end(); vstr++)
		{
			
			 Process& mv = v;
			for (list<Process>::const_iterator v = buf.begin(); v != buf.end(); v++)
			{
				const string& str = *vstr;
				if (false == mv.whether_have_string(str))
				{
					int a, b;
					char ch;
					a = mv.get_value(); // �����ƶq
					b = mv.get_tid_count(str); //
					if (min_conf <= ((float)b / ((float)a)))
					{
						cout << a<<b << endl;
					}
				}
			}
		}

	}
	*/








	// ���JItem
	item.Input(input_file);                   //296
	// ����
	input_file.close();
	item.Support(outList, min_support);
	// ��X


	//test
/*
	for (list<string>::iterator v = minsupport.begin(); v != minsupport.end(); v++)
	{
		if ( v->c_str()==true)
		{
			cout << v->c_str() << endl;
		}
		else
		{
			break;
		}

	}
	
	*/



	//test
	/*
	for (list<Process>::iterator v = base.begin(); v != base.end(); v++)
	{
		Process& value = *v;
		const list<string>& vStr = value.get_list();
		for (list<Process>::const_iterator i = TID.begin(); i != TID.end(); i++)
		{
			if (i->whether_equal(vStr))
				value.add_tid(*i);
		}
	}
	*/

//	::strncpy_s( 
	// Association
	cout << "Strong association is : (" << min_conf << ")\r\n" << endl;
	outList.clear();

	//Strong association
	item.Association(outList, min_conf);
	{
		for (list<string>::iterator v = outList.begin(); v != outList.end(); v++)
		{
			cout << v->c_str() << endl;
		}

	}


	return 0;
}

