FILES="pixel_nlm.cxx Q7.cxx"
OUTPUT="Q7"

g++ -Wall -O3 -std=c++14 ${FILES} -o ${OUTPUT} `pkg-config opencv --cflags --libs`