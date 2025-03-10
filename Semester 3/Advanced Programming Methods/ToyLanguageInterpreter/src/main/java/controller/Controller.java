package controller;

import exceptions.ControllerException;
import exceptions.ExpressionException;
import javafx.util.Pair;
import model.adt.*;
import model.state.PrgState;
import model.value.IValue;
import model.value.RefValue;
import model.value.StringValue;
import repository.IRepository;

import java.io.BufferedReader;
import java.util.*;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class Controller {
    private IRepository  repository;
    private Boolean displayFlag = false;
    private ExecutorService executor;

    public Controller(IRepository repository){
        this.repository = repository;
    }

    public void setDisplayFlag(boolean value)
    {
        this.displayFlag = value;
    }


    public List<PrgState> removeCompletedPrg(List<PrgState> inPrgList)
    {
        return inPrgList.stream().filter(p->p.isNotCompleted()).collect(Collectors.toList());
    }

    public void oneStepForAllPrgGUI() throws ControllerException{
        this.executor= Executors.newFixedThreadPool(2);
        // remove the completed programs
        List<PrgState> prgList= removeCompletedPrg(repository.getProgramList());
        repository.setProgramList(prgList);
        if(prgList.size() == 0)
            throw new ControllerException("Program is done!");
        conservativeGarbageCollector(prgList);
        try {
            oneStepForAllPrg(prgList);
        }catch (Exception e) {
            throw new ControllerException(e.getMessage());
        }
        executor.shutdown();

    }
    public void oneStepForAllPrg(List<PrgState> prgList)throws ExpressionException, InterruptedException {
       prgList.forEach(prg -> {
            try {

                this.repository.logPrgState(prg);
            } catch (Exception e) {
                throw new ControllerException(e.getMessage());
            }
        });


        List<Callable<PrgState>> callList = prgList.stream()
                .map((PrgState p) -> (Callable<PrgState>) (() -> {
                    return p.oneStep();
                })).collect(Collectors.toList());

        List<PrgState> newPrgList = executor.invokeAll(callList).stream()
                .map(future -> {
                    try {
                        return future.get();
                    } catch (Exception e) {
                        throw new ControllerException(e.getMessage());
                    }

                })
                .filter(p -> p != null)
                .collect(Collectors.toList());

        prgList.addAll(newPrgList);
        prgList.forEach(prg -> {
            try {

                this.repository.logPrgState(prg);
            } catch (Exception e) {
                throw new ControllerException(e.getMessage());
            }
        });
        this.repository.setProgramList(prgList);
    }

    public void  allStep(){
        this.executor = Executors.newFixedThreadPool(2);
        List<PrgState> prgList = removeCompletedPrg(repository.getProgramList());
        while(prgList.size() > 0)
        {
            try {
                this.conservativeGarbageCollector(prgList);
                this.oneStepForAllPrg(prgList);
                prgList = removeCompletedPrg(this.repository.getProgramList());
            } catch (Exception e) {
                throw  new ControllerException(e.getMessage());
            }
        }
        executor.shutdownNow();
        this.repository.setProgramList(prgList);
    }

    public List<PrgState> getAllPrograms(){ return this.repository.getProgramList();}


    private Map<Integer, IValue> safeGarbageCollector(List<Integer> symbolTableAddresses, Map<Integer, IValue> heap) {
        return heap.entrySet().stream()
                .filter(e -> symbolTableAddresses.contains(e.getKey()))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue));
    }

    private void conservativeGarbageCollector(List<PrgState> prgStateList)
    {
        var heap = Objects.requireNonNull(
                prgStateList.stream()
                        .map(p->getAllAddressesFromSymTable(p.getSymTable().getValues(),p.getHeap()))
                        .map(Collection::stream)
                        .reduce(Stream::concat).orElse(null)).collect(Collectors.toList());

        prgStateList.forEach(prgState -> prgState.getHeap().setHeap(safeGarbageCollector(
                heap,prgStateList.get(0).getHeap().getHeap()
        )));
    }

    private List<Integer> getAllAddressesFromSymTable(Collection<IValue> symbolTableValues, IHeap heap) {
        return symbolTableValues.stream()
                .filter(v ->v instanceof RefValue)
                .map(v -> (RefValue)v)
                .flatMap(
                        v->{
                            List<Integer> addresses = new ArrayList<>();
                            while(true) {
                                if (v.getAddress() == 0)
                                    break;
                                addresses.add(v.getAddress());
                                try {
                                    IValue nextVal = heap.get(v.getAddress());
                                    if(nextVal instanceof RefValue)
                                        v = (RefValue) nextVal;
                                    else
                                        break;
                                } catch (ExpressionException e) {
                                    throw new ControllerException(e.getMessage());
                                }

                            }
                            return addresses.stream();
                        }).collect(Collectors.toList());
    }


    public void addProgramState(PrgState state)
    {
        this.repository.addPrgState(state);
    }

    public MyIList<String> getOutGUI(){
        return this.getAllPrograms().get(0).getOutputList();}

    public MyIDictionary<StringValue, BufferedReader> getFileTableGUI() {return this.getAllPrograms().get(0).getFileTable();}
    public IHeap getHeapTableGUI() {return this.getAllPrograms().get(0).getHeap();}
    public ISemaphoreTable getSemaphoreTableGUI() {
        return this.getAllPrograms().get(0).getSemaphoreTable();

    }
    public ILatchTable getLatchTableGUI() {
        return this.getAllPrograms().get(0).getLatchTable();
    }
    public ILockTable getLockTableGUI() {
        return this.getAllPrograms().get(0).getLockTable();
    }

}
