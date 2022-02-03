#ifndef _LIST_HPP_INCLUDED
#define _LIST_HPP_INCLUDED

#include <cstdlib>

namespace s1ky {
template<typename key_t, typename data_t>
class List
{
public:
    List();
    List(key_t key, data_t data);
    List(const List& other);
    List(List&& other) noexcept;
    ~List();

    bool operator==(const List<key_t, data_t>& other) const;
    bool operator!=(const List& other) const;

    List<key_t, data_t>& operator=(const List& other);
    List<key_t, data_t>& operator=(List&& other) noexcept;

    bool   empty() const;
    size_t size() const;

    data_t& front();
    data_t& back();

    const data_t& front() const;
    const data_t& back() const;

    void push(key_t key, data_t value);
    void pop();
    void swap(List* other);
/*    
    void delete_value_node(const T value);
    List<key_t, data_t>* find_value(const data_t value) const;
*/
private:
    struct Node
    {
        key_t  key_;
        data_t data_;
        Node*  next_ = nullptr;
    };

    size_t size_  = 0;
    Node*  front_ = nullptr;
    Node*  back_  = nullptr;

    void delete_nodes();
};
} // namespace s1ky

#endif // _LIST_HPP_INCLUDED