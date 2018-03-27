public class Position {
    Position(int digit,int character,Figure figure) {
        this.digit = digit;
        this.figure = figure;
        this.character = (char)(character+'a');
    }
    public Figure getFigure() {
        return figure;
    }

    public void print () {
        if (figure==null)
            System.out.print(" ["+character+":"+(8-digit)+"] ");
        else
            System.out.print(figure.getName());
    }

    public int getDigit() {
        return digit;
    }

    public char getCharacter() {
        return character;
    }

    public void setFigure(Figure figure) {
        this.figure = figure;
    }

    public CellState getStatusForFigure  (Figure figure) {
        //return this.figure==null || figure.getSide()!=this.figure.getSide();
        if (this.figure==null)
            return CellState.EMPTY;
        return (figure.getSide()!=this.figure.getSide()) ? CellState.WITH_ENEMY : CellState.WITH_FRIEND;
    }
    private final int digit;
    private final char character;
    private Figure figure;
}
