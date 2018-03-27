public class Queen extends Figure {
    Queen(Side side) {
        super(side);
    }


    @Override
    protected void getListOfAvailiblePosition(ChessBoard board, int i, int j) {
        int scaledI = i, scaledJ = j;
      //  System.out.println(i + " " + j);
        while (celllLooking(board, ++scaledI, scaledJ));
        scaledI = i;
        scaledJ = j;
        while (celllLooking(board, --scaledI, scaledJ));
        scaledI = i;
        scaledJ = j;
        while (celllLooking(board, scaledI, ++scaledJ));
        scaledI = i;
        scaledJ = j;
        while (celllLooking(board, scaledI, --scaledJ));
        scaledI = i;
        scaledJ = j;
        while (celllLooking(board, ++scaledI, ++scaledJ));
        scaledI = i;
        scaledJ = j;
        while (celllLooking(board, ++scaledI, --scaledJ));
        scaledI = i;
        scaledJ = j;
        while (celllLooking(board, --scaledI, --scaledJ));
        scaledI = i;
        scaledJ = j;
        while (celllLooking(board, --scaledI, ++scaledJ));
    }


    @Override
    public String getName() {
        return  "[" + side.name() + " Q]";
    }
}
