#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <queue>
#include <math.h>

using namespace std;

/*	@desc:BTreeNode
@1:B�����ص㣨ָ��ÿ��������n��key�������
@����㣺�����������������ָ�뱻ʹ�ã����н��ָ��B����һ���㡣
@Ҷ�ӽ�㣺����������ҷֲ������һ��ָ������ָ��ͬ����һ����㡣ʣ��ָ��������((n+1)/2)��ȡ������ʹ�ã���ȻҲ����((n+1)/2)��ȡ����key��
@�ڲ��㣺����������((n+1)/2)��ȡ����ָ��ʹ�á�

����1��n=3����Ҷ�ӽ������2��ָ�룬2��key���ڲ�������2��ָ�룬1��key��
����2��n=4����Ҷ�ӽ������2��ָ�룬2��key���ڲ�������3��ָ�룬2��key��
����3��n=5����Ҷ�ӽ������3��ָ�룬3��key���ڲ�������3��ָ�룬2��key��
����4��n=10����Ҷ�ӽ������5��ָ�룬5��key���ڲ�������6��ָ�룬5��key��
*/

template <class KeyType, class ValueType>
class BTreeNode {
public:
	int keyNumber = 0;//���ڼ�¼��ǰ�������key��������
	bool isLeaf = true;//��ʶ������Ƿ�ΪҶ�ӽ�㡣
	KeyType * key;//key���ڼ�¼���е�key��
				  //n��(����ʱ����n+1������ʹ�õ�0��)
	BTreeNode<KeyType, ValueType> * parent;//parentָ�򸸽ڵ�
	void ** ptr; //ptr�Ǻ���ָ��
				 //n+1��(����ʱ����n+1����ȫ��ʹ��)
	ValueType * value;//Ҷ�ӽ���ֵ��

	BTreeNode(int n, bool isLeaf);//n��ʾ�����������key����
	~BTreeNode();
};

template <class KeyType, class ValueType>
BTreeNode<KeyType, ValueType>::BTreeNode(int n, bool isLeaf) {
	this->isLeaf = isLeaf;
	this->keyNumber = 0;
	this->parent = NULL;
	this->key = new KeyType[n + 1];
	this->ptr = new void*[n + 1];
	for (int i = 0; i < n + 1; i++) {
		this->ptr[i] = NULL;
	}
	//Ҷ�ӽ��
	if (isLeaf) {
		value = new ValueType[n + 1];
	}
}

template <class KeyType, class ValueType>
BTreeNode<KeyType, ValueType>::~BTreeNode() {
	this->keyNumber = 0;
	this->parent = NULL;
	delete[] this->key;
	this->key = NULL;
	delete[] this->ptr;
	this->ptr = NULL;

	if (isLeaf) {
		delete[] value;
	}
}

/* BTree */
template <class KeyType, class ValueType>
class BTree {
private:
	int n = 0;//n��ʾÿ��������ٵ�key������
	int innerNodeMinPtrs = 0;
	int innerNodeMinKey = 0;
	int leafNodeMinPtrs = 0;
	int leafNodeMinKey = 0;

	BTreeNode<KeyType, ValueType> * root;//����㡣

public:

	BTree(int n);

	~BTree();

	//�ͷ�p��ָ�����Լ����ӽ�㡣
	void freeNode(BTreeNode<KeyType, ValueType> * p);

	//���������ֲ��ҹؼ���key��
	//	�ҵ�ʱpָ��key���ڽ��, ����key����λ��i;
	//	�Ҳ���ʱ, pָ��keyӦ�ò����Ҷ�ӽ��, ����0��
	int find(BTreeNode<KeyType, ValueType> * & p, KeyType key);

	//���������ֲ��ҹؼ���key�����ض�Ӧ��ֵ��
	//-1��ʾ�Ҳ���
	ValueType getKeyValue(KeyType key);

	//��ָ��������ֲ��ҹؼ���key��λ�á�
	//	�ҵ�--->����key����λ��i;
	//	�Ҳ���->����-1��
	int indexOf(BTreeNode<KeyType, ValueType> * p, KeyType key);

	//���һ��key��key���ջᱻ��ӵ�һ��Ҷ�ӽ�㡣
	int add(KeyType key, ValueType value);

	//��һ��ָ����Ҷ�ӽ���в���key��
	void insert2node(BTreeNode<KeyType, ValueType> * p, KeyType key, ValueType value);

	//��һ��ָ����δ��Ҷ�ӽ���в���key��
	void insert2notFullNode(BTreeNode<KeyType, ValueType> * p, KeyType key, ValueType value);

	//��һ��ָ�����ڲ�����в���key��
	void insertToInnerNode(BTreeNode<KeyType, ValueType> * p, KeyType key, BTreeNode<KeyType, ValueType> * ptr);

	//��һ��ָ����δ���ڲ�����в���key��
	void insertToNotFullInnerNode(BTreeNode<KeyType, ValueType> * p, KeyType key, BTreeNode<KeyType, ValueType> * ptr);

	//����Ҷ�ӽ��
	BTreeNode<KeyType, ValueType> * splitNode(BTreeNode<KeyType, ValueType> * p,
		KeyType key,
		ValueType value);

	//�����ڲ����
	BTreeNode<KeyType, ValueType> * splitInnerNode(BTreeNode<KeyType, ValueType> * p,
		KeyType key,
		BTreeNode<KeyType, ValueType> * ptr);

	//ɾ��key
	bool del(int key);

	//ɾ��ָ�������ָ��λ�õ�key�����������Ҫ�������Ƚ��ֵ����¡�
	bool del_direct_index(BTreeNode<KeyType, ValueType> * p, int index);

	//ɾ��ָ���ڲ������key��
	bool del_inner_direct_index(BTreeNode<KeyType, ValueType> * p, int index);

	//ɾ���ڲ�����ָ��key��
	bool del_inner_node(BTreeNode<KeyType, ValueType> * p, int key);

	//��ָ��������ֲ��ҹؼ���key��λ�á�
	//	����p���丸����λ��i;
	//	��p�޸��ף�����-1.
	int indexInParent(BTreeNode<KeyType, ValueType> * p);

