
build:
	g++ -o sedenv sedenv.cpp

test: build
	./sedenv < test.toml
