
#ifndef __MATRIX_HEADER__
#define __MATRIX_HEADER__







//==========[ Forward References ]=============================================

template <class T> class Vec;
template <class T> class Vec3;
template <class T> class Vec4;
template <class T> class Mat3;
template <class T> class Mat4;
template <class T> class Mat;

//==========[ class Mat ]=====================================================

template <typename T = float>
class Mat
{
public:
	Mat(int M, int N);
	Mat(T* data, int M, int N);
	~Mat();
	T* data();
	T at(int i, int j);
	void set(int i, int j, T v);
	T determinant();
	Mat<T> transposed();
	Mat<T> inverse();
	Mat<T> cofactor(int i, int j);
	void printData();
	void printData(T* data, int m, int n);
	void printData(T* data, int dim);
	int M;
	int N;
private:
	T* m_data;
	T* minorData(T* olddata, int m, int n, int dim);
	T determinantHelper(T* data, int dim);
};

template <typename T>
Mat<T> operator + (Mat<T>& m1, Mat<T>& m2)
{
	int M = m1.M;
	int N = m1.N;
	T* data = (T*)malloc(M * N * sizeof(T));
	for (int i = 0; i < M * N; i++)
		data[i] = (m1.data())[i] + (m2.data())[i];
	return (Mat<T>(data, M, N));
}

template <typename T>
Mat<T> operator - (Mat<T>& m1, Mat<T>& m2)
{
	int M = m1.M;
	int N = m1.N;
	T* data = (T*)malloc(M * N * sizeof(T));
	for (int i = 0; i < M * N; i++)
		data[i] = (m1.data())[i] - (m2.data())[i];
	return (Mat<T>(data, M, N));
}

template < typename T>
Mat<T> operator - (Mat<T>& m)
{
	int M = m1.M;
	int N = m1.N;
	T* data = (T*)malloc(M * N * sizeof(T));
	for (int i = 0; i < M * N; i++)
		data[i] = -(m.data())[i];
	return Mat<T>(data, M, N);
}

template <typename T>
Mat<T> operator * (Mat<T> m1, Mat<T> m2)
{
	int M = m1.M;
	int K = m1.N;
	int N = m2.N;
	//cout << "M:" << M << ",K:" << K << ",N:" << N << endl;
	T* data = (T*)malloc(M * N * sizeof(T));
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
		{
			T v = 0;
			T* d1 = m1.data();
			T* d2 = m2.data();
			for (int k = 0; k < K; k++)
			{
				v += d1[i * K + k] * d2[k * N + j];
			}
			data[i * N + j] = v;
		}
	return (Mat<T>(data, M, N));
}

template <typename T>
Mat<T> operator * (Mat<T>& m, T v)
{
	int M = m.M;
	int N = m.N;
	T* data = (T*)malloc(M * N * sizeof(T));
	for (int i = 0; i < M * N; i++)
		data[i] = (m.data())[i] * v;
	return (Mat<T>(data, M, N));
}

template <typename T>
Mat<T> operator * (T v, Mat<T>& m)
{
	int M = m.M;
	int N = m.N;
	T* data = (T*)malloc(M * N * sizeof(T));
	for (int i = 0; i < M * N; i++)
		data[i] = (m.data())[i] * v;
	return (Mat<T>(data, M, N));
}

template <typename T>
Mat<T> operator / (Mat<T>& m, T v)
{
	int M = m.M;
	int N = m.N;
	T* data = (T*)malloc(M * N * sizeof(T));
	for (int i = 0; i < M * N; i++)
		data[i] = (m.data())[i] / v;
	return (Mat<T>(data, M, N));
}

template <typename T>
void Mat<T>::printData()
{

// 	for (int i = 0; i < M; i++)
// 	{
// 		for (int j = 0; j < N; j++)
// 			cout << m_data[i * N + j] << '\t';
// 		cout << endl;
// 	}
// 	cout << endl;
}

template <typename T>
void Mat<T>::printData(T* data, int m, int n)
{
// 	for (int i = 0; i < m; i++)
// 	{
// 		for (int j = 0; j < n; j++)
// 			cout << data[i * n + j] << '\t';
// 		cout << endl;
// 	}
// 	cout << endl;
}

template <typename T>
void Mat<T>::printData(T* data, int dim)
{
// 	for (int i = 0; i < dim; i++)
// 	{
// 		for (int j = 0; j < dim; j++)
// 			cout << data[i * dim + j] << '\t';
// 		cout << endl;
// 	}
// 	cout << endl;
}

template <typename T>
Mat<T>::Mat(int M, int N)
{
	if (M < 1 || N < 1)
		throw "Error: M or N can't be less than 1.";
	//m_data = (T*)calloc(M*N,sizeof(T));
	m_data = new T[M * N];
	this->M = M;
	this->N = N;
}

template <typename T>
Mat<T>::Mat(T* data, int M, int N)
{
	if (M < 1 || N < 1)
		throw "Error: M or N can't be less than 1.";
	//m_data = (T*)malloc(M*N*sizeof(T));
	m_data = new T[M * N];
	for (int i = 0; i < M * N; i++)
		m_data[i] = data[i];
	this->M = M;
	this->N = N;
}

template <typename T>
Mat<T>::~Mat()
{

}

template <typename T>
T* Mat<T>::data()
{
	return m_data;
}

template <typename T>
T Mat<T>::at(int i, int j)
{
	return (m_data[i * N + j]);
}

template <typename T>
void Mat<T>::set(int i, int j, T v)
{
	m_data[i * N + j] = v;
}

template < typename T>
T Mat<T>::determinant()
{
	if (M != N)
		return 0;
	return determinantHelper(m_data, M);
}

template <typename T>
T Mat<T>::determinantHelper(T* data, int dim)
{
	if (dim == 1)
		return data[0];
	if (dim == 2)
		return data[0] * data[3] - data[1] * data[2];
	T deter = 0;
	for (int i = 0; i < dim; i++)
	{
		T* minData = minorData(data, 0, i, dim);
		deter += data[i] * pow(-1, i) * determinantHelper(minData, dim - 1);
	}
	return deter;
}

template <typename T>
Mat<T> Mat<T>::transposed()
{
	T* newData = (T*)calloc(N * M, sizeof(T));
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			newData[i * M + j] = m_data[j * N + i];
	return (Mat<T>(newData, N, M));
}

template <typename T>
Mat<T> Mat<T>::inverse()
{
	if (M != N)
		throw "Error: M!=N";
	T deter = determinant();
	if (deter == 0)
	{
		cout << "Error: matrix with determinant=0 has no inverse!\n";
		printData();
		throw "Error: matrix with determinant=0 has no inverse!\n";
	}
	if (M == 1)
	{
		Mat<T> ret = Mat<T>(1, 1);
		ret.set(0, 0, 1.0f / m_data[0]);
		return ret;
	}
	if (M == 2)
	{
		Mat<T> ret = Mat<T>(2, 2);
		ret.set(0, 0, m_data[3] / (deter));
		ret.set(0, 1, m_data[2] / (-deter));
		ret.set(1, 0, m_data[1] / (-deter));
		ret.set(1, 1, m_data[0] / (deter));
		return ret;
	}
	T* data = (T*)malloc(M * N * sizeof(T));
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			data[i * N + j] = pow(-1, i + j) * (cofactor(i, j).determinant()) / (deter);
	return Mat<T>(data, M, N).transposed();
}