	//�ݹ��滻oldKeyΪnewKey(ֱ���ҵ������滻����������ߵ�����㶼û�ҵ�Ҳ����)��
	void replace(BTreeNode<KeyType, ValueType> * p, KeyType oldKey, KeyType newKey);

	//�������ĵ�һ��Ҷ�ӽ�㡣
	BTreeNode<KeyType, ValueType> * firstLeafNode();

	//��ӡB��(�������)
	void print();

	//��ӡҶ�ӽ�㡣
	void printAllLeaf();

	//��ӡһ������key
	void printNode(BTreeNode<KeyType, ValueType> * pNode);

};

/**
@desc:���캯����n��ʾÿ���������key��������
*/
template <class KeyType, class ValueType>
BTree<KeyType, ValueType>::BTree(int n) {
	this->n = n;
	this->innerNodeMinPtrs = ceil((1.0 + n) / 2.0);
	this->innerNodeMinKey = innerNodeMinPtrs - 1;
	this->leafNodeMinPtrs = floor((1.0 + n) / 2.0);
	this->leafNodeMinKey = leafNodeMinPtrs;
	root = new BTreeNode<KeyType, ValueType>(n, true);


	//�������롣
	fstream fs;
	fs.open("index", ios::in | ios::binary);
	KeyType key;
	int pos;
	if (fs) {
		while (!fs.eof()) {
			key = -1;
			pos = -1;
			fs.read((char*)(&key), sizeof(KeyType));
			if (fs.eof())
				break;
			fs.read((char*)(&pos), sizeof(int));
			if (key != -1 && pos != -1) {
				this->add(key, pos);
			}
		}
	}

}

/**
@desc:�����������ͷ��������Ľ��ռ䡣
*/
template <class KeyType, class ValueType>
BTree<KeyType, ValueType>::~BTree() {

	//����д���ļ���
	fstream fs("index", ios::out | ios::binary);
	KeyType key;
	BTreeNode<KeyType, ValueType> * p = this->firstLeafNode();
	while (p) {
		//����p
		for (int i = 1; i <= p->keyNumber; i++) {
			fs.write((char*)(&(p->key[i])), sizeof(KeyType));
			fs.write((char*)(&(p->value[i])), sizeof(ValueType));
		}
		p = (BTreeNode<KeyType, ValueType> *)(p->ptr[0]);
	}
	fs.flush();
	fs.close();

	n = 0;
	freeNode(root);
	root = NULL;
}

/**
@desc:�ͷ�p��ָ�����Լ����ӽ�㡣
*/
template <class KeyType, class ValueType>
void BTree<KeyType, ValueType>::freeNode(BTreeNode<KeyType, ValueType> * p) {
	//Ҷ�ӽ��ֱ���ͷŲ��ҷ��ء�
	if (p->isLeaf) {
		delete p;
		return;
	}
	//��Ҷ�ӽ�㣬����ѭ���ͷ�p��ָ�������������
	//ע�⣺key�Ǵ��±�1->keyNumnber
	//ptr�Ǵ��±�0->keyNumnber
	//ptr���key��һ��
	for (int i = 0; i <= p->keyNumber; i++) {
		freeNode((BTreeNode<KeyType, ValueType> *)(p->ptr[i]));
	}
	//�ͷ�p���
	delete p;
}

/*
@desc:���������ֲ��ҹؼ���key��
@return:
�ҵ�ʱpָ��key���ڽ��,����key����λ��i;
�Ҳ���ʱ,pָ��keyӦ�ò����Ҷ�ӽ��,����0��
*/
template <class KeyType, class ValueType>
int BTree<KeyType, ValueType>::find(BTreeNode<KeyType, ValueType> * & p, KeyType key)
{
	p = this->root;
	while (p) {
		int i = p->keyNumber;
		while (i > 0 && key < p->key[i]) {
			i--;
		}
		/*
		Ҷ�ӽ��:
		//i==0 ==> key<p->key[1],����i(0) ==> û�ҵ�
		//i!=0 ==> key>=p->key[i],����i(��0,������λ��)
		//     ==> key==p->key[i]���ҵ�,����û�ҵ���
		*/
		if (p->isLeaf) {
			if (i > 0 && key == p->key[i]) {
				return i;//�ҵ�
			}
			return 0;//�Ҳ���
		}
		else {
			p = (BTreeNode<KeyType, ValueType> *)(p->ptr[i]);//�������Ҷ�ӽ��,�������Ѱ������
		}
	}//p==NULL�������ǲ��������������,ֻ���쳣�����
	return -1;//�쳣���
}

//���������ֲ��ҹؼ���key�����ض�Ӧ��ֵ��
//-1��ʾ�Ҳ���
template <class KeyType, class ValueType>
ValueType BTree<KeyType, ValueType>::getKeyValue(KeyType key) {
	BTreeNode<KeyType, ValueType> * pNode;
	int ret = this->find(pNode, key);
	if (ret > 0)
		return pNode->value[ret];
	else
		return -1;
}

/*
@desc:���key���������С�
@return:
-1,����key���̷����쳣��
0,����key�Ѿ������ˡ�
1,����ɹ���
*/

//��ָ��������ֲ��ҹؼ���key��λ�á�
//	�ҵ�--->����key����λ��i;
//	�Ҳ���->����-1��
template <class KeyType, class ValueType>
int BTree<KeyType, ValueType>::indexOf(BTreeNode<KeyType, ValueType> * p, KeyType key) {
	int i = p->keyNumber;
	while (i > 0 && key != p->key[i]) {
		i--;
	}
	if (i == 0) {
		//not found
		return -1;
	}
	else {
		return i;
	}
}

template <class KeyType, class ValueType>
int BTree<KeyType, ValueType>::add(KeyType key, ValueType value)
{
	BTreeNode<KeyType, ValueType> * p = NULL;//����һ�����ָ�����ڲ�ѯkey��ʱ��洢���ؽ��ָ�롣
	int ret = this->find(p, key);
	if (ret == -1 || p == NULL) {
		return -1;//�쳣���
	}
	if (ret != 0) {
		return 0;//���������ҵ���key,�����в���,����0��
	}
	insert2node(p, key, value);
	return 1;
}

