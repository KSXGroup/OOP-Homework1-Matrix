#ifndef SJTU_MATRIX_HPP
#define SJTU_MATRIX_HPP
#include <iostream>
#include <vector>
#include <memory.h>
#include <functional>
namespace sjtu
{
	static void throw_invalid_msg(){
		throw std::invalid_argument("error!");
	}
	template <class T>
	class Matrix
	{
	private:
		T *data = nullptr;
		size_t matRow = 0, matColumn = 0;
		std::vector<Matrix<T>*> subs;
		// your private member variables here.
		
	public:
		
		Matrix() = default;
		
		Matrix(size_t n, size_t m, T _init = T())
		{
			matRow = n;
			matColumn = m;
			//if(data) delete [] data;
			data = new T[n * m];
			for(int i = 0; i < matRow * matColumn; ++i){
				data[i] = _init;
			}
		}
		
		explicit Matrix(std::pair<size_t, size_t> sz, T _init = T())
		{
			matRow = sz.first;
			matColumn = sz.second;
			data = new T[matRow * matColumn];
			for(int i = 0; i < matColumn * matRow ; ++i){
				data[i] = _init;
			}
		}
		
		Matrix(const Matrix &o)
		{
			matRow = o.matRow;
			matColumn = o.matColumn;
			//if(data) delete [] data;
			data = new T[matRow * matColumn];
			for(int i = 0;i < matRow ; ++i){
				for(int j = 0; j < matColumn; ++j){
					(*this)(i,j) = T(o(i,j));
				}
			}
		}
		
		template <class U>
		Matrix(const Matrix<U> &o)
		{
			matRow = o.rowLength();
			matColumn = o.columnLength();
			data = new T[matRow * matColumn];
			for(int i = 0; i < matRow; ++i){
				for(int j = 0; j < matColumn; ++j){
					data[i * matColumn + j] = T(o(i,j));
				}
			}
		}
		
		Matrix &operator=(const Matrix &o)
		{
			if(this == &o){
				return *this;
			}
			matRow = o.matRow;
			matColumn = o.matColumn;
			T *tpt = new T[matRow * matColumn];
			if(data != nullptr){
				delete [] data;
			}
			data = tpt;
			for(int i = 0;i < matRow ; ++i){
				for(int j = 0; j < matColumn; ++j){
					(*this)(i,j) = T(o(i,j));
				}
			}
			return *this;
		}
		
		template <class U>
		Matrix &operator=(const Matrix<U> &o)
		{
			matRow = o.rowLength();
			matColumn = o.columnLength();
			T *tpt = new T[matRow * matColumn];
			if(data != nullptr){
				delete [] data;
			}
			data = tpt;
			for(int i = 0;i < matRow ; ++i){
				for(int j = 0; j < matColumn; ++j){
					(*this)(i, j) = T(o(i,j));
				}
			}
			return *this;
		}
		
		/*Matrix(Matrix &&o) noexcept
		{
			matRow = std::move(o.matRow);
			matColumn = std::move(o.matColumn);
			data = std::move(o.data);
			o.data = nullptr;
		}
		
		Matrix &operator=(Matrix &&o) noexcept
		{
			//std::cout << "move" << std::endl;
			matRow = std::move(o.matRow);
			matColumn = std::move(o.matColumn);
			data = std::move(o.data);
			o.data = nullptr;
			return *this;
		}*/
		
		~Matrix(){
			//std::cerr << matRow <<" dec "<< matColumn << std::endl;
			if(data != nullptr){
				delete[] data;
			}
			data = nullptr;
			matRow = 0;
			matColumn = 0;
			for(int i = 0; i < subs.size(); ++i){
				delete subs[i];
			}
		}
		
		Matrix(std::initializer_list<std::initializer_list<T>> il)
		{
			size_t pos = 0;
			matRow = il.size();
			matColumn = il.begin() -> size();
			data = new T[matRow * matColumn];
			for(auto rowIt = il.begin(); rowIt != il.end(); ++rowIt){
				for(auto columnIt = rowIt -> begin(); columnIt != rowIt -> end(); ++columnIt){
					data[pos++] = *columnIt;
				}
			}
		}
		
	public:
		size_t rowLength() const {
			return matRow;
		}
		
		size_t columnLength() const { 
			return matColumn;
		}
		
		void resize(size_t _n, size_t _m, T _init = T())
		{
			//TODO
		}
		
		void resize(std::pair<size_t, size_t> sz, T _init = T())
		{
			//TODO
		}
		
		std::pair<size_t, size_t> size() const
		{
			return std::pair<size_t, size_t>(matRow, matColumn);
		};
		
		void clear()
		{
			if (data) delete[] data;
			data = nullptr;
			matRow = 0;
			matColumn = 0;
		}
		
	public:
		const T &operator()(size_t i, size_t j) const
		{
			return data[i * matColumn + j];
		}
		
		T &operator()(size_t i, size_t j)
		{
			return data[i * matColumn + j];
		}
		
		Matrix<T> row(size_t i) const
		{
			Matrix<T> tmp(1, matColumn);
			for(int k = 0; k < matColumn; ++k){
				tmp(0, k) = (*this)(i, k);
			}
			return tmp;
		}
		
