package view;

import controller.Controller;
import model.adt.Heap;
import model.adt.MyDictionary;
import model.adt.MyList;
import model.adt.MyStack;
import model.expressions.*;
import model.state.PrgState;
import model.statements.*;
import model.type.BoolType;
import model.type.IntType;
import model.type.RefType;
import model.type.StringType;
import model.value.BoolValue;
import model.value.IValue;
import model.value.IntValue;
import model.value.StringValue;
import repository.IRepository;
import repository.Repository;

import java.io.BufferedReader;
import java.util.ArrayList;
import java.util.List;

import static model.expressions.ArithmeticalOperation.*;

public class Examples {

    IStatement ex1 = new CompStatement(
            new VarDeclStatement("v", new IntType()),
            new CompStatement(new AssignStatement("v", new ValueExpression(new IntValue(2))),
                    new PrintStatement(new VariableExpression("v"))));


    IStatement ex2 = new CompStatement(new VarDeclStatement("a", new IntType()),
            new CompStatement(new AssignStatement("a", new ArithmeticalExpression(
                    new ValueExpression(new IntValue(2)),
                    new ArithmeticalExpression(
                            new ValueExpression(new IntValue(3)),
                            new ValueExpression(new IntValue(5)), MULTIPLY), PLUS)),
                    new CompStatement(new VarDeclStatement("b", new IntType()),
                            new CompStatement(new AssignStatement("b",
                                    new ArithmeticalExpression(new VariableExpression("a"), new ValueExpression(new IntValue(1)), PLUS)),
                                    new PrintStatement(new VariableExpression("b"))))));

    IStatement ex3 = new CompStatement(new VarDeclStatement("a", new BoolType()),
            new CompStatement(new VarDeclStatement("v",new IntType()),
                    new CompStatement(new AssignStatement("a", new ValueExpression(new BoolValue(true))),
                            new CompStatement(new IfStatement(new VariableExpression("a"),new AssignStatement("v", new ValueExpression(new IntValue(2))),
                                    new AssignStatement("v",new ValueExpression(new IntValue(3)))), new PrintStatement(new VariableExpression("v")))))) ;



    IStatement ex4 = new CompStatement(
            new VarDeclStatement("varf", new StringType()),
            new CompStatement(
                    new AssignStatement("varf", new ValueExpression(new StringValue("test.in"))),
                    new CompStatement(
                            new OpenRFileStatement(new VariableExpression("varf")),
                            new CompStatement(
                                    new VarDeclStatement("varc", new IntType()),
                                    new CompStatement(
                                            new ReadFileStatement(new VariableExpression("varf"), "varc"),
                                            new CompStatement(
                                                    new PrintStatement(new VariableExpression("varc")),
                                                    new CompStatement(
                                                            new ReadFileStatement(new VariableExpression("varf"), "varc"),
                                                            new CompStatement(
                                                                    new PrintStatement(new VariableExpression("varc")),
                                                                    new CloseRFileStatement(new VariableExpression("varf"))))))))));

    IStatement ex5 = new CompStatement(
            new VarDeclStatement("v", new RefType(new IntType())),
            new CompStatement(
                    new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                    new CompStatement(
                            new VarDeclStatement("a",new RefType(new RefType(new IntType()))),
                            new CompStatement(
                                    new HeapAllocationStatement("a",new VariableExpression("v")),
                                    new CompStatement(
                                            new PrintStatement(new VariableExpression("v")),
                                            new PrintStatement(new VariableExpression("a"))
                                    )
                            )

                    )
            )
    );


    IStatement ex6 = new CompStatement(
            new VarDeclStatement("v", new RefType(new IntType())),
            new CompStatement(
                    new HeapAllocationStatement("v",new ValueExpression(new IntValue(20))),
                    new CompStatement(
                            new VarDeclStatement("a", new RefType(new RefType(new IntType()))),
                            new CompStatement(
                                    new HeapAllocationStatement("a", new VariableExpression("v")),
                                    new CompStatement(
                                            new PrintStatement(new HeapReadingExpression(new VariableExpression("v"))),
                                            new PrintStatement(new ArithmeticalExpression(
                                                    new HeapReadingExpression(new HeapReadingExpression(new VariableExpression("a"))),
                                                    new ValueExpression(new IntValue(5)), PLUS))

                                    )
                            )
                    )
            )
    );


