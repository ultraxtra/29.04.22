#include <iostream>

using namespace std;

template <class T>
struct Node
{
    T value;
    Node* prev;
    Node* next;
    Node() : value(0), prev(nullptr), next(nullptr) {}
    Node(const T& data) : value(data), prev(nullptr), next(nullptr) {}
};

template <class T>
class QueueList
{
    Node<T>* mpHead;
    Node<T>* mpTail;
    int mCount;
public:
    QueueList() : mpHead(nullptr), mpTail(nullptr), mCount(0) {}
    ~QueueList();

    QueueList(const QueueList& source);
    QueueList& operator=(const QueueList& source);

    void Clear() { this->~QueueList(); }
    int GetCount() const { return mCount; }

    void PushBack(const T& value);
    T PopFront();
};

template <class T>
QueueList<T>::~QueueList()
{
    while (mpHead)
    {
        Node<T>* tmp = mpHead;
        mpHead = mpHead->next;
        delete[] tmp;
    }
    mCount = 0;
}

template <class T>
QueueList<T>::QueueList(const QueueList<T>& source)
{
    mpHead = nullptr;
    mpTail = nullptr;
    mCount = 0;

    Node<T>* tmp = source.mpHead;
    for (int i = 0; i < source.mCount; ++i)
    {
        PushBack(tmp->value);
        tmp = tmp->next;
    }
}

template <class T>
QueueList<T>& QueueList<T>::operator=(const QueueList<T>& source)
{
    if (this == &source) return *this;

    this->~QueueList();

    Node<T>* tmp = source.mpHead;
    for (int i = 0; i < source.mCount; ++i)
    {
        PushBack(tmp->value);
        tmp = tmp->next;
    }

    return *this;
}

template <class T>
void QueueList<T>::PushBack(const T& value)
{
    Node<T>* tmp = new Node<T>;
    tmp->value = value;

    if (!mpHead)
    {
        mpHead = tmp;
        mpTail = tmp;
    }
    else
    {
        tmp->prev = mpTail;
        mpTail->next = tmp;
        mpTail = tmp;
    }
    mCount++;
}

template <class T>
T QueueList<T>::PopFront()
{
    if (mpHead)
    {
        T result = mpHead->value;
        Node<T>* tmp = mpHead;
        mpHead = mpHead->next;
        if (mpHead) { mpHead->prev = nullptr; }
        mCount--;
        delete[] tmp;

        return result;
    }
    else
    {
        return T();
    }
}


void main()
{
    QueueList<int> q1;
    cout << "Queue A: ";
    for (int i = 0; i < 5; ++i)
    {
        q1.PushBack(i);
    }
    int count = q1.GetCount();
    while (q1.GetCount())
    {
        cout << q1.PopFront() << " ";
    }
    cout << "\n\tTotal: " << count << " items" << endl;


    cout << "\n\nQueue A: ";
    q1.PushBack(7);
    QueueList<int> q2(q1);

    count = q1.GetCount();
    while (q1.GetCount())
    {
        cout << q1.PopFront() << " ";
    }
    cout << "\n\tTotal: " << count << " items" << endl;


    cout << "\n\nQueue B: ";
    for (int i = 0; i < 5; ++i)
    {
        q2.PushBack(i);
    }
    count = q2.GetCount();
    while (q2.GetCount())
    {
        cout << q2.PopFront() << " ";
    }
    cout << "\n\tTotal: " << count << " items" << endl;


    cout << "\n\nQueue B: ";
    for (int i = 0; i < 5; ++i)
    {
        q2.PushBack(i);
    }
    q2.Clear();
    count = q2.GetCount();
    while (q2.GetCount())
    {
        cout << q2.PopFront() << " ";
    }
    cout << "\n\tTotal: " << count << " items" << endl;

    cout << "\n\n";
}

#include <memory>
#include <iostream>
using namespace std;

template <class T>
class Array
{
    T* mArray;
    int mUpperBound;
    int mSize;
    int mGrow;

