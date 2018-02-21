public enum Direction {
	RIGHT,UP,DOWN,LEFT,RANDOM;
	public Direction opposite() {
		switch (this) {
			case RIGHT:
				return LEFT;
			case LEFT:
				return RIGHT;
			case DOWN:
				return  UP;
			case UP:
				return DOWN;
			case RANDOM:
				return RIGHT;
		}
		return DOWN;
	}
}