		Matrix<T> column(size_t i) const
		{
			Matrix<T> tmp(matRow, 1);
			for(int k = 0; k < matRow; ++k){
				tmp(k, 0) = (*this)(k, i);
			}
			return tmp;		
		}
		
		
	public:
		template <class U>
		bool operator==(const Matrix<U> &o) const
		{
			if(matRow == o.rowLength() && matColumn == o.columnLength()){
				for(int i = 0; i < matRow; ++i){
					for(int j = 0; j < matColumn; ++j){
						if(data[i * matColumn + j] != o(i,j)){
							return 0;
						}
					}
				}
				return 1;
			}
			else{
				return 0;
			}
		}
		
		template <class U>
		bool operator!=(const Matrix<U> &o) const
		{
			if(matRow == o.rowLength() && matColumn == o.columnLength()){
				for(int i = 0; i < matRow; ++i){
					for(int j = 0; j < matColumn; ++j){
						if(data[i * matColumn + j] != o(i,j)){
							return 1;
						}
					}
				}
				return 0;
			}
			else{
				return 1;
			}
		}
		
		Matrix<T> operator-() const
		{
			if(matRow != rowLength() || matColumn != columnLength()){
				throw_invalid_msg();
			}
			Matrix<T> tmp = *this;
			for(int i = 0; i < matRow ; ++i){
				for(int j = 0; j < matColumn; ++j){
					tmp(i, j) = -data[i * matColumn + j];
				}
			}
			return tmp;
		}
		
		template <class U>
		Matrix &operator+=(const Matrix<U> &o)
		{
			if(matRow != o.rowLength() || matColumn != o.columnLength()){
				throw_invalid_msg();
			}
			for(int i = 0;i < matRow; ++i){
				for(int j = 0; j < matColumn; ++j){
					data[i * matColumn + j] = data[i * matColumn + j] + o(i ,j);
				}
			}
			return *this;
		}
		
		template <class U>
		Matrix &operator-=(const Matrix<U> &o)
		{
			if(matRow != o.rowLength() || matColumn != o.columnLength()){
				throw_invalid_msg();
			}
			for(int i = 0;i < matRow; ++i){
				for(int j = 0; j < matColumn; ++j){
					data[i * matColumn + j] = data[i * matColumn + j] - o(i ,j);
				}
			}
			return *this;
		}
		
		template <class U>
		Matrix &operator*=(const U &x)
		{
			for(int i = 0;i < matRow; ++i){
				for(int j = 0; j < matColumn; ++j){
					data[i * matColumn + j] = data[i * matColumn + j] * x;
				}
			}
			return *this;
		}
		
		Matrix<T> tran() const
		{
			if(data == nullptr || rowLength() == 0 || columnLength() == 0){
				Matrix<T> t;
				return t;
			}
			Matrix<T> tmp(matColumn, matRow);
			for(int i = 0; i < matRow; ++i){
				for(int j = 0; j < matColumn; ++j){
					tmp.data[j * matRow + i] = data[i * matColumn + j];
				}
			}
			return tmp;
		}
		
	public: // iterator
		class iterator
		{
		public:
			friend class Matrix<T>;
			using iterator_category = std::random_access_iterator_tag;
			using value_type        = T;
			using pointer           = T *;
			using reference         = T &;
			using size_type         = size_t;
			using difference_type   = std::ptrdiff_t;
			
			iterator() = default;
			
			iterator(const iterator &) = default;
			
			iterator &operator=(const iterator &) = default;
			
		private:
			pointer iter = nullptr;
			size_type max_pos = 0;
			size_type pos = 0;
			/*void throw_invalid_msg(){
				const std::invalid_argument &msg;
				throw msg;
			}*/
			
		public:
			difference_type operator-(const iterator &o)
			{
				if(iter != o.iter){
					throw_invalid_msg;
				}
				return (iter + pos) - (o.iter + o.pos);
			}
			
			iterator &operator+=(difference_type offset)
			{
				
				if(pos + offset > max_pos){
					throw_invalid_msg();
				}
				pos += offset;
				return *this;
			}
			
			iterator operator+(difference_type offset) const
			{
				if(pos + offset > max_pos){
					throw_invalid_msg();
				}
				Matrix<T>::iterator tmp;
				tmp.iter = iter;
				tmp.pos = pos + offset;
				tmp.max_pos = max_pos;
				return tmp;
			}
			
			iterator &operator-=(difference_type offset)
			{
				if(pos - offset < 0){
					throw_invalid_msg();
				}
				pos -= offset;
				return *this;			
			}
			
			iterator operator-(difference_type offset) const
			{
				if(pos - offset < 0){
					throw_invalid_msg();
				}
				Matrix<T>::iterator tmp;
				tmp.iter = iter;
				tmp.pos = pos - offset;
				tmp.pos = max_pos;
				return tmp;
			}
			
			iterator &operator++()
			{
				this -> operator+=(1);
			}
			
