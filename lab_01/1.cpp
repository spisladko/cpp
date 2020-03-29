#include <iostream>
#include <cmath>
#include <list>
#include <vector>
#include <fstream>
using namespace std;

double func(double n) {
	//double value = -n*log(n);
	//double value = sqrt(n);
	double value = -(pow(n,2))-0.5;
	return value;
}

vector<vector<char> > get_grid(double (*func)(double), double a, double b, int width, int height) {
	int i, j;
	double step, n = a, min = 0, max = 0;
	
	step = (b-a)/width;
	
	vector<double> values;
	for (int i = 0; i < width; i++) {
        value = func(n);
        values.push_back(value);
        n += step;
	}

	for (double value: values) {
		if (value < min) { min = value; }
		if (value > max) { max = value; }
	}
	
	double k = height/(abs(max)+abs(min));
	
	int zero;	
	if (min == 0) { zero = height; }
	else if (max == 0) { zero = -1; }
	else { zero = abs(round(max * k)); }
	
	vector<vector<char>> grid(height, vector<char>(width, ' '));
	for(int i = 0; i < height; i++) {
		for(int j = 0; j < width; j++) {
			if (i == zero)  { grid[i][j] = '-'; }
		}
	}
	
	for (i = 0; i < values.size(); i++) {
			values[i] = round(values[i]*k);
	}
	
	for (int j = 0; j < values.size(); j++) {
	
		if (values[j] > 0) {
			for (int i = (zero - 1); i >= (zero - values[j]); i--) {
				grid[i][j] = '#';
			}
			
		} else if (values[j] < 0) {
			for (int i = (zero + 1); i < (zero + abs(values[j])); i++) {
				grid[i][j] = '#';
			} 
		} else {}	
	}
	
	vector<char> axes (width, '-');
	if (min == 0) { grid.push_back(axes); }
	if (max == 0) { grid.insert(grid.begin(),axes); }

	return grid;
}

int draw_grid(vector<vector<char> > grid) {
	ofstream fout;
	fout.open("file3.txt");
	
	for (vector<char> line: grid) {
		for (char element: line) {
			fout << element;
		}
		fout << endl;
	}
	return 0;
}
 
int main() {
	int width, height, i, j;
	double a,b;
	vector<vector<char> > table;
	cout << "Количество столбиков и высота графика" << endl;
	cin >> width >> height;
	cout << "Начало и конец отрезка" << endl;
	cin >> a >> b;

	draw_grid(get_grid(func, a, b, width, height));
	
	return 0;
}

