FILES="Q6.cxx"
OUTPUT="Q6"

g++ -Wall -O3 -std=c++14 ${FILES} -o ${OUTPUT} `pkg-config opencv --cflags --libs`