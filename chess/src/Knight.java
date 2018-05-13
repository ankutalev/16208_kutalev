public class Knight extends Figure {

    Knight(Side side) {
        super(side);
    }

    @Override
    public String getName() {
        return  "[" + side.name() + " K]";
    }

    @Override
    protected void getListOfAvailiblePosition(ChessBoard board, int i, int j) {
        celllLooking(board,i+2,j+1);
        celllLooking(board, i+2, j-1);
        celllLooking(board, i-2, j+1);
        celllLooking(board,i-2,j-1);
    }
}
