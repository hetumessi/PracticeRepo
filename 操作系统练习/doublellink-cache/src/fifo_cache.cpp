#include "/Users/xushaoqian/Library/Mobile Documents/com~apple~CloudDocs/cpp/编程基础/ppt/cpp/computer_principle/include/fifo_cache.h"

// map的find函数来定位数据出现位置，它返回的一个迭代器，当数据出现时，它返回数据所在位置的迭代器
// 如果map中没有要查找的数据，它返回的迭代器等于end函数返回的迭代器
//(简单来讲，迭代器和指针非常类似，它可以是需要的任意类型，通过迭代器可以指向容器中的某个元素，如果需要还可以对该元素进行读/写操作。)
int FIFOCache::get(int key){
    std::map<int,Node*>::iterator it = this->map.find(key);
    // end()函数用于返回映射中最后一个条目后面的迭代器
    if (it == this->map.end()){
        return -1;
    }
    // map中的first会得到key的有效值，second会得到value的有效值。
    return this->map.find(key)->second->get_value();
}

Node* FIFOCache::put(int key, int value){
    if(this->capacity == 0){
        return nullptr;
    }
    std::map<int,Node*>::iterator it = this->map.find(key);
    if (it != this->map.end()){
        Node* node = this->map.find(key)->second;
        this->list->remove(node);
        node->set_value(value);
        return this->list->append(node);
    } else {
        if (this->list->get_size() == this->list->get_capacity()){
            Node* node = this->list->pop();
            /* erase()是C++ STL中的内置函数，用于从容器中擦除元素。它可用于擦除键，位于任何指定位置或给定范围的元素。 */
            /* erase(key)擦除指定的key对应的元素 */
            /* erase(iterator)删除指定迭代器对应的元素 */
            /* erase(iiterator position1, iterator position2)删除给定范围的迭代器之间的所有元素
                position1–指定迭代器，该迭代器是要从中进行删除的元素的引用
                position2–指定迭代器，该迭代器是要进行删除的元素的引用 
            */
            this->map.erase(node->get_key());
            delete node;
        }
        Node* node = new Node(key, value);
        this->list->append(node);
        // begin()函数用于返回指向Map容器第一个元素的迭代器
        std::map<int,Node*>::iterator it = this->map.begin();
        /* std::pair主要的作用是将两个数据组合成一个数据，两个数据可以是同一类型或者不同类型。*/
        /* 通过map的insert()可以把一个pair对象插入map中   */
        /* insert(pair)直接插入pair对象，insert()的返回值也是一个pair对象
           其first成员为map与插入的pair的键相同的pair，second成员为bool变量用于标识插入是否成功
           (插入成功则返回插入的pair和1，插入失败则返回map中相同键对应的pair和0) 

           insert(iterator,pair)支持向map指定位置插入pair对象，此时的返回值是迭代器
           如果插入成功，insert()返回一个指向map中已插入pair的迭代器；
           如果插入失败，insert()同样返回一个迭代器，该迭代器指向map中和pair具有相同键的那个pair
           
           insert(InputIterator first, InputIterator last)支持向当前map中插入其它map指定区域内的所有键值对
           其中first和last都是迭代器，它们的组合<first,last>可以表示某map中的指定区域
           (插入失败的原因一般是map中已经包含相同键的pair) */
        this->map.insert(std::pair<int, Node*>(key, node));
        return node;
    }
}