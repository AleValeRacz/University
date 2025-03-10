package view;

import controller.Controller;
import exceptions.ControllerException;
import model.adt.*;
import model.expressions.ArithmeticalExpression;
import model.expressions.ValueExpression;
import model.expressions.VariableExpression;
import model.state.PrgState;
import model.statements.*;
import model.type.BoolType;
import model.type.IntType;
import model.value.BoolValue;
import model.value.IValue;
import model.value.IntValue;
import model.value.StringValue;

import java.io.BufferedReader;
import java.util.Scanner;

import static model.expressions.ArithmeticalOperation.*;

public class View {

    Controller controller;
    public View(Controller cont){
        this.controller = cont;
    }
    public void printMenu(){
        System.out.println("1. Run hardcoded programs: \n" +
                "a. int v; v=2;Print(v)\n" +
                "b. int a; a=2+3*5; int b; b=a+1;Print(b)\n" +
                "c. bool a;int v; a=true;(If a Then v=2 Else v=3);Print(v)\n" +
                "2.Exit");

    }

    public void run() throws ControllerException {

        while (true){
            this.printMenu();
        System.out.print("Enter your choice: ");
        Scanner sc = new Scanner(System.in);
        String choice = sc.nextLine();
        if (choice.equals("1")) {
            System.out.println("Choose between program a,b, or c:");
            String choice2 = sc.nextLine();
            IStatement st;
            switch (choice2) {

                case "a":

                    st = new CompStatement(
                            new VarDeclStatement("v", new IntType()),
                            new CompStatement(new AssignStatement("v", new ValueExpression(new IntValue(2))),
                                    new PrintStatement(new VariableExpression("v"))));

                    break;
                case "b":
                    st = new CompStatement(new VarDeclStatement("a", new IntType()),
                            new CompStatement(new AssignStatement("a", new ArithmeticalExpression(
                                    new ValueExpression(new IntValue(2)),
                                    new ArithmeticalExpression(
                                            new ValueExpression(new IntValue(3)),
                                            new ValueExpression(new IntValue(5)), MULTIPLY), PLUS)),
                                    new CompStatement(new VarDeclStatement("b", new IntType()),
                                            new CompStatement(new AssignStatement("b",
                                                    new ArithmeticalExpression(new VariableExpression("a"), new ValueExpression(new IntValue(1)), PLUS)),
                                                    new PrintStatement(new VariableExpression("b"))))));


                    break;

                case "c":
                    st = new CompStatement(
                            new VarDeclStatement("a", new BoolType()),
                               new CompStatement(new VarDeclStatement("v",new IntType()),
                                       new CompStatement(new AssignStatement("a", new ValueExpression(new BoolValue(true))),
                                               new CompStatement(new IfStatement(new VariableExpression("a"),new AssignStatement("v", new ValueExpression(new IntValue(2))),
                                                       new AssignStatement("v",new ValueExpression(new IntValue(3)))), new PrintStatement(new VariableExpression("v")))))) ;
                    break;
                default:
                    System.out.println("Invalid program choice");
                   continue;
            }
            PrgState prgState = new PrgState(st, new MyStack<IStatement>(), new MyDictionary<String, IValue>(), new MyList<String>(), new MyDictionary<StringValue, BufferedReader>(), new Heap(), new SemaphoreTable(), new LatchTable(), new LockTable());
            this.controller.addProgramState(prgState);
            System.out.println("Do you want to display the execution step by step? (y/n)");
            String choice3 = sc.nextLine();
            if(choice3.equals("y"))
                this.controller.setDisplayFlag(true);
            try {
                this.controller.allStep();
            }
            catch(Exception e)
            {
                System.out.println(e.getMessage());
            }
            break;
        }
        else if(choice.equals("2")) {
            System.out.println("Goodbye!");
            break;
        }

        else
        {
            System.out.println("Invalid choice!");
        }

        }
        }


    }






