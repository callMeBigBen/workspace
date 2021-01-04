## 模版类的成员函数

- 由于C++11正式废弃“模板导出”这一特性，因此模版类的成员函数，必须在头文件中实现。 例如：
```c++
template <typename T>
class vector
{
public:
    void clear()
    {
        // Function body
    }
	
private:
    T* elements;
};
```

- 模版类型的返回值
```c++
template <typename T>
T foo(std::string str){
    return std::static_cast<T>(str);
}
foo("1"); //wrong
foo<int>("1"); //true
```
