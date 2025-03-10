package com.example.guiproject;

import controller.Controller;
import exceptions.ControllerException;
import exceptions.FileException;
import exceptions.StackException;
import javafx.beans.property.SimpleObjectProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.util.Callback;
import javafx.util.Pair;
import model.adt.*;
import model.state.PrgState;
import model.statements.IStatement;
import model.value.IValue;
import model.value.StringValue;
import repository.Repository;

import java.io.BufferedReader;
import java.util.List;
import java.util.Map;
import java.util.stream.IntStream;

public class RunProgramController {

    private Controller controller = null;

    @FXML
    private Button runOneStepButton;


    @FXML
    private TextField noOfPrograms;

    @FXML
    private ListView<PrgState> programStateListView;

    @FXML
    private TableView<Map.Entry<String, IValue>> symbolTableView;
    @FXML
    private TableColumn<Map.Entry<String, IValue>, String> nameSymbolTableColumn;
    @FXML
    private TableColumn<Map.Entry<String, IValue>, String> valueSymbolTableColumn;

    @FXML
    private ListView<IStatement> exeStackListView;

    @FXML
    private ListView<String> outListView;

    @FXML
    private ListView<StringValue> fileListView;

    @FXML
    private TableView<Map.Entry<Integer, IValue>> heapTable;
    @FXML
    private TableColumn<Map.Entry<Integer, IValue>, String> addressHeapTableColumn;
    @FXML
    private TableColumn<Map.Entry<Integer, IValue>, String> valueHeapTableColumn;

    @FXML
    private TableView<Pair<Pair<Integer, Integer>, String>> semaphoreTableTableView;

    @FXML
    private TableView<Pair<Integer,Integer>> latchTableTableView;

    @FXML
    private TableColumn<Pair<Integer, Integer>, String> locationLatchTableColumn;

    @FXML
    private TableColumn<Pair<Integer, Integer>, String> valueLatchTableColumn;

    @FXML
    private TableView<Pair<Integer,Integer>> lockTableTableView;

    @FXML
    private TableColumn<Pair<Integer, Integer>, String> locationLockTableColumn;

    @FXML
    private TableColumn<Pair<Integer, Integer>, String> valueLockTableColumn;


    @FXML
    private TableColumn<Pair<Pair<Integer, Integer>, String>, Integer> idSemaphoreTableColumn;

    @FXML
    private TableColumn<Pair<Pair<Integer, Integer>, String>, Integer> countSemaphoreTableColumn;

    @FXML
    private TableColumn<Pair<Pair<Integer, Integer>, String>, String> threadsSemaphoreTableColumn;

    @FXML
    public void initialize() {
        this.runOneStepButton.setOnAction(actionEvent -> runOneStepButtonHandler());

        // when you set the value of a cell, set the text to be the id of the thread, since a cell is a program state.
        this.programStateListView.setCellFactory(new Callback<>() {
            @Override
            public ListCell<PrgState> call(ListView<PrgState> programStateListView) {
                return new ListCell<>() {
                    @Override
                    public void updateItem(PrgState item, boolean empty) {
                        super.updateItem(item, empty);
                        if (item != null) {
                            setText(Integer.toString(item.getID()));
                        }
                        else
                            setText("");
                    }
                };
            }
        });
        // setCellValueFactory -> which is used to populate individual cells in the column
        this.nameSymbolTableColumn.setCellValueFactory(cellDataMapEntry -> new SimpleStringProperty(cellDataMapEntry.getValue().getKey()));
        this.valueSymbolTableColumn.setCellValueFactory(cellDataMapEntry -> new SimpleStringProperty(cellDataMapEntry.getValue().getValue().toString()));
        // for heap
        this.addressHeapTableColumn.setCellValueFactory(cellDataMapEntry -> new SimpleStringProperty(cellDataMapEntry.getValue().getKey().toString()));
        this.valueHeapTableColumn.setCellValueFactory(cellDataMapEntry -> new SimpleStringProperty(cellDataMapEntry.getValue().getValue().toString()));

        // you are allowed to select ONLY ONE id, because when you click on it, you need to change the state(because
        // every thread has a different symbol table and exe stack)
        this.programStateListView.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
        this.programStateListView.getSelectionModel().selectedItemProperty().addListener(
                (observableValue, oldState, newState) -> changeThreadState(newState)
        );

        this.idSemaphoreTableColumn.setCellValueFactory(cellDataPair ->
                new SimpleObjectProperty<>(cellDataPair.getValue().getKey().getKey()));
        this.countSemaphoreTableColumn.setCellValueFactory(cellDataPair ->
                new SimpleObjectProperty<>(cellDataPair.getValue().getKey().getValue()));
        this.threadsSemaphoreTableColumn.setCellValueFactory(cellDataPair ->
                new SimpleStringProperty(cellDataPair.getValue().getValue()));

        this.locationLatchTableColumn.setCellValueFactory(cellDataPair ->
                new SimpleObjectProperty<>(cellDataPair.getValue().getKey().toString()));
        this.valueLatchTableColumn.setCellValueFactory(cellDataPair ->
                new SimpleObjectProperty<>(cellDataPair.getValue().getValue().toString()));

        this.locationLockTableColumn.setCellValueFactory(cellDataPair ->
                new SimpleObjectProperty<>(cellDataPair.getValue().getKey().toString()));
        this.valueLockTableColumn.setCellValueFactory(cellDataPair ->
                new SimpleObjectProperty<>(cellDataPair.getValue().getValue().toString()));


    }

