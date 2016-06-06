#include <iostream>
#include <thread>

class thread_guard {
    private:
        std::thread& t;

    public:
        explicit thread_guard(std::thread& t_): t(t_) {}  // constructor


        ~ thread_guard() {    // destructor
            if (t.joinable())
                t.join();
        }


        thread_guard(thread_guard const&)=delete;  // disable the copy constructor
        thread_guard& operator=(thread_guard const&)=delete;  // disable the assignment operator
};

class Worker {
    private:
        int i;
    public:
        Worker(int var) : i(var) {}  // constructor

        void do_work() {
           for(int j = 0; j < i; j++)
                std::cout << j;
            std::cout << std::endl;
        }
        void operator () () {
            do_work();
        }
};

int main(){

    Worker w1 {5};
    std::thread thread1(w1);
    thread_guard tg1(thread1);

    Worker w2 {7};
    std::thread thread2(w2);
    thread_guard tg2(thread2);

    Worker w3 {9};
    std::thread thread3(w3);
    thread_guard tg3(thread3);
    return 0;
}
