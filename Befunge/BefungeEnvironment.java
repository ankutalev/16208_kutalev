public interface BefungeEnvironment {
	void move(Direction dir);
	void ifMove(Direction dir);
	void push();
	void skip();
	void endProgram();
	void getNumber();
	void swap ();
	void deleteTop();
	void putOnStack();
	void getFromStack();
	void getStringOfASCI();
	void arithOperations(Operations op);
	void stackRevert();
	void stackMoreThan();
	void askForNumber();
	void askForSymbol();
	void printTopAsInt();
	void printTopAsSymbol();
}
