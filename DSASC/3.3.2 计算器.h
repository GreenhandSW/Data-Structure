#include"3.3.2 栈的数组实现 Stack.h"

#ifndef FUNC
typedef ElementType(*FUNC)(const ElementType, const ElementType);
#endif // !FUNC

void Infix2Postfix(const char * src, char * dst);
ElementType plus(const ElementType x, const ElementType y);
ElementType minus(const ElementType x, const ElementType y);
ElementType multiply(const ElementType x, const ElementType y);
ElementType divide(const ElementType x, const ElementType y);
ElementType Calc(const char * src);

extern const char * operators;