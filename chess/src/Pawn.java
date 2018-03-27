public class Pawn extends Figure {

    Pawn( Side side) {
        super(side);
    }

    @Override
    public String getName() {
        return null;
    }

    @Override
    protected void move(ChessBoard board, Position position) {
        isMovedYet=true;
        super.move(board, position);
    }

    @Override
    protected void getListOfAvailiblePosition(ChessBoard board, int i, int j) {
        CellState check;
        int boardSize = board.getBoardSize();
        if ((i < 0 || j < 0 || i >= boardSize || j >= boardSize))
            return;

        check = board.getPositionByIndexes(i,j).getStatusForFigure(this);

    }

    private boolean cellCheck(ChessBoard board, int i, int j) {
        CellState check;
        check = board.getPositionByIndexes(i,j).getStatusForFigure(this);
        switch (check) {
            case EMPTY:
                positionsToMove.add(board.getPositionByIndexes(i,j));
                return true;
            case WITH_ENEMY:
            case WITH_FRIEND:
                default:
                    return false;
        }
    }
    private boolean isMovedYet = false;
}


