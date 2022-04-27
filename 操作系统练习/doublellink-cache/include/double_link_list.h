#ifndef __DOUBLE_LINK_LIST_H__
#define __DOUBLE_LINK_LIST_H__

#include <iostream>
#include <sstream>
#include <string>

class Node {
   private:
    /* data */
    int key;
    int value;
    Node* prev;
    Node* next;

   public:
    Node(int key, int value) {
        this->key = key;
        this->value = value;
        this->next = nullptr;
        this->prev = nullptr;
    }

    ~Node(){};

    int get_key() { return this->key; };
    int get_value() { return this->value; };
    Node* get_prev() { return this->prev; };
    Node* get_next() { return this->next; };
    void set_key(int key) { this->key = key; };
    void set_value(int value) { this->value = value; };
    void set_prev(Node* prev) { this->prev = prev; };
    void set_next(Node* next) { this->next = next; };

    std::string to_string() {
        std::ostringstream ss;
        // ss << "@"<< this << "{key: " << this->key << ", value: " << this->value << "}";
        ss << "{key: " << this->key << ", value: " << this->value << "}";
        return ss.str();
    }
};

class DoubleLinkList {
   private:
    int size;
    int capacity;
    Node* head;
    Node* tail;

    Node* add_head(Node*);
    Node* add_tail(Node*);
    Node* del_head();
    Node* del_tail();
    Node* _remove(Node* node=nullptr);

   public:
    DoubleLinkList(int capacity = 0xffff) {
    this->capacity = capacity;
    this->size = 0;
    this->head = nullptr;
    this->tail = nullptr;
    };
    ~DoubleLinkList(){};

    Node* pop();
    Node* append(Node*);
    Node* append_front(Node*);
    Node* remove(Node* node=nullptr);

    int get_capacity() { return this->capacity; };
    void set_capacity(int capacity) { this->capacity = capacity; };
    int get_size() { return this->size; };

    std::string to_string() {
        /*  ostringstream是C++的一个字符集操作模板类，定义在sstream.h头文件中。
            ostringstream类通常用于执行C风格的串流的输出操作，格式化字符串，避免申请大量的缓冲区，可替代sprintf
            有时候，我们需要格式化一个字符串，但通常并不知道需要多大的缓冲区。为了保险常常申请大量的缓冲区以防止缓冲区过小造成字符串无法全部存储。
            这时我们可以考虑使用ostringstream类，该类能够根据内容自动分配内存，并且其对内存的管理也是相当的到位。
            取得std::ostringstream里的内容可以通过str()和str(string&)成员函数。
            示例：
            ostringstream ostr1; // 构造方式1  
            ostringstream ostr2("abc"); // 构造方式2  
            ostr1 << "ostr1" << 2012 << endl; // 格式化，此处endl也将格式化进ostr1中  
            cout << ostr1.str()<<endl;  
            cout<<ostr2.str()<<endl;
        
        */
        std::ostringstream ss;
        Node* p = this->head;
        int num = this->size;
        while (p != nullptr && num --) {
            ss << p->to_string();
            if (p->get_next() != nullptr) {
                ss << "->";
            }
            p = p->get_next();
        }
        return ss.str();
    }
};

#endif