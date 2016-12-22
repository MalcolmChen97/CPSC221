#ifndef MYPRIORITY_QUEUE_H
#define MYPRIORITY_QUEUE_H
#include <vector>
#include <functional>

namespace PQ {
    
    template<typename Item_Type,
    typename Container = std::vector<Item_Type>,
    typename Compare = std::less<Item_Type> >
    class mypriority_queue {
    public:
        
        mypriority_queue() {}
        ~mypriority_queue(){}
        void push(const Item_Type& item){
                the_data.push_back(item);
                int child = size() - 1;
                int parent = (child - 1) / 2;
              
                while (parent >= 0
                       && comp(the_data[parent], the_data[child])) {
                    std::swap(the_data[child], the_data[parent]);
                    child = parent;
                    parent = (child - 1) / 2;
                }
        }
                void pop(){
            if (size() == 1) {
                the_data.pop_back();
                return;
            }
            std::swap(the_data[0], the_data[size() - 1]);
            the_data.pop_back();
            int parent = 0;
            while (true) {
                int left_child = 2 * parent + 1;
                if (left_child >= size())
                    break; // out of heap
                int right_child = left_child + 1;
                int max_child = left_child;
                if (right_child < size()
                    && comp(the_data[left_child], the_data[right_child]))
                    max_child = right_child;
                if (comp(the_data[parent], the_data[max_child])) {
                    std::swap(the_data[max_child], the_data[parent]);
                    parent = max_child;
                }
                else
                    break;
            }
        }
        bool empty() const {return the_data.empty();}
        
               
        size_t size() const {return the_data.size();}
        /** Return a reference to the smallest item */
        const Item_Type& top() const {return the_data.front();}
    private:
        
        Container the_data;
        
        Compare comp;
    };
   
}
#endif
