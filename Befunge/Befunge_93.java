import java.util.*;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.BufferedReader;
import java.io.IOException;

public class Befunge_93 implements Befunge {

	public void run() {

        Command currentCommand;
        Character currentSymbol = table[verticalIndex][horyzontalIndex];

        int i = 0;
        while (isWorking){//&& i< 100*100*100) {
          //  System.out.printf("CURRENT SYMBOL AND HIS CODE %c %d %n",currentSymbol,(int)currentSymbol);
            if (currentSymbol ==' ')
                bf93env.move(currentDir);
            else {
                if (loadedCommands.containsKey(currentSymbol))
                    currentCommand = loadedCommands.get(currentSymbol);
                else {
                    try {
                        currentCommand = Factory.getInstance().getCommand(currentSymbol.toString());
                    } catch (ClassNotFoundException exc) {
                        if ((int)currentSymbol!=0)
                            System.out.println(exc.getMessage());
                        return;
                    }
                    loadedCommands.put(currentSymbol, currentCommand);
                }
                currentCommand.execute(bf93env);
            }
            currentSymbol = table[verticalIndex][horyzontalIndex];
            i++;
        }
    }
	public void setupTable() throws IOException {
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		String commandLine;
		System.out.println("BEFUNGE-93 CONSOLE INPUT MODE; HERE THE RULES:");
		System.out.printf("1)MAXIMUM SYMBOLS IN ONE LINE - %d%n",height);
		System.out.printf("2)MAXIMUM LINES - %d ",width);
		System.out.println("(all lines after this limit will be ignored)");
		System.out.println("3)TO STOP INPUT TYPE 'END' without quotes IN NEW(!!!) LINE ");
		for (int i = 0 ; i < width;i++) {
			commandLine = reader.readLine();
			if (commandLine.equals("END"))
				break;
			if (commandLine.length() > height)
				throw new IOException ("Dude,read rulez - that line was too long!");
			System.arraycopy(commandLine.toCharArray(),0,table[i],0,commandLine.length());
		}
	}
	Befunge_93() {
		bf93env = new ExecutionContext();
		loadedCommands  = new HashMap <>();
		Symbols = new Stack<> ();
		table =  new char[width][height];
		for(int i =0; i< width;i++)
			Arrays.fill(table[i],' ');
	}
	private BefungeEnvironment bf93env;
	private HashMap<Character,Command> loadedCommands; 
	private Direction currentDir = Direction.RIGHT;	
	private Stack<Integer> Symbols;
	private int horyzontalIndex = 0;
	private int verticalIndex = 0;
	private final int width = 25;
	private final int height = 80;
	private char table[][];
	private boolean isWorking = true;

	class ExecutionContext implements BefungeEnvironment {
	    @Override public void move (Direction dir) {
		    currentDir = dir;
		 /*   System.out.printf("MY COORDINATS: %d %d %n",horyzontalIndex,verticalIndex);
		    if (horyzontalIndex==15& verticalIndex==1) {
                System.out.println((int) table[verticalIndex][horyzontalIndex]);
                System.out.println((int)' ');
            }
            if (table[horyzontalIndex][verticalIndex]==' ')
                System.out.println("BIG ENOUGH AAAAAAAAAAAAA    ");*/
			switch (dir) {
                case UP:
                    verticalIndex= (verticalIndex-1+ width) % width;
                    break;
                case DOWN:
                    verticalIndex= (verticalIndex+1+ width) % width;
                    break;
                case LEFT:
                    horyzontalIndex= (horyzontalIndex-1+ height) % height;
                    break;
                case RIGHT:
                    horyzontalIndex= (horyzontalIndex+1+ height) % height;
                    break;
                case RANDOM:
                    Random yield = new Random(System.currentTimeMillis());
                    int rand = yield.nextInt(3);
                    move(Direction.values()[rand]);

            }

		}

        @Override public void ifMove(Direction dir) {
		    int check = getTop();
            currentDir =  (check==0) ? dir.opposite() : dir;
		    move(currentDir);
        }

