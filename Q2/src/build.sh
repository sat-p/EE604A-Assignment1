FILES="histogram_matching.cxx Q2.cxx"
OUTPUT="Q2"

g++ -Wall -O3 -std=c++14 ${FILES} -o ${OUTPUT} `pkg-config opencv --cflags --libs`