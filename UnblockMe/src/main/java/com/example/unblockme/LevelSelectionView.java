package com.example.unblockme;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class LevelSelectionView extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        stageNow = stage;
        FXMLLoader fxmlLoader = new FXMLLoader(LevelSelectionView.class.getResource("levelSelection.fxml"));

        Scene scene = new Scene(fxmlLoader.load());
        stageNow.setScene(scene);
        stageNow.setTitle("Select Level");
        stageNow.show();
    }

    public static Stage GetStage() {
        return stageNow;
    }

    private static Stage stageNow = null;
}