        @Override public void push(){
		    int x=0;
		    if(!Symbols.empty()) {
                x = Symbols.peek();
                Symbols.push(x);
            }
            move(currentDir);

        }

        @Override public void skip(){
	        move(currentDir);
	        move(currentDir);
	    }

        @Override public void endProgram(){
	        isWorking=!isWorking;
	    }

        @Override public void getNumber() {
	        Symbols.push(Character.digit(table[verticalIndex][horyzontalIndex],10));
	        move(currentDir);
        }

        @Override public void swap () {
            int x = getTop(), y = getTop();
                Symbols.push(x);
                Symbols.push(y);
                move(currentDir);
        }

        @Override public void deleteTop(){
	            getTop();
                move(currentDir);
        }

        @Override public void putOnStack() {
            int x = getTop(), y = getTop();
            char value = (char)getTop();
            table[x][y] = value;
            move(currentDir);
        }

        @Override public void getFromStack(){
	        int x=getTop(),y=getTop();
	            Symbols.push((int)table[(x+width)%width][(y+height)%height]);
	            move(currentDir);
        }

        @Override public void getStringOfASCI(){
	        do {
	            move(currentDir);
	            if (table[verticalIndex][horyzontalIndex]!='"')
	                Symbols.push((int)table[verticalIndex][horyzontalIndex]);
            }while (table[verticalIndex][horyzontalIndex]!='"');
	        move(currentDir);
        }

        @Override public void arithOperations(Operations op) {
            int x = getTop();
            int y = getTop();
            switch (op) {
                case DIV:
                    if (x != 0)
                        Symbols.push(y / x);
                    else
                        Symbols.push(0);
                    break;
                case MUL:
                    Symbols.push(x * y);
                    break;
                case SUB:
                    Symbols.push(y - x);
                    break;
                case SUM:
                    Symbols.push(x + y);
                    break;
                case MOD:
                    Symbols.push(y % x);
                    break;
            }
            move(currentDir);
        }


        @Override public void stackRevert() {
            int x =getTop();
                if (x == 0)
                    Symbols.push(1);
                else
                    Symbols.push(0);
                move(currentDir);
        }

        @Override public void stackMoreThan() {
	        int x,y;
	        try {
	            x = Symbols.pop();
            }
            catch (EmptyStackException exc) {
	            Symbols.push(0);
	            move(currentDir);
	            return;
            }
            try {
	            y = Symbols.pop();
            }
            catch (EmptyStackException exc) {
                Symbols.push(0);
                move(currentDir);
                return;
            }
            if (x < y) {
                Symbols.push(x);
                Symbols.push(y);
                Symbols.push(1);
            } else {
                Symbols.push(x);
                Symbols.push(y);
                Symbols.push(0);
            }
            move(currentDir);
        }


        @Override public void askForNumber(){
	        System.out.println("Type a number!");
	        Scanner in = new Scanner(System.in);
	        int x;
	        try {
                x = in.nextInt();
            }
            catch (InputMismatchException exc) {
	            System.out.println("I SAID TYPE A NUMBER,DUMB USER!!!");
	            isWorking=!isWorking;
	            return;
            }
            Symbols.push(x);
	        move(currentDir);
        }

        @Override public void askForSymbol(){
	        System.out.println("Type a symbol!");
            Scanner in = new Scanner(System.in);
            char x = in.next().charAt(0);
            Symbols.push((int)(x));
            move(currentDir);
        }

        @Override public void printTopAsInt() {
            int x = getTop();
            System.out.printf("%d ", x);
            move(currentDir);

        }

        @Override public void printTopAsSymbol(){
	        int x;
	        try {
	            x = Symbols.pop();
            }
            catch ( EmptyStackException exc) {
	           // System.out.println(0);
	            move(currentDir);
	            return;
            }
            System.out.printf("%c",x);
	        move(currentDir);
        }
        private int getTop() {
	        int x = 0;
	        try {
	            x = Symbols.pop();
            }
            catch (EmptyStackException exc) {
	          //  Symbols.push(0);
            }
            return x;
        }
	}
	
}
