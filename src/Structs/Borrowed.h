
#ifndef PONGPROJECT_BORROWED_H
#define PONGPROJECT_BORROWED_H

#include <type_traits>

using namespace std;
namespace Paradigm {


    template<class T>
    class _Borrowed {
    public:
        T val;
        bool isPointer;

        explicit _Borrowed(T value);

        ~_Borrowed();

        T get();

        void set(T *newVal);
    };

    template<class T>
    Paradigm::_Borrowed<T>::_Borrowed(T value) {
        val = value;
        isPointer = is_pointer<T>::value;
    }

    template<class T>
    T _Borrowed<T>::get() {
        return val;
    }

    template<class T>
    void _Borrowed<T>::set(T *newVal) {
        val = newVal;
        isPointer = is_pointer<T>(newVal);
    }

    template<class T>
    _Borrowed<T>::~_Borrowed() {
        if (!isPointer || val == nullptr) return;
        delete val;
    }


    template<class T>
    struct Borrowing {
        bool deleteOnBorrowed;
        _Borrowed<T> *borrowedValue;

        T get() {
            return borrowedValue->get();
        }

        void set(T *newValue) {
            borrowedValue->set(newValue);
        }

        void toggleDeleteOnBorrow(bool);

        void toggleDeleteOnBorrow();

        Borrowing();

        ~Borrowing();

        Borrowing(T, bool = true);

        Borrowing(_Borrowed<T> *, bool = true);
    };

    template<class T>
    Borrowing<T>::Borrowing() {
        borrowedValue = new _Borrowed<T>(nullptr);
        deleteOnBorrowed = true;
    }

    template<class T>
    Borrowing<T>::Borrowing(T p_value, bool p_deleteOnBorrowed) {
        borrowedValue = new _Borrowed<T>(p_value);
        deleteOnBorrowed = p_deleteOnBorrowed;
    }

    template<class T>
    Borrowing<T>::Borrowing(_Borrowed<T> *p_borrowedValue, bool p_deleteOnBorrowed) {
        borrowedValue = new _Borrowed(p_borrowedValue->get());
        delete p_borrowedValue;
        deleteOnBorrowed = p_deleteOnBorrowed;

    }

    template<class T>
    void Borrowing<T>::toggleDeleteOnBorrow(bool p_toggleValue) {
        deleteOnBorrowed = p_toggleValue;
    }

    template<class T>
    void Borrowing<T>::toggleDeleteOnBorrow() {
        deleteOnBorrowed = !deleteOnBorrowed;
    }

    template<class T>
    Borrowing<T>::~Borrowing() {
        if (deleteOnBorrowed) {
            delete borrowedValue;
        }
    }

    template<class T>
    Borrowing<T> *borrowedVar(T p_value) {
        return new Borrowing<T>(p_value, true);
    }

    template<class T>
    Borrowing<T> *sharedVar(T p_value) {
        return new Borrowing<T>(p_value, false);
    }


} // Paradigm

#endif //PONGPROJECT_BORROWED_H