template <typename T>
Mat<T> Mat<T>::cofactor(int i, int j)
{
	T* data = minorData(m_data, i, j, M);
	Mat<T> ret = Mat<T>(data, M - 1, N - 1);
	return ret;
}


template <typename T>
T* Mat<T>::minorData(T* olddata, int m, int n, int dim)
{
	T* data = (T*)calloc((dim - 1) * (dim - 1), sizeof(T));
	int r = 0;
	int c = 0;
	for (int i = 0; i < dim; i++)
	{
		if (i == m) continue;
		c = 0;
		for (int j = 0; j < dim; j++)
		{
			if (j == n) continue;
			data[r * (dim - 1) + c] = olddata[i * (dim)+j];
			c++;
		}
		r++;
	}
	return data;
}


//==========[ class Mat3 ]=====================================================

template <class T>
class Mat3 {

	//---[ Private Variable Declarations ]-----------------

		// matrix elements in row major order
	T		n[9];

public:

	//---[ Constructors ]----------------------------------

	Mat3()
	{
		memset(n, 0, 9 * sizeof(T)); n[0] = 1; n[3] = 1; n[6] = 1;
	}
	Mat3(T n0, T n1, T n2, T n3, T n4, T n5, T n6, T n7, T n8)
	{
		n[0] = n0; n[1] = n1; n[2] = n2;
		n[3] = n3; n[4] = n4; n[5] = n5;
		n[6] = n6; n[7] = n7; n[8] = n8;
	}
	Mat3(const Mat3<T>& m)
	{
		memcpy(n, m.n, 9 * sizeof(T));
	}

	//---[ Equal Operators ]-------------------------------

	Mat3<T>& operator =(const Mat3<T>& m)
	{
		memcpy(n, m.n, 9 * sizeof(T)); return *this;
	}
	Mat3<T>& operator +=(const Mat3<T>& m)
	{
		n[0] += m.n[0]; n[1] += m.n[1]; n[2] += m.n[2]; n[3] += m.n[3]; n[4] += m.n[4]; n[5] += m.n[5]; n[6] += m.n[6]; n[7] += m.n[7]; n[8] += m.n[8]; return *this;
	}
	Mat3<T>& operator -=(const Mat3<T>& m)
	{
		n[0] -= m.n[0]; n[1] -= m.n[1]; n[2] -= m.n[2]; n[3] -= m.n[3]; n[4] -= m.n[4]; n[5] -= m.n[5]; n[6] -= m.n[6]; n[7] -= m.n[7]; n[8] -= m.n[8]; return *this;
	}
	Mat3<T>& operator *=(const T d)
	{
		n[0] *= d; n[1] *= d; n[2] *= d; n[3] *= d; n[4] *= d; n[5] *= d; n[6] *= d; n[7] *= d; n[8] *= d; return *this;
	}
	Mat3<T>& operator /=(const T d)
	{
		n[0] /= d; n[1] /= d; n[2] /= d; n[3] /= d; n[4] /= d; n[5] /= d; n[6] /= d; n[7] /= d; n[8] /= d; return *this;
	}

	//---[ Access Operators ]------------------------------

	T* operator [](int i)
	{
		return &n[i * 3];
	}
	const T* operator [](int i) const
	{
		return &n[i * 3];
	}

	//---[ Ordering Methods ]------------------------------

	Mat3<T> transpose() const { return Mat3<T>(n[0], n[3], n[6], n[1], n[4], n[7], n[2], n[5], n[8]) }
	double trace() const { return n[0] + n[4] + n[8]; }

	//---[ GL Matrix ]-------------------------------------

	void getGLMatrix(T* mat) const
	{
		mat[0] = n[0]; mat[1] = n[3]; mat[2] = n[6];
		mat[3] = n[1]; mat[4] = n[4]; mat[5] = n[7];
		mat[6] = n[2]; mat[7] = n[5]; mat[8] = n[8];
	}

	//---[ Transformation Matrices ]-----------------------

	static Mat3<T> createRotation(T angle, float x, float y);
	static Mat3<T> createTranslation(T x, T y);
	static Mat3<T> createScale(T sx, T sy);
	static Mat3<T> createShear(T shx, T shy);

	//---[ Friend Methods ]--------------------------------

#if _MSC_VER >= 1300

	template <class U> friend Mat3<U> operator -(const Mat3<U>& a);
	template <class U> friend Mat3<U> operator +(const Mat3<U>& a, const Mat3<U>& b);
	template <class U> friend Mat3<U> operator -(const Mat3<U>& a, const Mat3<U>& b);
	template <class U> friend Mat3<U> operator *(const Mat3<U>& a, const Mat3<U>& b);
	template <class U> friend Mat3<U> operator *(const Mat3<U>& a, const double d);
	template <class U> friend Mat3<U> operator *(const double d, const Mat3<U>& a);
	template <class U> friend Mat3<U> operator /(const Mat3<U>& a, const double d);
	template <class U> friend bool operator ==(const Mat3<U>& a, const Mat3<U>& b);
	template <class U> friend bool operator !=(const Mat3<U>& a, const Mat3<U>& b);

#else // _MSC_VER >= 1300

	friend Mat3<T> operator -(const Mat3<T>& a);
	friend Mat3<T> operator +(const Mat3<T>& a, const Mat3<T>& b);
	friend Mat3<T> operator -(const Mat3<T>& a, const Mat3<T>& b);
	friend Mat3<T> operator *(const Mat3<T>& a, const Mat3<T>& b);
	friend Mat3<T> operator *(const Mat3<T>& a, const double d);
	friend Mat3<T> operator *(const double d, const Mat3<T>& a);
	friend Mat3<T> operator /(const Mat3<T>& a, const double d);
	friend bool operator ==(const Mat3<T>& a, const Mat3<T>& b);
	friend bool operator !=(const Mat3<T>& a, const Mat3<T>& b);

#endif
};

typedef Mat3<int> Mat3i;
typedef Mat3<float> Mat3f;
typedef Mat3<double> Mat3d;

//==========[ class Mat4 ]=====================================================

template <class T>
class Mat4 {

	//---[ Private Variable Declarations ]-----------------
public:
	// matrix elements in row-major order
	T		n[16];



	bool isZero() { return n[0] == 0 && n[1] == 0 && n[2] == 0 && n[3] == 0 && n[4] == 0 && n[5] == 0 && n[6] == 0 && n[7] == 0 && n[8] == 0 && n[9] == 0 && n[10] == 0 && n[11] == 0 && n[12] == 0 && n[13] == 0 && n[14] == 0 && n[15] == 0; }

	//---[ Constructors ]----------------------------------

	Mat4()
	{
		memset(n, 0, 16 * sizeof(T)); n[0] = 1;n[5] = 1;n[10] = 1;n[15] = 1;
	}
	Mat4(T n0, T n1, T n2, T n3, T n4, T n5, T n6, T n7, T n8, T n9, T n10, T n11, T n12, T n13, T n14, T n15)
	{
		n[0] = n0; n[1] = n1; n[2] = n2; n[3] = n3;
		n[4] = n4; n[5] = n5; n[6] = n6; n[7] = n7;
		n[8] = n8; n[9] = n9; n[10] = n10; n[11] = n11;
		n[12] = n12; n[13] = n13; n[14] = n14; n[15] = n15;
	}
	Mat4(const Mat4<T>& m)
	{
		memcpy(n, m.n, 16 * sizeof(T));
	}

	//---[ Equal Operators ]-------------------------------

