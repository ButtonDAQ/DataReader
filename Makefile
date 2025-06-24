all:
	g++ src/reader.cpp -o Reader -I include -I Dependencies/ToolFrameworkCore/include -L Dependencies/ToolFrameworkCore/lib/ -lStore

clean:
	rm -rf Reader
