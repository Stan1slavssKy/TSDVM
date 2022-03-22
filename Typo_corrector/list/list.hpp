#ifndef HASH_TABLE_LIST_LIST_HPP_INCLUDED_
#define HASH_TABLE_LIST_LIST_HPP_INCLUDED_

#include <cstddef>
#include <cstdlib>
#include <iterator>

namespace s1ky {
template<typename key_t, typename data_t>
struct Node
{
    key_t  key_;
    data_t data_;
    Node*  next_ = nullptr;
};

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

    Node<key_t, data_t>* push(const key_t& key, const data_t& value);

    void pop();
    void swap(List* other);

    void delete_invalid_node();

    Node<key_t, data_t>* delete_node(const key_t& key);
    Node<key_t, data_t>* find_value(const key_t& key);

    struct Iterator;
    Iterator begin()
    {
        return Iterator(front_);
    };
    Iterator end()
    {
        return Iterator(nullptr);
    };

private:
    size_t size_ = 0;

    Node<key_t, data_t>* front_ = nullptr;
    Node<key_t, data_t>* back_  = nullptr;

    void delete_nodes();
};

template<typename key_t, typename data_t>
class List<key_t, data_t>::Iterator
{
public:
    explicit Iterator(Node<key_t, data_t>* cur_node) : cur_node_(cur_node) {};
    Iterator(const Iterator& other) : cur_node_(other.cur_node_) {};
    Iterator(Iterator&& other) noexcept : cur_node_(other.cur_node_) {};
    ~Iterator() = default;

    Iterator& operator=(const Iterator& other);
    Iterator& operator=(Iterator&& other) noexcept;

    Node<key_t, data_t>& operator*() const
    {
        return *cur_node_;
    };
    Node<key_t, data_t>* operator->() const
    {
        return cur_node_;
    };

    Iterator& operator++()
    {
        cur_node_ = cur_node_->next_;
        return *this;
    };
    Iterator operator++(int)
    {
        Iterator temp = *this;
        cur_node_     = cur_node_->next_;
        return temp;
    };

    bool operator==(const Iterator& other) const
    {
        return cur_node_ == other.cur_node_;
    };
    bool operator!=(const Iterator& other) const
    {
        return cur_node_ != other.cur_node_;
    };

private:
    Node<key_t, data_t>* cur_node_;
};
} // namespace s1ky

#endif // HASH_TABLE_LIST_LIST_HPP_INCLUDED_
