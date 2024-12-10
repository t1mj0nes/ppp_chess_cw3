chess: chessMain.o chessGame.o bishop.o king.o knight.o pawn.o queen.o rook.o  chessPiece.o colour.o
	g++ -g chessMain.o chessGame.o bishop.o king.o knight.o pawn.o queen.o rook.o chessPiece.o colour.o -o chess

chessMain.o: chessMain.cpp chessGame.h
	g++ -Wall -g -c chessMain.cpp

chessGame.o: chessGame.cpp chessGame.h chessPiece.h bishop.h knight.h pawn.h queen.h rook.h king.h colour.h
	g++ -Wall -g -c chessGame.cpp

bishop.o: bishop.cpp bishop.h chessPiece.h colour.h
	g++ -Wall -g -c bishop.cpp

king.o: king.cpp king.h chessPiece.h colour.h
	g++ -Wall -g -c king.cpp

knight.o: knight.cpp knight.h chessPiece.h colour.h
	g++ -Wall -g -c knight.cpp

pawn.o: pawn.cpp pawn.h chessPiece.h colour.h
	g++ -Wall -g -c pawn.cpp

queen.o: queen.cpp queen.h chessPiece.h colour.h
	g++ -Wall -g -c queen.cpp

rook.o: rook.cpp rook.h chessPiece.h colour.h
	g++ -Wall -g -c rook.cpp

chessPiece.o: chessPiece.cpp chessPiece.h colour.h
	g++ -Wall -g -c chessPiece.cpp

colour.o: colour.cpp colour.h
	g++ -Wall -g -c colour.cpp

clean:
	rm -f *.o chess
