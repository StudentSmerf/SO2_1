NOP?=5
	
main:
	g++ SO2.cpp -o SO2 -std=c++11
	./SO2 ${NOP}

clean:
	rm -f SO2