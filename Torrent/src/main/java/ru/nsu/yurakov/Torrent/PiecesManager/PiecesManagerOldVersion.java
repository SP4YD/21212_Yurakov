//package ru.nsu.yurakov.Torrent.PiecesManager;
//
//import ru.nsu.yurakov.Torrent.ParserTorrent.TorrentInfo;
//
//import java.io.File;
//import java.io.FileInputStream;
//import java.io.IOException;
//import java.security.MessageDigest;
//import java.security.NoSuchAlgorithmException;
//import java.util.BitSet;
//
//import static java.lang.Long.min;
//
//public class PiecesManagerOldVersion {
//    public PiecesManagerOldVersion(TorrentInfo info, File file) throws IOException {
//        this.file = file;
//        this.info = info;
//
//        sizePiece = (int) min(info.sizeFile, info.sizePiece);
//
//        CheckingFile();
//        NewPiece(sizePiece);
//    }
//    public void NewPiece(int sizePiece) {
//        Piece = new byte[sizePiece];
//        len = 0;
//    }
//
//    public void CheckingFile() throws IOException {
//        if (!file.isFile()) {
//            file.createNewFile();
//        }
//        try (FileInputStream fileInputStream = new FileInputStream(file)) {
//            byte[] buffer = new byte[sizePiece];
//            sizeBitSet = (int) (info.sizeFile / info.sizePiece + (info.sizeFile % info.sizePiece == 0 ? 0 : 1));
//            whatHave = new BitSet(sizeBitSet);
//            for (int i = 0; i < sizeBitSet; ++i) {
//                //System.out.println("sizePiece = " + sizePiece);
//                fileInputStream.read(buffer, 0, sizePiece);
//
//                MessageDigest md = MessageDigest.getInstance("SHA-1");
//                byte[] realHash = md.digest(buffer);
//
//                whatHave.set(i);
//                for (int j = 0; j < 20; ++j) {
//                    if (realHash[j] != info.pieces[i * 20 + j]) {
//                        //System.out.println("Hash куска не совпал");
//                        whatHave.clear(i);
//                        break;
//                    }
//                }
//
////                System.out.println("Size = " + getWhatHave().length());
////                System.out.println("До [0] = " + getWhatHave().get(0));
////                System.out.println("До [1] = " + getWhatHave().get(1));
//                //System.out.println(i + " кусок = " + whatHave.get(i));
//            }
//        } catch (NoSuchAlgorithmException e) {
//            throw new RuntimeException(e);
//        }
//    }
//
//    public int getIndexPiece() {
//        for (int i = 0; i < sizeBitSet; ++i) {
//            if (!getWhatHave().get(i) && bitSetChannel.get(i)) {
//                return i;
//            }
//        }
//
//        return -1;
//    }
//
//    public byte[] getPiece() {
//        return Piece;
//    }
//    public int getLen() {
//        return len;
//    }
//    public void setBitSetChannel(BitSet bitSetChannel) { this.bitSetChannel = bitSetChannel; }
//
//    public BitSet getWhatHave() {
//        return whatHave;
//    }
//
//    private BitSet bitSetChannel;
//    private int sizeBitSet;
//    private int sizePiece;
//    private byte[] Piece;
//    private int len = 0;
//    private final int BUF_SIZE = 100;
//    private BitSet whatHave;
//    private TorrentInfo info;
//    private File file;
//}
