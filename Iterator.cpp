/*  Iterator.cpp
 *
 *  sane iterator with next() and has_next()
 *  
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#include "Iterator.h"

using namespace predeepredee
{
    // different constructor for each container type
    // gets begin and end pointers and casts them as void pointers
    // but remembers what container type they came from
    Iterator<Data>::Iterator(const std::vector& v)
    {
        // get begin and end iterators
        vector_iter b = v.begin();
        vector_iter e = v.end();
        
        // cast them as void pointers to save them
        current = reinterpret_cast<void*> &b;
        end = reinterpret_cast<void*> &e;
        
        // remember what type of container they belong to though
        container = vector_type;
    }
    Iterator<Data>::Iterator(const std::deque& d)
    {
        // get begin and end iterators
        deque_iter b = d.begin();
        deque_iter e = d.end();
        
        // cast them as void pointers to save them
        current = reinterpret_cast<void*> &b;
        end = reinterpret_cast<void*> &e;
        
        // remember what type of container they belong to though
        container = deque_type;
    }
    Iterator<Data>::Iterator(const std::list& l)
    {
        // get begin and end iterators
        list_iter b = l.begin();
        list_iter e = l.end();
        
        // cast them as void pointers to save them
        current = reinterpret_cast<void*> &b;
        end = reinterpret_cast<void*> &e;
        
        // remember what type of container they belong to though
        container = list_type;
    }
    
    Iterator<Data>::~Iterator()
    {
        delete current;
        delete end;
        delete container;
    }
    
    // cast begin and end back to appropriate iterator type
    // and check if there are more elements left
    bool Iterator<Data>::has_next()
    {
        switch(ct)
        {
            case vector_type:
                return *(reinterpret_cast<vector_iter*> current)
                    == *(reinterpret_cast<vector_iter*> end);
                break;
            case deque_type:
                return *(reinterpret_cast<deque_iter*> current)
                    == *(reinterpret_cast<deque_iter*> end);
                break;
            case list_type:
                return *(reinterpret_cast<list_iter*> current)
                    == *(reinterpret_cast<list_iter*> end);
                break;
        }
    }
    
    // cast current to appropriate iterator type to return next element
    Data Iterator<Data>::next()
    {
        Data d;
        switch(ct)
        {
            case vector_type:
                vector_iter c = *(reinterpret_cast<vector_iter*> current);
                d = *c;
                c++;
                break;
            case deque_type:
                vector_iter c = *(reinterpret_cast<deque_iter*> current);
                d = *c;
                c++;
                break;
            case list_type:
                vector_iter c = *(reinterpret_cast<list_iter*> current);
                d = *c;
                c++;
                break;
        }
        return d; // return element
    }
}
