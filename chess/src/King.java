public class King extends Figure {

    King(Side side) {
        super(side);
    }

    @Override
    protected void move(ChessBoard board, Position position) {
        isMovedYet = true;
        canCastling = false;
        super.move(board, position);
    }

    @Override
    protected void getListOfAvailiblePosition(ChessBoard board, int i, int j) {

    }

    @Override
    public String getName() {
        return "[" + side.name() + " KING]";
    }

    private boolean isCastlingPossible(ChessBoard chessBoard) {
        if (isChecked)
            return false;

    }

    private boolean rookLooking (ChessBoard chessBoard, int distance) {
        int counter = 0;
        Position current = chessBoard.getFigurePosition(this);
        int jIndex = current.getCharacter() - 'a'; //todo: maybe(definately) need fix this shit???
        int iIndex = current.getDigit();
        while (celllLooking(chessBoard,iIndex,jIndex))
    }
    private boolean canCastling = true;
    private boolean isChecked = false;
    private boolean isMovedYet = false;
}