    public void setStatement(IStatement statement, String filename) {
        PrgState state = new PrgState(statement, new MyStack<IStatement>(), new MyDictionary<String, IValue>(), new MyList<String>(), new MyDictionary<StringValue, BufferedReader>(), new Heap(), new SemaphoreTable(), new LatchTable(), new LockTable());
        try {

            Repository repo = new Repository(filename);
            repo.addPrgState(state);
            this.controller = new Controller(repo);

            this.updateFields();
            this.programStateListView.getSelectionModel().select(0);

            this.runOneStepButton.setDisable(false);

        } catch (FileException e) {
            e.printStackTrace();
        }
    }

    @FXML
    private void runOneStepButtonHandler(){
        try {
            this.controller.oneStepForAllPrgGUI();
        } catch (ControllerException exception) {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setContentText(exception.getMessage());
            alert.showAndWait();
            this.runOneStepButton.setDisable(true);
        } finally {
            this.updateFields();
        }
    }

    private void updateFields(){
        // nr of programs
        this.setNoOfPrograms();
        // populate the program states list (initially only one, and only with threads there will be multiple)
        this.populateStateListView();
        // populate exe stack and symbol table
        this.changeThreadState(this.programStateListView.getSelectionModel().getSelectedItem());
        // populate out
        this.populateOut();
        // populate file table
        this.populateFileList();
        // populate heap
        this.populateHeapTable();

        this.populateSemaphoreTable();
        this.populateLatchTable();
        this.populateLockTable();

    }

    private void changeThreadState(PrgState newState){
        this.populateSymTable(newState);
        this.populateExeStack(newState);
    }

    public void setNoOfPrograms(){
        this.noOfPrograms.setText(String.valueOf(this.controller.getAllPrograms().size()));
    }

    public void populateHeapTable(){
        if(this.controller.getAllPrograms().size() > 0)
            this.heapTable.getItems().setAll(FXCollections.observableArrayList(this.controller.getHeapTableGUI().getHeap().entrySet()));

    }

    public void populateFileList(){
        if(this.controller.getAllPrograms().size() > 0)
            this.fileListView.getItems().setAll(FXCollections.observableArrayList(this.controller.getFileTableGUI().getContent().keySet()));
    }

    public void populateOut(){
        // error "Index 0 out of bounds for length 0" because of .getOutGUI if you don't put the if and you reach the end
        if(this.controller.getAllPrograms().size() > 0)
            this.outListView.getItems().setAll(FXCollections.observableArrayList(this.controller.getOutGUI().getAll()));
    }

    public void populateSymTable(PrgState state){
        if(state != null)
            this.symbolTableView.getItems().setAll(FXCollections.observableArrayList(state.getSymTable().getContent().entrySet()));
        else
            this.symbolTableView.getItems().setAll(FXCollections.observableArrayList());
    }

    public void populateExeStack(PrgState state){
        if (state != null){
            ObservableList<IStatement> statements = FXCollections.observableArrayList();
            MyIStack<IStatement> exeStack = state.getExecStack();

            // add to the ListView every statement from the exeStack (either 0, 1 or 2)
            while(!exeStack.isEmpty()){
                try{
                    statements.add(exeStack.pop());
                } catch (StackException e) {
                    e.printStackTrace();
                }
            }

            // after popping, we need to add them again in reverse order into the exeStack.
            IntStream.range(0, statements.size()).forEach(pos -> exeStack.push(statements.get(statements.size() - 1 - pos)));
            this.exeStackListView.getItems().setAll(statements);
        } else {
            this.exeStackListView.getItems().setAll(FXCollections.observableArrayList());
        }
    }

    public void populateStateListView(){
        ObservableList<PrgState> ids = FXCollections.observableList(this.controller.getAllPrograms());
        this.programStateListView.setItems(ids);

    }

    public void populateSemaphoreTable() {
        if (this.controller.getAllPrograms().size() > 0) {
            // Fetch the semaphore table data from the controller
            Map<Integer, Pair<Integer, List<Integer>>> semaphoreTable =
                    this.controller.getSemaphoreTableGUI().getSemaphoreTable();

            // Convert the semaphore table into rows for the TableView
            ObservableList<Pair<Pair<Integer, Integer>, String>> semaphoreEntries = FXCollections.observableArrayList();
            semaphoreTable.forEach((id, pair) -> {
                int count = pair.getKey();                // Semaphore count
                List<Integer> threads = pair.getValue();  // Threads waiting on semaphore
                String threadsStr = threads.toString();   // Convert threads to string for display
                semaphoreEntries.add(new Pair<>(new Pair<>(id, count), threadsStr));
            });

            // Set the items in the TableView
            this.semaphoreTableTableView.setItems(semaphoreEntries);
        } else {
            // Clear the table if no programs exist
            this.semaphoreTableTableView.setItems(FXCollections.observableArrayList());
        }
    }
    public void populateLatchTable() {
        if (this.controller.getAllPrograms().size() > 0) {
            Map<Integer, Integer> latchTable = this.controller.getLatchTableGUI().getLatchTable();
            ObservableList<Pair<Integer,Integer>> latchEntries = FXCollections.observableArrayList();
            latchTable.forEach((location, value) -> {
                latchEntries.add(new Pair<>(location,value));
            });

            this.latchTableTableView.setItems(latchEntries);
        } else {
            this.latchTableTableView.setItems(FXCollections.observableArrayList());
        }
    }
    public void populateLockTable() {
        if (this.controller.getAllPrograms().size() > 0) {
            Map<Integer, Integer> lockTable = this.controller.getLockTableGUI().getLockTable();
            ObservableList<Pair<Integer,Integer>> lockEntries = FXCollections.observableArrayList();
            lockTable.forEach((location, value) -> {
                lockEntries.add(new Pair<>(location,value));
            });

            this.lockTableTableView.setItems(lockEntries);
        } else {
            this.lockTableTableView.setItems(FXCollections.observableArrayList());
        }
    }

}
