import java.io.*;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ThreadLocalRandom;

public class Downloader {
    Downloader (String fileName,List<String> ipAdresses, List <FilePiece> filePieces) {
        try {
            this.fileName = fileName;
            this.pieceNumber= filePieces.size();
            receivedPiece = ByteBuffer.allocate(filePieces.get(0).getLength());
            for (int i = 0; i < pieceNumber; i++) {
                recordedPieces.put(i,false);
            }
            SocketChannel sc;
            String fullIp;


            for (String ip: ipAdresses) {
                sc = SocketChannel.open(new InetSocketAddress(ip,9875));
                fullIp = sc.getRemoteAddress().toString();
                sendInfoMessage(sc);
                receiveMessage(sc);
                int availablePieces = tableOfAvailablePieces.get(fullIp).size();
                if(availablePieces>0) {
                    int nextPieceNumber = getNumberOfNextRecordedPiece(fullIp);
                    System.out.println(nextPieceNumber);
                    downloadPiece(sc,filePieces.get(nextPieceNumber));
                }


            }

        } catch (IOException e) {
            e.printStackTrace();
            System.out.println("error");
            System.exit(0);
        }
    }

    private void downloadPiece(SocketChannel sc, FilePiece piece)  {
        pieceLength = piece.getLength();
        String msg = fileName+" "+piece.getId()*pieceLength+" "+pieceLength;
        try {

            System.out.println("dlina :mesagi" +msg.length());
            System.out.println("dlina kuska"+pieceLength);
            ByteBuffer size = ByteBuffer.allocate(4);
            size.putInt(msg.length());
            size.rewind();
            sc.write(size);
            sc.write(ByteBuffer.wrap(msg.getBytes()));
            System.out.println(msg);
            sc.read(receivedPiece);
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println(pieceLength);
        System.out.println(receivedPiece);
        System.exit(0);

//           os.println(fileName+" "+piece.getId()*pieceLength+" "+piece.getLength());
//           os.flush();
           byte data[] = new byte[piece.getLength()];


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
            parseMessage(answer,sc.getRemoteAddress().toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void parseMessage(String msg,String source) {
        if (!tableOfAvailablePieces.containsKey(source))
            tableOfAvailablePieces.put(source,new ArrayList<>());

        switch (msg) {
            case "ALL":
                for (int i = 0; i < pieceNumber; i++) {
                    tableOfAvailablePieces.get(source).add(i);
                    System.out.println(tableOfAvailablePieces.get(source).get(i));
                }
                break;
            case "NONE":
                break;
            default:
                String [] data = msg.split(" ");
                if (data[0].equals("PIECES")) {
                    for (String s:data) {
                        tableOfAvailablePieces.get(source).add(Integer.parseInt(s));
                    }
                }
                else
                    System.out.println("PRISLALI HUYNU!");
        }
    }

    private int getNumberOfNextRecordedPiece(String src) {
        Integer index;
        do {
             index = ThreadLocalRandom.current().nextInt(0,tableOfAvailablePieces.get(src).size()-1);
        }while (recordedPieces.get(index));

        int pieceNumber = tableOfAvailablePieces.get(src).get(index);
        recordedPieces.replace(pieceNumber,true);
        return pieceNumber;
    }

    private Map<Integer,Boolean> recordedPieces = new HashMap<>();
    private Map<String,List<Integer>> tableOfAvailablePieces = new HashMap<>();
    private int pieceLength;
    private String fileName;
    private FileWorker fw;
    private int pieceNumber;
    private ByteBuffer receivedPiece;
}
























/*
    есть тред "раздающий" - он долбится в ендлесс лупе и смотрит, не постучались ли  к нему
    если постучались, он смотрит что именнно у него спрашивают - название файла, номер куска длину и стартпоинт
    при на



* */