/*
@desc:����Ҷ�ӽ��p�����ط��Ѻ��ұ��Ǹ���㡣
*/
template <class KeyType, class ValueType>
BTreeNode<KeyType, ValueType> * BTree<KeyType, ValueType>::splitNode(BTreeNode<KeyType, ValueType> * p, KeyType key, ValueType value) {
	BTreeNode<KeyType, ValueType> * r = new BTreeNode<KeyType, ValueType>(n, true);
	r->isLeaf = p->isLeaf;
	r->parent = p->parent;

	//1,2,3,...,leafNodeMinKey(leafMinKey��key������)
	//leafNodeMinKey+1,leafNodeMinKey+2m....(ʣ�µ����ҽ��)
	//key���ı��أ��������ߣ�����Ҫ��leafNodeMinKey��һ����ұ�

	//���keyС��leafMinKey�Ǹ�λ�õ�key�����������
	if (key < p->key[this->leafNodeMinKey]) {
		//��leafMinKeyλ�ÿ�ʼ��r����и���
		int j = 1;
		for (int i = this->leafNodeMinKey; i <= p->keyNumber; i++, j++) {
			r->key[j] = p->key[i];
			r->value[j] = p->value[i];
			//r->ptr[j] = p->ptr[i];
			//p->ptr[i] = NULL;
		}
		//����߽���в���key,��Ҫ����λ��֮���key��ptr���к��ơ�
		int i = -1;
		for (i = this->leafNodeMinKey - 1; i > 0; i--) {
			if (key < p->key[i]) {
				p->key[i + 1] = p->key[i];
				p->value[i + 1] = p->value[i];
				//p->ptr[i + 1] = p->ptr[i];
			}
			else {
				//��ʱkeyҪ�����λ�þ���i+1��
				break;
			}
		}
		//����key
		p->key[i + 1] = key;
		p->value[i + 1] = value;
		p->keyNumber = this->leafNodeMinKey;
		//ȷ���ұ߽���key����
		r->keyNumber = this->n + 1 - p->keyNumber;
	}
	else {
		//��leafMinKey+1λ�ÿ�ʼ��r����и���(���ƹ�����˳�����key)
		int j = 1;
		int flag = 0;
		for (int i = this->leafNodeMinKey + 1; i <= p->keyNumber; i++) {
			if (p->key[i] > key) {
				//����key
				r->key[j] = key;
				r->value[j] = value;
				j++;
				flag = 1;
			}
			r->key[j] = p->key[i];
			r->value[j] = p->value[i];
			//r->ptr[j] = p->ptr[i];
			//p->ptr[i] = NULL;
			j++;
		}
		if (!flag) {
			//û�в���key��˵��key�����ģ����Լ�������key����
			r->key[j] = key;
			r->value[j] = value;
		}
		//ȷ����߽���key����
		p->keyNumber = this->leafNodeMinKey;
		//ȷ���ұ߽���key����
		r->keyNumber = this->n + 1 - p->keyNumber;
	}
	//ͨ����0��ָ��ָ����һ��Ҷ�ӽ��
	if (p->isLeaf) {
		r->ptr[0] = p->ptr[0];
		p->ptr[0] = r;
	}

	return r;
}

/*
@desc:�����ڲ����p�����ط��Ѻ��ұ��Ǹ���㡣
@return�����ط��ѳ������ұ߽�㣬���ң��ұ߽���0��λ��key����Ҫ���뵽������еġ�
*/
template <class KeyType, class ValueType>
BTreeNode<KeyType, ValueType> * BTree<KeyType, ValueType>::splitInnerNode(BTreeNode<KeyType, ValueType> * p, KeyType key, BTreeNode<KeyType, ValueType> * ptr) {
	BTreeNode<KeyType, ValueType> * r = new BTreeNode<KeyType, ValueType>(n, true);
	r->isLeaf = p->isLeaf;
	r->parent = p->parent;

	//1,2,3,...,leafNodeMinKey(leafMinKey��key������)
	//leafNodeMinKey+1,leafNodeMinKey+2m....(ʣ�µ����ҽ��)
	//key���ı��أ��������ߣ�����Ҫ��leafNodeMinKey��һ����ұ�

	//--->���Ҳ�ͬ��Ҷ�ӽ����ѵ��ǣ��ұ߽��ĵ�һ��key���洢������Ҫ��Ϊp��parent��key�����ȥ��

	//���keyС��leafMinKey�Ǹ�λ�õ�key�����������
	if (key < p->key[this->leafNodeMinKey]) {
		//��leafMinKeyλ�ÿ�ʼ��r����и���
		/*	ע��˴�j����Ϊ0
		@1�����ȣ�leafNodeMinKeyλ�õ�key�ǲ���Ҫ�ŵ��ҽ��ģ����Է����ҽ��0λ��Ҳ�޷���0λ�����ã�
		@2����Σ��ҽ���ptr[0]λ����Ҫ���õ���׼�����뵽������е�key��Ӧ���Ǹ�ptr�������������Ҳ���þ���leafNodeMinKeyλ�á�
		*/
		int j = 0;
		for (int i = this->leafNodeMinKey; i <= p->keyNumber; i++, j++) {
			r->key[j] = p->key[i];
			r->ptr[j] = p->ptr[i];
			((BTreeNode<KeyType, ValueType> *)(r->ptr[j]))->parent = r;//���¸����
			p->ptr[i] = NULL;
		}
		//����߽���в���key,��Ҫ����λ��֮���key��ptr���к��ơ�
		int i = -1;
		for (i = this->leafNodeMinKey - 1; i > 0; i--) {
			if (key < p->key[i]) {
				p->key[i + 1] = p->key[i];
				p->ptr[i + 1] = p->ptr[i];
			}
			else {
				//��ʱkeyҪ�����λ�þ���i+1��
				break;
			}
		}
		//����key
		p->key[i + 1] = key;
		p->ptr[i + 1] = ptr;
		ptr->parent = p;//���¸����
		p->keyNumber = this->leafNodeMinKey;
		//ȷ���ұ߽���key����(���Ҷ�ӽ����Ѷ��ȥ1)
		r->keyNumber = this->n + 1 - p->keyNumber - 1;
	}
	else {
		//��leafMinKey+1λ�ÿ�ʼ��r����и���(���ƹ�����˳�����key)
		int j = 0;
		int flag = 0;
		for (int i = this->leafNodeMinKey + 1; i <= p->keyNumber; i++) {
			if (p->key[i] > key) {
				//����key
				r->key[j] = key;
				r->ptr[j] = ptr;
				ptr->parent = r;
				j++;
				flag = 1;
			}
			r->key[j] = p->key[i];
			r->ptr[j] = p->ptr[i];
			((BTreeNode<KeyType, ValueType> *)(r->ptr[j]))->parent = r;//���¸����
			p->ptr[i] = NULL;
			j++;
		}
		if (!flag) {
			//û�в���key��˵��key�����ģ����Լ�������key����
			r->key[j] = key;
			r->ptr[j] = ptr;
			ptr->parent = r;
		}
		//ȷ����߽���key����
		p->keyNumber = this->leafNodeMinKey;
		//ȷ���ұ߽���key����(���Ҷ�ӽ����Ѷ��ȥ1)
		r->keyNumber = this->n + 1 - p->keyNumber - 1;
	}
	return r;
}

