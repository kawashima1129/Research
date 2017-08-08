/*注意：テンプレート関数の定義と実装はヘッダファイルに書かなければならない*/

#include<stdio.h>


template <class type>
class MemoryClass
{
public:
	type* Get1Array(int num1);
	type** Get2Array(int num1, int num2);
	type*** Get3Array(int num1, int num2, int num3);

	void Free1Array(type* p);
	void Free2Array(type** p, int num1);
	void Free3Array(type*** p, int num1, int num2);
};



/*メモリの動的確保*/
template<class type>
type* MemoryClass<type>::Get1Array(int num1){
	type *p;
	p = new type[num1];

	return p;
}


template<class type>
type** MemoryClass<type>::Get2Array(int num1, int num2){
	type **p;
	p = new type*[num1];

	for (int i = 0; i < num1; i++){
		p[i] = new type[num2];
	}

	return p;
}

template<class type>
type*** MemoryClass<type>::Get3Array(int num1, int num2, int num3)
{
	type ***p;
	p = new type**[num1];

	for (int i = 0; i < num1; i++){
		p[i] = new type*[num2];
		for (int j = 0; j < num2; j++){
			p[i][j] = new type[num3];
		}
	}

	return p;
}



/*メモリの解放*/
template<class type>
void MemoryClass<type>::Free1Array(type* p){
	delete[] p;
}

template<class type>
void MemoryClass<type>::Free2Array(type** p, int num1){
	if (p != NULL){
		for (int i = 0; i < num1; i++){
			delete[] p[i];
		}
		delete[] p;
	}
}

template<class type>
void MemoryClass<type>::Free3Array(type*** p, int num1, int num2){
	if (p != NULL){
		for (int i = 0; i < num1; i++){
			for (int j = 0; j < num2; j++){
				delete[] p[i][j];
			}
			delete[] p[i];
		}
		delete[] p;
	}
}