	Mat4<T>& operator =(const Mat4<T>& m)
	{
		memcpy(n, m.n, 16 * sizeof(T)); return *this;
	}
	Mat4<T>& operator +=(const Mat4<T>& m)
	{
		n[0] += m.n[0]; n[1] += m.n[1]; n[2] += m.n[2]; n[3] += m.n[3];
		n[4] += m.n[4]; n[5] += m.n[5]; n[6] += m.n[6]; n[7] += m.n[7];
		n[8] += m.n[8]; n[9] += m.n[9]; n[10] += m.n[10]; n[11] += m.n[11];
		n[12] += m.n[12]; n[13] += m.n[13]; n[14] += m.n[14]; n[15] += m.n[15];
		return *this;
	}
	Mat4<T>& operator -=(const Mat4<T>& m)
	{
		n[0] -= m.n[0]; n[1] -= m.n[1]; n[2] -= m.n[2]; n[3] -= m.n[3];
		n[4] -= m.n[4]; n[5] -= m.n[5]; n[6] -= m.n[6]; n[7] -= m.n[7];
		n[8] -= m.n[8]; n[9] -= m.n[9]; n[10] -= m.n[10]; n[11] -= m.n[11];
		n[12] -= m.n[12]; n[13] -= m.n[13]; n[14] -= m.n[14]; n[15] -= m.n[15];
		return *this;
	}
	Mat4<T>& operator *=(const T d)
	{
		n[0] *= d; n[1] *= d; n[2] *= d; n[3] *= d;
		n[4] *= d; n[5] *= d; n[6] *= d; n[7] *= d;
		n[8] *= d; n[9] *= d; n[10] *= d; n[11] *= d;
		n[12] *= d; n[13] *= d; n[14] *= d; n[15] *= d;
		return *this;
	}
	Mat4<T>& operator /=(const T d)
	{
		n[0] /= d; n[1] /= d; n[2] /= d; n[3] /= d;
		n[4] /= d; n[5] /= d; n[6] /= d; n[7] /= d;
		n[8] /= d; n[9] /= d; n[10] /= d; n[11] /= d;
		n[12] /= d; n[13] /= d; n[14] /= d; n[15] /= d;
		return *this;
	}

	//---[ Access Operators ]------------------------------

	T* operator [](int i)
	{
		return &n[i * 4];
	}
	const T* operator [](int i) const
	{
		return &n[i * 4];
	}

	//---[ Ordering Methods ]------------------------------

	Mat4<T> transpose() const
	{
		return Mat4<T>(n[0], n[4], n[8], n[12],
			n[1], n[5], n[9], n[13],
			n[2], n[6], n[10], n[14],
			n[3], n[7], n[11], n[15]);
	}
	double trace() const { return n[0] + n[5] + n[10] + n[15]; }

	Mat4<T> inverse() const {
		Mat4<T>		a(*this);
		Mat4<T>		b;

		int			i, j, k, l;

		for (i = 0;i < 4;i++) {
			j = i;
			for (k = i + 1;k < 4;k++) {
				if (fabs(a[k][i]) > fabs(a[j][i]))
					j = k;
			}

			a.swapRows(i, j);
			b.swapRows(i, j);

			if (a[i][i] == 0.0)
				return Mat4<T>();

			float diag = a[i][i];
			for (k = 0;k < 4;k++) {
				a[i][k] /= diag;
				b[i][k] /= diag;
			}

			for (k = 0;k < 4;k++) {
				if (k != i) {
					float aki = a[k][i];
					for (l = 0;l < 4;l++) {
						a[k][l] -= aki * a[i][l];
						if (fabs(a[k][l]) < 0.00000001) a[k][l] = 0.0;
						b[k][l] -= aki * b[i][l];
						if (fabs(b[k][l]) < 0.00000001) b[k][l] = 0.0;
					}
				}
			}
		}

		return b;
	}

	void swapRows(int a, int b) {
		T		temp;

		for (int i = 0;i < 4;i++) {
			temp = n[a * 4 + i];
			n[a * 4 + i] = n[b * 4 + i];
			n[b * 4 + i] = temp;
		}
	}

	//---[ GL Matrix ]-------------------------------------

	void getGLMatrix(T* mat) const
	{
		mat[0] = n[0]; mat[1] = n[4]; mat[2] = n[8]; mat[3] = n[12];
		mat[4] = n[1]; mat[5] = n[5]; mat[6] = n[9]; mat[7] = n[13];
		mat[8] = n[2]; mat[9] = n[6]; mat[10] = n[10]; mat[11] = n[14];
		mat[12] = n[3]; mat[13] = n[7]; mat[14] = n[11]; mat[15] = n[15];
	}

	//---[ Transformation Matrices ]-----------------------

	static Mat4<T> createRotation(T angle, float x, float y, float z);
	static Mat4<T> createTranslation(T x, T y, T z);
	static Mat4<T> createScale(T sx, T sy, T sz);
	static Mat4<T> createShear(T shx, T shy, T shz);

	//---[ Friend Methods ]--------------------------------

#if _MSC_VER >= 1300

	template <class U> friend Mat4<U> operator -(const Mat4<U>& a);
	template <class U> friend Mat4<U> operator +(const Mat4<U>& a, const Mat4<U>& b);
	template <class U> friend Mat4<U> operator -(const Mat4<U>& a, const Mat4<U>& b);
	template <class U> friend Mat4<U> operator *(const Mat4<U>& a, const Mat4<U>& b);
	template <class U> friend Mat4<U> operator *(const Mat4<U>& a, const double d);
	template <class U> friend Mat4<U> operator *(const double d, const Mat4<U>& a);
	template <class U> friend Vec3<U> operator *(const Mat4<U>& a, const Vec3<U>& b);
	template <class U> friend Mat4<U> operator /(const Mat4<U>& a, const double d);
	template <class U> friend bool operator ==(const Mat4<U>& a, const Mat4<U>& b);
	template <class U> friend bool operator !=(const Mat4<U>& a, const Mat4<U>& b);

#else // _MSC_VER >= 1300

	friend Mat4<T> operator -(const Mat4<T>& a);
	friend Mat4<T> operator +(const Mat4<T>& a, const Mat4<T>& b);
	friend Mat4<T> operator -(const Mat4<T>& a, const Mat4<T>& b);
	friend Mat4<T> operator *(const Mat4<T>& a, const Mat4<T>& b);
	friend Mat4<T> operator *(const Mat4<T>& a, const double d);
	friend Mat4<T> operator *(const double d, const Mat4<T>& a);
	friend Vec3<T> operator *(const Mat4<T>& a, const Vec3<T>& b);
	friend Mat4<T> operator /(const Mat4<T>& a, const double d);
	friend bool operator ==(const Mat4<T>& a, const Mat4<T>& b);
	friend bool operator !=(const Mat4<T>& a, const Mat4<T>& b);

#endif // _MSC_VER >= 1300

};

typedef Mat4<int> Mat4i;
typedef Mat4<float> Mat4f;
typedef Mat4<double> Mat4d;

//==========[ Inline Method Definitions (Matrix) ]=============================

template <class T>
inline Mat3<T> Mat3<T>::createRotation(T angle, float x, float y) {
	Mat3<T> rot;

	return rot;
}

template <class T>
inline Mat3<T> Mat3<T>::createTranslation(T x, T y) {
	Mat3<T> trans;

	return trans;
}

