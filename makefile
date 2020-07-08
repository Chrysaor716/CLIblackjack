CC = g++
CFLAGS = -std=c++11

TARGET = BlackJack

$(TARGET): src/$(TARGET).cpp src/Deck.cpp src/Player.cpp src/Game.cpp
	$(CC) $(CFLAGS) src/$(TARGET).cpp src/Deck.cpp src/Player.cpp src/Game.cpp -o $(TARGET)

clean:
	$(RM) $(TARGET)
