#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>

using namespace std;

void philosopher(int id, std::mutex* forks, int num_philosophers) {
    int dinner_time = 0;
    while (dinner_time < 10) {
        cout << "Philosopher " << id << " is thinking." << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));

        //Lock two forks (left and right) using std::lock to avoid deadlock
        std::lock(forks[id], forks[(id + 1) % num_philosophers]);
        this_thread::sleep_for(chrono::milliseconds(100)); 

        //Lock the forks using std::unique_lock to ensure they are unlocked after use
        unique_lock<std::mutex> left_fork(forks[id], std::adopt_lock);  
        unique_lock<std::mutex> right_fork(forks[(id + 1) % num_philosophers], std::adopt_lock); 
        
        cout << "Philosopher " << id << " is eating." << endl;
        this_thread::sleep_for(chrono::milliseconds(1000)); 

        cout << "Philosopher " << id << " finished eating." << endl;
        //Ensure forks are unlocked after eating
        left_fork.unlock();
        right_fork.unlock();
        
        dinner_time++;
    }
}

int main(int argc, char* argv[]) {
    cout << "Dining Philosophers Problem" << endl;
    //Set number of philosophers
    int num_philosophers = 5;
    try {
        num_philosophers = stoi(argv[1]);
    } catch (const std::exception& e) {
        cerr << "Invalid number of philosophers: " << e.what() << endl;
        return 1;
    }
    
    //check if num_philosophers is set corectly
    cout << "Number of philosophers: " << num_philosophers << endl;
    if (num_philosophers < 2) {  
        cerr << "Number of philosophers can't be less than 2!" << endl;
        return 1;
    }

    //Create forks (mutexes) and philosophers (threads)
    std::mutex* forks = new std::mutex[num_philosophers];  
    thread* threads = new thread[num_philosophers];  

    //Create threads for each philosopher
    for (int i = 0; i < num_philosophers; ++i) {
        threads[i] = thread(philosopher, i, forks, num_philosophers);
    }

    //Join threads to ensure they finish before main thread exits
    for (int i = 0; i < num_philosophers; ++i) {
        threads[i].join();
    }

    //Clean up
    delete[] forks;
    delete[] threads;
    cout << "Dinner time is over" << endl;
    return 0;
}
