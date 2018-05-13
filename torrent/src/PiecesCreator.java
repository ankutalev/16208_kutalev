import java.util.ArrayList;
import java.util.List;

public class PiecesCreator {
    public List<FilePiece> getFilePieces(TorrentFile torrentFile) {
        ArrayList<FilePiece> pieces = new ArrayList<>();
       final long fileLength = torrentFile.getFileLength();
       final long pieceLength = torrentFile.getPieceLength();
       final long pieceCount = torrentFile.getPiecesCount();
       int i;
       for (i = 0; i < torrentFile.getPiecesCount()-1; i++) {
            pieces.add(new FilePiece(i,pieceLength));
       }
       pieces.add(new FilePiece(i,fileLength - pieceCount*Long.divideUnsigned(fileLength , pieceCount))); //last piece smaller than all;
       return pieces;
    }
}