template <class T>
inline Mat3<T> Mat3<T>::createScale(T sx, T sy) {
	Mat3<T> scale;

	return scale;
}

template <class T>
inline Mat3<T> Mat3<T>::createShear(T shx, T shy) {
	Mat3<T> shear;

	return shear;
}

template <class T>
inline Mat3<T> operator -(const Mat3<T>& a) {
	return Mat3<T>(-a.n[0], -a.n[1], -a.n[2],
		-a.n[3], -a.n[4], -a.n[5],
		-a.n[6], -a.n[7], -a.n[8]);
}

template <class T>
inline Mat3<T> operator +(const Mat3<T>& a, const Mat3<T>& b) {
	return Mat3<T>(a.n[0] + b.n[0], a.n[1] + b.n[1], a.n[2] + b.n[2],
		a.n[3] + b.n[3], a.n[4] + b.n[4], a.n[5] + b.n[5],
		a.n[6] + b.n[6], a.n[7] + b.n[7], a.n[8] + b.n[8], );
}

template <class T>
inline Mat3<T> operator -(const Mat3<T>& a, const Mat3<T>& b) {
	return Mat3<T>(a.n[0] - b.n[0], a.n[1] - b.n[1], a.n[2] - b.n[2],
		a.n[3] - b.n[3], a.n[4] - b.n[4], a.n[5] - b.n[5],
		a.n[6] - b.n[6], a.n[7] - b.n[7], a.n[8] - b.n[8], );
}

template <class T>
inline Mat3<T> operator *(const Mat3<T>& a, const Mat3<T>& b) {
	return Mat3<T>(a.n[0] * b.n[0] + a.n[1] * b.n[3] + a.n[2] * b.n[6],
		a.n[0] * b.n[1] + a.n[1] * b.n[4] + a.n[2] * b.n[7],
		a.n[0] * b.n[2] + a.n[1] * b.n[5] + a.n[2] * b.n[8],
		a.n[3] * b.n[0] + a.n[4] * b.n[3] + a.n[5] * b.n[6],
		a.n[3] * b.n[1] + a.n[4] * b.n[4] + a.n[5] * b.n[7],
		a.n[3] * b.n[2] + a.n[4] * b.n[5] + a.n[5] * b.n[8],
		a.n[6] * b.n[0] + a.n[7] * b.n[3] + a.n[8] * b.n[6],
		a.n[6] * b.n[1] + a.n[7] * b.n[4] + a.n[8] * b.n[7],
		a.n[6] * b.n[2] + a.n[7] * b.n[5] + a.n[8] * b.n[8]);
}

template <class T>
inline Mat3<T> operator *(const Mat3<T>& a, const double d) {
	return Mat3<T>(a.n[0] * d, a.n[1] * d, a.n[2] * d,
		a.n[3] * d, a.n[4] * d, a.n[5] * d,
		a.n[6] * d, a.n[7] * d, a.n[8] * d);
}

template <class T>
inline Mat3<T> operator *(const double d, const Mat3<T>& a) {
	return Mat3<T>(a.n[0] * d, a.n[1] * d, a.n[2] * d,
		a.n[3] * d, a.n[4] * d, a.n[5] * d,
		a.n[6] * d, a.n[7] * d, a.n[8] * d);
}

template <class T>
inline Mat3<T> operator /(const Mat3<T>& a, const double d) {
	return Mat3<T>(a.n[0] / d, a.n[1] / d, a.n[2] / d,
		a.n[3] / d, a.n[4] / d, a.n[5] / d,
		a.n[6] / d, a.n[7] / d, a.n[8] / d);
}

template <class T>
inline bool operator ==(const Mat3<T>& a, const Mat3<T>& b) {
	return !memcmp(a.n, b.n, 9 * sizeof(T));
}

template <class T>
inline bool operator !=(const Mat3<T>& a, const Mat3<T>& b) {
	return memcmp(a.n, b.n, 9 * sizeof(T));
}

template <class T>
inline void swap(Mat3<T>& a, Mat3<T>& b) {
	//	swap( a.v[0], b.v[0] );
	//	swap( a.v[1], b.v[1] );
	//	swap( a.v[2], b.v[2] );
}

template <class T>
inline Mat4<T> Mat4<T>::createRotation(T angle, float x, float y, float z) {
	Mat4<T> rot;

	return rot;
}

template <class T>
inline Mat4<T> Mat4<T>::createTranslation(T x, T y, T z) {
	Mat4<T> trans;

	return trans;
}

template <class T>
inline Mat4<T> Mat4<T>::createScale(T sx, T sy, T sz) {
	Mat4<T> scale;

	return scale;
}

template <class T>
inline Mat4<T> Mat4<T>::createShear(T shx, T shy, T shz) {
	Mat4<T> shear;

	return shear;
}

template <class T>
inline Mat4<T> operator -(const Mat4<T>& a) {
	return Mat4<T>(-a.n[0], -a.n[1], -a.n[2], -a.n[3],
		-a.n[4], -a.n[5], -a.n[6], -a.n[7],
		-a.n[8], -a.n[9], -a.n[10], -a.n[11],
		-a.n[12], -a.n[13], -a.n[14], -a.n[15]);
}

template <class T>
inline Mat4<T> operator +(const Mat4<T>& a, const Mat4<T>& b) {
	return Mat4<T>(a.n[0] + b.n[0], a.n[1] + b.n[1], a.n[2] + b.n[2], a.n[3] + b.n[3],
		a.n[4] + b.n[4], a.n[5] + b.n[5], a.n[6] + b.n[6], a.n[7] + b.n[7],
		a.n[8] + b.n[8], a.n[9] + b.n[9], a.n[10] + b.n[10], a.n[11] + b.n[11],
		a.n[12] + b.n[12], a.n[13] + b.n[13], a.n[14] + b.n[14], a.n[15] + b.n[15]);
}

template <class T>
inline Mat4<T> operator -(const Mat4<T>& a, const Mat4<T>& b) {
	return Mat4<T>(a.n[0] - b.n[0], a.n[1] - b.n[1], a.n[2] - b.n[2], a.n[3] - b.n[3],
		a.n[4] - b.n[4], a.n[5] - b.n[5], a.n[6] - b.n[6], a.n[7] - b.n[7],
		a.n[8] - b.n[8], a.n[9] - b.n[9], a.n[10] - b.n[10], a.n[11] - b.n[11],
		a.n[12] - b.n[12], a.n[13] - b.n[13], a.n[14] - b.n[14], a.n[15] - b.n[15]);
}

