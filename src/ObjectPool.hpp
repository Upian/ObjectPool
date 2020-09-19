#ifndef __OBJECT_POOL_H__
#define __OBJECT_POOL_H__

/*
*	ObjectPool
*	class Temp : public ObjectPool<Temp, cnt> //cnt는 Pool에 초기화될 갯수
*	Temp* temp = new Temp; 

*	Func
	void* operator new(size_t size); -> 오브젝트풀에 있는 메모리 할당
	void operator delete(void* obj); -> 메모리를 오브젝트풀에 반환

	static void InitializeObjectPool(int size = _Cnt);
	static void Allocate(int size = _Cnt);
	static void Deallocate(int size = _Cnt);

	static const size_t ObjectCount() { return m_objectsCount; }
	static bool IsEmpty() { return (0 == m_objectsCount) ? true : false; }

*/
template<typename _Type, int _Cnt = 10>
class ObjectPool{
public:
	ObjectPool();
	virtual ~ObjectPool(){}

	void* operator new(size_t size);
//	void* operator new[](size_t size);
	void operator delete(void* obj);
//	void operator delete[](void* obj);

	static void InitializeObjectPool(int size = _Cnt);
	static void Allocate(int size = _Cnt);
	static void Deallocate(int size = _Cnt);

	static const size_t ObjectCount() { return m_objectsCount; }
	static bool IsEmpty() { return (0 == m_objectsCount) ? true : false; }
private:
	thread_local static _Type* m_objects;
 	thread_local static size_t m_objectsCount;
    
};
template<typename _Type, int _Cnt>
thread_local _Type* ObjectPool<_Type, _Cnt>::m_objects = nullptr;

template<typename _Type, int _Cnt>
thread_local size_t ObjectPool<_Type, _Cnt>::m_objectsCount = 0;
//--------------------------------------
template<typename _Type, int _Cnt>
ObjectPool<_Type, _Cnt>::ObjectPool(){
}

template<typename _Type, int _Cnt>
void* ObjectPool<_Type, _Cnt>::operator new(size_t size){
	if(nullptr == m_objects) //남아있는 메모리가 없을 경우 
		return malloc(size);

	_Type* obj = m_objects;
	m_objects = *((_Type**)m_objects);
	--m_objectsCount;
	return obj;
}

template<typename _Type, int _Cnt>
void ObjectPool<_Type, _Cnt>::operator delete(void* obj){
	*((_Type**)obj) = m_objects;
	m_objects = (_Type*)obj;
	++m_objectsCount;
}

template<typename _Type, int _Cnt>
void ObjectPool<_Type, _Cnt>::InitializeObjectPool(int size){
	_Type::Allocate(size);
}

template<typename _Type, int _Cnt>
void ObjectPool<_Type, _Cnt>::Allocate(int size){
	for(int i = 0; i < size; ++i){
		_Type* temp = static_cast<_Type*>(malloc(sizeof(_Type)));
		*((_Type**)temp) = m_objects;
		m_objects = temp;
	}
	m_objectsCount += size;
}

/*
for (int i = 0; i < m_capacity; ++i) {
				//mutex
				T_Type* temp = static_cast<T_Type*>(malloc(m_memorySize));
				*((T_Type**)temp) = m_ptr;
				m_ptr = temp;
			}
*/

#endif //!__OBJECT_POOL_H__
