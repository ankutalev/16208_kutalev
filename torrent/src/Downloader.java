import java.io.*;
import java.net.Socket;
import java.util.List;

public class Downloader {
    Downloader (String fileName,List<String> ipAdresses, List <FilePiece> filePieces) throws InterruptedException {
        try {
            this.fileName = fileName;
            firstTestSocket = new Socket(ipAdresses.get(0),9875);

              downloadPiece(filePieces.get(filePieces.size()-2));
//            Thread.sleep(10000);
//            downloadPiece(filePieces.get(filePieces.size()-1));
//            Thread.sleep(10000);
//            downloadPiece(filePieces.get(0));
        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("ti huy");
            System.exit(0);
        }
    }

   private void downloadPiece(FilePiece piece)  {
       try (FileOutputStream fileWriter = new FileOutputStream("/home/ulyssess/tmp/piece1");
            InputStream is = firstTestSocket.getInputStream();
            PrintWriter os = new PrintWriter(new OutputStreamWriter(firstTestSocket.getOutputStream())) ) {
            os.write(fileName+" "+piece.getId()+" "+piece.getLength());
       } catch (IOException e) {
           System.out.println("Ne mogu nichego otkrit'");
           System.exit(0);
       }

   }
//   private
   private String fileName;
   private Socket firstTestSocket;
}
/*
    есть тред "раздающий" - он долбится в ендлесс лупе и смотрит, не постучались ли  к нему
    если постучались, он смотрит что именнно у него спрашивают - название файла, номер куска длину и стартпоинт
    при на

* */