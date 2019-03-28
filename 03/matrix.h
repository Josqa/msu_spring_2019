#define SIZE rows * cols
class Matrix
{
public:
	int *matr;
	size_t rows, cols;
	Matrix(const size_t rows, const size_t cols)
	{ 
		matr = new int[SIZE]; 
		this->rows = rows;
		this->cols = cols;
	}
	~Matrix() { delete[] matr; }
	size_t getRows() { return rows; }
	size_t getColumns() { return cols; }
	Matrix& operator*= (int x)
	{
		for (size_t i = 0; i < SIZE; i++) matr[i] *= x;
		return *this;
	}

	void show()
	{
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < cols; j++)
				std::cout << matr[i * cols + j] << " ";
			std::cout << std::endl;
		}
	}

	bool operator==(const Matrix& other) const
	{
		if (cols != other.cols || rows != other.rows) return false;
		for (size_t i = 0; i < SIZE; i++)
		if (matr[i] != other.matr[i]) return false;
		return true;
	}

	bool operator!=(const Matrix& other) const
	{
		return !(*this == other);
	}

	class Proxy
	{
	private:
		int* data;
		size_t size;
	public:
		Proxy(int* data, size_t size) : data(data), size(size){}
		int operator[](size_t i) const{
			if (i >= size)
				throw std::out_of_range("");
			return data[i];
		}
		int& operator[](size_t i){
			if (i >= size)
				throw std::out_of_range("");
			return data[i];
		}
	};
	Proxy operator[](size_t i)
	{
		if (i >= rows)
			throw std::out_of_range("");
		return Proxy(matr + i * cols, cols);
	}
	const Proxy operator[](size_t i) const
	{
		if (i >= rows)
			throw std::out_of_range("");
		return Proxy(matr + i * cols, cols);
	}
};
