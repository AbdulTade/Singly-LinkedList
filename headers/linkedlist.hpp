#pragma once

#include <iostream>
#include <cstddef>
#include <cstdlib>
#include <mutex>
#include <ostream>
#include <stdexcept>
#include <string>
#include <thread>

template <typename T>
struct Node
{
public:
    T value;
    Node<T> *next;
};

template <typename T>
class LinkedList
{

public:
    struct Iterator
    {

    private:
        Node<T> *head;

    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T *;
        using reference = T &;

        Iterator(Node<T> *ptr)
            : head(ptr)
        {
        }

        reference operator*() const
        {
            if (head == nullptr)
                std::runtime_error("LinkedList is empty");
            return (*head).value;
        }

        pointer operator->()
        {
            return &head->value;
        }

        Iterator &operator++()
        {
            head = head->next;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        friend bool operator==(const Iterator &a, const Iterator &b)
        {
            return a.head == b.head;
        }

        friend bool operator!=(const Iterator &a, const Iterator &b)
        {
            return a.head != b.head;
        }
    };

    Iterator begin()
    {
        return Iterator(this->head);
    }

    Iterator end()
    {
        return Iterator(nullptr);
    }

private:

    std::size_t length;
    Node<T> *head;
    std::mutex mutex{};

public:

    LinkedList()
        : length(0),
          head(nullptr)
    {
    }

    ~LinkedList() noexcept
    {
        if (this->head == nullptr)
            return;

        Node<T> *h = this->head;
        Node<T> *n = h->next;

        while (n != nullptr)
        {
            delete h;
            h = n;
            n = n->next;
        }
    }

    void insertEnd(const T &value)
    {
        std::lock_guard<std::mutex> lock{this->mutex};

        if (this->length == 0)
        {
            this->head = new Node<T>;
            if (this->head == nullptr)
                throw std::runtime_error(
                    "Could not allocate memory to store head node");
            this->head->value = value;
            this->head->next = nullptr;
        }

        else
        {
            auto h = this->head;
            Node<T> *n = this->head->next;
            while (n != nullptr)
            {
                h = n;
                n = n->next;
            }

            h->next = new Node<T>;
            if (h->next == nullptr)
                throw std::runtime_error(
                    "Could not allocate memory for node to be added");
            h->next->value = value;
            h->next->next = nullptr;
        }

        this->length += 1;
    }

    friend std::ostream &operator<<(std::ostream &oss, LinkedList<T> const &ll)
    {
        Node<T> *h = ll.head;
        Node<T> *n = h->next;

        oss << h->value << " --> ";
        while (n != nullptr)
        {
            h = n;
            n = n->next;
            oss << h->value << " --> ";
        }

        return oss;
    }

    void clear() {
        this->~LinkedList();
    }

    std::size_t size()
    {
        return this->length;
    }

    void insertBegin(const T &value)
    {
        std::lock_guard<std::mutex> lock(this->mutex); // Acquire lock
        Node<T> *h = new Node<T>;
        h->value = value;
        h->next = this->head;
        this->head = h;
        this->length += 1;
    }

    bool removeBegin()
    {

        std::lock_guard<std::mutex> lock(this->mutex);
        if (this->head == nullptr)
            return false;

        Node<T> *h = this->head;
        this->head = h->next;

        delete h;
        this->length -= 1;

        return true;
    }

    T operator[](const std::size_t index)
    {
        std::lock_guard<std::mutex> lock(this->mutex); // Acquire lock

        if (index > this->length - 1)
            throw std::runtime_error("index out of range");

        if (this->head == nullptr)
            return nullptr;

        Node<T> *h = this->head;
        Node<T> *n = this->head->next;
        std::size_t count = 0;
        T value;

        while (n != nullptr)
        {
            if (count == index)
            {
                std::cout << "Value at iteration " << count << " " << h->value
                          << std::endl;
                value = h->value;
            }

            std::cout << "Value at iteration " << count << " " << h->value
                      << std::endl;

            h = n;
            n = n->next;
            count += 1;
        }

        return nullptr;
    }
};