			iterator operator++(int)
			{
				if(pos + 1 > max_pos){
					throw_invalid_msg();
				}
				Matrix<T>::iterator tmp(*this);
				pos += 1;
				return tmp;
			}
			
			iterator &operator--()
			{
				this -> operator-=(1);
			}
			
			iterator operator--(int)
			{
				if(pos - 1 < 0){
					throw_invalid_msg();
				}
				Matrix<T>::iterator tmp;
				tmp = *this;
				pos -= 1;
				return tmp;
			}
			
			reference operator*() const
			{
				return *(iter + pos);
			}
			
			pointer operator->() const
			{
				return iter + pos;
			}
			
			bool operator==(const iterator &o) const
			{
				return (iter == o.iter && pos == o.pos && o.max_pos == max_pos) ? 1 : 0;
			}
			
			bool operator!=(const iterator &o) const
			{
				return !(operator==(o));
			}
		};
		
		iterator begin()
		{
			Matrix<T>::iterator tmp;
			tmp.iter = &data[0];
			tmp.pos = 0;
			tmp.max_pos = matRow * matColumn;
			return tmp;
		}
		
		iterator end()
		{
			Matrix<T>::iterator tmp;
			tmp.iter = &data[0];
			tmp.pos = matRow * matColumn;
			tmp.max_pos = matRow * matColumn;
			return tmp;
		}
		
		std::pair<iterator, iterator> subMatrix(std::pair<size_t, size_t> l, std::pair<size_t, size_t> r)
		{
			size_t pos = 0;
			if(l.first < r.first && l.second < r.second){
				Matrix<T> *tmp = new Matrix<T>(r.first - l.first + 1, r.second - l.second + 1);
				subs.push_back(tmp);
				for(int i = l.first; i <= r.first; ++i){
					for(int j = l.second; j <= r.second; ++j){
						tmp -> data[pos++] = (*this)(i, j);
					}
				}
				return std::pair<Matrix<T>::iterator, Matrix<T>::iterator>(subs[subs.size() - 1] -> begin(), subs[subs.size() - 1] -> end());
			}
			else{
				throw_invalid_msg();
			}
		}
		
};
}
//
namespace sjtu
{
	template <class T, class U>
	auto operator*(const Matrix<T> &mat, const U &x)
	{
		/*if(mat.rowLength() == 0 || mat.columnLength() == 0){
			Matrix<decltype(mat(0,0) * x)> t;
			return t;
		}*/
		Matrix<decltype(mat(0,0) * x)> tmp(mat);
		for(int i = 0;i < tmp.rowLength(); ++i){
			for(int j = 0;j < tmp.columnLength(); ++j){
				tmp(i,j) = tmp(i, j) * x;
			}
		}
		return tmp;
		
	};
	
	template <class T, class U>
	auto operator*(const U &x, const Matrix<T> &mat)
	{
		//std::cerr << "???" << std::endl;
		if(mat.rowLength() == 0 || mat.columnLength() == 0){
			Matrix<decltype(mat(0,0) * x)> t;
			return t;
		}
		Matrix<decltype(mat(0,0) * x)> tmp(mat);
		for(int i = 0;i < tmp.rowLength(); ++i){
			for(int j = 0;j < tmp.columnLength(); ++j){
				tmp(i,j) = tmp(i, j) * x;
			}
		}
		return tmp;
	};
	
	template <class U, class V>
	auto operator*(const Matrix<U> &a, const Matrix<V> &b)
	{
		if(a.columnLength() != b.rowLength()){
			throw_invalid_msg();
		}
		else{
			Matrix<decltype(a(0,0) * b(0,0))> tmp(a.rowLength(), b.columnLength());
			for(int i = 0;i < tmp.rowLength(); ++i){
				for(int j = 0;j < tmp.columnLength(); ++j){
					for(int k = 0; k < a.columnLength(); ++k){
						tmp(i, j) += a(i, k) * b(k, j);
					}
				}
			}
			return tmp;
		}
	};
	
	template <class U, class V>
	auto operator+(const Matrix<U> &a, const Matrix<V> &b)
	{
		if(a.rowLength() != b.rowLength() || a.columnLength() != b.columnLength()){
			throw_invalid_msg();
		}
		else{
			Matrix<decltype(U() + V())> tmp(a.rowLength(), a.columnLength());
			for(int i = 0; i < a.rowLength(); ++i){
				for(int j = 0;j < a.columnLength(); ++j){
					tmp(i, j) = a(i, j) + b(i, j);
				}
			}
			return tmp;
		}
	};
	
	template <class U, class V>
	auto operator-(const Matrix<U> &a, const Matrix<V> &b)
	{
		if(a.rowLength() != b.rowLength() || a.columnLength() != b.columnLength()){
			throw_invalid_msg();
		}
		else{
			Matrix<decltype(U() - V())> tmp(a.rowLength(), a.columnLength());
			for(int i = 0; i < a.rowLength(); ++i){
				for(int j = 0;j < a.columnLength(); ++j){
					tmp(i, j) = a(i, j) - b(i, j);
				}
			}
			return tmp;
		}
	};
	
}

#endif //SJTU_MATRIX_HPP