//��һ��ָ���Ľ���в���key��
template <class KeyType, class ValueType>
void BTree<KeyType, ValueType>::insert2node(BTreeNode<KeyType, ValueType> * p, KeyType key, ValueType value) {
	//������δ��
	if (p->keyNumber < n) {
		this->insert2notFullNode(p, key, value);
	}
	else {
		//������ˣ�����p��㡣
		BTreeNode<KeyType, ValueType> * r = this->splitNode(p, key, value);
		//�򸸽�����key
		if (p->parent) {
			//���ѵĲ��Ǹ����
			this->insertToInnerNode(p->parent, r->key[1], r);
		}
		else {
			//���ѵ��Ǹ����
			BTreeNode<KeyType, ValueType> * newRoot = new BTreeNode<KeyType, ValueType>(this->n, false);
			newRoot->keyNumber = 1;
			newRoot->key[1] = r->key[1];
			newRoot->ptr[0] = p;
			newRoot->ptr[1] = r;
			p->parent = newRoot;//���¸���
			r->parent = newRoot;//���¸���
			this->root = newRoot;
		}
	}
}

//��һ��ָ����δ������в���key
template <class KeyType, class ValueType>
void BTree<KeyType, ValueType>::insert2notFullNode(BTreeNode<KeyType, ValueType> * p, KeyType key, ValueType value) {
	//���Ƚ�Ҫ����λ��֮���key��ptr���к��ơ�
	int i = -1;
	for (i = p->keyNumber; i > 0; i--) {
		if (key < p->key[i]) {
			p->key[i + 1] = p->key[i];
			p->value[i + 1] = p->value[i];
			//p->ptr[i + 1] = p->ptr[i];
		}
		else {
			//��ʱkey>p->key[i](���ڵ����������,���ڼ��Ѿ�����key,����ִ�е��⡣)
			//��ʱkeyҪ�����λ�þ���i+1��
			break;
		}
	}
	//����key
	p->key[i + 1] = key;
	p->value[i + 1] = value;
	p->keyNumber++;
}

/**
@desc:��һ��ָ�����ڲ�����в���key��
*/
template <class KeyType, class ValueType>
void BTree<KeyType, ValueType>::insertToInnerNode(BTreeNode<KeyType, ValueType> * p, KeyType key, BTreeNode<KeyType, ValueType> * ptr) {
	//������ڲ����δ��
	if (p->keyNumber < n) {
		this->insertToNotFullInnerNode(p, key, ptr);
	}
	else {
		//������ˣ�����p��㡣
		BTreeNode<KeyType, ValueType> * r = this->splitInnerNode(p, key, ptr);
		//�򸸽�����key
		if (p->parent) {
			//���ѵĲ��Ǹ����
			this->insertToInnerNode(p->parent, r->key[0], r);
		}
		else {
			//���ѵ��Ǹ����
			BTreeNode<KeyType, ValueType> * newRoot = new BTreeNode<KeyType, ValueType>(this->n, false);
			newRoot->keyNumber = 1;
			newRoot->key[1] = r->key[0];
			newRoot->ptr[0] = p;
			newRoot->ptr[1] = r;
			p->parent = newRoot;//���¸���
			r->parent = newRoot;//���¸���
			this->root = newRoot;
		}

	}
}

/**
@desc:��һ��ָ����δ���ڲ�����в���key��
*/
template <class KeyType, class ValueType>
void BTree<KeyType, ValueType>::insertToNotFullInnerNode(BTreeNode<KeyType, ValueType> * p, KeyType key, BTreeNode<KeyType, ValueType> * ptr) {
	//���Ƚ�Ҫ����λ��֮���key��ptr���к��ơ�
	int i = -1;
	for (i = p->keyNumber; i > 0; i--) {
		if (key < p->key[i]) {
			p->key[i + 1] = p->key[i];
			p->ptr[i + 1] = p->ptr[i];
		}
		else {
			//��ʱkey>p->key[i](���ڵ����������,���ڼ��Ѿ�����key,����ִ�е��⡣)
			//��ʱkeyҪ�����λ�þ���i+1��
			break;
		}
	}
	//����key
	p->key[i + 1] = key;
	p->ptr[i + 1] = ptr;
	p->keyNumber++;
}

