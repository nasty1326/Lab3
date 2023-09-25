#include <cstring>
#include <ctime>
#include <iostream>
#include <cstdio >
#include <cstdlib>

using namespace std;

template <typename T> //Шаблон класса
class TVector {
	int raz;   // длина вектора
	T* mass;		// динамический массив-содержимое
public:

	// КОНСТРУКТОР БЕЗ ПАРАМЕТРА РЕЗУЛЬТАТ: НУЛЕВОЙ ВЕКТОР
	TVector() {
		raz = 0; // нулевая длина
		mass = new T [0]; // не ссылается ни на что
	}

	// КОНСТРУКТОР С ПАРАМЕТРОМ (РАЗМЕР) РЕЗУЛЬТАТ: ВЕКТОР ЗАДАННОЙ ДЛИНЫ
	TVector(int a) {
		raz = a;
		mass = new T[a]; // выделяем память под размер элементов
	}

	// КОНСТРУКТОР КОПИЙ С ПАРАМЕТРОМ (ОБЪЕКТ) РЕЗУЛЬТАТ: КОПИЯ ОБЪЕКТА
	TVector(TVector& obj) {
		mass = new T[obj.raz];
		for (int i = 0; i < (obj.raz); i++)
			mass[i] = obj.mass[i];
		return *this;
	}

	// ДЕКСТРУКТОР РЕЗУЛЬТАТ: УДАЛЕНИЕ ВЕКТОРА
	~TVector() {
		if (mass) delete[] mass;
	}

	// МЕТОД ЗАДАЧИ ДЛИНЫ ВЕКТОРА РЕЗУЛЬТАТ: ВЕКТОР ЗАДАННОЙ ДЛИНЫ
	void SetLength(int l) {
		if (mass) delete[] mass;
		raz = l;
		mass = new T[l];
	}

	// ДРУЖЕСТВЕННЫЙ МЕТОД ВЫВОДА В ПОТОК РУЗУЛЬТАТ: ОБЪЕКТ ВЫВОДИТСЯ В ПОТОК
	friend ostream& operator<< (ostream& str, TVector<T>& obj) {
		for (int i = 0; i < obj.raz; i++) {
			str << obj.mass[i] << " ";
		}
		str << endl;
		return str;
	}

	// ОПЕРАТОР ИНТЕКСАЦИИ С ПАРАМЕТРОМ (ИНДЕКС) РЕЗУЛЬТАТ: ЭЛЕМЕНТ НУЖНОГО ИНДЕКСА
	T& operator[](int i) {
		if (i < 0) 
			i = 0;			 
		if (i >= raz) 
			i = raz - 1; 
		return mass[i];
	}

	// ОПЕРАТОР ПРИСВОЕНИЕ С ПАРАМЕТРОМ (ОБЪЕКТ) РЕЗУЛЬТАТ: ВЕКТОР
	TVector<T>& operator=(/*const*/ TVector<T>& obj) {
		raz = obj.raz;
		mass = new T[raz];
		for (int i = 0; i < raz; i++)
			mass[i] = obj.mass[i];
		return *this;
	}

	// ОПЕРАТОР СЛОЖЕНИЯ С ПАРАМЕТРОМ (ОБЪЕКТ) РЕЗУЛЬТАТ: ВЕКТОР С СУММОЙ ВЕКТОРОВ
	TVector<T>& operator+(TVector<T>& obj) {
		for (int i = 0; i < obj.raz; i++) {
			this->mass[i] = this->mass[i] + obj.mass[i];
		}
		return *this;
	}
};

template<class T>
class TMatrix {
	TVector<T>* Vector;
	int m, n;
public:
	// КОНСТРУКТОР С ПАРАМЕТРАМИ (СТРОКИ, СТОЛБЦЫ) РЕЗУЛЬТАТ: МАТРИЦВ MxN
	TMatrix(int strok, int stolb) {
		m = strok;
		n = stolb;
		Vector = new TVector<T>[n];
		for (int i = 0; i < n; i++)
			Vector[i].SetLength(m); //созданием новый вектор
	}

	// ДЕСТРУКТОР
	~TMatrix() {
		delete[] Vector;
	}

	// ОПЕРАТОР ИНДЕКСАЦИИ 
	TVector<T>& operator[](int i)
	{
		if (i < 0)
			i = 0;
		if (i >= m)
			i = m - 1;
		return Vector[i];
	}

