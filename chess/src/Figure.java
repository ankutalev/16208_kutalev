import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Scanner;

public abstract class Figure {
    Figure (Side side) {
        this.side= side;
    }

     public  Boolean makeTurn(ChessBoard board) {
         int boardSize = board.getBoardSize();
         Position current = board.getFigurePosition(this);
         int jIndex = current.getCharacter()-'a';
         int iIndex = current.getDigit();


         positionsToMove.clear(); // clear at the beginning of turn to ez check check )))))___)0_))
         getListOfAvailiblePosition(board,iIndex,jIndex);

         if (positionsToMove.isEmpty()) {
             System.out.println("THIS FIGURE CAN'T MOVE RIGHT NOW!!!");
             return false;
         }

         int i = 0;
         System.out.println("You can go to:");


         for (Position pos: positionsToMove) {
             System.out.println(++i +") "+pos.getCharacter() +":"+(boardSize-pos.getDigit()));
         }

         Scanner in = new Scanner(new InputStreamReader(System.in));
         i = in.nextInt();
         // todo: unsafe, but with gui its not a problem
         try {
             move(board,positionsToMove.get(i-1));
         }
         catch (IndexOutOfBoundsException exc) {
             System.out.println("You pick incorrect variant; maybe you just want to make turn with another figure?");
             return false;
         }
         return true;
     }

     public abstract String getName();
     public Side getSide() {
        return side;
    }

     protected void move(ChessBoard board, Position position) { //method exist due to king, pawn and rook
         board.moveFigure(this, position);
     }
     protected abstract void getListOfAvailiblePosition(ChessBoard board,int i,int j);


     protected boolean celllLooking(ChessBoard board, int i, int j) {
        CellState check;
        int boardSize = board.getBoardSize();
        if ((i < 0 || j < 0 || i >= boardSize || j >= boardSize))
            return false;
        check = board.getPositionByIndexes(i, j).getStatusForFigure(this);
        switch (check) {
            case WITH_FRIEND:
                return false;
            case WITH_ENEMY:
                positionsToMove.add(board.getPositionByIndexes(i, j));
                return false;
            case EMPTY:
            default:
                positionsToMove.add(board.getPositionByIndexes(i, j));
                return true;
        }
    }
     protected final Side side;
     protected ArrayList <Position> positionsToMove = new ArrayList<>();
}
