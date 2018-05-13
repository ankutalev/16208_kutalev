import java.util.ArrayList;

public class ClassicBoard implements ChessBoard {
    @Override
    public void setUpBoard() {

        for (int i = 0; i <BOARD_SIZE;i++) {
            for (int j = 0; j <BOARD_SIZE ; j++) {
                board[i][j] = new Position(i,j,null);
            }
        }
        board[4][4].setFigure(new Rook(Side.BLACK));
        board[1][4].setFigure(new Rook(Side.WHITE));
        board[3][4].setFigure(new Queen(Side.BLACK));
        board[5][6].setFigure(new Knight(Side.WHITE));
    }

    @Override
    public void showBoard() {
        for (int i = 0; i < BOARD_SIZE ; i++) {
            for (int j = 0; j <BOARD_SIZE ; j++) {
                board[i][j].print();
            }
            System.out.println();
        }
        board[1][4].getFigure().makeTurn(this);
    }

    @Override
    public Position getPositionByIndexes(int i, int j) {
        return board[i][j];
    }

    @Override
    public void moveFigure(Figure figure, Position newPosition) {
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (board[i][j].getFigure()==figure) {
                    newPosition.setFigure(figure);
                    board[i][j].setFigure(null);
                    return;
                }
            }
        }
    }

    @Override
    public Position getFigurePosition(Figure f) {
        for (int i = 0; i < BOARD_SIZE ; i++) {
            for (int j = 0; j < BOARD_SIZE ; j++) {
                if (board[i][j].getFigure()==f) {
                   return board[i][j];
                }
            }
        }
        return null;
    }

    @Override
    public int getBoardSize() {
        return BOARD_SIZE;
    }

    private final int BOARD_SIZE = 8;
    private Position[][] board = new Position[BOARD_SIZE][BOARD_SIZE] ;
}
