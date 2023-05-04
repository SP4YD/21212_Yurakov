package com.example.unblockme;

import javafx.application.Application;
import javafx.stage.Stage;

import java.io.IOException;

public class Main extends Application {

    @Override
    public void start(Stage stage) throws IOException {
        LevelSelectionView mainWindow = new LevelSelectionView();
        stage.setResizable(false);
        mainWindow.start(stage);
    }

    public static void main(String[] args) {
        launch(args);
    }
}