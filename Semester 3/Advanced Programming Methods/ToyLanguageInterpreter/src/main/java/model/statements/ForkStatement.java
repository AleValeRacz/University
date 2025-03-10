package model.statements;

import exceptions.ExpressionException;
import exceptions.StatementException;
import model.adt.MyDictionary;
import model.adt.MyIDictionary;
import model.adt.MyIStack;
import model.adt.MyStack;
import model.state.PrgState;
import model.type.IType;
import model.value.IValue;

import java.util.Map;

public class ForkStatement implements IStatement {

    private IStatement statement;

    public ForkStatement(IStatement statement) {
        this.statement = statement;
    }

    @Override
    public PrgState execute(PrgState state) throws StatementException, ExpressionException {

        MyIStack<IStatement> newExecStack = new MyStack<>();
        PrgState newPrgState = new PrgState( this.statement,(MyStack<IStatement>) newExecStack, (MyDictionary<String, IValue>) state.getSymTable().deepCopy(), state.getOutputList(), state.getFileTable(), state.getHeap(), state.getSemaphoreTable(), state.getLatchTable(), state.getLockTable());
        newPrgState.setId();
        return newPrgState;

    }



    @Override
    public IStatement deepCopy() {
        return new ForkStatement(statement.deepCopy());

    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws StatementException {
        return statement.typecheck(typeEnv);
    }

    @Override
    public String toString() {
        return "fork(" + this.statement.toString() + ")";

    }

     /*
    private MyIDictionary<String, IValue> deepCopySymTable(MyIDictionary<String, IValue> oldSymTable) {
        MyIDictionary<String, IValue> newSymTable = new MyDictionary<>();
        for(Map.Entry<String,IValue> element: oldSymTable.getContent().entrySet()){
            String newKey = element.getKey();
            IValue newVal = element.getValue().deepCopy();
            newSymTable.insert(newKey,newVal);
        }
        return newSymTable;

    }
    */
}