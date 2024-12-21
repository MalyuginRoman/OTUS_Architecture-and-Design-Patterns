all:
	g++ -std=c++17 main.cpp icommand.cpp object.cpp -o main_adapter
test:
	chmod +x main_adapter
clean:
	$(RM) main_adapter
