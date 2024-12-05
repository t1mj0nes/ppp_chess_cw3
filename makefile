chess: chessMain.o chessGame.o pawn.o chessPiece.o
	g++ -g chessMain.o chessGame.o pawn.o chessPiece.o -o chess

chessMain.o: chessMain.cpp chessGame.h
	g++ -Wall -g -c chessMain.cpp

chessGame.o: chessGame.cpp  chessGame.h chessPiece.h pawn.h
	g++ -Wall -g -c chessGame.cpp

pawn.o: pawn.cpp pawn.h chessPiece.h
	g++ -Wall -g -c pawn.cpp

chessPiece.o: chessPiece.cpp chessPiece.h
	g++ -Wall -g -c chessPiece.cpp

clean:
	rm -f *.o chess
