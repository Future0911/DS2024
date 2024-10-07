#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>

using namespace std;

class Complex {
private:
    double real;
    double imag;

public:
    // Ĭ�Ϲ��캯��
    Complex() {
        real = 0;
        imag = 0;
    }

    // ���������캯��
    Complex(double r, double i) {
        real = r;
        imag = i;
    }

    // Getter and Setter
    double getReal() const {
        return real;
    }

    double getImag() const {
        return imag;
    }

    void setReal(double r) {
        real = r;
    }

    void setImag(double i) {
        imag = i;
    }

    // ���㸴����ģ
    double modulus() const {
        return sqrt(real * real + imag * imag);
    }

    // ��������� ==
    friend bool operator==(const Complex& c1, const Complex& c2) {
        return c1.real == c2.real && c1.imag == c2.imag;
    }

    // ��������� <<
    friend ostream& operator<<(ostream& out, const Complex& c) {
        out << c.real << "+" << c.imag << "i";
        return out;
    }

    // ��������� <
    friend bool operator<(const Complex& c1, const Complex& c2) {
        if (c1.modulus() != c2.modulus()) {
            return c1.modulus() < c2.modulus();
        }
        return c1.real < c2.real;
    }

    // ��������� >
    friend bool operator>(const Complex& c1, const Complex& c2) {
        return c2 < c1; // �������е� < ���������
    }
};

// ϴ�ƺ���
void shuffle(vector<Complex>& vec) {
    srand(time(NULL));
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        int j = rand() % n;
        swap(vec[i], vec[j]);
    }
}

// ���Һ���
int find(const vector<Complex>& vec, const Complex& c) {
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        if (vec[i] == c) {
            return i;
        }
    }
    return -1;
}

// ���뺯��
void insert(vector<Complex>& vec, const Complex& c) {
    vec.push_back(c);
}

// ɾ������
void remove(vector<Complex>& vec, const Complex& c) {
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        if (vec[i] == c) {
            vec.erase(vec.begin() + i);
            break;
        }
    }
}

// Ψһ������
void unique(vector<Complex>& vec) {
    int n = vec.size();
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (vec[i] == vec[j]) {
                vec.erase(vec.begin() + j);
                n--;
                j--;
            }
        }
    }
}

// ��������
void bubbleSort(vector<Complex>& vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (vec[j] > vec[j + 1]) {
                swap(vec[j], vec[j + 1]);
            }
        }
    }
}

// �鲢����������
void merge(vector<Complex>& vec, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Complex> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = vec[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = vec[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] < R[j]) {
            vec[k] = L[i];
            i++;
        }
        else {
            vec[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        vec[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        vec[k] = R[j];
        j++;
        k++;
    }
}

// �鲢����
void mergeSort(vector<Complex>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);

        merge(vec, left, mid, right);
    }
}

// ������Һ���
vector<Complex> rangeSearch(const vector<Complex>& vec, double m1, double m2) {
    vector<Complex> result;
    for (const auto& c : vec) {
        double mod = c.modulus();
        if (mod >= m1 && mod < m2) {
            result.push_back(c);
        }
    }
    return result;
}

// ������
int main() {
    vector<Complex> vec = {
        Complex(1, 2), Complex(3, 4), Complex(5, 6),
        Complex(1, 2), Complex(7, 8), Complex(9, 10)
    };

    cout << "Before shuffle: ";
    for (const auto& c : vec) {
        cout << c << " ";
    }
    cout << endl;

    // ����
    shuffle(vec);
    cout << "After shuffle: ";
    for (const auto& c : vec) {
        cout << c << " ";
    }
    cout << endl;

    // ����
    Complex target(1, 2);
    int index = find(vec, target);
    if (index != -1) {
        cout << "Found " << target << " at index " << index << endl;
    }
    else {
        cout << "Not found " << target << endl;
    }

    // ����
    Complex newComplex(5, 6);
    insert(vec, newComplex);
    cout << "After insert " << newComplex << ": ";
    for (const auto& c : vec) {
        cout << c << " ";
    }
    cout << endl;

    // ɾ��
    remove(vec, target);
    cout << "After remove " << target << ": ";
    for (const auto& c : vec) {
        cout << c << " ";
    }
    cout << endl;

    // Ψһ��
    unique(vec);
    cout << "After unique: ";
    for (const auto& c : vec) {
        cout << c << " ";
    }
    cout << endl;

    // ���򲢼�ʱ
    vector<Complex> vecBubble = vec;
    vector<Complex> vecMerge = vec;

    clock_t start, end;

    start = clock();
    bubbleSort(vecBubble);
    end = clock();
    cout << "Bubble sort time: " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;

    start = clock();
    mergeSort(vecMerge, 0, vecMerge.size() - 1);
    end = clock();
    cout << "Merge sort time: " << double(end - start) / CLOCKS_PER_SEC << "s" << endl;

    // �������
    double m1 = 5.0, m2 = 10.0;
    vector<Complex> rangeResult = rangeSearch(vecMerge, m1, m2);
    cout << "Range search [" << m1 << ", " << m2 << "): ";
    for (const auto& c : rangeResult) {
        cout << c << " ";
    }
    cout << endl;

    return 0;
}
