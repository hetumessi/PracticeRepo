#include "lfu_cache.h"

#include <cstdlib>

void LFUCache::update_freq(LFUNode* node){
    int freq = node->freq;
    this->freq_map.find(freq)->second->remove((Node*)node);
    if(this->freq_map.find(freq)->second->get_size() == 0){
        DoubleLinkList* list = this->freq_map.find(freq)->second;
        this->freq_map.erase(freq);
        delete list;
    }
    freq += 1;
    node->freq = freq;
    std::map<int,DoubleLinkList*>::iterator it = this->freq_map.find(freq);
    if (it == this->freq_map.end()){
        std::map<int,DoubleLinkList*>::iterator it = this->freq_map.begin();
        this->freq_map.insert(std::pair<int, DoubleLinkList*>(freq, new DoubleLinkList()));
    }
    this->freq_map.find(freq)->second->append((Node*)node);
}

int LFUCache::get(int key){
    std::map<int,LFUNode*>::iterator it = this->map.find(key);
    if (it == this->map.end()){
        return -1;
    }
    LFUNode* node = this->map.find(key)->second;
    this->update_freq(node);
    return node->get_value();
}

Node* LFUCache::put(int key, int value){
    if(this->capacity == 0){
        return nullptr;
    }
    std::map<int,LFUNode*>::iterator it = this->map.find(key);
    if (it != this->map.end()){
        LFUNode* node = this->map.find(key)->second;
        node->set_value(value);
        this->update_freq(node);
        return node;
    } else {
        if (this->size == this->capacity) {
            int min_freq = 0xffff;
            /* map的四种遍历方式
                值传递遍历：for(pair it:map)或for(auto i:map)
                引用传递遍历：for(const pair&it:map)或for(auto&it:map)
                使用迭代器遍历：for(map::iterator it=map.begin();it!=map.end();it++)或
                             for(auto it=map.begin();it!=map.end();it++)
                结构化绑定(c++17特性)：值传递for(auto [k,v]:map)   (k,v对应元素的first和second成员)
                                    引用传递for(auto&[k,v]:map)
             */
            for(std::map<int,DoubleLinkList*>::iterator it=this->freq_map.begin();it!=this->freq_map.end();it++){
                // min()是algorithm.h的库函数，用于从给定的两个值中找到最小值，它接受两个值并返回最小值，如果两个值相同则返回第一个值。
                min_freq = std::min(min_freq, it->first);
            }
            Node *node = this->freq_map.find(min_freq)->second->pop();
            this->map.erase(node->get_key());
            delete node;
            this->size--;
        }
        LFUNode *node = new LFUNode(key, value);
        node->freq = 1;
        std::map<int,LFUNode*>::iterator it = this->map.begin();
        this->map.insert(it, std::pair<int, LFUNode*>(key, node));
        std::map<int,DoubleLinkList*>::iterator p = this->freq_map.find(node->freq);
        if (p == this->freq_map.end()){
            std::map<int,DoubleLinkList*>::iterator it = this->freq_map.begin();
            this->freq_map.insert(it, std::pair<int, DoubleLinkList*>(node->freq, new DoubleLinkList()));
        }
        this->freq_map.find(node->freq)->second->append(node);
        this->size++;
        return (Node*)node;
    }
}

std::string LFUCache::to_string(){
    std::ostringstream ss;
    ss << "*********************\n";
    for(std::map<int,DoubleLinkList*>::iterator item=this->freq_map.begin();item!=this->freq_map.end();item++){
        ss << item->first << ": " << item->second->to_string() << "\n";
    }
    return ss.str();
}