/*
@desc:ɾ���������е�key��
@return:����Ҳ���Ҫɾ����key������false��
����ɾ��key�����ҷ���true��
*/
template <class KeyType, class ValueType>
bool BTree<KeyType, ValueType>::del(int key)
{
	BTreeNode<KeyType, ValueType> * p = NULL;//����һ�����ָ�����ڲ�ѯkey��ʱ��洢���ؽ��ָ�롣
	int ret = this->find(p, key);
	if (ret == -1 || p == NULL) {
		return false;//�쳣���
	}
	if (!ret) {
		//can not find
		return false;
	}
	//���ɾ��֮���㻹������������(����������ֻ��һ�������Ҷ�ӵ����Ҳ����ֱ��ɾ����)
	if (p->keyNumber >= this->leafNodeMinKey + 1 || p->parent == NULL) {
		return this->del_direct_index(p, ret);
	}
	else if (p->keyNumber == this->leafNodeMinKey) {
		//���ɾ��֮���㲻������������
		BTreeNode<KeyType, ValueType> * pp = p->parent;//�����
		BTreeNode<KeyType, ValueType> * left_partner = NULL;//ָ������������
		BTreeNode<KeyType, ValueType> * right_partner = NULL;//
		//��ͼ���ұ߽�(���ұ߽跽���ң���Ϊ���Ը���p->ptr[0]�ҵ��ұ߽��)
		right_partner = (BTreeNode<KeyType, ValueType>*)(p->ptr[0]);
		//�ж��Ƿ�������ֵܣ�����right_partner�Ƿ��������ֵܡ�
		if (right_partner && pp == right_partner->parent) {
			//�����ֵܣ��衣(ע�⣬��������ֵܣ���ôright_partner->key[0] == pp->key[��Ӧ���Ǹ�key]����Ϊright_partner���ұߣ���Ȼ������ĳ�������ĵ�һ����㣬ֻ�е�һ�������п��ܳ���[��һ��key�ڸ����в����ڵ����]��)
			//������ֵ�key��������key������衣
			if (right_partner->keyNumber >= this->leafNodeMinKey + 1) {
				//�ҵ�������ж�Ӧ��right_partner->key[1]��λ�á�
				int pos = this->indexOf(pp, right_partner->key[1]);
				//ɾ��������е�key
				this->del_direct_index(p, ret);
				//�򱾽������Ӵ�right_partner�н������key��
				p->keyNumber++;
				p->key[p->keyNumber] = right_partner->key[1];
				p->value[p->keyNumber] = right_partner->value[1];
				//p->ptr[p->keyNumber] = right_partner->ptr[1];
				//ɾ��right_partner�б����ߵ�key(������̲����ܷ��ѣ���Ȼ�����裬��������������������ȥ��Ҳ�����ٺϲ�)
				del_direct_index(right_partner, 1);
				//���ˣ�����ɾ������������ֱ���˳���
				return true;
			}
			//else {//�˴���ʾ�������ֵܵ���û���㹻����key���²��ܽ裬Ԥ���������Ҫ��߿�����Ҫ���ϲ���}
		}
		else {
			//���right_partner!=NULL����û��ȥ��һ��if��˵��((right_partner && pp == right_partner->parent))���������������ֵܵ��������ֵܡ�
			//���right_partner==NULL��û�����ֵܡ�
			//��֮������else����û�������ֵ� --> ��Ȼ�������ֵܡ�

			//û�������ֵܵ����ֵܣ�û�ã���������ΪNULL��
			right_partner = NULL;
		}

		//����ֻ������ͼȥ�����ֵ�(ͨ���жϸ�������Ƿ���p->key[1]����֪���Ƿ������ֵ�)��
		//��Ϊ��һ��������ֻ�е�һ�������������ֵܣ�Ҳֻ�е�һ�����ӵ�key[1]���ڸ�����С�(ע����仰ֻ��Ҷ�ӽ���г���)

		//ѽѽѽѽѽѽѽ���޵�--->>>�ش�������˺þã�����˴��Ĳ��ҽ�����Ϊ��ȷ���Ƿ��ǵ�һ�����ӣ�������find���ǵݹ�p�������Ƿ����ָ��key����ʵ�������pp�������p�ĸ��ף���Ȼ���ҵ����˴���Զ���ҵ��������߼��ϴ�����Ȼ��һ�Ѷ����ˡ�
		//int splitKey = this->find(pp, p->key[1]);
		int splitKey = this->indexOf(pp, p->key[1]);
		if (splitKey != -1) {
			//�������0��˵�����ҵ����˴�����Ҫ�ж��Ƿ������ֵܣ��϶����׵ġ�
			//splitKeyλ��ָ��Ϊp��splitKey-1λ��ָ�뼴Ϊ���ֵܡ�
			//������Ҫ�жϸ��ֵ��Ƿ����㹻��key�ܹ��衣
			left_partner = (BTreeNode<KeyType, ValueType> *)(pp->ptr[splitKey - 1]);
			if (left_partner->keyNumber >= this->leafNodeMinKey + 1) {
				//���Խ衣
				//��ɾ��p����retλ��key(ֱ��ɾ��������Ҳ���ϲ�)��
				this->del_direct_index(p, ret);
				//���¸������ p->key[1] --> left_partner->key[left_partner->keyNumber]
				this->replace(pp, p->key[1], left_partner->key[left_partner->keyNumber]);
				//Ȼ������ֵ��н�һ��������
				this->insert2notFullNode(p, left_partner->key[left_partner->keyNumber], left_partner->value[left_partner->keyNumber]);
				left_partner->keyNumber--;
				//���ˣ�����ɾ���ֽ����ˡ�
				return true;
			}//else {//�˴���ʾ�������ֵܵ���û���㹻����key���²��ܽ裬Ԥ���������Ҫ��߿�����Ҫ���ϲ���}
		}
		else {
			//p�Ǹ��׵ĵ�һ�����ӣ�Ҳ����û�������ֵܡ�
			left_partner = NULL;
		}

		//����������˵�������ֵܶ�û�ܳɹ��赽��
		//����ע�⣬�����������ֵܶ������ڣ����һ�������ڣ���һ�������衣
		//���Ժϲ����ɡ�
		if (!left_partner && !right_partner) {
			//�쳣��������������ֵܶ�û�С�
			cout << "�쳣���Ҿ�Ȼһ�����ֵܶ�û�У�" << endl;
			return false;
		}

		//��һ�����ֵ�
		//��ʼɾ���Լ��ϲ�
		if (left_partner) {
			//cout<< "�ϲ����ֵܽ��" <<endl;
			//�ϲ����ֵ�
			//�������ɾ��ָ��key��ʣ���keyȫ�����Ƶ������С�
			//�������key������������key�������Կ���˳���ƹ�ȥ��
			//ɾ����ֱ��ɾ����
			this->del_direct_index(p, ret);
			//���Ʊ������key����߽���С�
			int j = left_partner->keyNumber + 1;
			for (int i = 1; i <= p->keyNumber; i++, j++) {
				left_partner->key[j] = p->key[i];
				left_partner->value[j] = p->value[i];
				//left_partner->ptr[j] = p->ptr[i];
			}
			//���������key��������
			left_partner->keyNumber += p->keyNumber;
			//����Ҷ�ӽ��ֱ�ӵ����ӡ�
			left_partner->ptr[0] = p->ptr[0];
			//ɾ��������е�key=p->key[1]���Ǹ�key��
			this->del_inner_node(pp, p->key[1]);
			//�ͷ�p���ռ�
			delete p;
			return true;
		}
		else {
			//�ϲ����ֵ�
			//cout << "�ϲ����ֵܽ��" << endl;
			//�����ֵܽ��ȫ��key���Ƶ���ǰ����С�
			//���ֵܽ����key�ȵ�ǰ���������key�������Կ���˳���ơ�

			//ɾ����ֱ��ɾ����
			this->del_direct_index(p, ret);

			//�������ֵܽ����key����ǰ�߽���С�
			int j = p->keyNumber + 1;
			for (int i = 1; i <= right_partner->keyNumber; i++, j++) {
				p->key[j] = right_partner->key[i];
				p->value[j] = right_partner->value[i];
				//p->ptr[j] = right_partner->ptr[i];
			}
			//���µ�ǰ����key��������
			p->keyNumber += right_partner->keyNumber;
			//����Ҷ�ӽ��ֱ�ӵ����ӡ�
			p->ptr[0] = right_partner->ptr[0];

			//ɾ��������е�key=right_partner->key[1]���Ǹ�key��
			this->del_inner_node(pp, right_partner->key[1]);

			//�ͷ�p���ռ�
			delete right_partner;

			return true;
		}
	}
	else {
		cout << "invalid keyNumber: " << p->keyNumber << endl;;
		return false;
	}
}

