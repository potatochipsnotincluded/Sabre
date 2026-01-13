# Style Guide (MUST BE FOLLOWED)

1. Drop { onto new lines. There is an exeption
2. Don't drop { onto new lines for namespaces
3. For namespaces, leave an empty line at the start and end of the namespace eg:
```cpp
namespace Billy {

// code here
// code here

}
```
4. Capital letters for functions
5. Lower-case for normal variables.
6. Use m_Variable (capital first name letter), s_Variable (static, with capital first name letter), and for global inline variables, use g_GlobalVariable. For public variables start it with a capital eg MyPublicVariable
7. For global constants (constexpr, define, etc.), use SCREAMING_SNAKE_CASE
And in the source code: `std::exit(-1); // (StackOverFlow, 2025)`
9. Use double-quote includes for code owned and written within Sabre Engine, and angle brackets for things outside Sabre Engine.