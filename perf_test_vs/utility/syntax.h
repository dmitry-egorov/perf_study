#pragma once

template<typename T>
struct ExitScope {
    T lambda;
    ExitScope(T lambda):lambda(lambda) {}
    ~ExitScope() { lambda(); }
private:
    ExitScope& operator =(const ExitScope&);
};

class ExitScopeHelp {
public:
    template<typename T>
    ExitScope<T> operator+(T t) { return t; }
};

#define stx_concat_internal(x,y) x##y
#define stx_concat(x,y) stx_concat_internal(x,y)
#define line_var(prefix) stx_concat(prefix, __LINE__)
#define defer [[maybe_unused]]auto stx_concat(line_var(defer_), __COUNTER__) = ExitScopeHelp() + [&]