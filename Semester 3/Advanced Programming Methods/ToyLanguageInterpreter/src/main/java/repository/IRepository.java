package repository;

import java.util.List;

import exceptions.ExpressionException;
import exceptions.RepositoryException;
import model.state.PrgState;

public interface IRepository {

    void addPrgState(PrgState state);
    void logPrgState(PrgState state) throws  RepositoryException, ExpressionException;
    //PrgState getCurrentState() throws RepositoryException;
    List<PrgState> getProgramList();
    void setProgramList(List<PrgState> programList);
 
}