    IStatement ex7 = new CompStatement(
            new VarDeclStatement("v", new RefType(new IntType())),
            new CompStatement(
                    new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                    new CompStatement(
                            new PrintStatement(new HeapReadingExpression(new VariableExpression("v"))),
                            new CompStatement(
                                    new HeapWritingStatement("v", new ValueExpression(new IntValue(30))),
                                    new PrintStatement(new ArithmeticalExpression(

                                            new HeapReadingExpression(new VariableExpression("v")),
                                            new ValueExpression(new IntValue(5)),
                                            PLUS
                                    ))
                            )
                    )
            )
    );

    IStatement ex8 = new CompStatement(
            new VarDeclStatement("v", new RefType(new IntType())),
            new CompStatement(
                    new HeapAllocationStatement("v", new ValueExpression(new IntValue(20))),
                    new CompStatement(
                            new VarDeclStatement("a", new RefType(new RefType(new IntType()))),
                            new CompStatement(
                                    new HeapAllocationStatement("a",new VariableExpression("v")),
                                    new CompStatement(
                                            new HeapAllocationStatement("v", new ValueExpression(new IntValue(30))),
                                            new PrintStatement(
                                                    new HeapReadingExpression(new HeapReadingExpression(new VariableExpression("a")))
                                            )
                                    )
                            )
                    )
            )
    );

    IStatement ex9 = new CompStatement(
            new VarDeclStatement("v", new IntType()),
            new CompStatement(
                    new AssignStatement("v", new ValueExpression(new IntValue(4))),
                    new CompStatement(
                            new WhileStatement(
                                    new RelationalExpression(
                                            new VariableExpression("v"),
                                            new ValueExpression(new IntValue(0)),
                                            ">"),
                                    new CompStatement(
                                            new PrintStatement(new VariableExpression("v")),
                                            new AssignStatement(
                                                    "v",
                                                    new ArithmeticalExpression(
                                                            new VariableExpression("v"),
                                                            new ValueExpression(new IntValue(1)),MINUS)

                                            )
                                    )),
                            new PrintStatement(new VariableExpression("v"))
                    )
            )
    );



    IStatement ex10 = new CompStatement(
            new VarDeclStatement("v", new IntType()),
            new CompStatement(
                    new VarDeclStatement("a", new RefType(new IntType())),
                    new CompStatement(
                            new AssignStatement("v", new ValueExpression(new IntValue(10))),
                            new CompStatement(
                                    new HeapAllocationStatement("a", new ValueExpression(new IntValue(22))),
                                    new CompStatement(
                                            new ForkStatement(
                                                    new CompStatement(
                                                            new HeapWritingStatement("a", new ValueExpression(new IntValue(30))),
                                                            new CompStatement(
                                                                    new AssignStatement("v", new ValueExpression(new IntValue(32))),
                                                                    new CompStatement(
                                                                            new PrintStatement(new VariableExpression("v")),
                                                                            new PrintStatement(new HeapReadingExpression(new VariableExpression("a")))
                                                                    )
                                                            )
                                                    )
                                            ),
                                            new CompStatement(
                                                    new PrintStatement(new VariableExpression("v")),
                                                    new PrintStatement(new HeapReadingExpression(new VariableExpression("a")))
                                            )
                                    )
                            )
                    )
            )
    );
    IStatement ex11 = new CompStatement(
            new VarDeclStatement("a", new IntType()),
            new CompStatement(
                    new VarDeclStatement("b", new IntType()),
                    new CompStatement(
                            new VarDeclStatement("c", new IntType()),
                            new CompStatement(
                                    new AssignStatement("a", new ValueExpression(new IntValue(1))),
                                    new CompStatement(
                                            new AssignStatement("b", new ValueExpression(new IntValue(2))),
                                            new CompStatement(
                                                    new AssignStatement("c", new ValueExpression(new IntValue(5))),
                                                    new CompStatement(
                                                    new SwitchStatement(
                                                            new ArithmeticalExpression(new VariableExpression("a"), new ValueExpression(new IntValue(10)), MULTIPLY), // a*10
                                                            new ArithmeticalExpression(new VariableExpression("b"), new VariableExpression("c"), MULTIPLY), // b*c
                                                            new CompStatement(
                                                                    new PrintStatement(new VariableExpression("a")),
                                                                    new PrintStatement(new VariableExpression("b"))
                                                            ),
                                                            new ValueExpression(new IntValue(10)),
                                                            new CompStatement(
                                                                    new PrintStatement(new ValueExpression(new IntValue(100))),
                                                                    new PrintStatement(new ValueExpression(new IntValue(200)))
                                                            ),
                                                            new PrintStatement(new ValueExpression(new IntValue(300)))
                                                    ),
                                                            new PrintStatement(new ValueExpression(new IntValue(300))) )
                                            )
                                    )
                            )
                    )
            )
    );

