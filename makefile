chess: chessMain.o chessGame.o
	g++ -g chessMain.o chessGame.o -o chess

chessMain.o: chessMain.cpp chessGame.h
	g++ -Wall -g -c chessMain.cpp

chessGame.o: chessGame.cpp  chessGame.h chessPiece.h
	g++ -Wall -g -c chessGame.cpp

chessPiece.o: chessPiece.cpp chessPiece.h 
	g++ -Wall -g -c chessPiece.cpp

clean:
	rm -f *.o chess
