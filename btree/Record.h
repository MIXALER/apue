#pragma once

//Ϊ��ʵ�鷽��,ȫ��ʹ��public���ݡ�
//ÿ����¼100�ֽڴ�С��
class Record
{
public:
	//��Ϊ�ؼ���
	int key = -1;
	//value
	char content[96] = "";

	Record();
	Record(int key);
};

Record::Record()
{
}
Record::Record(int key)
{
	this->key = key;
}

