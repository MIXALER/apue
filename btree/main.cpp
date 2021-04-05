
#include <stdio.h>
#include <iostream>
#include "BTreeIndex.h"
#include "Record.h"

void printMenu();

//function declares
//���Ժ����ˣ���Щ���ǲ����õġ���ֱ�����г���ͺá�
void t_empty();
void t_1_to_10();
void t_btree4();
void t_del();

int main()
{
	//t_empty();
	//t_add();
	//t_1_to_10();
	//t_btree4();
	//t_del();

	DataBase<Record> db("dbFile");

	//����һ��BTree�������ݱ�
	BTreeIndex<int, Record> indexDB(3);
	//���ݼ�¼�����ڴ���������ʱ���ݡ�
	Record record;
	//���ڴ���������ʱ���ݡ�
	int key;
	//��ӡ���
	printMenu();
	//�����
	int cmd = -1;
	//�������
	while (cin >> cmd) {
		switch (cmd)
		{
			//1:�������� ��ʽ��key value��
		case 1:
			cout << "please input key and value:";
			cin >> record.key >> record.content;
			indexDB.add(record.key, record);
			break;
			//2:ɾ������ ��ʽ��key��
		case 2:
			cout << "please input key:";
			cin >> key;
			indexDB.del(key);
			break;
			//3:��ѯ���� ��ʽ��key��
		case 3:
			cout << "please input key:";
			cin >> key;
			record.key = -1;
			indexDB.find(key, record);
			if (record.key != -1) {
				cout << "Record[key=" << record.key << ",content=" << record.content << "]" << endl;
			}
			else {
				cout << "Record with key=" << key << " is not found��" << endl;
			}
			break;
			//4:��ӡB������" << endl;
		case 4:
			indexDB.getBTree()->print();
			break;
		case 5:
			indexDB.getBTree()->printAllLeaf();
			break;
		default:
			cout << "invalid cmmand!" << endl;
			break;
		}
		printMenu();
	}
	return 0;
}


//��ӡ���ܲ˵�
void printMenu() {
	cout << endl;
	cout << "1:�������� ��ʽ��key value��;" << endl;
	cout << "2:ɾ������ ��ʽ��key��;" << endl;
	cout << "3:��ѯ���� ��ʽ��key��;" << endl;
	cout << "4:��ӡB������" << endl;
	cout << "5:��ӡҶ�ӽ��" << endl;
}

void t_del() {
	BTree<int, int> btree(3);
	for (int i = 1; i <= 3; i++) {
		btree.add(10 * i, 10 * i);
		btree.printAllLeaf();
	}
	btree.add(25, 25);
	btree.printAllLeaf();
	btree.add(45, 45);
	btree.printAllLeaf();
	btree.add(61, 61);
	btree.printAllLeaf();
	btree.add(63, 63);
	btree.printAllLeaf();
	btree.add(65, 65);
	btree.printAllLeaf();

	btree.add(64, 64);
	btree.printAllLeaf();

	btree.add(62, 62);
	btree.printAllLeaf();

	btree.add(82, 82);
	btree.printAllLeaf();
	btree.add(84, 84);
	btree.printAllLeaf();
	btree.add(86, 86);
	btree.printAllLeaf();
	btree.add(88, 88);
	btree.printAllLeaf();

	btree.add(85, 85);
	cout << "ɾ��65֮ǰ-------------------------------------" << endl;
	btree.print();
	btree.printAllLeaf();
	cout << "ɾ��65֮��-------------------------------------" << endl;
	btree.del(65);
	btree.print();
	btree.printAllLeaf();

	//�ϲ�����
	//btree.del(100);
	//btree.print();
	//btree.printAllLeaf();

	//�ϲ��ҽ��
	btree.del(85);
	btree.print();
	btree.printAllLeaf();
	btree.del(80);
	btree.print();
	btree.printAllLeaf();

	//���쵼�¸����Ҳ�ϲ������


	//�ڲ����ϲ�����ͨ������ʵ�֣�����裩
	btree.del(61);
	btree.print();
	btree.printAllLeaf();

	//�ڲ����ϲ�����ͨ������ʵ�֣����ҽ裩
	btree.del(50);
	btree.print();
	btree.printAllLeaf();

	btree.del(60);
	btree.print();
	btree.printAllLeaf();

	//�ڲ����ϲ�����ͨ���ϲ�ʵ��(������ֵܺϲ�)
	//btree.del(88);
	//btree.print();
	//btree.printAllLeaf();

	//�ڲ����ϲ�����ͨ���ϲ�ʵ��(���ұ��ֵܺϲ�)
	btree.del(20);
	btree.print();
	btree.printAllLeaf();
	btree.del(25);
	btree.print();
	btree.printAllLeaf();

	btree.del(30);
	btree.print();
	btree.printAllLeaf();

	//����ɾ����֪�����ݹ�ɾ��
	btree.del(10);
	btree.print();

	btree.del(40);
	btree.print();

	btree.del(62);
	btree.print();

	btree.del(86);
	btree.print();
	btree.printAllLeaf();


	//btree.del();
	//btree.print();

	//btree.printAllLeaf();

}

void t_btree4() {
	BTree<int, int> btree(4);
	for (int i = 1; i <= 13; i++) {
		btree.add(i, i);
	}
	btree.print();
}

void t_1_to_10() {
	BTree<int, int> btree(3);
	for (int i = 1; i <= 10; i++) {
		btree.add(i, i);
	}
	btree.print();
}

void t_add() {
	BTree<int, int> btree(3);
	btree.print();

	btree.add(4, 4);
	btree.print();

	btree.add(5, 5);
	btree.print();

	btree.add(8, 8);
	btree.print();

	btree.add(7, 7);
	btree.print();

	btree.add(2, 2);
	btree.print();

	btree.add(12, 12);
	btree.print();

	btree.add(10, 10);
	btree.print();

	btree.add(6, 6);
	btree.print();

	btree.add(3, 3);
	btree.print();

	btree.add(9, 9);
	btree.print();

	btree.add(20, 20);
	btree.print();

	btree.add(30, 30);
	btree.print();

	btree.add(1, 1);
	btree.print();

	btree.add(0, 0);
	btree.print();

	btree.add(-1, -1);
	btree.print();

}

void t_empty() {
	BTree<int, int> btree(3);
	btree.print();
}
