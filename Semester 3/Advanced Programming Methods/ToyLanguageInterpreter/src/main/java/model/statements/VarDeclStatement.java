package model.statements;

import exceptions.StatementException;
import model.adt.MyIDictionary;
import model.state.PrgState;
import model.type.IType;

public class VarDeclStatement implements IStatement{
    private String name;
    private IType type;
    public VarDeclStatement(String name, IType type)
    {
        this.name = name;
        this.type = type;
    }

    @Override
    public PrgState execute(PrgState state) throws StatementException  {
        if(state.getSymTable().contains(this.name))
            throw new StatementException("A variable with this name already exists!\n");
        state.getSymTable().insert(this.name, this.type.getDefaultValue());
        return null;
    }

    @Override
    public IStatement deepCopy() {
        return new VarDeclStatement(this.name,this.type);

    }

    @Override
    public MyIDictionary<String, IType> typecheck(MyIDictionary<String, IType> typeEnv) throws StatementException {
        typeEnv.insert(name, type);
        return typeEnv;
    }

    @Override
    public String toString(){
        return this.type +" "+ this.name;
    }
}