    void CreateArray(const int size);
    void ReSize(const int size, const int grow = 0);
public:
    Array(const int size = 1, const int grow = 1)
        : mSize(size), mUpperBound(-1), mGrow(grow)
    {
        if (size < 1  grow < 1)
        {
            cout << "\nError: incorrect parametrs!";
            exit(1);
        }
        CreateArray(size);
    }
    ~Array();
    int GetSize() const { return mSize; }
    void SetSize(const int size, const int grow = 1);
    int GetUpperBound() const { return mUpperBound; }
    bool IsEmpty() const { return mUpperBound == -1; }
    void FreeExtra();
    void RemoveAll();
    T& operator[](const int index);
    T GetAt(int index);
    void SetAt(const int index, const T& value);
    void Add(const T& value);
    void Append(const Array& appendedObj);
    Array(const Array& source);
    Array& operator=(const Array& source);
    T* GetData() const { return mArray; }
    void InsertAt(const int index, const T& value);
    void RemoveAt(const int index);
};

template <class T>
Array<T>::~Array()
{
    delete[] mArray;
    mArray = nullptr;
    mSize = 0;
    mUpperBound = -1;
    mGrow = 1;
}


template<class T>
void Array<T>::CreateArray(const int size)
{
    try {
        mArray = new T[size];
    }
    catch (bad_alloc)
    {
        cout << "\nError: out of memory!\n\n";
        exit(1);
    }
}

template <class T>
void Array<T>::ReSize(const int size, const int grow/*=0*/)
{
    if (size < 0  grow < 0)
    {
        cout << "Error: incorrect parametrs!";
        exit(1);
    }
    if (grow) mGrow = grow;

    if (mSize == size)  return;
    else mSize = size;

    if (mUpperBound + 1 > mSize)
    {
        mUpperBound = mSize - 1;
    }

    T* tmp = mArray;
    CreateArray(mSize);
    for (int i = 0; i <= mUpperBound; ++i)
    {
        mArray[i] = tmp[i];
    }
    delete[] tmp;
}

template <class T>
void Array<T>::SetSize(const int size, const int grow/*=1*/)
{
    if (size < 0  grow < 0)
    {
        cout << "Error: incorrect parametrs!";
        exit(1);
    }

    if (mArray)
    {
        ReSize(size, grow);
    }
    else
    {
        mSize = size;
        mUpperBound = -1;
        mGrow = grow;
        CreateArray(size);
    }
}

template <class T>
void Array<T>::FreeExtra()
{
    ReSize(mUpperBound + 1);
}

template <class T>
void Array<T>::RemoveAll()
{
    this->~Array();
}

template <class T>
T& Array<T>::operator[](const int index)
{
    if (index >= 0 && index <= mUpperBound)
    {
        return mArray[index];
    }
    else
    {
        cout << endl << "Error: out of range!" << endl;
        exit(1);
    }
}

template <class T>
T Array<T>::GetAt(int index)
{
    return this->operator[](index);
}


template <class T>
void Array<T>::SetAt(const int index, const T& value)
{
    this->operator[](index) = value;
}

template <class T>
void Array<T>::Add(const T& value)
{
    if (mUpperBound + 1 >= mSize)
    {
        ReSize(mSize + mGrow);
    }
    mUpperBound++;
    mArray[mUpperBound] = value;
}

template<class T>
void Array<T>::Append(const Array& appendedObj)
{
    if (appendedObj.IsEmpty()) return;

    int newSize = mUpperBound + appendedObj.mUpperBound + 2;
    newSize += newSize % mGrow;
    ReSize(newSize);

    for (int i = 0; i <= appendedObj.GetUpperBound(); ++i)
    {
        Add(appendedObj.mArray[i]);
    }
}

template <class T>
Array<T>::Array(const Array<T>& source)
{
    mSize = source.mSize;
    mUpperBound = source.mUpperBound;
    mGrow = source.mGrow;
    CreateArray(mSize);

    for (int i = 0; i <= mUpperBound; ++i)
    {
        mArray[i] = source.mArray[i];
    }
}

