public class FilePiece {
    private final  long startPoint;
    private final int id;
    private final long length;
    private byte [] hashAsBinary; //todo: think about necessary of this
    private byte [] data;
    private String hashAsString;


    public FilePiece(int id, long pieceLength) {
        this.id = id;
        this.startPoint =  id*pieceLength;
        this.length = pieceLength;
    }

    public long getStartPoint() {
        return startPoint;
    }

    public int getId() {
        return id;
    }

    public long getLength() {
        return length;
    }
}

//длина файла % длина куска
