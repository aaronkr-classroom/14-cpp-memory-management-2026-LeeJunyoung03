#pragma once
#pragma once
#ifndef GUARD_Ptr_h
#define GUARD_Ptr_h

#include<cstddef>
#include<stdexcept>
#include"Vec.h"	//추가

using namespace std;

template <class T> class Ptr {
public:
	//필요하면 조건에 따라 객체를 복사하는 새 멤버함수
	void make_unipue() {
		if (*refptr != 1) {
			--*refptr;
			refptr = new size_t(1);
			p = p ? clone(p) : 0;
		}
	}

	// 참조 카운트를 포인터처럼 관리
	Ptr() : p(0), refptr(new size_t(1)) { }
	Ptr(T* t) :p(t), refptr(new size_t(1)) { }
	Ptr(const Ptr& h) :p(h, p), refptr(h.refptr) {
		++*refptr;
	}
	//할당연산자
	Ptr& operator=(const Ptr&);
	~Ptr();	//소멸자

	//이전거ㅣ 같음(Handleclaas)
	operator bool() const { return p; }
	T& operator*() const {
		if (p) return *p;
		throw runtime_error("unboind Ptr!");
	}
	T* operator->() const {
		if (p) return p;
		throw runtime_error("unboind Ptr!");
	}
private:
	T* p;
	size_t* refptr;
};

//clone() 함수의 3개의 경우
template <class T>T* clone(const Vec<char>* vp) {
	return new Vec<char>(*vp);
}

template<class T>T* clone(const T* vp) {
	return tp->clone();
}
template<class T>
Ptr<T>& Ptr<T>::operator =(const Ptr& rhs) {
	++*rhs.refptr;	//참조 포인터 이동

	//상황에 따라 좌별을 할당 해제하고 포인터 소멸
	if (--*refptr == 0) {
		delete refptr;
		delete p;
	}

	//우변 값들을 복사
	refptr = rhs.refptr;
	p = rhs.p;

	return *this;
}

template<class T>
Ptr<T>::~Ptr() {
	if (--*refptr == 0) {
		delete refptr;
		delete p;
	}
}

#endif // !GUARD_Ref_handle_h