template <class T>
Array<T>& Array<T>::operator=(const Array<T>& source)
{
    if (this == &source) return *this;

    if (mSize != source.mSize)
    {
        delete[] mArray;
        CreateArray(source.mSize);
    }

    mSize = source.mSize;
    mUpperBound = source.mUpperBound;
    mGrow = source.mGrow;

    for (int i = 0; i <= mUpperBound; ++i)
    {
        mArray[i] = source.mArray[i];
    }

    return *this;
}

template <class T>
void Array<T>::InsertAt(const int index, const T& value)
{
    if (index<0  index>mUpperBound)
    {
        cout << endl << "Error: out of range!" << endl;
        exit(1);
    }

    if (mUpperBound + 1 == mSize) ReSize(mSize + mGrow);

    for (int i = ++mUpperBound; i > index; --i)
    {
        mArray[i] = mArray[i - 1];
    }
    mArray[index] = value;
}

template <class T>
void Array<T>::RemoveAt(const int index)
{
    if (index<0 || index>mUpperBound)
    {
        cout << endl << "Error: out of range!" << endl;
        exit(1);
    }

    for (int i = index; i < mUpperBound; ++i)
    {
        mArray[i] = mArray[i + 1];
    }
    mUpperBound--;
}

template <class T>
void GetInfo(Array<T>& obj, char* test)
{
    cout << "\n\n*" << test << endl;
    cout << "\n\t size=\t" << obj.GetSize();
    cout << "\n\t upper bound=\t" << obj.GetUpperBound();
    cout << "\n\t is empty=\t" << obj.IsEmpty();

    cout << "\n\t ";
    for (int i = 0; i <= obj.GetUpperBound(); ++i)
    {
        cout << obj.GetAt(i) << " ";
    }
    cout << endl << endl;
}

void main()
{
    cout << "\n***A***\n";

    Array<int> a;
    a.SetSize(3, 5);
    GetInfo(a, "SetSize(3,5)");

    a.Add(1);
    GetInfo(a, "Add(1)");

    a.SetSize(13, 5);
    GetInfo(a, "SetSize(13,5)");

    for (int i = 0; i < 13; ++i)
    {
        a.Add(i);
    }
    GetInfo(a, "for i=0 to 12: Add(i)");

    a.RemoveAll();
    GetInfo(a, "RemoveAll()");

    a.SetSize(10, 5);
    GetInfo(a, "SetSize(10)");


    for (int i = 0; i < 5; ++i)
    {
        a.Add(i * 3);
    }
    GetInfo(a, "for i=0 to 5: Add(i*3)");

    a.FreeExtra();
    GetInfo(a, "FreeExtra()");


    cout << "\n***B****\n";
    Array<int> b;
    b = a;
    GetInfo(b, "B=A");

    for (int i = 0; i < 5; ++i)
    {
        b.SetAt(i, i);
    }
    GetInfo(b, "for i=0 to 5: SetAt(i, i)");

    b.Append(a);
    GetInfo(b, "Append(a)");

    cout << "*InsertAt(0, 111)\n";
    b.InsertAt(0, 111);
    cout << "*InsertAt(4, 444)\n";
    b.InsertAt(4, 444);
    cout << "*InsertAt(11, 111)\n";
    b.InsertAt(11, 1222);
    GetInfo(b, "After insertion");

    cout << "*RemoveAt(11)\n";
    b.RemoveAt(11);
    cout << "*RemoveAt(4)\n";
    b.RemoveAt(4);
    cout << "*RemoveAt(0)\n";
    b.RemoveAt(0);
    GetInfo(b, "After deletion");

    cout << "\n***pA****\n";
    cout << "*pa=a.GetData()\n\t";
    int* pa = a.GetData();
    for (int i = 0; i <= a.GetUpperBound(); ++i)
    {
        cout << pa[i] << " ";
    }

    cout << "\n\n***pB***\n";
    cout << "*pb=b.GetData()\n\t";
    int* pb = b.GetData();
    for (int i = 0; i <= b.GetUpperBound(); ++i)
    {
        cout << pb[i] << " ";
    }
    cout << "\n\n";
}