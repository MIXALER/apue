#pragma once

#include <iostream>
#include <fstream>

using namespace std;



/**
@title:����ģ�����ݿ��ļ�����װ�����ļ�������һ����¼��ɾ����¼�ķ�����
*/
template <class RecordType>
class DataBase {
private:
	string dbFilePath;
	int recordSize = 0;
public:
	//���캯��
	DataBase<RecordType>(string dbFilePath);
	//����һ����¼���ļ���Ȼ�󷵻ظü�¼��λ�á�
	int save(RecordType record);
	//ɾ��ָ��λ�õļ�¼��
	void remove(int offset);
	//����ָ��λ�õļ�¼��
	RecordType getByOffset(int offset);
};

//���캯��
template <class RecordType>
DataBase<RecordType>::DataBase(string dbFilePath) {
	this->dbFilePath = dbFilePath;
	//��¼�Ĵ�С��
	this->recordSize = sizeof(RecordType);

	//���������ļ��Ƿ���ڡ�
	fstream fs;
	fs.open(this->dbFilePath, ios::in | ios::binary);
	if (fs) {
		fs.close();
	}
	else {
		//�������ݿ��ļ���
		fstream fs(this->dbFilePath, ios::out | ios::binary);
		fs.close();
	}
}

template <class RecordType>
//����һ����¼���ļ���Ȼ�󷵻ظü�¼��λ�á�
int DataBase<RecordType>::save(RecordType record) { 
	int pos = -1;
	//���ļ���
	fstream fs;
	fs.open(this->dbFilePath, ios::in |ios::out | ios::binary);
	//��λ���ļ���ĩβ��
	fs.seekp(0, ios::end);
	//��¼�洢�ü�¼�Ŀ�ʼλ�á�
	pos = fs.tellp();
	//д���¼��
	fs.write((char*)(&record), this->recordSize);
	//�ر��ļ�����
	fs.flush();
	fs.close();
	//���ظü�¼���ļ��еĿ�ʼλ�á�
	return pos;
}

/**
	@desc:ɾ��ָ��λ�õļ�¼��
	ע�⣬ɾ������ͨ����ɾ�����Ǻ�һ����
	����˵abcɾ��b֮��Ϊac�����Ǳ�Ϊa�հ�b��
	��Ϊabc������¼��λ�ö��Ǳ������˵ġ����ֱ��ɾ��b�����ҽ�c��ǰ��£�Ļ�����Ҫ����������
	�������ǲ������������������b��¼���ɡ�
*/
template <class RecordType>
void DataBase<RecordType>::remove(int offset) {
	//...��ʱ��ʵ��ɾ������Ϊ�ô���������������������ʵ����û������ġ�
	//ֻҪ�ǿ����ݲ���ʹ�ã�����������һ����
	//�ص��������ռ���������á�
}

//����ָ��λ�õļ�¼��
template <class RecordType>
RecordType DataBase<RecordType>::getByOffset(int offset) {
	//���ڴ洢��ʱ����ֵ��
	Record ret;
	//���ļ���
	fstream fs;
	fs.open(this->dbFilePath, ios::in | ios::binary);
	//��λ��ָ��λ�á�
	fs.seekp(offset, ios::beg);
	//�����¼��
	fs.read((char*)(&ret), this->recordSize);
	//�ر��ļ�����
	fs.flush();
	fs.close();
	//���ظü�¼��
	return ret;
}