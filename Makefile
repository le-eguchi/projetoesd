CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

TARGET = simulador

SRC = Aluno.cpp AVL.cpp Hash.cpp Lista.cpp SkipList.cpp \
      Trie.cpp TrieOptimizada.cpp Gerador.cpp TratamentoDados.cpp \
      Benchmark.cpp main.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -f $(TARGET) simulador.exe
