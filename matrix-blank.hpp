#ifndef SJTU_MATRIX_HPP
#define SJTU_MATRIX_HPP
#include <bits/stdc++.h>
namespace sjtu
{
	template <class T>
	class Matrix
	{
	//using std::size_t;
	private:
		T *data = nullptr;
		size_t matRow = 0, matColumn = 0;
		// your private member variables here.
		
	public:
		Matrix() = default;
		
		Matrix(size_t n, size_t m, T _init = T())
		{
			matRow = n;
			matColumn = m;
			data = new T[matRow * matColumn + 1];
			for(int i = 0; i < matRow * matColumn + 1; ++i){
				data[i] = _init;
			}
		}
		
		explicit Matrix(std::pair<size_t, size_t> sz, T _init = T())
		{
			matRow = sz.first;
			matColumn = sz.second;
			data = new T[matRow * matColumn + 1];
			for(int i = 0; i < matColumn * matRow + 1; ++i){
				data[i] = _init;
			}
		}
		
		Matrix(const Matrix &o)
		{
			matRow = o.matRow;
			matColumn = o.matColumn;
			data = new T[matRow * matColumn + 1];
			memcpy(data, o.data, sizeof(T) * (matRow * matColumn + 1));
		}
		
		template <class U>
		Matrix(const Matrix<U> &o)
		{
			matRow = o.matRow;
			matColumn = o.matColumn;
			data = new T[matRow * matColumn + 1];
			for(int i = 0; i < matRow * matColumn + 1; ++i){
				data[i] = T(o.data[i]);
			}
		}
		
		Matrix &operator=(const Matrix &o)
		{
			matRow = o.matRow;
			matColumn = o.matColumn;
			memcpy(data, o.data, sizeof(T) * (matRow * matColumn + 1));
			return *this;
		}
		
		template <class U>
		Matrix &operator=(const Matrix<U> &o)
		{
			matRow = o.matRow;
			matColumn = o.matColumn;
			for(int i = 0;i < matRow * matColumn + 1; ++i){
				data[i] = T(o.data[i]);
			}
			return *this;
		}
		
		Matrix(Matrix &&o) noexcept
		{
			matRow = o.matRow;
			matColumn = o.matColumn;
			memcpy(data, o.data, sizeof(T) * (matRow * matColumn + 1));
		}
		
		Matrix &operator=(Matrix &&o) noexcept
		{
			matRow = o.matRow;
			matColumn = o.matColumn;
			memcpy(data, o.data, sizeof(T) * (matRow * matColumn + 1));
			return *this;
		}
		
		~Matrix(){
			delete [] data;
			matRow = 0;
			matColumn = 0;
		}
		
		Matrix(std::initializer_list<std::initializer_list<T>> il)
		{
			matRow = il.size();
			matColumn = il.begin() -> size();
			data = new T[matRow * matColumn + 1];
			
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
			delete [] data;
			matRow = 0;
			matColumn = 0;
		}
		
	public:
		const T &operator()(size_t i, size_t j) const
		{
			return data[i * matRow + j];
		}
		
		T &operator()(size_t i, size_t j)
		{
			return data[i * matRow + j];
		}
		
		Matrix<T> row(size_t i) const
		{
			Matrix<T> tmp;
			tmp.matRow = 1;
			tmp.matColumn = matColumn;
			for(int k = 0; k < matColumn; ++k){
				tmp(0, k) = data[i * matRow + k];
			}
		}
		
		Matrix<T> column(size_t i) const
		{
			
		}
		
		
	public:
		template <class U>
		bool operator==(const Matrix<U> &o) const
		{
			
		}
		
		template <class U>
		bool operator!=(const Matrix<U> &o) const
		{
			
		}
		
		Matrix operator-() const
		{
			
		}
		
		template <class U>
		Matrix &operator+=(const Matrix<U> &o)
		{
			
		}
		
		template <class U>
		Matrix &operator-=(const Matrix<U> &o)
		{
			
		}
		
		template <class U>
		Matrix &operator*=(const U &x)
		{
			
		}
		
		Matrix tran() const
		{
			
		}
		
	public: // iterator
		class iterator
		{
		public:
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

			
		public:
			difference_type operator-(const iterator &o)
			{
				
			}
			
			iterator &operator+=(difference_type offset)
			{
				
			}
			
			iterator operator+(difference_type offset) const
			{
				
			}
			
			iterator &operator-=(difference_type offset)
			{
				
			}
			
			iterator operator-(difference_type offset) const
			{
				
			}
			
			iterator &operator++()
			{
				
			}
			
			iterator operator++(int)
			{
				
			}
			
			iterator &operator--()
			{
				
			}
			
			iterator operator--(int)
			{
				
			}
			
			reference operator*() const
			{
				
			}
			
			pointer operator->() const
			{
				
			}
			
			bool operator==(const iterator &o) const
			{
				
			}
			
			bool operator!=(const iterator &o) const
			{
				
			}
		};
		
		iterator begin()
		{
			
		}
		
		iterator end()
		{
			
		}
		
		std::pair<iterator, iterator> subMatrix(std::pair<size_t, size_t> l, std::pair<size_t, size_t> r)
		{
			
		}
		
};
}
//
namespace sjtu
{
	template <class T, class U>
	auto operator*(const Matrix<T> &mat, const U &x)
	{
		
	};
	
	template <class T, class U>
	auto operator*(const U &x, const Matrix<T> &mat)
	{
		
	};
	
	template <class U, class V>
	auto operator*(const Matrix<U> &a, const Matrix<V> &b)
	{
		
	};
	
	template <class U, class V>
	auto operator+(const Matrix<U> &a, const Matrix<V> &b)
	{
		
	};
	
	template <class U, class V>
	auto operator-(const Matrix<U> &a, const Matrix<V> &b)
	{
		
	};
	
}

#endif //SJTU_MATRIX_HPP

