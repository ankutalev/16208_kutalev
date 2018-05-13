public class Bishop extends Figure {
    Bishop(Side side) {
        super(side);
    }

    @Override
    protected void getListOfAvailiblePosition(ChessBoard board, int i, int j) {
        diagonalSearch(board, i, j);
    }

    private void diagonalSearch(ChessBoard board, int i, int j) {
        int scaledI = i, scaledJ = j;
        System.out.println(i + " " + j);
        while (celllLooking(board, ++scaledI, ++scaledJ)) ;
        scaledI = i;
        scaledJ = j;
        while (celllLooking(board, ++scaledI, --scaledJ)) ;
        scaledI = i;
        scaledJ = j;
        while (celllLooking(board, --scaledI, ++scaledJ)) ;
        scaledI = i;
        scaledJ = j;
        while (celllLooking(board, --scaledI, --scaledJ)) ;
    }

    @Override
    public String getName() {
        return "[" + side.name() + " B]";
    }

}


