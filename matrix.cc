#include <stdexcept>
#include <iostream>
#include <vector>

template<typename T>
class Matrix
{
public:
    typedef typename std::vector<T>::iterator iterator;

    Matrix(std::initializer_list<std::initializer_list<T>> init) :
        m_x {init.size()},
        m_y {init.begin()->size()}
    {
        m_storage.reserve(m_x * m_y);

        for (const auto& r : init)
            for (const auto& v : r)
                m_storage.emplace_back(v);
    }

    iterator begin()
    {
        return m_storage.begin();
    }

    iterator end()
    {
        return m_storage.end();
    }
    
private:
    size_t m_x;
    size_t m_y;

    std::vector<T> m_storage;
};

int main()
{
    Matrix<int> m {{1,2,3}, {4,5,6}, {7,8,9}};

    for (const auto& v : m)
        std::cout << v << " ";
    std::cout << std::endl;
}
