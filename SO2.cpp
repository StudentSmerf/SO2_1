#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>

using namespace std;

void philosopher(int id, std::mutex* forks, int num_philosophers) {
    while (true) {
        unique_lock<std::mutex> left_fork(forks[id]);  
        this_thread::sleep_for(chrono::milliseconds(10)); 
        unique_lock<std::mutex> right_fork(forks[(id + 1) % num_philosophers]); 

        cout << "Philosopher " << id << " is eating." << endl;
        this_thread::sleep_for(chrono::milliseconds(100)); 

        cout << "Philosopher " << id << " finished eating." << endl;
    }
}

int main(int argc, char* argv[]) {
    
    cout << "Dining Philosophers Problem" << endl;

    int num_philosophers = stoi(argv[1]);

    //check if num_philosophers is set corectly
    cout << "Number of philosophers: " << num_philosophers << endl;

    if (num_philosophers < 2) {  
        cerr << "Number of philosophers can't be less than 2!" << endl;
        return 1;
    }

    std::mutex* forks = new std::mutex[num_philosophers];  

    thread* threads = new thread[num_philosophers];  

    for (int i = 0; i < num_philosophers; ++i) {
        threads[i] = thread(philosopher, i, forks, num_philosophers);
    }

    for (int i = 0; i < num_philosophers; ++i) {
        threads[i].join();
    }

    delete[] forks;
    delete[] threads;

    return 0;
}
