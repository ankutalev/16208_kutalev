import java.io.*;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Downloader {
    Downloader (String fileName,List<String> ipAdresses, List <FilePiece> filePieces) {
        try {
            this.fileName = fileName;
            this.pieceNumber= filePieces.size();
            SocketChannel sc;
            for (String ip: ipAdresses) {
                sc = SocketChannel.open(new InetSocketAddress(ip,9875));
                sendInfoMessage(sc);
                receiveMessage(sc);
            }
//  sc.connect(new InetSocketAddress(ipAdresses.get(0),9875));


            try {
                Thread.sleep(50000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            //            sc.close();
//            System.out.println(new String(heh.array()));
//            System.exit(-2);
//            System.exit(0);
//            pieceLength = (int) filePieces.get(0).getLength();
//            for (FilePiece fp: filePieces) {
//                firstTestSocket = new Socket(ipAdresses.get(0),9875);
//                downloadPiece(fp);
//            }

//                downloadPiece(filePieces.get(0));
//                firstTestSocket = new Socket(ipAdresses.get(0),9875);
//                downloadPiece(filePieces.get(1));

        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("error");
            System.exit(0);
        }
    }

    private void downloadPiece(FilePiece piece)  {
//       try (FileOutputStream fileWriter = new FileOutputStream("/home/ulyssess/tmp/piece"+piece.getId());
//            DataInputStream is = new DataInputStream(firstTestSocket.getInputStream());
//            PrintWriter os = new PrintWriter(new OutputStreamWriter(firstTestSocket.getOutputStream())) ) {

//           os.println(fileName+" "+piece.getId()*pieceLength+" "+piece.getLength());
//           os.flush();
           byte data[] = new byte[(int) piece.getLength()];


//           is.readNBytes(data,0, (int) piece.getLength());
           piece.data = data;
//           fileWriter.write(piece.data); // todo: eto toje v failovy tred pihnut'
           FileWorker.invokeLater(new RecordPieceTask(piece,fileName));
       }

//       catch (IOException e) {
//           e.printStackTrace();
//           System.out.println("heh'");
//           System.exit(0);
//       }

    }

    private void sendInfoMessage(SocketChannel sc) {
        System.out.println(fileName);
        ByteBuffer a = ByteBuffer.allocate(4);
        a.putInt(fileName.length());
        a.rewind();
        try {
            sc.write(a);
            sc.write(ByteBuffer.wrap(fileName.getBytes()));
        }
        catch (IOException e) {
            e.printStackTrace();
        }

    }

    private void receiveMessage(SocketChannel sc) {
        ByteBuffer size = ByteBuffer.allocate(4);
        try {
            sc.read(size);
            size.rewind();
            int len  = size.getInt();
            ByteBuffer msg = ByteBuffer.allocate(len);
            sc.read(msg);
            byte[] data = new byte[msg.position()];
            msg.rewind();
            msg.get(data);
            String answer = new String(data);
            System.out.println(answer);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private Map<String,Boolean> tableOfAvailablePieces = new HashMap<>();
    private int pieceLength;
    private String fileName;
    private FileWorker fw;
    private int pieceNumber;
}
























/*
    есть тред "раздающий" - он долбится в ендлесс лупе и смотрит, не постучались ли  к нему
    если постучались, он смотрит что именнно у него спрашивают - название файла, номер куска длину и стартпоинт
    при на



* */