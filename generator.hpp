#include <cstdlib>
#include <stdexcept>

#include <ucontext.h>

class generator {
    ucontext_t _context_child;
    ucontext_t _context_parent;
    char *_stack;
    int   _stack_size;
    
    bool  _end;
    
    static void callChild(generator* gen) {
        gen->body();
        gen->_end = true;
    }

    typedef void func_t();

protected:
    generator( int stack_size=16*1024 ): 
        _end(false) 
    {
        if(getcontext(&_context_child)==-1)
            throw std::runtime_error("generator: fail @ getcontext");
        _stack = (char*)malloc(stack_size);
        _stack_size = stack_size;
        _context_child.uc_stack.ss_sp   = _stack;
        _context_child.uc_stack.ss_size = _stack_size;
        _context_child.uc_link          = &_context_parent;
        makecontext(&_context_child, (func_t*)callChild, 1, this);
    }

    virtual ~generator() {
        free(_stack);
    }

    virtual void body() = 0;

public:
    struct stop_iteration: std::exception {};

    void next() {
        if(_end)
            throw stop_iteration();
        if(swapcontext(&_context_parent, &_context_child) == -1)
            throw std::runtime_error("next: fail @ swapcontext");
    }

protected:
    void yield() {
        if(swapcontext(&_context_child, &_context_parent) == -1)
            throw std::runtime_error("yield: fail @ swapcontext");
    }
};
