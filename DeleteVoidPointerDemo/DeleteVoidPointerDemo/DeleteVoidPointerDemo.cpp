// DeleteVoidPointerDemo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>

class Fuck {
public:
    Fuck() {
        m_BufferPtr = new char[80];
        strcpy_s(m_BufferPtr, 80, "Hello World!");
    }
    ~Fuck() { std::cout << "Delete Fuck" << std::endl;
        memset(name, 0, sizeof(name));
        memset(m_BufferPtr, 0, sizeof(m_BufferPtr));
        delete[] m_BufferPtr;
    }
    char* getBuffer() { return m_BufferPtr;
    }

private:
    char name[10] = "Fuck";
    char* m_BufferPtr;
};

class Base {
public:
    Base() {}
    virtual ~Base() { std::cout << "destruct base" << std::endl;
    }
};

class Derived : public Base {
public:
    Derived() {}
    ~Derived() { std::cout << "destruct derived" << std::endl;
    }
};
int main()
{
    Fuck* pFuck = new Fuck();
    int size = sizeof(Fuck);
    std::cout << "Fuck Size: " << size << std::endl;
    char* pBuffer = pFuck->getBuffer();
    delete (void*)pFuck;
    strcpy_s(pBuffer, 80, "Shit");
    // 正常释放说明pBuffer没有被释放
    delete []pBuffer;
    std::cout << "Hello World!\n"; 

    std::shared_ptr<Derived> pDerived = std::make_shared<Derived>();
    //std::shared_ptr<Base> pBase = pDerived;
    std::shared_ptr<void> pBase = pDerived;
    //Derived derived;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
