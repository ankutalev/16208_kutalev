import java.util.List;

public class TorrentFile {


//    private String announceURL; //todo: возможно когда-нибудь появится трекер

    TorrentFile(jBittorrentAPI.TorrentFile file) {
        this.comment = file.comment;
        this.fileName = file.saveAs;
        this.pieceLength = file.pieceLength;
        this.binaryHash = file.info_hash_as_binary;
        this.pieceHashValues = file.piece_hash_values_as_binary;
        this.pieceHashValuesAsHex=file.piece_hash_values_as_hex;
        this.pieceHashValuesAsUrl = file.piece_hash_values_as_url;
        this.fileLength=file.total_length;
        this.hashAsHexString = file.info_hash_as_hex;
    }
    public String getFileName() {
        return fileName;
    }

    public long getPieceLength() {
        return pieceLength;
    }

    public int getPiecesCount() { return  pieceHashValues.size();}

    public String getPieceHashValueAsHex(int index) { return pieceHashValuesAsHex.get(index);}

    public byte[] getPieceHashValueAsBinary (int index) { return  pieceHashValues.get(index);}

    public String getHashAsHexString()  {
        return hashAsHexString;
    }

    public long getFileLength() {
        return fileLength;
    }
    private String comment;
    private String createdBy;
    private long creationDate;
    private String encoding;
    private String fileName;
    private long pieceLength;

    /* In case of multiple files torrent, fileName is the name of a directory
     * and name contains the path of the file to be saved in this directory
     *
     */

    private List name;
    private List length;

    private byte[] binaryHash;
    private String hashAsHexString;
    private String info_hash_as_url;
    private long fileLength;

    private List<byte[]> pieceHashValues;
    private List<String> pieceHashValuesAsHex;
    private List<String> pieceHashValuesAsUrl;
}
