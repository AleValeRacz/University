package model.state;
import exceptions.ControllerException;
import exceptions.ExpressionException;
import model.adt.*;
import model.statements.IStatement;
import model.value.IValue;
import model.value.StringValue;
import java.io.BufferedReader;
import java.util.List;

public class PrgState {
    private MyIStack<IStatement> execStack;
    private MyIDictionary<String, IValue>  symTable;
    private MyIList<String> outputList;
    private IStatement  originalStatement;
    private MyIDictionary<StringValue, BufferedReader> fileTable;
    private IHeap heap;
    private int id;
    private static int currentId = 1;
    private ISemaphoreTable semaphoreTable;
    private ILatchTable latchTable;
    private ILockTable lockTable;
    public PrgState(IStatement initState, MyStack<IStatement> execStack, MyDictionary<String, IValue> symTable, MyIList<String> outputList,MyIDictionary<StringValue,BufferedReader> fileTable, IHeap heap, ISemaphoreTable semaphoreTable, ILatchTable latchTable, ILockTable lockTable ) {
        this.execStack = execStack;
        this.symTable = symTable;
        this.outputList = outputList;
        this.originalStatement = initState.deepCopy();
        this.fileTable = fileTable;
        this.heap = heap;
        this.semaphoreTable = semaphoreTable;
        this.latchTable = latchTable;
        this.lockTable = lockTable;
        //execStack.push(initState);
        this.id = 1;


        if(this.originalStatement != null){
            execStack.push(this.originalStatement);
        }
    }


    public Integer getID() {return this.id;}
    public MyIStack<IStatement> getExecStack() {
        return execStack;
    }
    public MyIDictionary<String, IValue> getSymTable() {
        return symTable;
    }
    public MyIList<String> getOutputList() {
        return outputList;
    }


    public MyIDictionary<StringValue, BufferedReader> getFileTable() {
        return fileTable;
    }

    public IHeap getHeap()
    {
        return this.heap;
    }

    public ISemaphoreTable getSemaphoreTable(){ return this.semaphoreTable;}
    public ILatchTable getLatchTable(){return this.latchTable;}
    public ILockTable getLockTable(){return this.lockTable;}
    public synchronized  void setId()
    {
        currentId++;
        this.id = currentId;
    }
    @Override
    public String toString() {

        return execStack.toString() + "\n" + symTable.toString() + "\n"
                + outputList.toString()+ "\n"; //+ this.toStringFile()+ "\n";
    }

    public Boolean isNotCompleted()
    {
        if(this.execStack.isEmpty())
            return false;
        return true;
    }

    public String toStringFile() throws ExpressionException {
        StringBuilder result = new StringBuilder();
        result.append("Program State: \n");
        result.append("ID: ").append(Integer.toString(this.id)).append("\n");
        result.append("ExecStack: \n");
        List<IStatement> list = this.execStack.toList();
        for(IStatement statement: list){
            result.append(statement.toString()).append("\n");
        }

        result.append("SymTable: \n");
        for(String sym : this.symTable.getKeys())
        {
            result.append(sym).append("->").append(symTable.get(sym).toString()).append("\n");
        }

        result.append("OutputList: \n");
        for(String output: this.outputList.getAll())
        {
            result.append(output).append("\n");
        }

        result.append("File table: \n");
        for(StringValue v: this.fileTable.getKeys()) {
            result.append(v.getValue()).append("\n");

        }
        result.append(this.heap.toString());

        result.append(this.semaphoreTable.toString());

        result.append(this.latchTable.toString());
        result.append(this.lockTable.toString());
        return result.toString();
    }

    public PrgState oneStep() throws ControllerException {
        if(this.execStack.isEmpty()){
            throw new ControllerException("Exec Stack is empty!!!");

        }
        try{
            IStatement statement = this.execStack.pop();
            return statement.execute(this);
        }
        catch(Exception e){
            throw new ControllerException(e.getMessage());
        }


    }


}
