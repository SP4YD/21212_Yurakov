package ru.nsu.yurakov.Torrent.ParserTorrent;

import com.dampcake.bencode.Bencode;
import com.dampcake.bencode.Type;

import java.io.FileInputStream;
import java.io.IOException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;
import java.util.Map;

public class ParserTorrent {
    public TorrentInfo getInfo (String pathFile) {
        TorrentInfo TorInfo = new TorrentInfo();
        try(FileInputStream fileInputStream = new FileInputStream(pathFile)) {
            Bencode bencode = new Bencode();
            byte[] allBytesTorrent = fileInputStream.readAllBytes();
            int infoStart = (new String(allBytesTorrent).indexOf("4:info")) + 6;
            int piecesStart = findPiecesIndex(allBytesTorrent);

            MessageDigest md = MessageDigest.getInstance("SHA-1");
            byte[] infoData = Arrays.copyOfRange(allBytesTorrent, infoStart, allBytesTorrent.length - 1);
            TorInfo.hashInfo = md.digest(infoData);
            TorInfo.pieces = Arrays.copyOfRange(allBytesTorrent, piecesStart, allBytesTorrent.length - 1);

            Map<String, Object> dict = bencode.decode(allBytesTorrent, Type.DICTIONARY);
            String info = dict.get("info").toString();
            ParserInfo(info, TorInfo);
        } catch (IOException | NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }

        return TorInfo;
    }

    public static String bytesToHex(byte[] hash) {
        StringBuilder hexString = new StringBuilder();
        for (byte b : hash) {
            String hex = Integer.toHexString(0xff & b);
            if (hex.length() == 1) hexString.append('0');
            hexString.append(hex);
        }
        return hexString.toString();
    }

    private void ParserInfo(String info, TorrentInfo TorInfo) {
        info = info.replace(',', ' ');
        String[] PiecesInfo = info.split("  ");
        TorInfo.sizeFile = Long.parseLong((PiecesInfo[0].split("length="))[1]);
        TorInfo.nameFile = (PiecesInfo[1].split("name="))[1];
        TorInfo.sizePiece = Long.parseLong((PiecesInfo[2].split("piece length="))[1]);
    }

    private static int findPiecesIndex(byte[] info) {
        int index = 0;
        while (index < info.length - 8) {
            if (info[index] == '6' && info[index + 1] == ':' &&
                    info[index + 2] == 'p' && info[index + 3] == 'i' &&
                    info[index + 4] == 'e' && info[index + 5] == 'c' &&
                    info[index + 6] == 'e' && info[index + 7] == 's') {
                index += 8;

                while (info[index] != ':') {
                    index++;
                }
                return index + 1;
            }
            index++;
        }
        return -1;
    }

    private void PrintInfoAboutTorrentFile (TorrentInfo TorInfo) {
        System.out.println("sizeFile = " + TorInfo.sizeFile);
        System.out.println("nameFile = " + TorInfo.nameFile);
        System.out.println("sizePiece = " + TorInfo.sizePiece);
        System.out.println("hashInfo = " + bytesToHex(TorInfo.hashInfo));
    }
}
