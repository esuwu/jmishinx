//
// Created by kira on 27.09.2020.
//

#include <iostream>
#include <unordered_map>
//#include <c++>

class SmallAllocator {
 private:
    char _memory[1048576]{};
    char *_end = _memory;
    std::unordered_map<char *, char *> _ends;
 public:
    void *Alloc(unsigned int Size) {
        auto start = _end;
        _end += Size;
        _ends[start] = _end;
        return start;
    };
    void *ReAlloc(void *Pointer, unsigned int Size) {
        auto new_mem = Alloc(Size);
        for (size_t i = 0; i < Size; ++i) {
            *((char *)new_mem + i) = *((char *)Pointer + i);
        }
        Free(Pointer);
        return new_mem;
    };
    void Free(void *Pointer) {
        if (_ends[(char *)Pointer] == _end) {
            _end = (char *)Pointer;
        }
    };
};

int main() {
    SmallAllocator A1;
    int * A1_P1 = (int *) A1.Alloc(sizeof(int));
    A1_P1 = (int *) A1.ReAlloc(A1_P1, 2 * sizeof(int));
    A1.Free(A1_P1);
    SmallAllocator A2;
    int * A2_P1 = (int *) A2.Alloc(10 * sizeof(int));
    for(unsigned int i = 0; i < 10; i++) A2_P1[i] = i;
    for(unsigned int i = 0; i < 10; i++) if(A2_P1[i] != i) std::cout << "ERROR 1" << std::endl;
    int * A2_P2 = (int *) A2.Alloc(10 * sizeof(int));
    for(unsigned int i = 0; i < 10; i++) A2_P2[i] = -1;
    for(unsigned int i = 0; i < 10; i++) if(A2_P1[i] != i) std::cout << "ERROR 2" << std::endl;
    for(unsigned int i = 0; i < 10; i++) if(A2_P2[i] != -1) std::cout << "ERROR 3" << std::endl;
    A2_P1 = (int *) A2.ReAlloc(A2_P1, 20 * sizeof(int));
    for(unsigned int i = 10; i < 20; i++) A2_P1[i] = i;
    for(unsigned int i = 0; i < 20; i++) if(A2_P1[i] != i) std::cout << "ERROR 4" << std::endl;
    for(unsigned int i = 0; i < 10; i++) if(A2_P2[i] != -1) std::cout << "ERROR 5" << std::endl;
    A2_P1 = (int *) A2.ReAlloc(A2_P1, 5 * sizeof(int));
    for(unsigned int i = 0; i < 5; i++) if(A2_P1[i] != i) std::cout << "ERROR 6" << std::endl;
    for(unsigned int i = 0; i < 10; i++) if(A2_P2[i] != -1) std::cout << "ERROR 7" << std::endl;
    A2.Free(A2_P1);
    A2.Free(A2_P2);
    return 0;
}