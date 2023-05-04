package com.example.unblockme;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class AskNickname extends Application {
    public AskNickname(String time) {
        AskNicknameController.setTime(time);
    }

    public static Stage getStageNow() {
        return stageNow;
    }

    @Override
    public void start(Stage primaryStage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(LevelSelectionView.class.getResource("askNickname.fxml"));

        Scene scene = new Scene(fxmlLoader.load());
        Stage stage = new Stage();
        stageNow = stage;
        stage.setTitle("Enter Name");
        stage.setResizable(false);
        stage.setScene(scene);
        stage.showAndWait();
    }

    private static Stage stageNow = null;
}
