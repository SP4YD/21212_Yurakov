package ru.nsu.yurakov.Torrent.PiecesManager;

import ru.nsu.yurakov.Torrent.ParserTorrent.TorrentInfo;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.BitSet;

import static java.lang.Long.min;

public class PiecesManager {
    public PiecesManager(TorrentInfo info, File file) throws IOException {
        this.file = file;
        this.info = info;

        sizePiece = (int) min(info.sizeFile, info.sizePiece);
        countPieces = (int) Math.ceil((double)info.sizeFile / info.sizePiece);
        sizeLastPiece = (int) (info.sizeFile - (countPieces - 1) * info.sizePiece);
//        System.out.println("sizeLastPiece - " + sizeLastPiece);
//        System.out.println("countPieces - " + countPieces);

        CheckingFile();
    }

    public void CheckingFile() throws IOException {
        if (!file.isFile()) {
            file.createNewFile();
        }
        try (FileInputStream fileInputStream = new FileInputStream(file)) {
            byte[] buffer = new byte[sizePiece];
            sizeBitSet = countPieces;
            whatHave = new BitSet(sizeBitSet);
            for (int i = 0; i < sizeBitSet - 1; ++i) {
                //System.out.println("sizePiece = " + sizePiece);
                fileInputStream.read(buffer);

                MessageDigest md = MessageDigest.getInstance("SHA-1");
                byte[] realHash = md.digest(buffer);

                whatHave.set(i);
                for (int j = 0; j < 20; ++j) {
                    if (realHash[j] != info.pieces[i * 20 + j]) {
                        //System.out.println("Hash куска №" + i + " не совпал");
                        whatHave.clear(i);
                        break;
                    }
                }

//                System.out.println("Size = " + getWhatHave().length());
//                System.out.println("До [0] = " + getWhatHave().get(0));
//                System.out.println("До [1] = " + getWhatHave().get(1));
                //System.out.println(i + " кусок = " + whatHave.get(i));
            }

            buffer = new byte[sizeLastPiece];
            fileInputStream.read(buffer);

            MessageDigest md = MessageDigest.getInstance("SHA-1");
            byte[] realHash = md.digest(buffer);
            int index = sizeBitSet - 1;
            whatHave.set(index);
            for (int j = 0; j < 20; ++j) {
                if (realHash[j] != info.pieces[index * 20 + j]) {
                    //System.out.println("Hash куска №" + index + " не совпал");
                    whatHave.clear(index);
                    break;
                }
            }
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }

    public void setPieceReceived(int index) {
        whatHave.set(index);
        //System.out.println("bitSet[" + index + "] = " + whatHave.get(index));
    }

    public int getIndexPiece() {
        for (int i = 0; i < sizeBitSet; ++i) {
            if (!whatHave.get(i) && bitSetChannel.get(i)) {
                return i;
            }
        }

        return -1;
    }

    public boolean isFileUploaded() {
        for (int i = 0; i < sizeBitSet; ++i) {
            if (!whatHave.get(i)) {
//                System.out.println("Client: Нет куска - " + i);
                return false;
            }
        }

        return true;
    }

    public int getSizePiece(int index) {
        if (index != countPieces - 1) {
            return sizePiece;
        } else {
            return sizeLastPiece;
        }
    }

    public void setBitSetChannel(BitSet bitSetChannel) { this.bitSetChannel = bitSetChannel; }

    public BitSet getWhatHave() { return whatHave; }

    public int getCountPieces() { return countPieces; }

    private BitSet bitSetChannel;
    private int sizeBitSet;
    private int sizePiece;
    private int sizeLastPiece;
    private int countPieces;
    private BitSet whatHave;
    private TorrentInfo info;
    private File file;
}
