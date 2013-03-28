COMPILER = g++
FLAGS = -W -Wall
LIBS = -lpthread

first: client server

client: chat_client.o
	$(COMPILER) $(FLAGS) chat_client.o -o chat_client $(LIBS)

server: chat_server.o
	$(COMPILER) $(FLAGS) chat_server.o -o chat_server $(LIBS)

debug:
	$(COMPILER) -c -g chat_client.cpp
	$(COMPILER) -c -g chat_server.cpp
	$(COMPILER) $(FLAGS) chat_server.o -o chat_server $(LIBS)
	$(COMPILER) $(FLAGS) chat_client.o -o chat_client $(LIBS)

chat_client.o:
	$(COMPILER) -c chat_client.cpp

chat_server.o:
	$(COMPILER) -c chat_server.cpp

runclient:
	./chat_client

runserver:
	./chat_server

clean:
	rm chat_client chat_server *.o