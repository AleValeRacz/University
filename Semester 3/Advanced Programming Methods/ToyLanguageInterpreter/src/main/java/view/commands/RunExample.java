package view.commands;

import controller.Controller;

public class RunExample extends Command{

    private Controller cont;
    public RunExample(String key, String desc, Controller cont){
        super(key,desc);
        this.cont = cont;
    }

    @Override
    public void execute()
    {
        try {
            this.cont.allStep();
        }
        catch(Exception e){
                System.out.println(e.getMessage());
            }

    }
}