//ɾ���ڲ�����ָ��key
template <class KeyType, class ValueType>
bool BTree<KeyType, ValueType>::del_inner_node(BTreeNode<KeyType, ValueType> * p, int key) {
	int ret = this->indexOf(p, key);
	if (ret == -1) {
		//û�ҵ�
		return false;
	}
	else {
		//�ҵ�
		if (p->keyNumber >= this->innerNodeMinKey + 1) {
			//����ֱ��ɾ��
			this->del_inner_direct_index(p, ret);
			return true;
		}

		//��ǰ����Ǹ����������
		if (p->parent == NULL) {
			if (p->keyNumber > 1) {
				//����һ�����Ͻ��
				//ֱ��ɾ�����ɡ�
				this->del_inner_direct_index(p, ret);
				return true;
			}
			else {
				//ֻʣ��һ�������
				//���������Ҫɾ������㼴�ɣ���Ψһ��һ��������Ϊ�µĸ���㡣
				BTreeNode<KeyType, ValueType> * newRoot = (BTreeNode<KeyType, ValueType> *)(p->ptr[0]);
				newRoot->parent = NULL;//����µĸ�����parent
				delete this->root;
				this->root = newRoot;
				return true;
			}
		}
		//ɾ��֮���������᲻��(��Ҫ����ߺϲ�)
		//�Ǹ����
		BTreeNode<KeyType, ValueType> * pp = p->parent;
		BTreeNode<KeyType, ValueType> * left_partner = NULL;
		BTreeNode<KeyType, ValueType> * right_partner = NULL;
		//���Ȼ�õ�ǰ����ڸ�����е�λ��
		int pos = this->indexInParent(p);
		//cout << "��ǰ����ڸ������λ��Ϊ pos = "<<pos << endl;
		//ע��pos������-1����Ϊ�ϱ��Ѿ���pΪ�����������������ˡ�
		if (pos > 0) {
			//pos!=0 ��������ֵ�
			//�õ����ֵ�ָ��
			left_partner = (BTreeNode<KeyType, ValueType> *)(pp->ptr[pos - 1]);
			if (left_partner->keyNumber >= this->innerNodeMinKey + 1) {
				//����ֵܹ���
				//��ֱ��ɾ��
				this->del_inner_direct_index(p, ret);
				/*	��
				@1:��p�ĸ�����ж�Ӧ��key��Ϊp����һ��key����
				@2:�����ֵܵ����key�滻�������p��Ӧ���Ǹ�key��
				@3:�����ֵܵ�����ptr��Ϊp��������ߵ�ptr���롣
				*/
				//����Ӹ����p��Ӧ��key�� ���ֵܵ����key��Ӧ��ptr��p��
				//�����p��Ӧ�� key = pp->key[pos] ; ���ֵܵ����key = left_partner->key[left_partner->keyNumber] ;���� ptr = left_partner->ptr[left_partner->keyNumber]��
				//@1��������������������ƶ�
				int i = p->keyNumber;
				while (i >= 0) {
					p->key[i + 1] = p->key[i];
					p->ptr[i + 1] = p->ptr[i];
					i--;
				}
				//���
				p->key[1] = pp->key[pos];
				//����p����key����
				p->keyNumber++;

				//@2:�����ֵܵ����key�滻�������p��Ӧ���Ǹ�key��
				pp->key[pos] = left_partner->key[left_partner->keyNumber];

				//@3:�����ֵܵ�����ptr��Ϊp��������ߵ�ptr���롣
				p->ptr[0] = left_partner->ptr[left_partner->keyNumber];
				((BTreeNode<KeyType, ValueType> *)(left_partner->ptr[left_partner->keyNumber]))->parent = p;//ά���µĸ��׹�ϵ

																								 //�������ֵܽ���key����
				left_partner->keyNumber--;

				//�����۲죬���׹�ϵ�Լ����£�Ҷ�ӽ���˳������Ҫ�ܣ���Ϊû��Ӱ�쵽����ͼ��ֱ���ܿ���������

				//����
				return true;
			}
			//else {//���ֵܲ�����}
		}
		else {
			//pos = 0����p�ǵ�һ�����ӣ�û�����ֵܡ�
			left_partner = NULL;
		}
		//�ж��Ƿ������ֵ�
		if (pos < pp->keyNumber) {
			//pos < pp->keyNumber �����ұ��ֵ�
			//�õ����ֵ�ָ��
			right_partner = (BTreeNode<KeyType, ValueType> *)(pp->ptr[pos + 1]);
			if (right_partner->keyNumber >= this->innerNodeMinKey + 1) {
				//���ֵ�key����������
				//��ֱ��ɾ��
				this->del_inner_direct_index(p, ret);
				/*	��
				@1:��p�ĸ�����ж�Ӧ��key�ұ�һ��key��Ϊp����һ��key����
				@2:�����ֵܵ���Сkey�滻�������p��Ӧ���Ǹ�key���ұߵ�key��
				@3:�����ֵܵ�����ptr��Ϊp�������ұߵ�ptr���롣
				*/
				//����Ӹ����p��Ӧ��key�ұߵ�key �� ���ֵ�������ߵ�ptr��p�����ұߡ�
				//�����p��Ӧ�� key���ұ�key = pp->key[pos+1] ; ���ֵܵ���С key = right_partner->key[1] ;���� ptr = right_partner->ptr[0]��
				//@1���
				//����p����key����
				p->keyNumber++;
				//keyNumber�Ѿ�����1������keyNumberλ���Ѿ������ұ�λ�á�
				p->key[p->keyNumber] = pp->key[pos + 1];

				//@2:�����ֵܵ���Сkey�滻�������p��Ӧ���Ǹ�key��
				pp->key[pos + 1] = right_partner->key[1];

				//@3:�����ֵܵ�����ptr��Ϊp�������ұߵ�ptr���롣
				p->ptr[p->keyNumber] = right_partner->ptr[0];

				((BTreeNode<KeyType, ValueType> *)(right_partner->ptr[0]))->parent = p;//ά���µĸ��׹�ϵ

																			//�����ֵܽ���ʣ������key��ptr���ƣ���Ϊ��С��һ���Ѿ�û�ˣ�
																			//ע����Ȼ��һ�����key����Ҫ���ƣ����ǻ��Ǵ�i=1��ʼ����Ϊ��������˳���ptr[0]����
				for (int i = 1; i <= right_partner->keyNumber; i++) {
					right_partner->key[i - 1] = right_partner->key[i];
					right_partner->ptr[i - 1] = right_partner->ptr[i];
				}
				//�������ֵܽ���key����
				right_partner->keyNumber--;

				//�����۲죬���׹�ϵ�Լ����£�Ҷ�ӽ���˳������Ҫ�ܣ���Ϊû��Ӱ�쵽����ͼ��ֱ���ܿ���������

				//����
				return true;
			}
			//else {//���ֵܲ�����}
		}
		else {
			//pos = pp->keyNumber����p�����һ�����ӣ�û�����ֵܡ�
			right_partner = NULL;
		}

		//��һ�����ֵ�
		//��ʼɾ���Լ��ϲ�
		if (left_partner) {
			//cout<< "�ϲ����ֵܽ��" <<endl;
			//�ϲ����ֵ�
			//�������ɾ��ָ��key��ʣ���keyȫ�����Ƶ������С�
			//�������key������������key�������Կ���˳���ƹ�ȥ��

			//ɾ����ֱ��ɾ����
			this->del_inner_direct_index(p, ret);

			//���Ʊ������key/ptr����߽���С�
			//�Ƚ�������Ӧ����������Ǹ����Էŵ������ĵ�0��λ�ã��������Ƶ�ʱ�����ͳһ�㣨����������Ǹ�key����Ҫ���ȷŵ����ֵ������ұߣ����������Ƿű�����ʣ��key�ģ���
			p->key[0] = pp->key[pos];
			int j = left_partner->keyNumber + 1;
			for (int i = 0; i <= p->keyNumber; i++, j++) {
				left_partner->key[j] = p->key[i];
				left_partner->ptr[j] = p->ptr[i];
				((BTreeNode<KeyType, ValueType> *)(left_partner->ptr[j]))->parent = left_partner;//���¸��׹�ϵ
			}
			//���������key������(ע�⻹��һ��0��λ�ã�������Ҫ��1��0��λ��ʵ���ǴӸ������������)��
			left_partner->keyNumber += (p->keyNumber + 1);

			//ɾ��������е�key=p->key[0]���Ǹ�key��Ҳ����˵�� pp->key[pos]��
			this->del_inner_node(pp, pp->key[pos]);

			//�ͷ�p���ռ�
			delete p;

			return true;
		}
		else {
			//�ϲ����ֵ�
			//cout << "�ϲ����ֵܽ��" << endl;
			//�����ֵܽ��ȫ��key���Ƶ���ǰ����С�
			//���ֵܽ����key�ȵ�ǰ���������key�������Կ���˳���ơ�

			//ɾ����ֱ��ɾ����
			this->del_inner_direct_index(p, ret);

			//�������ֵܽ����key����ǰ�߽����(�����������һ��)��
			right_partner->key[0] = pp->key[pos + 1];
			int j = p->keyNumber + 1;
			for (int i = 0; i <= right_partner->keyNumber; i++, j++) {
				p->key[j] = right_partner->key[i];
				p->ptr[j] = right_partner->ptr[i];
				((BTreeNode<KeyType, ValueType> *)(p->ptr[j]))->parent = p;
			}
			//���µ�ǰ����key��������
			p->keyNumber += (right_partner->keyNumber + 1);

			//ɾ��������е�key=right_partner->key[0]���Ǹ�key��Ҳ����˵�� pp->key[pos+1]��
			this->del_inner_node(pp, pp->key[pos + 1]);

			//�ͷ�p���ռ�
			delete right_partner;

			return true;
		}

	}
}