	// ОПЕРАТОР СЛОЖЕНИЯ РЕЗУЛЬТАТ: СУММА МАТРИЦ
	TMatrix<T>& operator + (TMatrix<T>& obj)
	{
		for (int i = 0; i < m; i++)
		{
			Vector[i] + obj.Vector[i];
		}
		return *this;
	}

	// ОПЕРАТОР ПРИСВОЕНИЯ   
	TMatrix <T>& operator=(TMatrix<T>& obj) {
		if (this == &obj)
			return *this;
		for (int i = 0; i < m; i++)
			Vector[i] = obj.Vector[i];
		return *this;
	}

	// ДРУЖЕСТВЕННЫЙ ОПЕРАТОР ВЫВОДА В ПОТОК  
	friend ostream& operator<<(ostream& stream, const TMatrix<T>& obj) {
		for (int i = 0; i < obj.m; i++)
			stream << obj.Vector[i] << " ";
		stream << endl;
		return stream;
	}
};

class CStr
{
	char* s;

	// ПРИВАТ МЕТОД ГЕНЕРАЦИИ СЛУЧАЙНОЙ СТРОКИ
	void generate(int length)
	{
		length = 3;
		s = new char[length + 1];
		for (int i = 0; i < length; i++)
			s[i] = 'a' + (rand() % 26);
		s[length] = '\0';
	}

public:

	// КОНСТРУКТОР БЕЗ ПАРАМЕТРА
	CStr()
	{
		int len = 1 + rand() % 20;
		generate(len);
	}

	// КОНСТРУКТОР С ПАРАМЕТРОМ (СТРОКА)
	CStr(char* str)
	{
		s = new char[strlen(str) + 1];
		strcpy(s, str);
	}

	// КОНСТРУКТОР С ПАРАМЕТРОМ (ДЛИНА СТРОКИ) 
	CStr(int length)
	{
		generate(length);
	}

	// КОНСТРУКТОР КОПИЙ
	CStr(CStr& obj)
	{
		s = new char[strlen(obj.s) + 1];
		strcpy(s, obj.s);
	}

	// ДЕСТРУКТОР
	~CStr()
	{
		delete[] s;
	}

	// ОПЕРАТОР ПРИСВОЕНИЯ ОБЪЕКТА
	CStr& operator= (CStr& obj)
	{
		if (this == &obj)
			return *this;   //Проверка на самоприсваивание
		delete s; //Удаляем всё, что к этому моменту может хранить указатель
		s = new char[obj.get_length() + 1]; //динамическое выделение памяти
		strcpy(s, obj.s);   // Копируем передаваемый объект
		return *this;      //возврат текущего измененного объекта
	}

	// ОПЕРАТОР ПРИСВОЕНИЯ СТРОКИ
	CStr& operator= (const char* str)
	{
		if (s) 
			delete[] s;
		s = new char[strlen(str) + 1];
		strcpy(s, str);
		return *this;
	}

	// ОПЕРАТОР СРАВНЕНИЯ БОЛЬШЕ
	bool operator>(CStr& obj)
	{
		if (strcmp(s, obj.s) == 1) 
			return true;
		return false;
	}

	// ОПЕРАТОР СРАВНЕНИЯ МЕНЬШЕ
	bool operator<(CStr& obj)
	{
		if (strcmp(s, obj.s) == -1)
			return true;
		return false;
	}
	// МЕТОД ВОЗВРАЩЕНИЯ ДЛИНЫ СТРОКИ
	int get_length()//метод, возвращающий длину строки.
	{
		return strlen(s);

	}
	// ОПЕРАТОР ВЫВОДА В ПОТОК
	friend ostream& operator<<(ostream& str, CStr& obj)
	{
		return str << obj.s;
	}

	// ОПЕРАТОР СЛОЖЕНИЯ ОБЪЕКТОВ 
	CStr& operator+(CStr& obj) {
		if (s) {
			if (obj.s) {
				char* t = new char[strlen(s) + strlen(obj.s) + 1];
				strcpy(t, s);
				strcpy(t + strlen(s), obj.s);
				return *(new CStr(t));
			}
			else return *this;
		}
		return obj;
	}

	// ОПЕРАТОР СЛОЖЕНИЯ СТРОК (ВТОРУЮ СТАВИМ В КОНЕЦ ПЕРВОЙ)
	CStr& operator+(char* str) {
		char* d = new char[strlen(s) + 1];
		int i;
		if (s) {
			i = strlen(s);
			d = s;
		}
		s = new char[strlen(str) + i + 2];
		s = d;
		strcat(s, str);
		return *this;
	}
};

