import java.util.Comparator;
import java.util.concurrent.ThreadLocalRandom;

public class UnitSpeedComparator implements Comparator<Unit> {
    @Override
    public int compare(Unit o1, Unit o2) {
        int a = o2.getSpeed() + ThreadLocalRandom.current().nextInt(1,7) - o1.getSpeed() -
                ThreadLocalRandom.current().nextInt(1,7);
        //System.out.println(a);
        return a;
    }
}
