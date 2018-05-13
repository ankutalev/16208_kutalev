
import java.util.ArrayList;
import java.util.List;
public class Main {

    public static void main(String[] args) throws InterruptedException {
        List<String> clientsAddress = new ArrayList<>();
        clientsAddress.add("192.168.0.196"); //my homepc
        System.out.println("Hello World!");
        TorrentFileParser tp = new TorrentFileParser();
        TorrentFile torrentFile = tp.getTorrentFile("wathmen_torrent.torrent");
        PiecesCreator pc = new PiecesCreator();
        System.out.println(torrentFile.getFileLength());
        Downloader wld = new Downloader(torrentFile.getFileName(),clientsAddress,pc.getFilePieces(torrentFile));
//        TorrentFile torrentFile = tp.getTorrentFile("t.torrent");
//        System.out.println(torrentFile.getFileName());
//        System.out.println(torrentFile.getHashAsHexString());
        }
//        PrintWriter pw
        //try(pw)// он сам проинициализирует и закроет если надо
    }





//есть чувак с файлом. файл нужно подробить на кусочки





//должен быть файл, куски файла; начинаем с одного файла без трекера
//начинаем с одного лича и один кому раздаем (тупа для начала)
//обязательная поддержка отваливающегося клиента
// не должно быть на каждое соединение отдельных тредов
//1 файловый тред,который пишет на диск, 2 сетевых,  главный тред;
//ну,собственно,вот
//найти либу для разбора торрент файлов; абстракции для файлов и кучи кусков, очередь скачивания
//заводим абстракции сервер и клиент
//потом думать про селектор на обработку несколько входящих соединений и думать про несколько закачек
//поддержка нескольких файлов + трекеров по желанию