template <class T>
inline Mat4<T> operator *(const Mat4<T>& a, const Mat4<T>& b) {
	return Mat4<T>(a.n[0] * b.n[0] + a.n[1] * b.n[4] + a.n[2] * b.n[8] + a.n[3] * b.n[12],
		a.n[0] * b.n[1] + a.n[1] * b.n[5] + a.n[2] * b.n[9] + a.n[3] * b.n[13],
		a.n[0] * b.n[2] + a.n[1] * b.n[6] + a.n[2] * b.n[10] + a.n[3] * b.n[14],
		a.n[0] * b.n[3] + a.n[1] * b.n[7] + a.n[2] * b.n[11] + a.n[3] * b.n[15],
		a.n[4] * b.n[0] + a.n[5] * b.n[4] + a.n[6] * b.n[8] + a.n[7] * b.n[12],
		a.n[4] * b.n[1] + a.n[5] * b.n[5] + a.n[6] * b.n[9] + a.n[7] * b.n[13],
		a.n[4] * b.n[2] + a.n[5] * b.n[6] + a.n[6] * b.n[10] + a.n[7] * b.n[14],
		a.n[4] * b.n[3] + a.n[5] * b.n[7] + a.n[6] * b.n[11] + a.n[7] * b.n[15],
		a.n[8] * b.n[0] + a.n[9] * b.n[4] + a.n[10] * b.n[8] + a.n[11] * b.n[12],
		a.n[8] * b.n[1] + a.n[9] * b.n[5] + a.n[10] * b.n[9] + a.n[11] * b.n[13],
		a.n[8] * b.n[2] + a.n[9] * b.n[6] + a.n[10] * b.n[10] + a.n[11] * b.n[14],
		a.n[8] * b.n[3] + a.n[9] * b.n[7] + a.n[10] * b.n[11] + a.n[11] * b.n[15],
		a.n[12] * b.n[0] + a.n[13] * b.n[4] + a.n[14] * b.n[8] + a.n[15] * b.n[12],
		a.n[12] * b.n[1] + a.n[13] * b.n[5] + a.n[14] * b.n[9] + a.n[15] * b.n[13],
		a.n[12] * b.n[2] + a.n[13] * b.n[6] + a.n[14] * b.n[10] + a.n[15] * b.n[14],
		a.n[12] * b.n[3] + a.n[13] * b.n[7] + a.n[14] * b.n[11] + a.n[15] * b.n[15]);
}

template <class T>
inline Mat4<T> operator *(const Mat4<T>& a, const double d) {
	return Mat4<T>(a.n[0] * d, a.n[1] * d, a.n[2] * d, a.n[3] * d,
		a.n[4] * d, a.n[5] * d, a.n[6] * d, a.n[7] * d,
		a.n[8] * d, a.n[9] * d, a.n[10] * d, a.n[11] * d,
		a.n[12] * d, a.n[13] * d, a.n[14] * d, a.n[15] * d);
}

template <class T>
inline Mat4<T> operator *(const double d, const Mat4<T>& a) {
	return Mat4<T>(a.n[0] * d, a.n[1] * d, a.n[2] * d, a.n[3] * d,
		a.n[4] * d, a.n[5] * d, a.n[6] * d, a.n[7] * d,
		a.n[8] * d, a.n[9] * d, a.n[10] * d, a.n[11] * d,
		a.n[12] * d, a.n[13] * d, a.n[14] * d, a.n[15] * d);
}

template <class T>
inline Mat4<T> operator /(const Mat4<T>& a, const double d) {
	return Mat4<T>(a.n[0] / d, a.n[1] / d, a.n[2] / d, a.n[3] / d,
		a.n[4] / d, a.n[5] / d, a.n[6] / d, a.n[7] / d,
		a.n[8] / d, a.n[9] / d, a.n[10] / d, a.n[11] / d,
		a.n[12] / d, a.n[13] / d, a.n[14] / d, a.n[15] / d);
}

template <class T>
inline bool operator ==(const Mat4<T>& a, const Mat4<T>& b) {
	return !memcmp(a.n, b.n, 16 * sizeof(T));
}

template <class T>
inline bool operator !=(const Mat4<T>& a, const Mat4<T>& b) {
	return memcmp(a.n, b.n, 16 * sizeof(T));
}

#endif


