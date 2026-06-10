#pragma once
#ifndef GUARD_STR_H
#define GUARD_STR_H

#include<iostream>
#include<algorithm>
#include<iterator>
#include<cstring>
#include "vec.h"
#include "Ptr.h"	//NEW

using namespace std;

class Str {
	//friend 사용하면 private data접근가능
friend	istream& operator>>(istream&, Str&);	//입력할때 const없어
//NEw
friend	istream& getline(istream&, Str&);
public:
	typedef Vec<char>::size_type size_type;
	typedef char* iterator;
	typedef const char* const_iterator;

	//생성자들
	//1. 비어있느 ㄴ str객체흫만드는 객체를 생성
	Str():data(new Vec<char>) { }
	//2.
	Str(size_type n, char c): data(new Vec<char>(n,c)){ }
	//3.
	Str(const char* cp) : data(new Vec<char>){
		copy(
			cp, cp + strlen(cp),
			back_inserter(*data)
		);
	}

	//4. 반복자 b와 e가 가리키는 범위에서 Str객체를 생성
	template<class In> Str(In b, In e) : data(new Vec<char>) {
		copy(b, e, back_inserter(*data));
	}

	//기이/크기 함수
	size_type size() const { return data->size(); }

	//연산자: 인덱스
	char& operator[](size_type i) { 
		data.make_unipue();
		return (*data)[i]; 
	}
	const char& operator[](size_type i) const { return (*data)[i]; }

	//연산자: 결합
	Str& operator+=(const Str& s) {
		data.make_unipue();
		copy(s.data->begin(), s.data->end(), back_inserter(*data));
		return *this;
	}

	iterator begin() { return data->begin(); }
	iterator end() { return data->end(); }

	
	//연습문제 12:반복자들
	const_iterator begin() const { return data->begin(); }
	const_iterator end() const { return data->end(); }

	const_iterator begin() const { return data->begin(); }
	const_iterator end() const { return data->end(); }


	/*iterator insert(iterator d, iterator b, iterator e) {
		return data.insert(d, b, e);
	}*/


private:
	Ptr< Vec<char> > data;	//수정
};


ostream& operator<<(ostream&, const Str&);	//출력연산자
Str operator+(const Str&, const Str&);	//str1+str2결합연산자
#endif