//��ָ��������ֲ��ҹؼ���key��λ�á�
//	����p���丸����λ��i;
//	��p�޸��ף�����-1.
template <class KeyType, class ValueType>
int BTree<KeyType, ValueType>::indexInParent(BTreeNode<KeyType, ValueType> * p) {
	if (p->parent == NULL)
		return -1;
	BTreeNode<KeyType, ValueType> * pp = p->parent;

	int i = pp->keyNumber;
	while (i > 0 && p->key[1] < pp->key[i]) {
		i--;
	}
	//i==0Ҳ�ԣ�i==0������ߺ��ӵ������
	return i;
}



/*
@desc:	ɾ��ָ������е�ָ��index��key��
@return:	ɾ���ɹ�����true��
���򷵻�false��
*/
template <class KeyType, class ValueType>
bool BTree<KeyType, ValueType>::del_direct_index(BTreeNode<KeyType, ValueType> * p, int index) {
	int delKey = p->key[index];
	//����ҵ��ˣ���p��ָ��ļ�Ϊkey���ڽ�㣬ret����key����λ�á�
	//ѭ����[ret+1 --> keyNumber]λ�õ�key��valueǰ�ơ�
	for (int i = index + 1; i <= p->keyNumber; i++) {
		p->key[i - 1] = p->key[i];
		p->value[i - 1] = p->value[i];
		//p->ptr[i - 1] = p->ptr[i];
	}
	p->keyNumber--;
	//���ɾ�����ǵ�һ��λ�ã����п�����Ҫ�滻�����(key-->p->ptr[ret])��
	//��Ҷ�ӽ�㲻�������Ҫ���¸��������(ע��˴��ж���Ϊ�˱��գ�ʵ�ʳ������ڲ���㲻������������)��
	if (p->isLeaf && index == 1) {
		this->replace(p->parent, delKey, p->key[1]);
	}
	return true;
}