/*#ifndef __MATRIX_HEADER__
#define __MATRIX_HEADER__

//==========[ Forward References ]=============================================

template <class T> class Vec;
template <class T> class Vec3;
template <class T> class Vec4;
template <class T> class Mat3;
template <class T> class Mat4;

//==========[ class Mat3 ]=====================================================

template <class T>
class Mat3 {

	//---[ Private Variable Declarations ]-----------------

		// matrix elements in row major order
	T		n[9];

public:

	//---[ Constructors ]----------------------------------

	Mat3()
		{ memset(n,0,9*sizeof(T)); n[0]=1; n[3]=1; n[6]=1; }
	Mat3( T n0, T n1, T n2, T n3, T n4, T n5, T n6, T n7, T n8 )
		{ n[0]=n0; n[1]=n1; n[2]=n2;
		  n[3]=n3; n[4]=n4; n[5]=n5;
		  n[6]=n6; n[7]=n7; n[8]=n8; }
	Mat3( const Mat3<T>& m )
		{ memcpy(n,m.n,9*sizeof(T)); }

	//---[ Equal Operators ]-------------------------------

	Mat3<T>& operator =( const Mat3<T>& m )
		{ memcpy(n,m.n,9*sizeof(T)); return *this; }
	Mat3<T>& operator +=( const Mat3<T>& m )
		{ n[0]+=m.n[0]; n[1]+=m.n[1]; n[2]+=m.n[2]; n[3]+=m.n[3]; n[4]+=m.n[4]; n[5]+=m.n[5]; n[6]+=m.n[6]; n[7]+=m.n[7]; n[8]+=m.n[8]; return *this; }
	Mat3<T>& operator -=( const Mat3<T>& m )
		{ n[0]-=m.n[0]; n[1]-=m.n[1]; n[2]-=m.n[2]; n[3]-=m.n[3]; n[4]-=m.n[4]; n[5]-=m.n[5]; n[6]-=m.n[6]; n[7]-=m.n[7]; n[8]-=m.n[8]; return *this; }
	Mat3<T>& operator *=( const T d )
		{ n[0]*=d; n[1]*=d; n[2]*=d; n[3]*=d; n[4]*=d; n[5]*=d; n[6]*=d; n[7]*=d; n[8]*=d; return *this; }
	Mat3<T>& operator /=( const T d )
		{ n[0]/=d; n[1]/=d; n[2]/=d; n[3]/=d; n[4]/=d; n[5]/=d; n[6]/=d; n[7]/=d; n[8]/=d; return *this; }

	//---[ Access Operators ]------------------------------

	T* operator []( int i )
		{ return &n[i*3]; }
	const T* operator []( int i ) const
		{ return &n[i*3]; }

	//---[ Ordering Methods ]------------------------------

	Mat3<T> transpose() const { return Mat3<T>(n[0],n[3],n[6],n[1],n[4],n[7],n[2],n[5],n[8]) }
	double trace() const { return n[0]+n[4]+n[8]; }

	//---[ GL Matrix ]-------------------------------------

	void getGLMatrix( T* mat ) const
	{ mat[0]=n[0]; mat[1]=n[3]; mat[2]=n[6];
	  mat[3]=n[1]; mat[4]=n[4]; mat[5]=n[7];
	  mat[6]=n[2]; mat[7]=n[5]; mat[8]=n[8]; }

	//---[ Transformation Matrices ]-----------------------

	static Mat3<T> createRotation( T angle, float x, float y );
	static Mat3<T> createTranslation( T x, T y );
	static Mat3<T> createScale( T sx, T sy );
	static Mat3<T> createShear( T shx, T shy );

	//---[ Friend Methods ]--------------------------------

#if _MSC_VER >= 1300

		template <class U> friend Mat3<U> operator -( const Mat3<U>& a );
	template <class U> friend Mat3<U> operator +( const Mat3<U>& a, const Mat3<U>& b );
	template <class U> friend Mat3<U> operator -( const Mat3<U>& a, const Mat3<U>& b );
	template <class U> friend Mat3<U> operator *( const Mat3<U>& a, const Mat3<U>& b );
	template <class U> friend Mat3<U> operator *( const Mat3<U>& a, const double d );
	template <class U> friend Mat3<U> operator *( const double d, const Mat3<U>& a );
	template <class U> friend Mat3<U> operator /( const Mat3<U>& a, const double d );
	template <class U> friend bool operator ==( const Mat3<U>& a, const Mat3<U>& b );
	template <class U> friend bool operator !=( const Mat3<U>& a, const Mat3<U>& b );

#else // _MSC_VER >= 1300

		friend Mat3<T> operator -( const Mat3<T>& a );
	friend Mat3<T> operator +( const Mat3<T>& a, const Mat3<T>& b );
	friend Mat3<T> operator -( const Mat3<T>& a, const Mat3<T>& b );
	friend Mat3<T> operator *( const Mat3<T>& a, const Mat3<T>& b );
	friend Mat3<T> operator *( const Mat3<T>& a, const double d );
	friend Mat3<T> operator *( const double d, const Mat3<T>& a );
	friend Mat3<T> operator /( const Mat3<T>& a, const double d );
	friend bool operator ==( const Mat3<T>& a, const Mat3<T>& b );
	friend bool operator !=( const Mat3<T>& a, const Mat3<T>& b );

#endif
};

typedef Mat3<int> Mat3i;
typedef Mat3<float> Mat3f;
typedef Mat3<double> Mat3d;

//==========[ class Mat4 ]=====================================================

template <class T>
class Mat4 {

	//---[ Private Variable Declarations ]-----------------
public:
		// matrix elements in row-major order
	T		n[16];



	bool isZero() { return n[0]==0&&n[1]==0&&n[2]==0&&n[3]==0&&n[4]==0&&n[5]==0&&n[6]==0&&n[7]==0&&n[8]==0&&n[9]==0&&n[10]==0&&n[11]==0&&n[12]==0&&n[13]==0&&n[14]==0&&n[15]==0; }

	//---[ Constructors ]----------------------------------

	Mat4()
		{ memset(n,0,16*sizeof(T)); n[0]=1;n[5]=1;n[10]=1;n[15]=1; }
	Mat4( T n0, T n1, T n2, T n3, T n4, T n5, T n6, T n7, T n8, T n9, T n10, T n11, T n12, T n13, T n14, T n15 )
		{ n[ 0]=n0 ; n[ 1]=n1 ; n[ 2]=n2 ; n[ 3]=n3 ;
		  n[ 4]=n4 ; n[ 5]=n5 ; n[ 6]=n6 ; n[ 7]=n7 ;
		  n[ 8]=n8 ; n[ 9]=n9 ; n[10]=n10; n[11]=n11;
		  n[12]=n12; n[13]=n13; n[14]=n14; n[15]=n15; }
	Mat4( const Mat4<T>& m )
		{ memcpy(n,m.n,16*sizeof(T)); }

	//---[ Equal Operators ]-------------------------------

	Mat4<T>& operator =( const Mat4<T>& m )
		{ memcpy(n,m.n,16*sizeof(T)); return *this; }
	Mat4<T>& operator +=( const Mat4<T>& m )
		{ n[ 0]+=m.n[ 0]; n[ 1]+=m.n[ 1]; n[ 2]+=m.n[ 2]; n[ 3]+=m.n[ 3];
		  n[ 4]+=m.n[ 4]; n[ 5]+=m.n[ 5]; n[ 6]+=m.n[ 6]; n[ 7]+=m.n[ 7];
		  n[ 8]+=m.n[ 8]; n[ 9]+=m.n[ 9]; n[10]+=m.n[10]; n[11]+=m.n[11];
		  n[12]+=m.n[12]; n[13]+=m.n[13]; n[14]+=m.n[14]; n[15]+=m.n[15];
		  return *this; }
	Mat4<T>& operator -=( const Mat4<T>& m )
		{ n[ 0]-=m.n[ 0]; n[ 1]-=m.n[ 1]; n[ 2]-=m.n[ 2]; n[ 3]-=m.n[ 3];
		  n[ 4]-=m.n[ 4]; n[ 5]-=m.n[ 5]; n[ 6]-=m.n[ 6]; n[ 7]-=m.n[ 7];
		  n[ 8]-=m.n[ 8]; n[ 9]-=m.n[ 9]; n[10]-=m.n[10]; n[11]-=m.n[11];
		  n[12]-=m.n[12]; n[13]-=m.n[13]; n[14]-=m.n[14]; n[15]-=m.n[15];
		  return *this; }
	Mat4<T>& operator *=( const T d )
		{ n[ 0]*=d; n[ 1]*=d; n[ 2]*=d; n[ 3]*=d;
		  n[ 4]*=d; n[ 5]*=d; n[ 6]*=d; n[ 7]*=d;
		  n[ 8]*=d; n[ 9]*=d; n[10]*=d; n[11]*=d;
		  n[12]*=d; n[13]*=d; n[14]*=d; n[15]*=d;
		  return *this; }
	Mat4<T>& operator /=( const T d )
		{ n[ 0]/=d; n[ 1]/=d; n[ 2]/=d; n[ 3]/=d;
		  n[ 4]/=d; n[ 5]/=d; n[ 6]/=d; n[ 7]/=d;
		  n[ 8]/=d; n[ 9]/=d; n[10]/=d; n[11]/=d;
		  n[12]/=d; n[13]/=d; n[14]/=d; n[15]/=d;
		  return *this; }

	//---[ Access Operators ]------------------------------

	T* operator []( int i )
		{ return &n[i*4]; }
	const T* operator []( int i ) const
		{ return &n[i*4]; }

	//---[ Ordering Methods ]------------------------------

	Mat4<T> transpose() const
		{ return Mat4<T>(n[ 0],n[ 4],n[ 8],n[12],
						 n[ 1],n[ 5],n[ 9],n[13],
						 n[ 2],n[ 6],n[10],n[14],
						 n[ 3],n[ 7],n[11],n[15]); }
	double trace() const { return n[0]+n[5]+n[10]+n[15]; }

	Mat4<T> inverse() const {
		Mat4<T>		a(*this);
		Mat4<T>		b;

		int			i, j, k, l;

		for( i=0;i<4;i++ ) {
			j = i;
			for( k=i+1;k<4;k++ ) {
				if( fabs(a[k][i]) > fabs(a[j][i]) )
					j = k;
			}

			a.swapRows(i,j);
			b.swapRows(i,j);

			if( a[i][i] == 0.0 )
				return Mat4<T>();

			float diag = a[i][i];
			for( k=0;k<4;k++ ) {
				a[i][k] /= diag;
				b[i][k] /= diag;
			}

			for( k=0;k<4;k++ ) {
				if( k != i ) {
					float aki = a[k][i];
					for( l=0;l<4;l++ ) {
						a[k][l] -= aki * a[i][l];
						if( fabs(a[k][l]) < 0.00000001 ) a[k][l] = 0.0;
						b[k][l] -= aki * b[i][l];
						if( fabs(b[k][l]) < 0.00000001 ) b[k][l] = 0.0;
					}
				}
			}
		}

		return b;
	}

	void swapRows(int a, int b) {
		T		temp;

		for( int i=0;i<4;i++ ) {
			temp = n[a*4+i];
			n[a*4+i] = n[b*4+i];
			n[b*4+i] = temp;
		}
	}

	//---[ GL Matrix ]-------------------------------------

	void getGLMatrix( T* mat ) const
	{ mat[ 0]=n[ 0]; mat[ 1]=n[ 4]; mat[ 2]=n[ 8]; mat[ 3]=n[12];
	  mat[ 4]=n[ 1]; mat[ 5]=n[ 5]; mat[ 6]=n[ 9]; mat[ 7]=n[13];
	  mat[ 8]=n[ 2]; mat[ 9]=n[ 6]; mat[10]=n[10]; mat[11]=n[14];
	  mat[12]=n[ 3]; mat[13]=n[ 7]; mat[14]=n[11]; mat[15]=n[15]; }

	//---[ Transformation Matrices ]-----------------------

	static Mat4<T> createRotation( T angle, float x, float y, float z );
	static Mat4<T> createTranslation( T x, T y, T z );
	static Mat4<T> createScale( T sx, T sy, T sz );
	static Mat4<T> createShear( T shx, T shy, T shz );

	//---[ Friend Methods ]--------------------------------

#if _MSC_VER >= 1300

	template <class U> friend Mat4<U> operator -( const Mat4<U>& a );
	template <class U> friend Mat4<U> operator +( const Mat4<U>& a, const Mat4<U>& b );
	template <class U> friend Mat4<U> operator -( const Mat4<U>& a, const Mat4<U>& b );
	template <class U> friend Mat4<U> operator *( const Mat4<U>& a, const Mat4<U>& b );
	template <class U> friend Mat4<U> operator *( const Mat4<U>& a, const double d );
	template <class U> friend Mat4<U> operator *( const double d, const Mat4<U>& a );
	template <class U> friend Vec3<U> operator *( const Mat4<U>& a, const Vec3<U>& b );
	template <class U> friend Mat4<U> operator /( const Mat4<U>& a, const double d );
	template <class U> friend bool operator ==( const Mat4<U>& a, const Mat4<U>& b );
	template <class U> friend bool operator !=( const Mat4<U>& a, const Mat4<U>& b );

#else // _MSC_VER >= 1300

	friend Mat4<T> operator -( const Mat4<T>& a );
	friend Mat4<T> operator +( const Mat4<T>& a, const Mat4<T>& b );
	friend Mat4<T> operator -( const Mat4<T>& a, const Mat4<T>& b );
	friend Mat4<T> operator *( const Mat4<T>& a, const Mat4<T>& b );
	friend Mat4<T> operator *( const Mat4<T>& a, const double d );
	friend Mat4<T> operator *( const double d, const Mat4<T>& a );
	friend Vec3<T> operator *( const Mat4<T>& a, const Vec3<T>& b );
	friend Mat4<T> operator /( const Mat4<T>& a, const double d );
	friend bool operator ==( const Mat4<T>& a, const Mat4<T>& b );
	friend bool operator !=( const Mat4<T>& a, const Mat4<T>& b );

#endif // _MSC_VER >= 1300

};

typedef Mat4<int> Mat4i;
typedef Mat4<float> Mat4f;
typedef Mat4<double> Mat4d;

//==========[ Inline Method Definitions (Matrix) ]=============================

template <class T>
inline Mat3<T> Mat3<T>::createRotation( T angle, float x, float y ) {
	Mat3<T> rot;

	return rot;
}

template <class T>
inline Mat3<T> Mat3<T>::createTranslation( T x, T y ) {
	Mat3<T> trans;

	return trans;
}

template <class T>
inline Mat3<T> Mat3<T>::createScale( T sx, T sy ) {
	Mat3<T> scale;

	return scale;
}

template <class T>
inline Mat3<T> Mat3<T>::createShear( T shx, T shy ) {
	Mat3<T> shear;

	return shear;
}

template <class T>
inline Mat3<T> operator -( const Mat3<T>& a ) {
	return Mat3<T>( -a.n[0], -a.n[1], -a.n[2],
					-a.n[3], -a.n[4], -a.n[5],
					-a.n[6], -a.n[7], -a.n[8] );
}

template <class T>
inline Mat3<T> operator +( const Mat3<T>& a, const Mat3<T>& b ) {
	return Mat3<T>( a.n[0]+b.n[0], a.n[1]+b.n[1], a.n[2]+b.n[2],
					a.n[3]+b.n[3], a.n[4]+b.n[4], a.n[5]+b.n[5],
					a.n[6]+b.n[6], a.n[7]+b.n[7], a.n[8]+b.n[8],);
}

template <class T>
inline Mat3<T> operator -( const Mat3<T>& a, const Mat3<T>& b) {
	return Mat3<T>( a.n[0]-b.n[0], a.n[1]-b.n[1], a.n[2]-b.n[2],
					a.n[3]-b.n[3], a.n[4]-b.n[4], a.n[5]-b.n[5],
					a.n[6]-b.n[6], a.n[7]-b.n[7], a.n[8]-b.n[8],);
}

template <class T>
inline Mat3<T> operator *( const Mat3<T>& a, const Mat3<T>& b ) {
	return Mat3<T>( a.n[0]*b.n[0]+a.n[1]*b.n[3]+a.n[2]*b.n[6],
					a.n[0]*b.n[1]+a.n[1]*b.n[4]+a.n[2]*b.n[7],
					a.n[0]*b.n[2]+a.n[1]*b.n[5]+a.n[2]*b.n[8],
					a.n[3]*b.n[0]+a.n[4]*b.n[3]+a.n[5]*b.n[6],
					a.n[3]*b.n[1]+a.n[4]*b.n[4]+a.n[5]*b.n[7],
					a.n[3]*b.n[2]+a.n[4]*b.n[5]+a.n[5]*b.n[8],
					a.n[6]*b.n[0]+a.n[7]*b.n[3]+a.n[8]*b.n[6],
					a.n[6]*b.n[1]+a.n[7]*b.n[4]+a.n[8]*b.n[7],
					a.n[6]*b.n[2]+a.n[7]*b.n[5]+a.n[8]*b.n[8] );
}

template <class T>
inline Mat3<T> operator *( const Mat3<T>& a, const double d ) {
	return Mat3<T>( a.n[0]*d, a.n[1]*d, a.n[2]*d,
					a.n[3]*d, a.n[4]*d, a.n[5]*d,
					a.n[6]*d, a.n[7]*d, a.n[8]*d );
}

template <class T>
inline Mat3<T> operator *( const double d, const Mat3<T>& a ) {
	return Mat3<T>( a.n[0]*d, a.n[1]*d, a.n[2]*d,
					a.n[3]*d, a.n[4]*d, a.n[5]*d,
					a.n[6]*d, a.n[7]*d, a.n[8]*d );
}

template <class T>
inline Mat3<T> operator /( const Mat3<T>& a, const double d ) {
	return Mat3<T>( a.n[0]/d, a.n[1]/d, a.n[2]/d,
					a.n[3]/d, a.n[4]/d, a.n[5]/d,
					a.n[6]/d, a.n[7]/d, a.n[8]/d );
}

template <class T>
inline bool operator ==( const Mat3<T>& a, const Mat3<T>& b ) {
	return !memcmp( a.n, b.n, 9*sizeof(T) );
}

template <class T>
inline bool operator !=( const Mat3<T>& a, const Mat3<T>& b ) {
	return memcmp( a.n, b.n, 9*sizeof(T) );
}

template <class T>
inline void swap(Mat3<T>& a, Mat3<T>& b) {
//	swap( a.v[0], b.v[0] );
//	swap( a.v[1], b.v[1] );
//	swap( a.v[2], b.v[2] );
}

template <class T>
inline Mat4<T> Mat4<T>::createRotation( T angle, float x, float y, float z ) {
	Mat4<T> rot;

	return rot;
}

template <class T>
inline Mat4<T> Mat4<T>::createTranslation( T x, T y, T z ) {
	Mat4<T> trans;

	return trans;
}

template <class T>
inline Mat4<T> Mat4<T>::createScale( T sx, T sy, T sz ) {
	Mat4<T> scale;

	return scale;
}

template <class T>
inline Mat4<T> Mat4<T>::createShear( T shx, T shy, T shz ) {
	Mat4<T> shear;

	return shear;
}

template <class T>
inline Mat4<T> operator -( const Mat4<T>& a ) {
	return Mat4<T>( -a.n[ 0], -a.n[ 1], -a.n[ 2], -a.n[ 3],
					-a.n[ 4], -a.n[ 5], -a.n[ 6], -a.n[ 7],
					-a.n[ 8], -a.n[ 9], -a.n[10], -a.n[11],
					-a.n[12], -a.n[13], -a.n[14], -a.n[15] );
}

template <class T>
inline Mat4<T> operator +( const Mat4<T>& a, const Mat4<T>& b ) {
	return Mat4<T>( a.n[ 0]+b.n[ 0], a.n[ 1]+b.n[ 1], a.n[ 2]+b.n[ 2], a.n[ 3]+b.n[ 3],
					a.n[ 4]+b.n[ 4], a.n[ 5]+b.n[ 5], a.n[ 6]+b.n[ 6], a.n[ 7]+b.n[ 7],
					a.n[ 8]+b.n[ 8], a.n[ 9]+b.n[ 9], a.n[10]+b.n[10], a.n[11]+b.n[11],
					a.n[12]+b.n[12], a.n[13]+b.n[13], a.n[14]+b.n[14], a.n[15]+b.n[15] );
}

template <class T>
inline Mat4<T> operator -( const Mat4<T>& a, const Mat4<T>& b ) {
	return Mat4<T>( a.n[ 0]-b.n[ 0], a.n[ 1]-b.n[ 1], a.n[ 2]-b.n[ 2], a.n[ 3]-b.n[ 3],
					a.n[ 4]-b.n[ 4], a.n[ 5]-b.n[ 5], a.n[ 6]-b.n[ 6], a.n[ 7]-b.n[ 7],
					a.n[ 8]-b.n[ 8], a.n[ 9]-b.n[ 9], a.n[10]-b.n[10], a.n[11]-b.n[11],
					a.n[12]-b.n[12], a.n[13]-b.n[13], a.n[14]-b.n[14], a.n[15]-b.n[15] );
}

template <class T>
inline Mat4<T> operator *( const Mat4<T>& a, const Mat4<T>& b ) {
	return Mat4<T>( a.n[ 0]*b.n[ 0]+a.n[ 1]*b.n[ 4]+a.n[ 2]*b.n[ 8]+a.n[ 3]*b.n[12],
					a.n[ 0]*b.n[ 1]+a.n[ 1]*b.n[ 5]+a.n[ 2]*b.n[ 9]+a.n[ 3]*b.n[13],
					a.n[ 0]*b.n[ 2]+a.n[ 1]*b.n[ 6]+a.n[ 2]*b.n[10]+a.n[ 3]*b.n[14],
					a.n[ 0]*b.n[ 3]+a.n[ 1]*b.n[ 7]+a.n[ 2]*b.n[11]+a.n[ 3]*b.n[15],
					a.n[ 4]*b.n[ 0]+a.n[ 5]*b.n[ 4]+a.n[ 6]*b.n[ 8]+a.n[ 7]*b.n[12],
					a.n[ 4]*b.n[ 1]+a.n[ 5]*b.n[ 5]+a.n[ 6]*b.n[ 9]+a.n[ 7]*b.n[13],
					a.n[ 4]*b.n[ 2]+a.n[ 5]*b.n[ 6]+a.n[ 6]*b.n[10]+a.n[ 7]*b.n[14],
					a.n[ 4]*b.n[ 3]+a.n[ 5]*b.n[ 7]+a.n[ 6]*b.n[11]+a.n[ 7]*b.n[15],
					a.n[ 8]*b.n[ 0]+a.n[ 9]*b.n[ 4]+a.n[10]*b.n[ 8]+a.n[11]*b.n[12],
					a.n[ 8]*b.n[ 1]+a.n[ 9]*b.n[ 5]+a.n[10]*b.n[ 9]+a.n[11]*b.n[13],
					a.n[ 8]*b.n[ 2]+a.n[ 9]*b.n[ 6]+a.n[10]*b.n[10]+a.n[11]*b.n[14],
					a.n[ 8]*b.n[ 3]+a.n[ 9]*b.n[ 7]+a.n[10]*b.n[11]+a.n[11]*b.n[15],
					a.n[12]*b.n[ 0]+a.n[13]*b.n[ 4]+a.n[14]*b.n[ 8]+a.n[15]*b.n[12],
					a.n[12]*b.n[ 1]+a.n[13]*b.n[ 5]+a.n[14]*b.n[ 9]+a.n[15]*b.n[13],
					a.n[12]*b.n[ 2]+a.n[13]*b.n[ 6]+a.n[14]*b.n[10]+a.n[15]*b.n[14],
					a.n[12]*b.n[ 3]+a.n[13]*b.n[ 7]+a.n[14]*b.n[11]+a.n[15]*b.n[15] );
}

template <class T>
inline Mat4<T> operator *( const Mat4<T>& a, const double d ) {
	return Mat4<T>( a.n[ 0]*d, a.n[ 1]*d, a.n[ 2]*d, a.n[ 3]*d,
					a.n[ 4]*d, a.n[ 5]*d, a.n[ 6]*d, a.n[ 7]*d,
					a.n[ 8]*d, a.n[ 9]*d, a.n[10]*d, a.n[11]*d,
					a.n[12]*d, a.n[13]*d, a.n[14]*d, a.n[15]*d );
}

template <class T>
inline Mat4<T> operator *( const double d, const Mat4<T>& a ) {
	return Mat4<T>( a.n[ 0]*d, a.n[ 1]*d, a.n[ 2]*d, a.n[ 3]*d,
					a.n[ 4]*d, a.n[ 5]*d, a.n[ 6]*d, a.n[ 7]*d,
					a.n[ 8]*d, a.n[ 9]*d, a.n[10]*d, a.n[11]*d,
					a.n[12]*d, a.n[13]*d, a.n[14]*d, a.n[15]*d );
}

template <class T>
inline Mat4<T> operator /( const Mat4<T>& a, const double d ) {
	return Mat4<T>( a.n[ 0]/d, a.n[ 1]/d, a.n[ 2]/d, a.n[ 3]/d,
					a.n[ 4]/d, a.n[ 5]/d, a.n[ 6]/d, a.n[ 7]/d,
					a.n[ 8]/d, a.n[ 9]/d, a.n[10]/d, a.n[11]/d,
					a.n[12]/d, a.n[13]/d, a.n[14]/d, a.n[15]/d );
}

template <class T>
inline bool operator ==( const Mat4<T>& a, const Mat4<T>& b ) {
	return !memcmp(a.n,b.n,16*sizeof(T));
}

template <class T>
inline bool operator !=( const Mat4<T>& a, const Mat4<T>& b ) {
	return memcmp(a.n,b.n,16*sizeof(T));
}

#endif*/

