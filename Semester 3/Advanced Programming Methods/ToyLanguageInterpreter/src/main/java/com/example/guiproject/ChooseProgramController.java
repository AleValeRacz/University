package com.example.guiproject;

import exceptions.StatementException;
import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.stage.Stage;
import model.adt.MyDictionary;
import model.statements.IStatement;
import view.Examples;

import java.io.IOException;

public class ChooseProgramController {

    @FXML
    private ListView<IStatement> listofPrograms;

    @FXML
    private Label chooseProgramText;

    private RunProgramController runProgramController;

    @FXML
    public void initialize(){
        listofPrograms.setItems(this.getStatements());

        FXMLLoader loader = new FXMLLoader(MainWindow.class.getResource("RunProgramStyle.fxml")) ;

        Stage stage = new Stage();
        try {
            Scene scene = new Scene(loader.load(), 950, 600);
            this.runProgramController = loader.getController();
            stage.setScene(scene);
            stage.show();
        } catch (IOException exception) {
            exception.printStackTrace();
        }
        listofPrograms.getSelectionModel().selectedItemProperty().addListener(new ChangeListener<IStatement>() {

            @Override
            public void changed(ObservableValue<? extends IStatement> observableValue, IStatement oldStatement, IStatement newStatement) {
                String filename = "log" + (listofPrograms.getSelectionModel().getSelectedIndex()+1)+ ".txt";
                runProgramController.setStatement(newStatement, filename);
            }
        });
    }

    private ObservableList<IStatement> getStatements(){
        ObservableList<IStatement> exampleList = FXCollections.observableArrayList();
        IStatement[] examples = new Examples().exampleList();
        for(IStatement example: examples){
            try{
                example.typecheck(new MyDictionary<>());
                exampleList.add(example);
            } catch (StatementException exception) {
                Alert error = new Alert(Alert.AlertType.ERROR);
                error.setContentText("Program that did not pass:\n" + example.toString() + "\n due to:\n" + exception.getMessage());
                error.showAndWait();
            }
        }
        return exampleList;
    }
}
