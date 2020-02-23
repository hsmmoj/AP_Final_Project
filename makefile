
CPPFLAGS = -Wall -pedantic -std=c++11
OBJS =main.o Interface.o App.o Person.o Check.o Product.o Cart.o
CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build
TEMPLATE_DIR=.template


all: $(BUILD_DIR) myserver.out

myserver.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/Interface.o $(BUILD_DIR)/App.o $(BUILD_DIR)/Person.o $(BUILD_DIR)/Check.o $(BUILD_DIR)/Product.o $(BUILD_DIR)/Offer.o $(BUILD_DIR)/Cart.o $(BUILD_DIR)/Model.o $(BUILD_DIR)/Data.o
	g++ $(CPPFLAGS) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_DIR)/Interface.o $(BUILD_DIR)/App.o $(BUILD_DIR)/Person.o $(BUILD_DIR)/Check.o $(BUILD_DIR)/Product.o $(BUILD_DIR)/Offer.o $(BUILD_DIR)/Cart.o $(BUILD_DIR)/Model.o $(BUILD_DIR)/Data.o -o myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	g++ $(CPPFLAGS) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	g++ $(CPPFLAGS) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	g++ $(CPPFLAGS) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	g++ $(CPPFLAGS) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	g++ $(CPPFLAGS) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	g++ $(CPPFLAGS) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	g++ $(CPPFLAGS) -c handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	g++ $(CPPFLAGS) -c my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp handlers.hpp App.hpp
	g++ $(CPPFLAGS) -c main.cpp -o $(BUILD_DIR)/main.o


$(BUILD_DIR)/Interface.o : Interface.cpp Interface.hpp 
	g++ $(CPPFLAGS) -c Interface.cpp -o $(BUILD_DIR)/Interface.o

$(BUILD_DIR)/App.o : App.cpp App.hpp Check.hpp model.hpp
	g++ $(CPPFLAGS) -c App.cpp -o $(BUILD_DIR)/App.o

$(BUILD_DIR)/Cart.o : Cart.cpp Cart.hpp Offer.hpp
	g++ $(CPPFLAGS) -c Cart.cpp -o $(BUILD_DIR)/Cart.o

$(BUILD_DIR)/Offer.o : Offer.cpp Offer.hpp Product.hpp
	g++ $(CPPFLAGS) -c Offer.cpp -o $(BUILD_DIR)/Offer.o

$(BUILD_DIR)/Product.o : Product.cpp Product.hpp
	g++ $(CPPFLAGS) -c Product.cpp -o $(BUILD_DIR)/Product.o

$(BUILD_DIR)/Check.o : Check.cpp Check.hpp App.hpp
	g++ $(CPPFLAGS) -c Check.cpp -o $(BUILD_DIR)/Check.o

$(BUILD_DIR)/Person.o: Person.cpp Person.hpp Offer.hpp
	g++ $(CPPFLAGS) -c Person.cpp -o $(BUILD_DIR)/Person.o

$(BUILD_DIR)/Model.o: model.cpp model.hpp data.hpp
	g++ $(CPPFLAGS) -c model.cpp -o $(BUILD_DIR)/Model.o

$(BUILD_DIR)/Data.o: data.cpp data.hpp
	g++ $(CPPFLAGS) -c data.cpp -o $(BUILD_DIR)/Data.o