package com.example.unblockme;

import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Modality;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

import java.io.File;
import java.io.IOException;

public class LevelSelectionController {

    public LevelSelectionController() {
        Stage stage = LevelSelectionView.GetStage();
        stage.setOnCloseRequest(new EventHandler<WindowEvent>() {
            public void handle(WindowEvent we) {
                CloseAllWindow();
            }
        });
    }
    @FXML
    public void startLevel1(ActionEvent actionEvent) throws Exception {
        nameLevel = "level1";
        startLevel();
    }
    @FXML
    public void startLevel2(ActionEvent actionEvent) throws Exception {
        nameLevel = "level2";
        startLevel();
    }
    @FXML
    public void startLevel3(ActionEvent actionEvent) throws Exception {
        nameLevel = "level3";
        startLevel();
    }
    @FXML
    public void startLevel4(ActionEvent actionEvent) throws Exception {
        nameLevel = "level4";
        startLevel();
    }
    @FXML
    public void startLevel5(ActionEvent actionEvent) throws Exception {
        nameLevel = "level5";
        startLevel();
    }
    @FXML
    public void startLevel6(ActionEvent actionEvent) throws Exception {
        nameLevel = "level6";
        startLevel();
    }
    @FXML
    public void startLevel7(ActionEvent actionEvent) throws Exception {
        nameLevel = "level7";
        startLevel();
    }
    @FXML
    public void startLevel8(ActionEvent actionEvent) throws Exception {
        nameLevel = "level8";
        startLevel();
    }
    @FXML
    public void startLevel9(ActionEvent actionEvent) throws Exception {
        nameLevel = "level9";
        startLevel();
    }
    @FXML
    public void startLevel10(ActionEvent actionEvent) throws Exception {
        nameLevel = "level10";
        startLevel();
    }
    @FXML
    public void CreateWindowWithRules(ActionEvent actionEvent) throws IOException {
        if (stageRules == null) {
            FXMLLoader fxmlLoader = new FXMLLoader(LevelSelectionView.class.getResource("rules.fxml"));

            Scene scene = new Scene(fxmlLoader.load());
            stageRules = new Stage();
            stageRules.setScene(scene);
            stageRules.setResizable(false);
            stageRules.setTitle("Rules");
            stageRules.initModality(Modality.APPLICATION_MODAL);
            stageRules.showAndWait();
            stageRules = null;
        } else {
            stageRules.toFront();
        }
    }
    @FXML
    public void CreateWindowWithLeaderBoard(ActionEvent actionEvent) {
        if (stageLeaderBoard == null) {
            LeaderBoard table = new LeaderBoard();
            stageLeaderBoard = table.Init();
            stageLeaderBoard.initModality(Modality.APPLICATION_MODAL);
            stageLeaderBoard.showAndWait();
            stageLeaderBoard = null;
        } else {
            stageLeaderBoard.toFront();
        }
    }

    private void startLevel () throws Exception {
        File level = new File(path + nameLevel);
        GameWindowController game = new GameWindowController();
        game.CreateGameWindow(LevelSelectionView.GetStage(), level, nameLevel);
    }

    public void CloseAllWindow() {
        if (stageRules != null) {
            stageRules.close();
        }
        if (stageLeaderBoard != null) {
            stageLeaderBoard.close();
        }
    }

    private String nameLevel;
    private final String path = "src/main/resources/com/example/unblockme/Levels/";
    private static Stage stageRules = null;
    private static Stage stageLeaderBoard = null;
}