    IStatement ex12 = new CompStatement(
            new VarDeclStatement("a", new RefType(new IntType())),
            new CompStatement(
                    new VarDeclStatement("b", new RefType(new IntType())),
                    new CompStatement(
                            new VarDeclStatement("v", new IntType()),
                            new CompStatement(
                                    new HeapAllocationStatement("a", new ValueExpression(new IntValue(0))),
                                    new CompStatement(
                                            new HeapAllocationStatement("b", new ValueExpression(new IntValue(0))),
                                            new CompStatement(
                                                    new HeapWritingStatement("a", new ValueExpression(new IntValue(1))),
                                                    new CompStatement(
                                                            new HeapWritingStatement("b", new ValueExpression(new IntValue(2))),
                                                            new CompStatement(
                                                                    new CondAssignStatement(
                                                                            "v",
                                                                            new RelationalExpression(
                                                                                    new HeapReadingExpression(new VariableExpression("a")),
                                                                                    new HeapReadingExpression(new VariableExpression("b")),
                                                                                    "<"
                                                                            ),
                                                                            new ValueExpression(new IntValue(100)),
                                                                            new ValueExpression(new IntValue(200))
                                                                    ),
                                                                    new CompStatement(
                                                                            new PrintStatement(new VariableExpression("v")),
                                                                            new CompStatement(
                                                                                    new CondAssignStatement(
                                                                                            "v",
                                                                                            new RelationalExpression(
                                                                                                    new ArithmeticalExpression(
                                                                                                            new HeapReadingExpression(new VariableExpression("b")),
                                                                                                            new ValueExpression(new IntValue(2)),
                                                                                                            MINUS
                                                                                                    ),
                                                                                                    new HeapReadingExpression(new VariableExpression("a")),
                                                                                                    ">"
                                                                                            ),
                                                                                            new ValueExpression(new IntValue(100)),
                                                                                            new ValueExpression(new IntValue(200))
                                                                                    ),
                                                                                    new PrintStatement(new VariableExpression("v"))
                                                                            )
                                                                    )
                                                            )
                                                    )
                                            )
                                    )
                            )
                    )
            )
    );

    IStatement ex13 = new CompStatement(
            new VarDeclStatement("a", new RefType(new IntType())),
            new CompStatement(
                    new HeapAllocationStatement("a", new ValueExpression(new IntValue(20))),
                    new CompStatement(
                            new ForStatement(
                                    "v",
                                    new ValueExpression(new IntValue(0)),
                                    new ValueExpression(new IntValue(3)),
                                    new ArithmeticalExpression(
                                            new VariableExpression("v"),
                                            new ValueExpression(new IntValue(1)),
                                            PLUS
                                    ),
                                    new ForkStatement(
                                            new CompStatement(
                                                    new PrintStatement(new VariableExpression("v")),
                                                    new AssignStatement(
                                                            "v",
                                                            new ArithmeticalExpression(
                                                                    new VariableExpression("v"),
                                                                    new HeapReadingExpression(new VariableExpression("a")),
                                                                    MULTIPLY
                                                            )
                                                    )
                                            )
                                    )
                            ),
                            new PrintStatement(
                                    new HeapReadingExpression(new VariableExpression("a"))
                            )
                    )
            )
    );


