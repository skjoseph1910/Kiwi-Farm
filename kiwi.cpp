#include <iostream>
#include <fstream>

using namespace std;

void print(int **mat, int size) {
	for (int i = 0; i < size; i++) {
		int *p = mat[i];
		for (int j = 0; j < size; j++) {
			cout << *p;
			
			if (j != size - 1)
				cout << " ";
			++p;
		}
		cout << endl;
	}
	cout << endl;
}

void print(int **mat, int size, ofstream &ofs) {
	for (int i = 0; i < size; i++) {
		int *p = mat[i];
		for (int j = 0; j < size; j++) {
			ofs << *p;
			
			if (j != size - 1)
				ofs << " ";
			++p;
		}
		ofs << endl;
	}
	ofs << endl;
}

int *countRow(int *row, int size) {
	int nRipe = 0;
	int nRot = 0;

	int *p = row;
	for (int i = 0; i < size; i++) {
		if (*p > 8)
			++nRot;
		else if (*p >= 6)
			++nRipe;

		++p;
	}

	int arr[2] = {nRipe, nRot};
	int *res = arr;
	return res;
}

bool canHarvest(int *row, int size) {
	int *data = countRow(row, size);
	return data[0] + data[1] >= size / 2;
}

void harvest(int *row, int size) {
	int *p = row;
	for (int i = 0; i < size; i++) {
		*p = 0;
		++p;
	}
}

void age(int *row, int size) {
	int *p = row;
	for (int i = 0; i < size; i++) {
		++(*p);
		++p;
	}
}

int main(int argc, char *argv[]) {
 
	string input = "input.txt";
	string output = "output.txt";

	ifstream ifs(input);
	
	int size;
	ifs >> size;
	
	int **mat;
	mat = new int*[size];
	int x;
	for (int i = 0; i < size; i++) {
		mat[i] = new int[size];
		int *p = mat[i];

		for (int j = 0; j < size; j++) {
			ifs >> x;
		
			*p = x;
			++p;
		}
	}

	int nRipe = 0;
	int nRot = 0;
	for (int day = 0; day < 7; day++) {
		bool b[size];
		for (int i = 0; i < size; i++) {
			b[i] = canHarvest(mat[i], size);
			if (b[i]) {
				int *data = countRow(mat[i], size);			
				nRipe += data[0];
				nRot += data[1];
				harvest(mat[i], size);
			}
		}

		for (int i = 0; i < size; i++)
			if (!b[i])
				age(mat[i], size);
	}
	for (int i = 0; i < size; i++)
		if (canHarvest(mat[i], size)) {
			int *data = countRow(mat[i], size);
			nRipe += data[0];
			nRot += data[1];
	
			harvest(mat[i], size);
		}

	ofstream ofs(output);
	print(mat, size, ofs);
	ofs << "Harvested kiwis: " << nRipe << endl;
	ofs << "Rotten kiwis: " << nRot << endl;

	return 0;
}
