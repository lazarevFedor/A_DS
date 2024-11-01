#ifndef A_DS_ARRAY_H
#define A_DS_ARRAY_H


template<typename Type> class Array{
public:
    Type* array;
    int currentSize = 0;
    int capacity = 0;
public:
    Array();

    Array(int inputSize);

    ~Array();

    void resize(int inputSize);

    void pushBack(Type data);

    void pushFront(Type data);

    void print();

    void insert(int index, Type data);

    bool empty();

    void erase(int index);

    Type* getAt(short index);

    void swap(short index1, short index2);
};


//Methods
template<typename Type> void Array<Type>::swap(short index1, short index2) {
    if(index1 < 0 || index2 >= currentSize) return;
    std::swap(array[index1], array[index2]);
}


template<typename Type> Type* Array<Type>::getAt(short index) {
    if(index < 0 || index >= currentSize) return nullptr;
    return array+index;
}


template<typename Type> void Array<Type>::erase(int index) {
    if(index >= currentSize || index < 0) return;
    capacity--;
    Type* tmp = new Type[capacity];
    for (int i = 0; i < index; i++){
        *(tmp + i) = *(array + i);
    }
    for (int i = index+1; i < currentSize; i++){
        *(tmp + i - 1) = *(array + i);
    }
    currentSize--;
    delete[]array;
    array = tmp;
}


template<typename Type> bool Array<Type>::empty() {
    if(currentSize == 0) return true;
    return false;
}


template<typename Type> void Array<Type>::insert(int index, Type data) {
    if(index < 0 || index > capacity) return;

    if(index == 0) {
        this->pushFront(data);
        return;
    }
    if(index == currentSize){
        this->pushBack(data);
        return;
    }

    if (currentSize + 1 >= capacity){
        capacity *= 2;
    }
    Type* tmp = new Type[capacity];
    if(index > currentSize){
        for (int i = 0; i < currentSize; i++) {
            tmp[i] = array[i];
        }
        for(int i = currentSize; i < index; i++){
            tmp[i] = 0;
        }
        tmp[index] = data;
    }else{
        for (int i = 0; i < index; i++) {
            tmp[i] = array[i];
        }
        *(tmp + index) = data;
        for (int i = index + 1; i <= currentSize; i++) {
            tmp[i] = array[i-1];
        }
    }
    if(index > currentSize){
        currentSize = index + 1;
    }else{
        currentSize++;
    }
    delete [] array;
    array = tmp;
}


template<typename Type> void Array<Type>::print() {
    if (currentSize == 0) return;
    std::cout << "[ ";
    for (int i = 0; i < currentSize; i++){
        std::cout << *(array + i) << " ";
    }
    std::cout << "]";
}


template<typename Type> void Array<Type>::pushFront(Type data) {
    Type  *tmp = new Type[capacity*2];
    if (currentSize + 1 < capacity){
        for (int i = currentSize; i > 0; i--){
            *(array + currentSize) = *(array + currentSize - 1);
        }
        *(array) = data;
        currentSize++;
    } else{
        capacity *= 2;
        for (int i = 1; i <= currentSize; i++) {
            tmp[i] = array[i-1];
        }
        *(tmp) = data;
        currentSize++;
        delete [] array;
        array = tmp;
    }
}


template<typename Type> void Array<Type>::pushBack(Type data) {
    Type  *tmp = new Type[capacity*2];
    if (currentSize + 1 < capacity){
        *(array + currentSize) = data;
        currentSize++;
    }else{
        capacity *= 2;
        for (int i = 0; i < currentSize; i++) {
            tmp[i] = array[i];
        }
        *(tmp + currentSize) = data;
        currentSize++;
        delete [] array;
        array = tmp;
    }
}


template<typename Type> void Array<Type>::resize(int inputSize) {
    if (inputSize < 0) return;
    Type  *tmp = new Type[inputSize];
    if(currentSize > inputSize){
        currentSize = inputSize;
        for (int i = 0; i < inputSize; i++) {
            tmp[i] = array[i];
        }
    } else{
        for (int i = 0; i < currentSize; i++){
            tmp[i] = array[i];
        }
    }
    capacity = inputSize;
    delete []array;
    array = tmp;
}


//Constructors and destructor
template<typename Type> Array<Type>::Array() {
    currentSize = 0;
    capacity = 5;
    array = new Type[capacity];
}


template<typename Type> Array<Type>::Array(int inputSize) {
    if (inputSize < 0){
        inputSize = 5;
    }
    capacity = inputSize;
    array = new Type[capacity];
}


template<typename Type> Array<Type>::~Array() {
    delete []array;
    array = nullptr;
}


#endif