    /*IStatement ex14 = new CompStatement(
            new VarDeclStatement("v", new IntType()),
            new CompStatement(
                    new AssignStatement("v", new ValueExpression(new IntValue(0))), // v = 0
                    new CompStatement(
                            new WhileStatement(
                                    new RelationalExpression(
                                            new VariableExpression("v"),
                                            new ValueExpression(new IntValue(3)),
                                            "<"), // while(v < 3)
                                    new CompStatement(
                                            new ForkStatement( // Fork the child process
                                                    new CompStatement(
                                                            new PrintStatement(new VariableExpression("v")), // print(v)
                                                            new AssignStatement(
                                                                    "v",
                                                                    new ArithmeticalExpression(
                                                                            new VariableExpression("v"),
                                                                            new ValueExpression(new IntValue(1)), PLUS) // v = v + 1
                                                            )
                                                    )
                                            ),
                                            new AssignStatement(
                                                    "v",
                                                    new ArithmeticalExpression(
                                                            new VariableExpression("v"),
                                                            new ValueExpression(new IntValue(1)), PLUS) // v = v + 1
                                            )
                                    )
                            ),
                            new CompStatement(
                                    new SleepStatement(new ValueExpression(new IntValue(5))),
                                    new PrintStatement( // print(v * 10)
                                            new ArithmeticalExpression(
                                                    new VariableExpression("v"),
                                                    new ValueExpression(new IntValue(10)),
                                                    MULTIPLY)
                                    )
                            )
                    )
            )
    );


     */
    IStatement ex14 = new CompStatement(
            new VarDeclStatement("v", new IntType()),
            new CompStatement(
                    new AssignStatement("v", new ValueExpression(new IntValue(20))),
                    new CompStatement(
                            new SleepStatement(new ValueExpression(new IntValue(10))),
                            new PrintStatement(new ArithmeticalExpression( new VariableExpression("v"), new ValueExpression(new IntValue(10)), MULTIPLY)))));



    IStatement ex15 = new CompStatement(
            new VarDeclStatement("v1", new RefType(new IntType())),
            new CompStatement(
                    new VarDeclStatement("cnt", new IntType()),
                    new CompStatement(
                            new HeapAllocationStatement("v1", new ValueExpression(new IntValue(1))),
                            new CompStatement(
                                    new CreateSemStatement("cnt", new HeapReadingExpression(new VariableExpression("v1"))),
                                    new CompStatement(
                                            new ForkStatement(
                                                    new CompStatement(
                                                            new AcquireStatement("cnt"),
                                                            new CompStatement(
                                                                    new HeapWritingStatement(
                                                                            "v1",
                                                                            new ArithmeticalExpression(

                                                                                    new HeapReadingExpression(new VariableExpression("v1")),
                                                                                    new ValueExpression(new IntValue(10)),MULTIPLY
                                                                            )
                                                                    ),
                                                                    new CompStatement(
                                                                            new PrintStatement(new HeapReadingExpression(new VariableExpression("v1"))),
                                                                            new ReleaseStatement("cnt")
                                                                    )
                                                            )
                                                    )
                                            ),
                                            new CompStatement(
                                                    new ForkStatement(
                                                            new CompStatement(
                                                                    new AcquireStatement("cnt"),
                                                                    new CompStatement(
                                                                            new HeapWritingStatement(
                                                                                    "v1",
                                                                                    new ArithmeticalExpression(
                                                                                            new HeapReadingExpression(new VariableExpression("v1")),
                                                                                            new ValueExpression(new IntValue(10)),MULTIPLY
                                                                                    )
                                                                            ),
                                                                            new CompStatement(
                                                                                    new HeapWritingStatement(
                                                                                            "v1",
                                                                                            new ArithmeticalExpression(
                                                                                                    new HeapReadingExpression(new VariableExpression("v1")),
                                                                                                    new ValueExpression(new IntValue(2)), MULTIPLY
                                                                                            )
                                                                                    ),
                                                                                    new CompStatement(
                                                                                            new PrintStatement(new HeapReadingExpression(new VariableExpression("v1"))),
                                                                                            new ReleaseStatement("cnt")
                                                                                    )
                                                                            )
                                                                    )
                                                            )
                                                    ),
                                                    new CompStatement(
                                                            new AcquireStatement("cnt"),
                                                            new CompStatement(
                                                                    new PrintStatement(
                                                                            new ArithmeticalExpression(

                                                                                    new HeapReadingExpression(new VariableExpression("v1")),
                                                                                    new ValueExpression(new IntValue(1)), MINUS
                                                                            )
                                                                    ),
                                                                    new ReleaseStatement("cnt")
                                                            )
                                                    )
                                            )
                                    )
                            )
                    )
            )
    );

