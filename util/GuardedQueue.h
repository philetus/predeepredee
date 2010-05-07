/*  GuardedQueue.h
 *
 *  fifo queue guarded by sdl mutex
 *
 *  copyright 2010 michael philetus weller <philetus@gmail.com>
 *  
 *  you may redistribute or modify this code under the terms of the 
 *  GNU General Public Licence version 3.
 *  for more information see: http://www.gnu.org/licenses/gpl.html
 *  
 */
 
#ifndef PDPD_UTIL_GUARDED_QUEUE
#define PDPD_UTIL_GUARDED_QUEUE

#include <iostream>
#include <deque>
#include <SDL/SDL.h>
#include <SDL/SDL_thread.h>

namespace pdpd
{
    namespace util
    {
        template<class Data>
        class GuardedQueue
        {
            std::deque<Data> stack;
            SDL_mutex* lock;
        public:
            
            GuardedQueue()
            {
                lock = SDL_CreateMutex();
            }
                        
            ~GuardedQueue()
            {
                SDL_DestroyMutex(lock);
            }

            bool is_empty()
            {
                bool b;
                
                if(SDL_mutexP(lock) < 0) // acquire lock first
                {
                    std::cout << "couldn't lock guarded queue!" << std::endl;
                    return false;
                }
                
                b = stack.empty();
                
                if(SDL_mutexV(lock) < 0) // release lock after
                {
                    std::cout << "couldn't unlock guarded queue!" << std::endl;
                    return false;
                }
                
                return b;
            }
            
            void push(Data d)
            {
            
                if(SDL_mutexP(lock) < 0) // acquire lock first
                {
                    std::cout << "couldn't lock guarded queue!" << std::endl;
                    return;
                }
                
                stack.push_back(d);

                if(SDL_mutexV(lock) < 0) // release lock after
                {
                    std::cout << "couldn't unlock guarded queue!" << std::endl;
                    return;
                }
            }
            
            Data pop()
            {
                Data temp;
                
                if(SDL_mutexP(lock) < 0) // acquire lock first
                {
                    std::cout << "couldn't lock guarded queue!" << std::endl;
                    return NULL;
                }

                temp = stack.front();
                stack.pop_front();
                
                if(SDL_mutexV(lock) < 0) // release lock after
                {
                    std::cout << "couldn't unlock guarded queue!" << std::endl;
                    return NULL;
                }

                return temp;
            }
        };
    }
} 
#endif // PDPD_UTIL_GUARDED_QUEUE
