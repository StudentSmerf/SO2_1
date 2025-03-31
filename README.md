# SO2_1
## Kurs Systemy Operacyjne 2
### Projekt 1


## Instalation
To download project clone repository using: 
`git clone https://github.com/StudentSmerf/SO2_1.git`

## Description
This project uses std::thread and std::mutex to solve **Dining Philosophers Problem**. 
In this problem philosophers are sitting at the oval table and can either think or eat. To eat philosophers need right and left fork. Between every two philosophers, there is one fork.
The number of philosophers can be changed at the start of the program. 

## How to use
To start program use:
`make`
in the project directory.

To change number of philosophers to for example 8 use:
`make NOP=8`

Default NOP is set to 5.