int main()
{
	setlocale(LC_CTYPE, "RUSSIAN");
	int n, m;
	int r;

	cout << "ВЕКТОР " << endl;

	//СЛОЖЕНИЕ ЦЕЛОЧИСЛЕННЫХ ЧИСЕЛ

	cout << "Введите длину веторов:  ";
	cin >> r;
	cout << endl;

	cout << "Вектор А:  ";
	TVector<int> A(r); 
	for (int i = 0; i < r; i++) 
	{ 
		A[i] = i + 1; 
		cout << A[i]<< " ";
	}
	cout << endl;

	cout << "Вектор B:  ";
	TVector<int> B(r); 
	for (int i = 0; i < r; i++) 
	{ 
		B[i] = i + 2; 
		cout << B[i] << " ";
	}
	cout << endl;
	
	cout << "Результатом сложения для целочисленных числе является: " << A+B << endl << endl;

	//СЛОЖЕНИЕ СТРОК
	cout << "Введите длину строк:  ";
	cin >> r;
	cout << endl;

	cout << "Вектор А:  ";
	TVector<string> C(r); 
	for (int i = 0; i < r; i++) 
	{ 
		C[i] = char(rand() % 26 + 0x61);
		cout << C[i] << " ";
	}

	cout << endl;

	cout << "Вектор B:  ";
	TVector<string> D(r); 
	for (int i = 0; i < r; i++) 
	{ 
		D[i] = char(rand() % 26 + 0x61);
		cout << D[i] << " ";
	}
	cout << endl;

	//cout << C1 << endl << endl << C2 << endl << endl;
	cout << "Результатом сложения для строк является: " << C+D << endl << endl;

	
	cout << "МАТРИЦА" << endl;
	// СЛОЖЕНИЕ МАТРИЦ ИЗ ЦЕЛОЧИСЛЕННЫЙ ЧИСЕЛ
	cout << "Введите размерность матрицы:  ";
	cin >> m;
	cin >> n;
	cout << endl;
	TMatrix<int> Mat1(m, n);
	TMatrix<int> Mat2(m, n);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			Mat1[i][j] = i + j*3;
			Mat2[i][j] = i * j;
		}
	cout << "Матрица А:  " << endl;
	cout << Mat1[1][3] << endl;

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << Mat1[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Матрица B:  " << endl;

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << Mat2[i][j] << " ";
		}
		cout << endl;
	}

	TMatrix<int> Mat3(m, n);
	Mat3 = Mat1 + Mat2;

	cout << "Результат сложения целочисленных матриц:  " <<  endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << Mat3[i][j] << " ";
		}
		cout << endl;
	}

	//СЛОЖЕНИЕ МАТРИЦ ИЗ СТРОК

	
	cout << "Введите размерность матрицы:  ";
	cin >> m;
	cin >> n;
	cout << endl;
	
	TMatrix<string> Mat4(m, n);
	TMatrix<string> Mat5(m, n);

	
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			Mat4[i][j] = char(rand() % 26 + 0x61);
			Mat5[i][j] = char(rand() % 26 + 0x61);
		}
	cout << "Матрица A" << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
		{
			cout << Mat4[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Матрица B" << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
		{
			cout << Mat5[i][j] << " ";
		}
		cout << endl;
	}
		

	cout << "Результат сложения строковых матриц:  " << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << Mat4[i][j] + Mat5[i][j]<< " ";
		}
		cout << endl;
	}

	
	// СЛОЖЕНИЕ МАТРИЦ ТИПА CSTR

	cout << "Введите размерность матрицы:  ";
	cin >> m;
	cin >> n;
	cout << endl;

	TMatrix<CStr> Mat6(m, n);
	TMatrix<CStr> Mat7(m, n);

	
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			Mat6[i][j] = *(new CStr('a' + rand() % 20));
			Mat7[i][j] = *(new CStr('a' + rand() % 20));
		}
	cout << "Матрица A" << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
		{
			cout << Mat6[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Матрица B" << endl;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
		{
			cout << Mat7[i][j] << " ";
		}
		cout << endl;
	}

	TMatrix<CStr> Mat8(m, n);
	Mat8 = Mat6 + Mat7;


	cout << "Результат сложения матриц типа Cstr:  " << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << Mat8[i][j] << " ";
		}
		cout << endl;
	}


	system("pause");
	return 0;
}