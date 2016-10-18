#include <vector>
#include <iostream>
using namespace std;

struct Simple {
    int i;
    Simple() : i(-99) { cout << "    defconstr!!" << endl; }
    Simple(int n) : i(n) { cout << "    constr " << i << endl; }
    ~Simple() { cout << "    destr " << i << endl; }
    Simple(const Simple& a) : i(a.i) { cout << "    copy " << i << endl; }
};

struct Move {
    int i;
    Move() : i(-99) { cout << "    defconstr!!" << endl; }
    Move(int n) : i(n) { cout << "    constr " << i << endl; }
    ~Move() { cout << "    destr " << i << endl; }
    Move(const Move& a) : i(a.i) { cout << "    copy " << i << endl; }
    Move(Move&& a) : i(a.i) { cout << "    move " << i << endl; }
};

struct MoveNoexcept {
    int i;
    MoveNoexcept() : i(-99) { cout << "    defconstr!!" << endl; }
    MoveNoexcept(int n) : i(n) { cout << "    constr " << i << endl; }
    ~MoveNoexcept() { cout << "    destr " << i << endl; }
    MoveNoexcept(const MoveNoexcept& a) : i(a.i) { cout << "    copy " << i << endl; }
    MoveNoexcept(MoveNoexcept&& a) noexcept : i(a.i) { cout << "    move " << i << endl; }
};

template<class T>
void test_class() {
    cout << "  create capacity=0 vector" << endl;
    vector<T> v;
    v.shrink_to_fit();
    cout << "  push 1" << endl;
    v.push_back(T(1));
    cout << "  push 2" << endl;
    v.push_back(T(2));
    cout << "  push 3" << endl;
    v.push_back(T(3));
    cout << "  destroy vector" << endl;
}

int main() {
    cout << "test with simple class" << endl;
    test_class<Simple>();

    cout << "test with a class with move constructor" << endl;
    test_class<Move>();

    cout << "test with a class with noexcept move constructor" << endl;
    test_class<MoveNoexcept>();
}