    IStatement ex16 = new CompStatement(
            new VarDeclStatement("v1", new RefType(new IntType())),
            new CompStatement(
                    new VarDeclStatement("v2", new RefType(new IntType())),
                    new CompStatement(
                            new VarDeclStatement("v3", new RefType(new IntType())),
                            new CompStatement(
                                    new VarDeclStatement("cnt", new IntType()),
                                    new CompStatement(
                                            new HeapAllocationStatement("v1", new ValueExpression(new IntValue(2))),
                                            new CompStatement(
                                                    new HeapAllocationStatement("v2", new ValueExpression(new IntValue(3))),
                                                    new CompStatement(
                                                            new HeapAllocationStatement("v3", new ValueExpression(new IntValue(4))),
                                                            new CompStatement(
                                                                    new NewLatchStatement("cnt", new HeapReadingExpression(new VariableExpression("v2"))),
                                                                    new CompStatement(
                                                                            new ForkStatement(
                                                                                    new CompStatement(
                                                                                            new HeapWritingStatement(
                                                                                                    "v1",
                                                                                                    new ArithmeticalExpression(
                                                                                                            new HeapReadingExpression(new VariableExpression("v1")),
                                                                                                            new ValueExpression(new IntValue(10)),
                                                                                                            MULTIPLY
                                                                                                    )
                                                                                            ),
                                                                                            new CompStatement(
                                                                                                    new PrintStatement(new HeapReadingExpression(new VariableExpression("v1"))),
                                                                                                    new CountDownStatement("cnt")
                                                                                            )
                                                                                    )
                                                                            ),
                                                                            new CompStatement(
                                                                                    new ForkStatement(
                                                                                            new CompStatement(
                                                                                                    new HeapWritingStatement(
                                                                                                            "v2",
                                                                                                            new ArithmeticalExpression(
                                                                                                                    new HeapReadingExpression(new VariableExpression("v2")),
                                                                                                                    new ValueExpression(new IntValue(10)),
                                                                                                                    MULTIPLY
                                                                                                            )
                                                                                                    ),
                                                                                                    new CompStatement(
                                                                                                            new PrintStatement(new HeapReadingExpression(new VariableExpression("v2"))),
                                                                                                            new CountDownStatement("cnt")
                                                                                                    )
                                                                                            )
                                                                                    ),
                                                                                    new CompStatement(
                                                                                            new ForkStatement(
                                                                                                    new CompStatement(
                                                                                                            new HeapWritingStatement(
                                                                                                                    "v3",
                                                                                                                    new ArithmeticalExpression(
                                                                                                                            new HeapReadingExpression(new VariableExpression("v3")),
                                                                                                                            new ValueExpression(new IntValue(10)),
                                                                                                                            MULTIPLY
                                                                                                                    )
                                                                                                            ),
                                                                                                            new CompStatement(
                                                                                                                    new PrintStatement(new HeapReadingExpression(new VariableExpression("v3"))),
                                                                                                                    new CountDownStatement("cnt")
                                                                                                            )
                                                                                                    )
                                                                                            ),
                                                                                            new CompStatement(
                                                                                                    new AwaitStatement("cnt"),
                                                                                                    new CompStatement(
                                                                                                            new PrintStatement(new ValueExpression(new IntValue(100))),
                                                                                                            new CompStatement(
                                                                                                                    new CountDownStatement("cnt"),
                                                                                                                    new PrintStatement(new ValueExpression(new IntValue(100)))
                                                                                                            )
                                                                                                    )
                                                                                            )
                                                                                    )
                                                                            )
                                                                    )
                                                            )
                                                    )
                                            )
                                    )
                            )
                    )
            )
    );


