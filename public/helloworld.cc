#include <stdio.h>
#include <emscripten/emscripten.h>
#include <emscripten/bind.h>
#include <vector>
#include <iostream>
#include <memory>

using namespace std;
using namespace emscripten;

int main(int argc, char ** argv) {
    // unique_ptr<Universe> universe(new Universe(5,5));
    printf("Hello World");
}

#ifdef __cplusplus
extern "C" {
#endif

void EMSCRIPTEN_KEEPALIVE myFunction(int argc, char ** argv) {
    printf("MyFunction Called\n");
}

// Binding code
// EMSCRIPTEN_BINDINGS(my_class_example) {
//   class_<MyClass>("MyClass")
//     .constructor<int, std::string>()
//     .function("incrementX", &MyClass::incrementX)
//     .property("x", &MyClass::getX, &MyClass::setX)
//     .class_function("getStringFromInstance", &MyClass::getStringFromInstance)
//     ;
// }



double EMSCRIPTEN_KEEPALIVE factorial(double n) {
    double ret = n;
    while (n-- > 1) {
        ret *= n;
    }
    return ret;
}


class Universe {
    private:
    int width, height;
    vector<bool> universe;
    vector<bool> nextState;
    
    public:
    Universe(int w, int h) {
        width = w;
        height = h;
        universe = vector<bool>(w * h);
        nextState = vector<bool>(w * h);

    }
    
    void advanceState() {
        universe = nextState;
    }
    
    void setCell(int y, int x) {
        int index = getLinearIndex(x, y);
        this->universe[index] = true;
    }
    
    int getArea() {
        return width * height;
    }
    
    bool getIndex(int x, int y) {
        return universe[x * this->width + y];
    }

    int getLinearIndex(int x, int y) {
        return (x * this->width + y);
    }

    void setNextState() {
        for (int i = 0; i < this->width; i++) {
            for (int j = 0; j < this->height; j++) {
                this->nextState[getLinearIndex(i, j)] = willLive(i, j);
            }
        }
    }
    
    bool willLive(int x, int y) {
        int count = 0;
        //Left
        if (x > 0) {
            if (getIndex(x - 1, y)) count++;
            //Left Up
            if (y > 0) if (getIndex(x - 1, y - 1)) count++;
        }
        
        //Up
        if (y > 0) {
            if (getIndex(x, y - 1)) count++;
            //Right Up
            if (x < this->width) if (getIndex(x + 1, y - 1)) count++;

        }
        //Right
        if (x < this->width) {
            if (getIndex(x + 1, y)) count++;
            //Right Down
            if (y < this->height) if (getIndex(x + 1, y + 1)) count++;
        }
        //Down
        if (y < this->height) {
            if (getIndex(x, y + 1)) count++;
            //Down Left
            if (x > 0) if (getIndex(x - 1, y + 1)) count++;
        }

        if (count == 2 || count == 3) return true;
        return false;
    }
    
};

EMSCRIPTEN_BINDINGS(universe_class) {
    class_<Universe>("Universe")
    .constructor<int, int>()
    .function("advanceState", &Universe::advanceState)
    .function("setCell", &Universe::setCell)
    .function("setNextState", &Universe::setNextState)
    .function("getIndex", &Universe::getIndex)
    ;
}

#ifdef __cplusplus
}
#endif