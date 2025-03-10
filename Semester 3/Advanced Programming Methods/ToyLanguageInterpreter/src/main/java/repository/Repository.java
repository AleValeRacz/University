package repository;

import exceptions.ExpressionException;
import exceptions.RepositoryException;
import model.state.PrgState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Repository implements IRepository {

    private List<PrgState> states;
    private String logFilePath;
    private int currentPrgState = 0;


    public Repository(String logFilePath) {
        this.logFilePath = logFilePath;
        this.states = new ArrayList<>();
    }

/*
    @Override
    public PrgState getCurrentState() throws RepositoryException {
       if(this.states.isEmpty())
           throw new RepositoryException("There's no current state!");
        return this.states.get(this.currentPrgState);
    }


 */
    @Override
    public void addPrgState(PrgState state)
    {
        this.states.add(state);
    }



    @Override
    public void logPrgState(PrgState state) throws RepositoryException, ExpressionException
    {
        try{
            PrintWriter pw = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath,true)));
            pw.println(state.toStringFile());
            pw.close();
        }
        catch(IOException e){
            throw new RepositoryException(e.getMessage());
        }
    }

    @Override
    public List<PrgState> getProgramList() {
        return this.states;
    }

    @Override
    public void setProgramList(List<PrgState> programList) {

        this.states = programList;
    }
}
