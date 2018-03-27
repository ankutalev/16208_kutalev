public interface ChessBoard {
    void setUpBoard();
    void moveFigure(Figure figure,Position position);
    Position getFigurePosition(Figure figure);
    Position getPositionByIndexes(int i,int j);
    int getBoardSize();
    void showBoard();
}
