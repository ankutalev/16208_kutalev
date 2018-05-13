import jBittorrentAPI.TorrentProcessor;
public class TorrentFileParser {
//    TorrentFileParser(String name) {
//        todo:
//    }
    public TorrentFile getTorrentFile (String filename){
        TorrentProcessor tp = new TorrentProcessor();
        return new TorrentFile(tp.getTorrentFile(tp.parseTorrent(filename)));
//            return tp.getTorrentFile(tp.parseTorrent(filename));
    }


}
