package com.example.unblockme;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.TextField;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintStream;
import java.util.Scanner;

public class AskNicknameController {
    int MaxLen = 7;
    @FXML
    private TextField textfield;

    public void initialize() {
        textfield.textProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue.length() >= MaxLen) {
                textfield.setText(newValue.substring(0, MaxLen - 1));
            }
        });
    }
    @FXML
    public void ButtonIsReady(ActionEvent actionEvent) throws FileNotFoundException {
        String leaderBoardFile = "src/main/resources/LeaderBoard.txt";
        String nickname = textfield.getText();
        if (nickname.length() > 0 && nickname.length() < MaxLen) {
            Scanner scanner = new Scanner(new File(leaderBoardFile));

            String beforeBoard = scanner.nextLine() + "\n";
            String afterBoard = "";

            if (beforeBoard.split(" ")[0].equals(GameWindowView.getNameLevel())) {
                beforeBoard = "";
            } else {
                String tmpstr = scanner.nextLine();
                while (!tmpstr.split(" ")[0].equals(GameWindowView.getNameLevel())) {
                    beforeBoard += tmpstr + "\n";
                    tmpstr = scanner.nextLine();
                }
            }

            while (scanner.hasNextLine()) {
                String tmpstr = scanner.nextLine();
                afterBoard += tmpstr + "\n";
            }

            try (PrintStream board = new PrintStream(leaderBoardFile)) {
                board.print(beforeBoard);
                board.println(GameWindowView.getNameLevel() + " " + nickname + " " + time);
                board.println(afterBoard);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            AskNickname.getStageNow().close();
        }
    }

    public static void setTime(String Time) {
        time = Time;
    }
    private static String time;
}