    IStatement ex17 = new CompStatement(
            new VarDeclStatement("v1", new RefType(new IntType())),
            new CompStatement(
                    new VarDeclStatement("v2", new RefType(new IntType())),
                    new CompStatement(
                            new VarDeclStatement("x", new IntType()),
                            new CompStatement(
                                    new VarDeclStatement("q", new IntType()),
                                    new CompStatement(
                                            new HeapAllocationStatement("v1", new ValueExpression(new IntValue(20))),
                                            new CompStatement(
                                                    new HeapAllocationStatement("v2", new ValueExpression(new IntValue(30))),
                                                    new CompStatement(
                                                            new NewLockStatement("x"),
                                                            new CompStatement(
                                                                    new ForkStatement(
                                                                            new CompStatement(
                                                                                    new ForkStatement(
                                                                                            new CompStatement(
                                                                                                    new LockStatement("x"),
                                                                                                    new CompStatement(
                                                                                                            new HeapWritingStatement(
                                                                                                                    "v1",
                                                                                                                    new ArithmeticalExpression(
                                                                                                                            new HeapReadingExpression(new VariableExpression("v1")),
                                                                                                                            new ValueExpression(new IntValue(1)),
                                                                                                                            MINUS
                                                                                                                    )
                                                                                                            ),
                                                                                                            new UnlockStatement("x")
                                                                                                    )
                                                                                            )
                                                                                    ),
                                                                                    new CompStatement(
                                                                                            new LockStatement("x"),
                                                                                            new CompStatement(
                                                                                                    new HeapWritingStatement(
                                                                                                            "v1",
                                                                                                            new ArithmeticalExpression(
                                                                                                                    new HeapReadingExpression(new VariableExpression("v1")),
                                                                                                                    new ValueExpression(new IntValue(10)),
                                                                                                                    MULTIPLY
                                                                                                            )
                                                                                                    ),
                                                                                                    new UnlockStatement("x")
                                                                                            )
                                                                                    )
                                                                            )
                                                                    ),
                                                                    new CompStatement(
                                                                            new NewLockStatement("q"),
                                                                            new CompStatement(
                                                                                    new ForkStatement(
                                                                                            new CompStatement(
                                                                                                    new ForkStatement(
                                                                                                            new CompStatement(
                                                                                                                    new LockStatement("q"),
                                                                                                                    new CompStatement(
                                                                                                                            new HeapWritingStatement(
                                                                                                                                    "v2",
                                                                                                                                    new ArithmeticalExpression(
                                                                                                                                            new HeapReadingExpression(new VariableExpression("v2")),
                                                                                                                                            new ValueExpression(new IntValue(5)),
                                                                                                                                            PLUS
                                                                                                                                    )
                                                                                                                            ),
                                                                                                                            new UnlockStatement("q")
                                                                                                                    )
                                                                                                            )
                                                                                                    ),
                                                                                                    new CompStatement(
                                                                                                            new LockStatement("q"),
                                                                                                            new CompStatement(
                                                                                                                    new HeapWritingStatement(
                                                                                                                            "v2",
                                                                                                                            new ArithmeticalExpression(
                                                                                                                                    new HeapReadingExpression(new VariableExpression("v2")),
                                                                                                                                    new ValueExpression(new IntValue(10)),
                                                                                                                                    MULTIPLY
                                                                                                                            )
                                                                                                                    ),
                                                                                                                    new UnlockStatement("q")
                                                                                                            )
                                                                                                    )
                                                                                            )
                                                                                    ),
                                                                                    new CompStatement(
                                                                                            new NopStatement(),
                                                                                            new CompStatement(
                                                                                                    new NopStatement(),
                                                                                                    new CompStatement(
                                                                                                            new NopStatement(),
                                                                                                            new CompStatement(
                                                                                                                    new NopStatement(),
                                                                                                                    new CompStatement(
                                                                                                                            new LockStatement("x"),
                                                                                                                            new CompStatement(
                                                                                                                                    new PrintStatement(new HeapReadingExpression(new VariableExpression("v1"))),
                                                                                                                                    new CompStatement(
                                                                                                                                            new UnlockStatement("x"),
                                                                                                                                            new CompStatement(
                                                                                                                                                    new LockStatement("q"),
                                                                                                                                                    new CompStatement(
                                                                                                                                                            new PrintStatement(new HeapReadingExpression(new VariableExpression("v2"))),
                                                                                                                                                            new UnlockStatement("q")
                                                                                                                                                    )
                                                                                                                                            )
                                                                                                                                    )
                                                                                                                            )
                                                                                                                    )
                                                                                                            )
                                                                                                    )
                                                                                            )
                                                                                    )
                                                                            )
                                                                    )
                                                            )
                                                    )
                                            )
                                    )
                            )
                    )
            )
    );


    public IStatement[] exampleList(){
        return new IStatement[]{ex1,ex2,ex3,ex4,ex5,ex6,ex7,ex8,ex9,ex10,ex11,ex12, ex13, ex14, ex15, ex16, ex17};
    }




}