/*
	@desc:	ɾ��ָ���ڲ�����е�ָ��index��key��
	@return:	ɾ���ɹ�����true��
	���򷵻�false��
*/
template <class KeyType, class ValueType>
bool BTree<KeyType, ValueType>::del_inner_direct_index(BTreeNode<KeyType, ValueType> * p, int index) {
	int delKey = p->key[index];
	//����ҵ��ˣ���p��ָ��ļ�Ϊkey���ڽ�㣬ret����key����λ�á�
	//ѭ����[ret+1 --> keyNumber]λ�õ�key��ptrǰ�ơ�
	for (int i = index + 1; i <= p->keyNumber; i++) {
		p->key[i - 1] = p->key[i];
		p->ptr[i - 1] = p->ptr[i];
	}
	p->keyNumber--;
	return true;
}

/**
@desc:��p�����ǰһֱ�����ҵ�����㣬ֱ���ҵ�oldKey�����滻ΪnewKey����ֱ��������Ҳ���Ҳ������
*/
template <class KeyType, class ValueType>
void BTree<KeyType, ValueType>::replace(BTreeNode<KeyType, ValueType> * p, KeyType oldKey, KeyType newKey) {
	int hasFind = 0;
	//�����û�ҵ� ���� û������㡣
	while (!hasFind && p) {
		//���Һ��滻
		for (int i = 1; i <= p->keyNumber; i++) {
			if (p->key[i] == oldKey) {
				p->key[i] = newKey;//�滻
				hasFind = 1;//���Ϊ�ҵ�
				break;
			}
		}
		p = p->parent;
	}

}

/**
@desc:��ӡB��(�������)
Ϊ�˿��������㣬��Ҫ��α�����
*/
template <class KeyType, class ValueType>
void BTree<KeyType, ValueType>::print() {
	if (this->root == NULL) {
		cout << "BTree is empty��" << endl;
		return;
	}

	cout << "BTree�����" << endl;
	//����һ������
	queue<BTreeNode<KeyType, ValueType> *> pnodeQueue;
	queue<int> keyNumberQueue;

	//��������
	pnodeQueue.push(this->root);

	//node��ʱ����(���ڴ�ӡBTree�Ľṹ��������ӡ��Ƚ�ֱ��)
	int nodeNumber = 0;//��¼��ǰ���������
	int nodeNumbers = 1;//��¼����������
	int newNodeNumbers = 0;//��¼��һ��������

						   //��ʼ��α���
	while (pnodeQueue.size()) {
		//��ȡ���׽�㣬���ҳ��ӡ�
		BTreeNode<KeyType, ValueType> * pNode = pnodeQueue.front();
		pnodeQueue.pop();
		if (pNode) {
			//��ӡ�ý���keys
			this->printNode(pNode);
			if (!pNode->isLeaf) {
				//���ý������к��ӽ��ָ����ӡ�
				for (int i = 0; i <= pNode->keyNumber; i++) {
					if (pNode->ptr[i])
						pnodeQueue.push((BTreeNode<KeyType, ValueType> *)(pNode->ptr[i]));
				}
				newNodeNumbers += pNode->keyNumber + 1;
			}
			nodeNumber++;
			if (nodeNumber == nodeNumbers) {
				cout << endl;
				keyNumberQueue.push(newNodeNumbers);
				newNodeNumbers = 0;
				if (!keyNumberQueue.empty()) {
					//���¼���
					nodeNumber = 0;
					nodeNumbers = keyNumberQueue.front();
					keyNumberQueue.pop();
				}
			}
		}
	}
	cout << "BTree�����ϣ�" << endl;
}

//��ӡһ������key
template <class KeyType, class ValueType>
void BTree<KeyType, ValueType>::printNode(BTreeNode<KeyType, ValueType> * pNode) {
	int isFirst = 1;
	cout << "(";
	//�����ý��
	for (int i = 1; i <= pNode->keyNumber; i++) {
		if (isFirst) {
			cout << pNode->key[i];
			isFirst = 0;
		}
		else {
			cout << ", " << pNode->key[i];
		}

	}
	cout << ") ";
}

//�������ĵ�һ��Ҷ�ӽ�㡣
template <class KeyType, class ValueType>
BTreeNode<KeyType, ValueType> * BTree<KeyType, ValueType>::firstLeafNode() {
	BTreeNode<KeyType, ValueType> * p = this->root;
	while (p && !p->isLeaf) {
		p = (BTreeNode<KeyType, ValueType> *)(p->ptr[0]);
	}
	return p;
}

template <class KeyType, class ValueType>
void BTree<KeyType, ValueType>::printAllLeaf() {
	cout << "��ӡҶ�ӽ�㣺" << endl;
	BTreeNode<KeyType, ValueType> * p = this->firstLeafNode();
	while (p) {
		cout << "(";
		//����p
		for (int i = 1; i <= p->keyNumber; i++) {
			cout << p->key[i] << "=" << p->value[i] << " ";
		}
		cout << ") ";
		p = (BTreeNode<KeyType, ValueType> *)(p->ptr[0]);
	}
	cout << endl << "��ӡҶ�ӽ�������" << endl;
}

