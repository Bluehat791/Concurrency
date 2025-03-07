#include<iostream>
#include<thread>

void hello()
{
    std::cout << "Hello world in concurrency!\n";
}

int main()
{
    std::thread t(hello);
    t.join();
}