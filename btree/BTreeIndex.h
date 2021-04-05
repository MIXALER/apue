#pragma once

#include "BTree.h"
#include "DataBase.h"

#include <iostream>

using namespace std;

template <class KeyType, class RecordType>
class BTreeIndex {
private:
	BTree<KeyType, int> * btree = NULL;
	DataBase<RecordType> * db = NULL;
public:
	BTreeIndex(int n);
	~BTreeIndex();
	//���һ����¼���ҽ�key����������
	void add(KeyType key, RecordType record);
	//ɾ��ָ��key�ļ�¼��
	void del(KeyType key);
	//��ѯָ��key�ļ�¼��
	void find(KeyType key ,RecordType & record);
	//���س�Ա����
	DataBase<RecordType> * getDB();
	//���س�Ա����
	BTree<KeyType, int> * getBTree();
};


template <class KeyType, class RecordType>
BTreeIndex<KeyType, RecordType>::BTreeIndex(int n) {
	btree = new BTree<KeyType, int>(n);
	db = new DataBase<RecordType>(string("dbFile"));
}

template <class KeyType, class RecordType>
BTreeIndex<KeyType, RecordType>::~BTreeIndex() {
	delete btree;
	btree = NULL;
	delete db;
	db = NULL;
}

//���һ����¼���ҽ�key����������
template <class KeyType, class RecordType>
void BTreeIndex<KeyType, RecordType>::add(KeyType key, RecordType record) {
	//�������ݣ���ø����ݵĵ�ַ��
	int pos = db->save(record);
	//��(key->pos)����������
	btree->add(key, pos);
}

//ɾ��ָ��key�ļ�¼��
template <class KeyType, class RecordType>
void BTreeIndex<KeyType, RecordType>::del(KeyType key) {
	//���������ҵ�Ҫɾ���ļ�¼��λ�á�
	int pos = this->btree->getKeyValue(key);
	//ɾ�����ݿ��ļ���ָ��λ�õļ�¼��
	this->db->remove(pos);
	//ɾ��������
	this->btree->del(key);
}

//��ѯָ��key�ļ�¼��
template <class KeyType, class RecordType>
void BTreeIndex<KeyType, RecordType>::find(KeyType key, RecordType & record) {
	//���������ҵ�Ҫ��ѯ�ļ�¼��λ�á�
	int pos = this->btree->getKeyValue(key);
	if (pos != -1) {
		//����posλ�õļ�¼��
		record = this->db->getByOffset(pos);
	}
}

//���س�Ա����
template <class KeyType, class RecordType>
DataBase<RecordType> * BTreeIndex<KeyType, RecordType>::getDB() {
	return this->db;
}

//���س�Ա����
template <class KeyType, class RecordType>
BTree<KeyType, int> * BTreeIndex<KeyType, RecordType>::getBTree() {
	return this->btree;
}
