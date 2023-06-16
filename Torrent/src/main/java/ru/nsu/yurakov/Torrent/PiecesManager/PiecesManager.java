package ru.nsu.yurakov.Torrent.PiecesManager;

import ru.nsu.yurakov.Torrent.ParserTorrent.TorrentInfo;
import ru.nsu.yurakov.Torrent.Peer.Peer;

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

        sizePiece = min(info.sizeFile, info.sizePiece);
        countPieces = (int) Math.ceil((double)info.sizeFile / info.sizePiece);
        sizeLastPiece = (info.sizeFile - (countPieces - 1) * info.sizePiece);

        CheckingFile();
    }

    public void CheckingFile() throws IOException {
        if (!file.isFile()) {
            file.createNewFile();
        }
        try (FileInputStream fileInputStream = new FileInputStream(file)) {
            byte[] buffer = new byte[(int) sizePiece];
            sizeBitSet = countPieces;
            whatHave = new BitSet(sizeBitSet);
            for (int i = 0; i < sizeBitSet - 1; ++i) {
                fileInputStream.read(buffer);

                MessageDigest md = MessageDigest.getInstance("SHA-1");
                byte[] realHash = md.digest(buffer);

                whatHave.set(i);
                for (int j = 0; j < 20; ++j) {
                    if (realHash[j] != info.pieces[i * 20 + j]) {
                        whatHave.clear(i);
                        break;
                    }
                }
            }

            buffer = new byte[(int) sizeLastPiece];
            fileInputStream.read(buffer);

            MessageDigest md = MessageDigest.getInstance("SHA-1");
            byte[] realHash = md.digest(buffer);
            int index = sizeBitSet - 1;
            whatHave.set(index);
            for (int j = 0; j < 20; ++j) {
                if (realHash[j] != info.pieces[index * 20 + j]) {
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
    }

    public int getIndexPiece(Peer peer) {
        BitSet bitSetChannel = peer.getBitSet();
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
                return false;
            }
        }

        return true;
    }

    public int alreadyDownloaded() {
        int count = 0;
        for (int i = 0; i < sizeBitSet; ++i) {
            if (whatHave.get(i)) {
                count++;
            }
        }

        return count;
    }

    public long getSizePiece(int index) {
        if (index != countPieces - 1) {
            return sizePiece;
        } else {
            return sizeLastPiece;
        }
    }


    public BitSet getWhatHave() { return whatHave; }

    public int getCountPieces() { return countPieces; }

    private int sizeBitSet;
    private long sizePiece;
    private long sizeLastPiece;
    private int countPieces;
    private BitSet whatHave;
    private TorrentInfo info;
    private File file;
}
